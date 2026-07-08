#include "stm32gxxx_i2c1.h"

/***
static i2c1_par par_setup =
{
    .timing            = 0,
    .own_address       = 0,
    .addressing_mode   = I2C1_ADDR_7BIT,
    .analog_filter     = I2C1_FILTER_ENABLE,
    .digital_filter    = 0,

    .status            = 0
};

static inline I2C_TypeDef *_i2c(void)
{
    return dev()->comm->i2c1;
}

static inline i2c1_par *_par(void)
{
    return i2c1()->par;
}
static uint8_t _busy(void)
{
    return get_field_value(
        _i2c()->ISR,
        I2C_ISR_BUSY_Msk,
        I2C_ISR_BUSY_Pos
    );
}
static uint8_t _enabled(void)
{
    return get_block_value(
        _i2c()->CR1,
        1,
        I2C_CR1_PE_Pos
    );
}
static void _enable(void)
{
    set_reg(&dev()->comm->i2c1->CR1,
            I2C_CR1_PE);

    i2c1()->par->status |= (1UL << 1);
}

static void _disable(void)
{
    clear_reg(&dev()->comm->i2c1->CR1,
              I2C_CR1_PE);

    i2c1()->par->status &= ~(1UL << 1);
}

static const i2c1_memory memory_setup =
{
    .write = NULL,
    .read  = NULL
};

static const i2c1_slave slave_setup =
{
    .enable = NULL,
    .disable = NULL,
    .listen = NULL
};

static const i2c1_dma dma_setup =
{
    .write = NULL,
    .read  = NULL
};

***/
#include "stm32gxxx_i2c1.h"

/* --- Private Variables --- */
static i2c1_par i2c1_internal_par = {0};
static i2c1_irq i2c1_internal_irq = {0};

/* --- Private Function Forward Declarations --- */
static uint8_t get_busy(void);
static uint8_t get_ready(void);
static uint8_t get_enabled(void);
static uint8_t get_error(void);

static void set_timing(uint32_t timing);
static void set_own_address(uint16_t address);
static void set_addressing_mode(uint8_t mode);
static void set_analog_filter(uint8_t state);
static void set_digital_filter(uint8_t filter_value);

/* Sub-interface: Common */
static void common_config(const i2c1_par *par);
static void common_init(void);
static void common_enable(void);
static void common_disable(void);
static void common_reset(void);
static void common_irq_event(void);
static void common_irq_error(void);

/* Sub-interface: Master */
static int8_t master_write_byte(uint16_t address, uint8_t data);
static int8_t master_read_byte(uint16_t address, uint8_t *data);
static int8_t master_write(uint16_t address, const uint8_t *buffer, uint16_t length);
static int8_t master_read(uint16_t address, uint8_t *buffer, uint16_t length);
static int8_t master_probe(uint16_t address);
static int8_t master_scan(uint8_t *list, uint16_t *count);

/* Sub-interface: Memory */
static int8_t memory_write(uint16_t address, uint16_t reg, const uint8_t *buffer, uint16_t length);
static int8_t memory_read(uint16_t address, uint16_t reg, uint8_t *buffer, uint16_t length);

/* Sub-interface: Slave */
static void slave_enable(void);
static void slave_disable(void);
static void slave_listen(void);

/* Sub-interface: DMA */
static int8_t dma_write(uint16_t address, const uint8_t *buffer, uint16_t length);
static int8_t dma_read(uint16_t address, uint8_t *buffer, uint16_t length);

/* --- Object Interface Structures --- */
static i2c1_get_par i2c1_get = {
    .busy    = get_busy,
    .ready   = get_ready,
    .enabled = get_enabled,
    .error   = get_error
};

static i2c1_set_par i2c1_set = {
    .timing          = set_timing,
    .own_address     = set_own_address,
    .addressing_mode = set_addressing_mode,
    .analog_filter   = set_analog_filter,
    .digital_filter  = set_digital_filter
};

static const i2c1_common i2c1_execute_common = {
    .config    = common_config,
    .init      = common_init,
    .enable    = common_enable,
    .disable   = common_disable,
    .reset     = common_reset,
    .irq_event = common_irq_event,
    .irq_error = common_irq_error
};

static const i2c1_master i2c1_execute_master = {
    .write_byte = master_write_byte,
    .read_byte  = master_read_byte,
    .write      = master_write,
    .read       = master_read,
    .probe      = master_probe,
    .scan       = master_scan
};

static const i2c1_memory i2c1_execute_memory = {
    .write = memory_write,
    .read  = memory_read
};

static const i2c1_slave i2c1_execute_slave = {
    .enable  = slave_enable,
    .disable = slave_disable,
    .listen  = slave_listen
};

static const i2c1_dma i2c1_execute_dma = {
    .write = dma_write,
    .read  = dma_read
};

static const i2c1_run i2c1_execute = {
    .common = &i2c1_execute_common,
    .master = &i2c1_execute_master,
    .memory = &i2c1_execute_memory,
    .slave  = &i2c1_execute_slave,
    .dma    = &i2c1_execute_dma
};

static i2c1_handler i2c1_obj = {
    .par     = &i2c1_internal_par,
    .get_par = &i2c1_get,
    .set_par = &i2c1_set,
    .irq     = &i2c1_internal_irq,
    .run     = &i2c1_execute
};

/* --- Public Interface Accessor --- */
i2c1_handler *i2c1(void) 
{
    return &i2c1_obj;
}

/* --- GET Functions Implementation --- */
static uint8_t get_busy(void) 
{
    return (I2C1->ISR & I2C_ISR_BUSY) ? 1U : 0U;
}

static uint8_t get_ready(void) 
{
    return ((I2C1->CR1 & I2C_CR1_PE) && !(I2C1->ISR & I2C_ISR_BUSY)) ? 1U : 0U;
}

static uint8_t get_enabled(void) 
{
    return (I2C1->CR1 & I2C_CR1_PE) ? 1U : 0U;
}

static uint8_t get_error(void) 
{
    uint32_t errors = (I2C_ISR_BERR | I2C_ISR_ARLO | I2C_ISR_OVR | I2C_ISR_PECERR | I2C_ISR_TIMEOUT);
    return (I2C1->ISR & errors) ? 1U : 0U;
}

/* --- SET Functions Implementation --- */
static void set_timing(uint32_t timing) 
{
    i2c1_internal_par.timing = timing;
    if (!get_enabled()) 
    {
        I2C1->TIMINGR = timing;
    }
}

static void set_own_address(uint16_t address) 
{
    i2c1_internal_par.own_address = address;
    if (!get_enabled()) 
    {
        I2C1->OAR1 &= ~I2C_OAR1_OA1EN;
        if (i2c1_internal_par.addressing_mode == I2C1_ADDR_10BIT) 
        {
            I2C1->OAR1 = I2C_OAR1_OA1EN | I2C_OAR1_OA1MODE | (address & 0x3FFU);
        } 
        else 
        {
            I2C1->OAR1 = I2C_OAR1_OA1EN | ((address & 0x7FU) << 1);
        }
    }
}

static void set_addressing_mode(uint8_t mode) 
{
    i2c1_internal_par.addressing_mode = mode;
}

static void set_analog_filter(uint8_t state) 
{
    i2c1_internal_par.analog_filter = state;
    if (!get_enabled()) 
    {
        if (state == I2C1_FILTER_DISABLE) 
        {
            I2C1->CR1 |= I2C_CR1_ANFOFF;
        } 
        else 
        {
            I2C1->CR1 &= ~I2C_CR1_ANFOFF;
        }
    }
}

static void set_digital_filter(uint8_t filter_value) 
{
    i2c1_internal_par.digital_filter = filter_value;
    if (!get_enabled()) 
    {
        I2C1->CR1 &= ~I2C_CR1_DNF;
        I2C1->CR1 |= ((uint32_t)filter_value & 0x0FU) << I2C_CR1_DNF_Pos;
    }
}

/* --- COMMON Execution Functions --- */
static void common_config(const i2c1_par *par) 
{
    if (par == NULL) return;
    common_disable();
    set_addressing_mode(par->addressing_mode);
    set_timing(par->timing);
    set_analog_filter(par->analog_filter);
    set_digital_filter(par->digital_filter);
    set_own_address(par->own_address);
}

static void common_init(void) 
{
    RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN;
    __DSB();
    common_config(&i2c1_internal_par);
}

static void common_enable(void) 
{
    I2C1->CR1 |= I2C_CR1_PE;
}

static void common_disable(void) 
{
    I2C1->CR1 &= ~I2C_CR1_PE;
}

static void common_reset(void) 
{
    RCC->APB1RSTR1 |= RCC_APB1RSTR1_I2C1RST;
    __DSB();
    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_I2C1RST;
    common_init();
}

static void common_irq_event(void) 
{
    uint32_t isr = I2C1->ISR;
    
    if ((isr & I2C_ISR_TC) && (I2C1->CR1 & I2C_CR1_TCIE)) 
    {
        if (i2c1_internal_irq.tx_complete) i2c1_internal_irq.tx_complete();
    }
    if ((isr & I2C_ISR_RXNE) && (I2C1->CR1 & I2C_CR1_RXIE)) 
    {
        if (i2c1_internal_irq.rx_complete) i2c1_internal_irq.rx_complete();
    }
    if ((isr & I2C_ISR_ADDR) && (I2C1->CR1 & I2C_CR1_ADDRIE)) 
    {
        I2C1->ICR = I2C_ICR_ADDRCF;
        if (i2c1_internal_irq.listen) i2c1_internal_irq.listen();
    }
}

static void common_irq_error(void) 
{
    uint32_t isr = I2C1->ISR;
    i2c1_internal_par.status = isr;
    
    if (isr & (I2C_ISR_BERR | I2C_ISR_ARLO | I2C_ISR_OVR | I2C_ISR_TIMEOUT)) 
    {
        I2C1->ICR = (I2C_ICR_BERRCF | I2C_ICR_ARLOCF | I2C_ICR_OVRCF | I2C_ICR_TIMEOUTCF);
        if (i2c1_internal_irq.error) i2c1_internal_irq.error();
    }
}

/* --- MASTER Execution Functions --- */
static int8_t master_write_byte(uint16_t address, uint8_t data) 
{
    return master_write(address, &data, 1);
}

static int8_t master_read_byte(uint16_t address, uint8_t *data) 
{
    return master_read(address, data, 1);
}

static int8_t master_write(uint16_t address, const uint8_t *buffer, uint16_t length) 
{
    if (buffer == NULL || length == 0) return -1;
    
    uint32_t timeout = 100000U;
    while (I2C1->ISR & I2C_ISR_BUSY) 
    {
        if (--timeout == 0) return -2;
    }

    uint32_t cr2 = I2C1->CR2 & ~((0xFFU << 16) | I2C_CR2_SADD | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP);
    cr2 |= ((uint32_t)length << 16);
    cr2 |= (address & 0x7FU) << 1; 
    cr2 |= I2C_CR2_AUTOEND;
    cr2 |= I2C_CR2_START;
    I2C1->CR2 = cr2;

    for (uint16_t i = 0; i < length; i++) 
    {
        timeout = 100000U;
        while (!(I2C1->ISR & I2C_ISR_TXIS)) 
        {
            if (I2C1->ISR & I2C_ISR_NACKF) 
            {
                I2C1->ICR = I2C_ICR_NACKCF;
                return -3;
            }
            if (--timeout == 0) return -2;
        }
        I2C1->TXDR = buffer[i];
    }

    timeout = 100000U;
    while (!(I2C1->ISR & I2C_ISR_STOPF)) 
    {
        if (--timeout == 0) return -2;
    }
    I2C1->ICR = I2C_ICR_STOPCF;
    return 0;
}

static int8_t master_read(uint16_t address, uint8_t *buffer, uint16_t length) 
{
    if (buffer == NULL || length == 0) return -1;

    uint32_t timeout = 100000U;
    while (I2C1->ISR & I2C_ISR_BUSY) 
    {
        if (--timeout == 0) return -2;
    }

    uint32_t cr2 = I2C1->CR2 & ~((0xFFU << 16) | I2C_CR2_SADD | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP);
    cr2 |= ((uint32_t)length << 16);
    cr2 |= (address & 0x7FU) << 1;
    cr2 |= I2C_CR2_RD_WRN;
    cr2 |= I2C_CR2_AUTOEND;
    cr2 |= I2C_CR2_START;
    I2C1->CR2 = cr2;

    for (uint16_t i = 0; i < length; i++) 
    {
        timeout = 100000U;
        while (!(I2C1->ISR & I2C_ISR_RXNE)) 
        {
            if (I2C1->ISR & I2C_ISR_NACKF) 
            {
                I2C1->ICR = I2C_ICR_NACKCF;
                return -3;
            }
            if (--timeout == 0) return -2;
        }
        buffer[i] = (uint8_t)(I2C1->RXDR);
    }

    timeout = 100000U;
    while (!(I2C1->ISR & I2C_ISR_STOPF)) 
    {
        if (--timeout == 0) return -2;
    }
    I2C1->ICR = I2C_ICR_STOPCF;
    return 0;
}

static int8_t master_probe(uint16_t address) 
{
    uint32_t timeout = 100000U;
    while (I2C1->ISR & I2C_ISR_BUSY) 
    {
        if (--timeout == 0) return -2;
    }

    uint32_t cr2 = I2C1->CR2 & ~((0xFFU << 16) | I2C_CR2_SADD | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP);
    cr2 |= (1U << 16); 
    cr2 |= (address & 0x7FU) << 1;
    cr2 |= I2C_CR2_AUTOEND;
    cr2 |= I2C_CR2_START;
    I2C1->CR2 = cr2;

    timeout = 100000U;
	while (!(I2C1->ISR & (I2C_ISR_STOPF | I2C_ISR_NACKF))){
		if (--timeout == 0) 
		return -2;
		}
		if (I2C1->ISR & I2C_ISR_NACKF){
			I2C1->ICR = I2C_ICR_NACKCF;I2C1->ICR = I2C_ICR_STOPCF;
			return -3;
		}
		I2C1->ICR = I2C_ICR_STOPCF;
		return 0;
	}
	static int8_t master_scan(uint8_t *list, uint16_t *count){
		if (list == NULL || count == NULL) 
		return -1;
		uint16_t found_devices = 0;
		for (uint8_t addr = 1; addr < 128; addr++){
			if (master_probe(addr) == 0){
				list[found_devices] = addr;
				found_devices++;
			}
			for(volatile uint32_t i=0; i<1000; i++);
		}
		*count = found_devices;
		return 0;
	}
	/* --- MEMORY Execution Functions (Repeated Start / Register Read-Write) --- */
	static int8_t memory_write(uint16_t address, uint16_t reg, const uint8_t *buffer, uint16_t length){
		if (buffer == NULL || length == 0) 
			return -1;
		uint32_t timeout = 100000U;
		while (I2C1->ISR & I2C_ISR_BUSY) { 
			if (--timeout == 0) 
				return -2; 
		}
		/* For simplicity, this assumes a 1-byte register address. Alter length to 2 for 16-bit registers */
		uint32_t cr2 = I2C1->CR2 & ~((0xFFU << 16) | I2C_CR2_SADD | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP);
		cr2 |= (((uint32_t)length + 1U) << 16);
		cr2 |= (address & 0x7FU) << 1;
		cr2 |= I2C_CR2_AUTOEND;
		cr2 |= I2C_CR2_START;
		I2C1->CR2 = cr2;
		/* Write Register Pointer */
		timeout = 100000U;
		while (!(I2C1->ISR & I2C_ISR_TXIS)) { 
			if (--timeout == 0) 
			return -2;
		}
		I2C1->TXDR = (uint8_t)(reg & 0xFFU);
		/* Write Buffer */
		for (uint16_t i = 0; i < length; i++){
			timeout = 100000U;
			while (!(I2C1->ISR & I2C_ISR_TXIS)){
				if (I2C1->ISR & I2C_ISR_NACKF) { 
					I2C1->ICR = I2C_ICR_NACKCF; 
					return -3; 
				}
				if (--timeout == 0) 
					return -2;
			}
			I2C1->TXDR = buffer[i];
		}
		timeout = 100000U;
		while (!(I2C1->ISR & I2C_ISR_STOPF)) { 
			if (--timeout == 0) return -2; 
		}
		I2C1->ICR = I2C_ICR_STOPCF;
		return 0;
	}
	static int8_t memory_read(uint16_t address, uint16_t reg, uint8_t *buffer, uint16_t length){
		if (buffer == NULL || length == 0) 
			return -1;
		uint32_t timeout = 100000U;
		while (I2C1->ISR & I2C_ISR_BUSY) { 
			if (--timeout == 0) 
				return -2; 
		}
		/* Step 1: Write register address (No Autoend to keep bus for Repeated Start) */
		uint32_t cr2 = I2C1->CR2 & ~((0xFFU << 16) | I2C_CR2_SADD | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP | I2C_CR2_AUTOEND);
		cr2 |= (1U << 16);
		cr2 |= (address & 0x7FU) << 1;
		cr2 |= I2C_CR2_START;
		I2C1->CR2 = cr2;timeout = 100000U;
		while (!(I2C1->ISR & I2C_ISR_TXIS)) { 
			if (--timeout == 0) 
				return -2; 
		}
		I2C1->TXDR = (uint8_t)(reg & 0xFFU);
		timeout = 100000U;
		while (!(I2C1->ISR & I2C_ISR_TC)) { 
			if (--timeout == 0) 
				return -2; 
		}
		/* Step 2: Repeated Start for Reading */
		cr2 = I2C1->CR2 & ~((0xFFU << 16) | I2C_CR2_SADD | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP);
		cr2 |= ((uint32_t)length << 16);
		cr2 |= (address & 0x7FU) << 1;
		cr2 |= I2C_CR2_RD_WRN;cr2 |= I2C_CR2_AUTOEND;
		cr2 |= I2C_CR2_START;I2C1->CR2 = cr2;
		for (uint16_t i = 0; i < length; i++){
			timeout = 100000U;
			while (!(I2C1->ISR & I2C_ISR_RXNE)){
				if (I2C1->ISR & I2C_ISR_NACKF) { 
					I2C1->ICR = I2C_ICR_NACKCF; 
					return -3; 
				}
				if (--timeout == 0) 
					return -2;
				}
				buffer[i] = (uint8_t)(I2C1->RXDR);
			}
			timeout = 100000U;
			while (!(I2C1->ISR & I2C_ISR_STOPF)) { 
				if (--timeout == 0) 
					return -2; 
			}
			I2C1->ICR = I2C_ICR_STOPCF;
			return 0;
		}
		/* --- SLAVE Execution Functions --- /static void slave_enable(void){/ Enable Address Match, NACK, and RX Interrupts for Slave Mode */
		I2C1->CR1 |= (I2C_CR1_ADDRIE | I2C_CR1_RXIE | I2C_CR1_NACKIE);
	}
	static void slave_disable(void){
		I2C1->CR1 &= ~(I2C_CR1_ADDRIE | I2C_CR1_RXIE | I2C_CR1_NACKIE);
	}
	static void slave_listen(void){
		/* Clear address flag to acknowledge match and release SCL stretch */
		I2C1->ICR = I2C_ICR_ADDRCF;
	}
	/* --- DMA Execution Functions (Configuration stubs) --- */
	static int8_t dma_write(uint16_t address, const uint8_t *buffer, uint16_t length){
		if (buffer == NULL || length == 0) 
			return -1;
		/* Enable I2C DMA Transmission requests */
		I2C1->CR1 |= I2C_CR1_TXDMAEN;
		/* Note: Configure DMA channel (e.g., DMA1_Channel1 via DMAMUX) externally */
		uint32_t cr2 = I2C1->CR2 & ~((0xFFU << 16) | I2C_CR2_SADD | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP);
		cr2 |= ((uint32_t)length << 16);
		cr2 |= (address & 0x7FU) << 1;
		cr2 |= I2C_CR2_AUTOEND;
		cr2 |= I2C_CR2_START;
		I2C1->CR2 = cr2;
		return 0;
	}
	static int8_t dma_read(uint16_t address, uint8_t *buffer, uint16_t length){
		if (buffer == NULL || length == 0) 
			return -1;
		/* Enable I2C DMA Reception requests */
		I2C1->CR1 |= I2C_CR1_RXDMAEN;
		/* Note: Configure DMA channel externally */
		uint32_t cr2 = I2C1->CR2 & ~((0xFFU << 16) | I2C_CR2_SADD | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP);
		cr2 |= ((uint32_t)length << 16);
		cr2 |= (address & 0x7FU) << 1;
		cr2 |= I2C_CR2_RD_WRN;cr2 |= I2C_CR2_AUTOEND;
		cr2 |= I2C_CR2_START;I2C1->CR2 = cr2;
		return 0;
	}
	
	
