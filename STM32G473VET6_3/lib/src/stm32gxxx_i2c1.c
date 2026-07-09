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
static void _common_config(void);
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
static i2c1_get i2c1_internal_get = {
    .busy    = get_busy,
    .ready   = get_ready,
    .enabled = get_enabled,
    .error   = get_error
};

static i2c1_set i2c1_internal_set = {
    .timing          = set_timing,
    .own_address     = set_own_address,
    .addressing_mode = set_addressing_mode,
    .analog_filter   = set_analog_filter,
    .digital_filter  = set_digital_filter
};

static const i2c1_common i2c1_execute_common = {
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
    .get     = &i2c1_internal_get,
    .set     = &i2c1_internal_set,
    .irq     = &i2c1_internal_irq,
    .run     = &i2c1_execute
};

/* --- Public Interface Accessor --- */
i2c1_handler *i2c1(void) { return &i2c1_obj; }

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
static void _common_config(void)
{
    if (i2c1_internal_par.scl_port == NULL || i2c1_internal_par.sda_port == NULL) return;

    /* 1. Turn on GPIO Clocks dynamically depending on ports assigned */
    if (i2c1_internal_par.scl_port == GPIOA || i2c1_internal_par.sda_port == GPIOA) RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    if (i2c1_internal_par.scl_port == GPIOB || i2c1_internal_par.sda_port == GPIOB) RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    if (i2c1_internal_par.scl_port == GPIOC || i2c1_internal_par.sda_port == GPIOC) RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
    /* Wait for stabilization clock cycle */
    __DSB();

    /* Helper variables to translate pin index from bitmasks if necessary */
    uint32_t scl_pos = i2c1_internal_par.scl_pin;
    uint32_t sda_pos = i2c1_internal_par.sda_pin;

    /* 2. Configure SCL Pin to Alternate Function Mode, Open-Drain, High Speed */
    i2c1_internal_par.scl_port->MODER   &= ~(3U << (scl_pos * 2U));
    i2c1_internal_par.scl_port->MODER   |=  (2U << (scl_pos * 2U));  /* AF Mode */
    i2c1_internal_par.scl_port->OTYPER  |=  (1U << scl_pos);         /* Open Drain */
    i2c1_internal_par.scl_port->OSPEEDR |=  (3U << (scl_pos * 2U));  /* Very High Speed */
    i2c1_internal_par.scl_port->PUPDR   &= ~(3U << (scl_pos * 2U));  /* No Pull (Assuming Ext Pull-ups) */

    /* 3. Configure SDA Pin identically */
    i2c1_internal_par.sda_port->MODER   &= ~(3U << (sda_pos * 2U));
    i2c1_internal_par.sda_port->MODER   |=  (2U << (sda_pos * 2U));
    i2c1_internal_par.sda_port->OTYPER  |=  (1U << sda_pos);
    i2c1_internal_par.sda_port->OSPEEDR |=  (3U << (sda_pos * 2U));
    i2c1_internal_par.sda_port->PUPDR   &= ~(3U << (sda_pos * 2U));

    /* 4. Map the Alternate Function (AF) Number into the AFR registers */
    /* SCL Alternate Function Multiplexing */
    if (scl_pos < 8U) {
        i2c1_internal_par.scl_port->AFR[0] &= ~(0xFU << (scl_pos * 4U));
        i2c1_internal_par.scl_port->AFR[0] |=  ((uint32_t)i2c1_internal_par.alternate_function << (scl_pos * 4U));
    } else {
        i2c1_internal_par.scl_port->AFR[1] &= ~(0xFU << ((scl_pos - 8U) * 4U));
        i2c1_internal_par.scl_port->AFR[1] |=  ((uint32_t)i2c1_internal_par.alternate_function << ((scl_pos - 8U) * 4U));
    }

    /* SDA Alternate Function Multiplexing */
    if (sda_pos < 8U) {
        i2c1_internal_par.sda_port->AFR[0] &= ~(0xFU << (sda_pos * 4U));
        i2c1_internal_par.sda_port->AFR[0] |=  ((uint32_t)i2c1_internal_par.alternate_function << (sda_pos * 4U));
    } else {
        i2c1_internal_par.sda_port->AFR[1] &= ~(0xFU << ((sda_pos - 8U) * 4U));
        i2c1_internal_par.sda_port->AFR[1] |=  ((uint32_t)i2c1_internal_par.alternate_function << ((sda_pos - 8U) * 4U));
    }

    /* 5. Proceed with standard I2C Register Setup as before */
    I2C1->CR1 &= ~I2C_CR1_PE;
    set_addressing_mode(i2c1_internal_par.addressing_mode);
    set_timing(i2c1_internal_par.timing);
    set_analog_filter(i2c1_internal_par.analog_filter);
    set_digital_filter(i2c1_internal_par.digital_filter);
    set_own_address(i2c1_internal_par.own_address);
}

static void common_init(void)
{
    RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN;
    __DSB();
    _common_config();
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
        /* Fixed: ST CMSIS uses I2C_ICR_TIMOUTCF (no 'E') */
        I2C1->ICR = (I2C_ICR_BERRCF | I2C_ICR_ARLOCF | I2C_ICR_OVRCF | I2C_ICR_TIMOUTCF);
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
    	I2C1->ICR = I2C_ICR_NACKCF;
    	I2C1->ICR = I2C_ICR_STOPCF;
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
	*count = found_devices;return 0;
}
/* --- MEMORY Execution Functions --- */
static int8_t memory_write(uint16_t address, uint16_t reg, const uint8_t *buffer, uint16_t length){
	if (buffer == NULL || length == 0)
		return -1;
	uint32_t timeout = 100000U;
	while (I2C1->ISR & I2C_ISR_BUSY) {
		if (--timeout == 0)
			return -2;
	}
	uint32_t cr2 = I2C1->CR2 & ~((0xFFU << 16) | I2C_CR2_SADD | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP);
	cr2 |= (((uint32_t)length + 1U) << 16);
	cr2 |= (address & 0x7FU) << 1;
	cr2 |= I2C_CR2_AUTOEND;
	cr2 |= I2C_CR2_START;I2C1->CR2 = cr2;
	timeout = 100000U;
	while (!(I2C1->ISR & I2C_ISR_TXIS)) {
		if (--timeout == 0)
			return -2;
	}
	I2C1->TXDR = (uint8_t)(reg & 0xFFU);
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
		if (--timeout == 0)
			return -2;
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
	uint32_t cr2 = I2C1->CR2 & ~((0xFFU << 16) | I2C_CR2_SADD | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP | I2C_CR2_AUTOEND);
	cr2 |= (1U << 16);
	cr2 |= (address & 0x7FU) << 1;
	cr2 |= I2C_CR2_START;I2C1->CR2 = cr2;
	timeout = 100000U;
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
	cr2 = I2C1->CR2 & ~((0xFFU << 16) | I2C_CR2_SADD | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP);
	cr2 |= ((uint32_t)length << 16);
	cr2 |= (address & 0x7FU) << 1;
	cr2 |= I2C_CR2_RD_WRN;
	cr2 |= I2C_CR2_AUTOEND;
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
/* --- SLAVE Execution Functions --- */
static void slave_enable(void){
	I2C1->CR1 |= (I2C_CR1_ADDRIE | I2C_CR1_RXIE | I2C_CR1_NACKIE);
}
static void slave_disable(void){
	I2C1->CR1 &= ~(I2C_CR1_ADDRIE | I2C_CR1_RXIE | I2C_CR1_NACKIE);
}
static void slave_listen(void){
	I2C1->ICR = I2C_ICR_ADDRCF;
}
/* --- DMA Execution Functions --- */
static int8_t dma_write(uint16_t address, const uint8_t *buffer, uint16_t length){
	if (buffer == NULL || length == 0)
		return -1;
	I2C1->CR1 |= I2C_CR1_TXDMAEN;
	uint32_t cr2 = I2C1->CR2 & ~((0xFFU << 16) | I2C_CR2_SADD | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP);
	cr2 |= ((uint32_t)length << 16);
	cr2 |= (address & 0x7FU) << 1;
	cr2 |= I2C_CR2_AUTOEND;
	cr2 |= I2C_CR2_START;I2C1->CR2 = cr2;
	return 0;
}
static int8_t dma_read(uint16_t address, uint8_t *buffer, uint16_t length){
	if (buffer == NULL || length == 0)
		return -1;
	I2C1->CR1 |= I2C_CR1_RXDMAEN;
	uint32_t cr2 = I2C1->CR2 & ~((0xFFU << 16) | I2C_CR2_SADD | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP);
	cr2 |= ((uint32_t)length << 16);
	cr2 |= (address & 0x7FU) << 1;
	cr2 |= I2C_CR2_RD_WRN;cr2 |= I2C_CR2_AUTOEND;
	cr2 |= I2C_CR2_START;I2C1->CR2 = cr2;
	return 0;
}

