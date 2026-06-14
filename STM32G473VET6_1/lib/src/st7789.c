/*************************************************************************
	ST7789
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License     
Hardware: ST7789 on stm32f411ceu6
Date:     23/01/2026
*************************************************************************/

/*** Library ***/
#include "st7789.h"
#include <stdlib.h>
#include <math.h>

/*** Define & Macros ***/
// Optional X/Y offsets for 240x240 modules
#define ST7789_X_OFFSET 0
#define ST7789_Y_OFFSET 0

#define ST_CMD_DELAY 0x80 // special signifier for command lists

#define ST77XX_NOP 0x00
#define ST77XX_SWRESET 0x01
#define ST77XX_RDDID 0x04
#define ST77XX_RDDST 0x09

#define ST77XX_SLPIN 0x10
#define ST77XX_SLPOUT 0x11
#define ST77XX_PTLON 0x12
#define ST77XX_NORON 0x13

#define ST77XX_INVOFF 0x20
#define ST77XX_INVON 0x21
#define ST77XX_DISPOFF 0x28
#define ST77XX_DISPON 0x29
#define ST77XX_CASET 0x2A
#define ST77XX_RASET 0x2B
#define ST77XX_RAMWR 0x2C
#define ST77XX_RAMRD 0x2E

#define ST77XX_PTLAR 0x30
#define ST77XX_TEOFF 0x34
#define ST77XX_TEON 0x35
#define ST77XX_MADCTL 0x36
#define ST77XX_COLMOD 0x3A

#define ST77XX_MADCTL_MY 0x80
#define ST77XX_MADCTL_MX 0x40
#define ST77XX_MADCTL_MV 0x20
#define ST77XX_MADCTL_ML 0x10
#define ST77XX_MADCTL_RGB 0x00

#define ST77XX_RDID1 0xDA
#define ST77XX_RDID2 0xDB
#define ST77XX_RDID3 0xDC
#define ST77XX_RDID4 0xDD

/*** Procedure and Function Definition ***/
static inline void st7789_delay_ms(uint32_t ms)
{
    // bind to your stm32xtool or system delay
    _delay_ms(ms);
}
// Returns the next multiple of 8 >= width
uint16_t _pad_width8(uint16_t width){
	return (width + 7) & ~7;
}

uint16_t _glyph_size_bytes(uint16_t width, uint16_t height){
	return ((width + 7) / 8) * height;
}

static inline void st7789_cs_low(ST7789_par* par) {
	clear_pin(par->scl_gpio, par->cs_pin);
}

static inline void st7789_cs_high(ST7789_par* par) {
	set_pin(par->scl_gpio, par->cs_pin);
}

static inline void st7789_dc_data(ST7789_par* par) {
	set_pin(par->scl_gpio, par->dc_pin);
}

static inline void st7789_dc_cmd(ST7789_par* par) {
	clear_pin(par->scl_gpio, par->dc_pin);
}


static inline void st7789_rst_low(ST7789_par* par) {
	clear_pin(par->scl_gpio, par->rst_pin);
}

static inline void st7789_rst_high(ST7789_par* par) {
	set_pin(par->scl_gpio, par->rst_pin);
}

// Reset the display
static inline void st7789_reset(ST7789_par* par)
{
    st7789_rst_high(par);
    st7789_delay_ms(10);

    st7789_rst_low(par);
    st7789_delay_ms(20);

    st7789_rst_high(par);
    st7789_delay_ms(120);
}

static inline void _spi_wait_txe(SPI_TypeDef *spi, uint32_t timeout)
{
    for( ;!(spi->SR & SPI_SR_TXE) && timeout; timeout--);
}

static inline void _spi_wait_bsy(SPI_TypeDef *spi, uint32_t timeout)
{
    for( ;(spi->SR & SPI_SR_BSY) && timeout ; timeout--);
}

static inline void st7789_spi_tx(ST7789_par* par, uint8_t d)
{
    SPI_TypeDef *spi = par->spi;

    _spi_wait_txe(spi, 1000);
    *(__IO uint8_t*)&spi->DR = d;

    _spi_wait_bsy(spi, 1000);

    // Drain RX to avoid OVR
    (void)spi->DR;
    (void)spi->SR;
}

// Push one byte, non-blocking except TXE
static inline void st7789_spi_tx_fast(ST7789_par* par, uint8_t d)
{
    SPI_TypeDef *spi = par->spi;
    _spi_wait_txe(spi, 1000);
    *(uint8_t*)&spi->DR = d;
}

/**
static inline void st7789_spi_tx(ST7789_par* par, uint8_t d)
{
    SPI_TypeDef *spi = par->spi;

    while(!(spi->SR & SPI_SR_TXE));
    *(__IO uint8_t*)&spi->DR = d;

    while(spi->SR & SPI_SR_BSY);

    (void)spi->DR;
    (void)spi->SR;
}

static inline void st7789_spi_tx_fast(ST7789_par* par, uint8_t d)
{
    SPI_TypeDef *spi = par->spi;
    while(!(spi->SR & SPI_SR_TXE));
    *(__IO uint8_t*)&spi->DR = d;
}
**/

// Flush SPI after a burst
static inline void st7789_spi_flush(ST7789_par* par)
{
    SPI_TypeDef *spi = par->spi;
    _spi_wait_bsy(spi, 1000);
    (void)spi->DR;  // drain RX
    (void)spi->SR;
}

/**
static inline void st7789_spi_flush(ST7789_par* par)
{
    SPI_TypeDef *spi = par->spi;
    while(spi->SR & SPI_SR_BSY);
    (void)spi->DR;
}
**/

// Send a command byte
static inline void st7789_cmd(ST7789_par* par, uint8_t c) {
	st7789_dc_cmd(par);
	st7789_spi_tx_fast(par, c);
}

// Send a data byte
static inline void st7789_data(ST7789_par* par, uint8_t d) {
	st7789_dc_data(par);
	st7789_spi_tx_fast(par, d);
}

void st7789_set_caset(ST7789_par* par, uint16_t x0, uint16_t x1)
{
	U_word w;
	
	st7789_cmd(par, ST77XX_CASET);
	w = writeHLbyte(x0 + ST7789_X_OFFSET); st7789_data(par, w.par.h); st7789_data(par, w.par.l);
	w = writeHLbyte(x1 + ST7789_X_OFFSET); st7789_data(par, w.par.h); st7789_data(par, w.par.l);
	st7789_spi_flush(par);
}

void st7789_set_raset(ST7789_par* par, uint16_t y0, uint16_t y1)
{
	U_word w;

	st7789_cmd(par, ST77XX_RASET);
	w = writeHLbyte(y0 + ST7789_Y_OFFSET); st7789_data(par, w.par.h); st7789_data(par, w.par.l);
	w = writeHLbyte(y1 + ST7789_Y_OFFSET); st7789_data(par, w.par.h); st7789_data(par, w.par.l);
	st7789_spi_flush(par);
}

// Initialization sequence
/**/
void st7789_init_seq(ST7789_par* par) {
	st7789_cs_low(par);
	//st7789_start(par);
	st7789_cmd(par, ST77XX_SWRESET); // SWRESET
	st7789_spi_flush(par);
	st7789_cs_high(par);
	
	//_delay_ms(150);
	st7789_delay_ms(150);
	
	st7789_cs_low(par);
	st7789_cmd(par, ST77XX_SLPOUT); // SLPOUT
	st7789_spi_flush(par);
	st7789_cs_high(par);
	
	//_delay_ms(120);
	st7789_delay_ms(120);
	
	st7789_cs_low(par);
	st7789_cmd(par, ST77XX_COLMOD); // COLMOD
	st7789_data(par, 0x55); // 0x55, 0x05
	st7789_spi_flush(par);
	//st7789_stop(par);

	st7789_cs_low(par);
	st7789_cmd(par, 0x36); // MADCTL
	st7789_data(par, 0x00); // 0x00, 0x08, 0xC0, 0x60
	st7789_spi_flush(par);
	st7789_cs_high(par);

	// CASET
	st7789_cs_low(par);
	st7789_set_caset(par, 0x0000, 0x00EF);
	//st7789_stop(par);
	
	// RASET
	//st7789_start(par);
	st7789_set_raset(par, 0x0000, 0x00EF); 
	//st7789_stop(par);
	
	//st7789_start(par);
	st7789_cmd(par, ST77XX_INVON); // INVON
	st7789_spi_flush(par);
	//st7789_stop(par);

	//_delay_ms(10);
	st7789_delay_ms(10);

	//st7789_start(par);
	st7789_cmd(par, ST77XX_NORON); // NORON
	st7789_spi_flush(par);
	//st7789_stop(par);
	
	//_delay_ms(10);
	st7789_delay_ms(10);
	
	//st7789_start(par);
	st7789_cmd(par, ST77XX_DISPON); // DISPON
	st7789_spi_flush(par);
	//st7789_stop(par);
	
	//_delay_ms(20);
	st7789_delay_ms(20);
	st7789_cs_high(par);
}

void st7789_set_window(ST7789_par* par, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	st7789_set_caset(par, x0, x1);

	st7789_set_raset(par, y0, y1);

	st7789_cmd(par, ST77XX_RAMWR);
}

void st7789_shift_pixel(ST7789_par* par, uint16_t color) {
	U_word data = { .var = color };
	st7789_data(par, data.par.h);
	st7789_data(par, data.par.l);
}

// Draw a single pixel
void st7789_draw_pixel(ST7789_par* par, uint16_t x, uint16_t y, uint16_t color) {
	
	if(x >= par->width || y >= par->height) return;

	st7789_set_window(par, x, y, x, y);
	st7789_shift_pixel(par, color);
	st7789_spi_flush(par);
}

void st7789_fill_screen(ST7789_par* par, uint16_t color) {
	st7789_cs_low(par);
	st7789_set_window(par, 0, 0, (par->width - 1), (par->height - 1));
	for (uint16_t y = 0; y < par->height; y++) {
		for (uint16_t x = 0; x < par->width; x++) {
			st7789_shift_pixel(par, color);
		}
	}
	st7789_spi_flush(par);
	st7789_cs_high(par);
}

static inline void st7789_draw_bits_fast(ST7789_par* par, uint8_t byte, uint8_t n_bits, uint16_t fg, uint16_t bg) {
    U_word FG = { .var = fg };
    U_word BG = { .var = bg };

    for(int i = 0; i < n_bits; i++) {
        uint8_t bit = 7 - i;
        if(byte & (1 << bit)) {
            st7789_data(par, FG.par.h);
            st7789_data(par, FG.par.l);
        } else {
            st7789_data(par, BG.par.h);
            st7789_data(par, BG.par.l);
        }
    }
}

void st7789_drawfont8x12(ST7789_par* par, char c, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg)
{
	const uint8_t first  = 32;   // first ASCII in font
	const uint8_t glyph_width  = 8;
	const uint8_t glyph_height = 12;

	if(c < first || c > 126) return;      // ignore out-of-range chars

	uint16_t base = (c - first) * glyph_height;

	// Local copies for bounds checking
	uint16_t w = glyph_width;
	uint16_t h = glyph_height;
	if(x + w > par->width)  w = par->width - x;
	if(y + h > par->height) h = par->height - y;

	st7789_set_window(par, x, y, x + w - 1, y + h - 1);
	
	for(uint8_t row = 0; row < h; row++)
	{
		uint8_t byte = pgm_read_byte(&font8x12[base + row]); // <-- must use &font8x12[index]!
		st7789_draw_bits_fast( par,byte,8,fg,bg );
	}
	st7789_spi_flush(par);
}

void st7789_drawstring8x12(ST7789_par* par, const char* str, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg)
{
	uint16_t cursorX = x;
	uint16_t cursorY = y;

	while (*str) {
		char c = *str++;
		st7789_drawfont8x12(par, c, cursorX, cursorY, fg, bg);
		cursorX += 8;
		if (cursorX + 8 > par->width) break;
	}
}

void st7789_drawstring8x12_size(ST7789_par* par, const char* str, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg, uint16_t size)
{
	uint16_t cursorX = x; char c;
	while (size) {
		if(*str){ c = *str++; }else{ c = ' '; } size--;
		st7789_drawfont8x12(par, c, cursorX, y, fg, bg);
		cursorX += 8;
		if (cursorX + 8 > par->width) break;
	}
}

void st7789_drawfont12x16(ST7789_par* par, char c, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg)
{
    const uint8_t first  = 32;
    const uint8_t glyph_width  = 12;
    const uint8_t glyph_height = 16;

    if(c < first || c > 126) return;

    uint16_t base = (c - first) * glyph_height * 2; // two bytes per row

    // Local copies for bounds checking
    uint16_t w = glyph_width;
    uint16_t h = glyph_height;
    if(x + w > par->width)  w = par->width - x;
    if(y + h > par->height) h = par->height - y;

    st7789_set_window(par, x, y, x + w - 1, y + h - 1);

    for(uint8_t row = 0; row < glyph_height; row++) {
        uint8_t high = pgm_read_byte(&font16x16[base + row*2]);
        uint8_t low  = pgm_read_byte(&font16x16[base + row*2 + 1]);

        st7789_draw_bits_fast(par, high, 8, fg, bg);
        st7789_draw_bits_fast(par, low, 4, fg, bg);  // draw the last 4 bits as-is
    }
    st7789_spi_flush(par);
}

void st7789_drawstring12x16(ST7789_par* par, const char* str, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg)
{
	uint16_t cursorX = x;
	while(*str) {
		char c = *str++;
		st7789_drawfont12x16(par, c, cursorX, y, fg, bg);
		cursorX += 12;
		if(cursorX + 12 > par->width) break;
	}
}

void st7789_drawstring12x16_size(ST7789_par* par, const char* str, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg, uint16_t size)
{
	uint16_t cursorX = x; char c;
	while(size) {
		if(*str){ c = *str++; }else{ c = ' '; } size--;
		st7789_drawfont12x16(par, c, cursorX, y, fg, bg);
		cursorX += 12;
		if(cursorX + 12 > par->width) break;
	}
}

void st7789_drawfont16x24( ST7789_par* par, char c, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg ){
	const uint8_t first = 32;
	const uint8_t glyph_w = 16;
	const uint8_t glyph_h = 24;

	if(c < first || c > 126) return;

	uint16_t base = (c - first) * glyph_h * 3;

	uint16_t w = glyph_w;
	uint16_t h = glyph_h;
	if(x + w > par->width)  w = par->width - x;
	if(y + h > par->height) h = par->height - y;

	st7789_set_window(par, x, y, x + w - 1, y + h - 1);

	for(uint8_t row = 0; row < h; row++) {
		uint8_t byte2 = pgm_read_byte(&font24x24[base + row*3 + 0]);
		uint8_t byte1 = pgm_read_byte(&font24x24[base + row*3 + 1]);

		st7789_draw_bits_fast( par,byte2,8,fg,bg );
		st7789_draw_bits_fast( par,byte1,8,fg,bg );
	}
	st7789_spi_flush(par);
}

void st7789_drawstring16x24( ST7789_par* par, const char* str, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg )
{
	uint16_t cursorX = x;
	while(*str){
		char c = *str++;
		st7789_drawfont16x24(par, c, cursorX, y, fg, bg);
		cursorX += 16;
		if(cursorX + 16 > par->width) break;
	}
}

void st7789_drawstring16x24_size( ST7789_par* par, const char* str, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg, uint16_t size )
{
	uint16_t cursorX = x;  char c;
	while(size){
		if(*str){ c = *str++; }else{ c = ' '; } size--;
		st7789_drawfont16x24(par, c, cursorX, y, fg, bg);
		cursorX += 16;
		if(cursorX + 16 > par->width) break;
	}
}

void st7789_drawfont32x32( ST7789_par* par, char c, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg ){
	const uint8_t first = 32;
	const uint8_t glyph_w = 32;
	const uint8_t glyph_h = 32;

	if(c < first || c > 126) return;

	// FIX 1: Change to uint32_t to prevent 16-bit multiplication memory truncation
	uint32_t base = (uint32_t)(c - first) * glyph_h * 4;

	uint16_t w = glyph_w;
	uint16_t h = glyph_h;
	if(x + w > par->width)  w = par->width - x;
	if(y + h > par->height) h = par->height - y;

	st7789_set_window(par, x, y, x + w - 1, y + h - 1);

	// FIX 2: Ensure row loop uses proper 32-bit math offsets
	for(uint32_t row = 0; row < h; row++) {
		uint8_t byte4 = pgm_read_byte(&font32x32[base + (row * 4) + 0]);
		uint8_t byte3 = pgm_read_byte(&font32x32[base + (row * 4) + 1]);
		uint8_t byte2 = pgm_read_byte(&font32x32[base + (row * 4) + 2]);
		uint8_t byte1 = pgm_read_byte(&font32x32[base + (row * 4) + 3]);

		st7789_draw_bits_fast( par, byte4, 8, fg, bg );
		st7789_draw_bits_fast( par, byte3, 8, fg, bg );
		st7789_draw_bits_fast( par, byte2, 8, fg, bg );
		st7789_draw_bits_fast( par, byte1, 8, fg, bg );
	}
	st7789_spi_flush(par);
}

void st7789_drawstring32x32_size( ST7789_par* par, const char* str, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg, uint16_t size )
{
	uint16_t cursorX = x;  char c;
	while(size){
		if(*str){ c = *str++; }else{ c = ' '; } size--;
		st7789_drawfont32x32(par, c, cursorX, y, fg, bg);
		cursorX += 32;
		if(cursorX + 32 > par->width) break;
	}
}

void st7789_drawfont18x32( ST7789_par* par, char c, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg ){
	const uint8_t first = 32;
	const uint8_t glyph_w = 18; // True window visual width
	const uint8_t glyph_h = 32; // True window height

	if(c < first || c > 126) return;

	// Keep multiplying by 4 because font32x32 allocates 4 bytes per row block
	uint32_t base = (uint32_t)(c - first) * glyph_h * 4;

	uint16_t w = glyph_w;
	uint16_t h = glyph_h;
	if(x + w > par->width)  w = par->width - x;
	if(y + h > par->height) h = par->height - y;

	st7789_set_window(par, x, y, x + w - 1, y + h - 1);

	for(uint32_t row = 0; row < h; row++) {
		uint8_t byte4 = pgm_read_byte(&font32x32[base + (row * 4) + 0]); // Bits 31-24 (Pixels 1-8)
		uint8_t byte3 = pgm_read_byte(&font32x32[base + (row * 4) + 1]); // Bits 23-16 (Pixels 9-16)
		uint8_t byte2 = pgm_read_byte(&font32x32[base + (row * 4) + 2]); // Bits 15-8  (Pixels 17-24)
		uint8_t byte1 = pgm_read_byte(&font32x32[base + (row * 4) + 3]); // Bits 15-8  (Pixels 17-24)
		(void) byte1;
		// byte1 contains bits 7-0 (Pixels 25-32), which are purely blank padding space

		// EXACTLY 18 BITS TOTAL SENT:
		st7789_draw_bits_fast( par, byte4, 8, fg, bg ); // Pushes the first 8 pixels
		st7789_draw_bits_fast( par, byte3, 8, fg, bg ); // Pushes the next 8 pixels (16 total)
		st7789_draw_bits_fast( par, byte2, 2, fg, bg ); // Pushes the final 2 pixels (18 total)

		// The remaining 6 bits of byte2 and all 8 bits of byte1 are completely ignored.
		// This matches your 18-pixel hardware window bounding boundary perfectly.
	}
	st7789_spi_flush(par);
}

void st7789_drawstring18x32_size( ST7789_par* par, const char* str, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg, uint16_t size )
{
	uint16_t cursorX = x;  char c;
	while(size){
		if(*str){ c = *str++; }else{ c = ' '; } size--;
		st7789_drawfont18x32(par, c, cursorX, y, fg, bg);
		cursorX += 18;
		if(cursorX + 18 > par->width) break;
	}
}
void st7789_drawfont48x48( ST7789_par* par, char c, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg ){
	const uint8_t first = 32;
	const uint8_t glyph_w = 48;
	const uint8_t glyph_h = 48;

	if(c < first || c > 126) return;

	// FIX 1: Change to uint32_t to prevent 16-bit multiplication memory truncation
	uint32_t base = (uint32_t)(c - first) * glyph_h * 6;

	uint16_t w = glyph_w;
	uint16_t h = glyph_h;
	if(x + w > par->width)  w = par->width - x;
	if(y + h > par->height) h = par->height - y;

	st7789_set_window(par, x, y, x + w - 1, y + h - 1);

	// FIX 2: Ensure row loop uses proper 32-bit math offsets
	for(uint32_t row = 0; row < h; row++) {
		uint8_t byte6 = pgm_read_byte(&font48x48[base + (row * 6) + 0]);
		uint8_t byte5 = pgm_read_byte(&font48x48[base + (row * 6) + 1]);
		uint8_t byte4 = pgm_read_byte(&font48x48[base + (row * 6) + 2]);
		uint8_t byte3 = pgm_read_byte(&font48x48[base + (row * 6) + 3]);
		uint8_t byte2 = pgm_read_byte(&font48x48[base + (row * 6) + 4]);
		uint8_t byte1 = pgm_read_byte(&font48x48[base + (row * 6) + 5]);

		st7789_draw_bits_fast( par, byte6, 8, fg, bg );
		st7789_draw_bits_fast( par, byte5, 8, fg, bg );
		st7789_draw_bits_fast( par, byte4, 8, fg, bg );
		st7789_draw_bits_fast( par, byte3, 8, fg, bg );
		st7789_draw_bits_fast( par, byte2, 8, fg, bg );
		st7789_draw_bits_fast( par, byte1, 8, fg, bg );
	}
	st7789_spi_flush(par);
}

void st7789_drawstring48x48_size( ST7789_par* par, const char* str, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg, uint16_t size )
{
	uint16_t cursorX = x;  char c;
	while(size){
		if(*str){ c = *str++; }else{ c = ' '; } size--;
		st7789_drawfont48x48(par, c, cursorX, y, fg, bg);
		cursorX += 48;
		if(cursorX + 48 > par->width) break;
	}
}

void st7789_drawfont24x48( ST7789_par* par, char c, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg ){
	const uint8_t first = 32;
	const uint8_t glyph_w = 24;
	const uint8_t glyph_h = 48;

	if(c < first || c > 126) return;

	// FIX 1: Change to uint32_t to prevent 16-bit multiplication memory truncation
	uint32_t base = (uint32_t)(c - first) * glyph_h * 6;

	uint16_t w = glyph_w;
	uint16_t h = glyph_h;
	if(x + w > par->width)  w = par->width - x;
	if(y + h > par->height) h = par->height - y;

	st7789_set_window(par, x, y, x + w - 1, y + h - 1);

	// FIX 2: Ensure row loop uses proper 32-bit math offsets
	for(uint32_t row = 0; row < h; row++) {
		uint8_t byte6 = pgm_read_byte(&font48x48[base + (row * 6) + 0]);
		uint8_t byte5 = pgm_read_byte(&font48x48[base + (row * 6) + 1]);
		uint8_t byte4 = pgm_read_byte(&font48x48[base + (row * 6) + 2]);
		uint8_t byte3 = pgm_read_byte(&font48x48[base + (row * 6) + 3]);
		uint8_t byte2 = pgm_read_byte(&font48x48[base + (row * 6) + 4]);
		uint8_t byte1 = pgm_read_byte(&font48x48[base + (row * 6) + 5]);
		(void) byte3;
		(void) byte2;
		(void) byte1;

		st7789_draw_bits_fast( par, byte6, 8, fg, bg );
		st7789_draw_bits_fast( par, byte5, 8, fg, bg );
		st7789_draw_bits_fast( par, byte4, 8, fg, bg );
		//st7789_draw_bits_fast( par, byte3, 8, fg, bg );
		//st7789_draw_bits_fast( par, byte2, 8, fg, bg );
		//st7789_draw_bits_fast( par, byte1, 8, fg, bg );
	}
	st7789_spi_flush(par);
}

void st7789_drawstring24x48_size( ST7789_par* par, const char* str, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg, uint16_t size )
{
	uint16_t cursorX = x;  char c;
	while(size){
		if(*str){ c = *str++; }else{ c = ' '; } size--;
		st7789_drawfont24x48(par, c, cursorX, y, fg, bg);
		cursorX += 24;
		if(cursorX + 24 > par->width) break;
	}
}

/**
void st7789_drawfont64x64( ST7789_par* par, char c, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg ){
	const uint8_t first = 32;
	const uint8_t glyph_w = 64;
	const uint8_t glyph_h = 64;

	if(c < first || c > 126) return;

	// FIX 1: Change to uint32_t to prevent 16-bit multiplication memory truncation
	uint32_t base = (uint32_t)(c - first) * glyph_h * 8;

	uint16_t w = glyph_w;
	uint16_t h = glyph_h;
	if(x + w > par->width)  w = par->width - x;
	if(y + h > par->height) h = par->height - y;

	st7789_set_window(par, x, y, x + w - 1, y + h - 1);

	// FIX 2: Ensure row loop uses proper 32-bit math offsets
	for(uint32_t row = 0; row < h; row++) {
		uint8_t byte8 = pgm_read_byte(&font64x64[base + (row * 8) + 0]);
		uint8_t byte7 = pgm_read_byte(&font64x64[base + (row * 8) + 1]);
		uint8_t byte6 = pgm_read_byte(&font64x64[base + (row * 8) + 2]);
		uint8_t byte5 = pgm_read_byte(&font64x64[base + (row * 8) + 3]);
		uint8_t byte4 = pgm_read_byte(&font64x64[base + (row * 8) + 4]);
		uint8_t byte3 = pgm_read_byte(&font64x64[base + (row * 8) + 5]);
		uint8_t byte2 = pgm_read_byte(&font64x64[base + (row * 8) + 6]);
		uint8_t byte1 = pgm_read_byte(&font64x64[base + (row * 8) + 7]);


		st7789_draw_bits_fast( par, byte8, 8, fg, bg );
		st7789_draw_bits_fast( par, byte7, 8, fg, bg );
		st7789_draw_bits_fast( par, byte6, 8, fg, bg );
		st7789_draw_bits_fast( par, byte5, 8, fg, bg );
		st7789_draw_bits_fast( par, byte4, 8, fg, bg );
		st7789_draw_bits_fast( par, byte3, 8, fg, bg );
		st7789_draw_bits_fast( par, byte2, 8, fg, bg );
		st7789_draw_bits_fast( par, byte1, 8, fg, bg );
	}
	st7789_spi_flush(par);
}

void st7789_drawstring64x64_size( ST7789_par* par, const char* str, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg, uint16_t size )
{
	uint16_t cursorX = x;  char c;
	while(size){
		if(*str){ c = *str++; }else{ c = ' '; } size--;
		st7789_drawfont64x64(par, c, cursorX, y, fg, bg);
		cursorX += 64;
		if(cursorX + 64 > par->width) break;
	}
}
**/

// font_array - Pass the specific font array (e.g., font16x16)
// size - Pass the size dimension (8, 16, 24, 32, etc.)
void st7789_drawfont_universal( ST7789_par* par, const uint8_t* font_array, uint8_t size, char c, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg ){
    const uint8_t first = 32;
    if(c < first || c > 126) return;

    // 1. Calculate bytes per row (e.g., 32/8 = 4 bytes)
    uint8_t bytes_per_row = size / 8;

    // 2. PERFECT MATH: base offset using glyph_h * bytes_per_row
    uint32_t base = (uint32_t)(c - first) * size * bytes_per_row;

    // Handle screen boundaries and clipping
    uint16_t w = size;
    uint16_t h = size;
    if(x + w > par->width)  w = par->width - x;
    if(y + h > par->height) h = par->height - y;

    st7789_set_window(par, x, y, x + w - 1, y + h - 1);

    // 3. Loop through rows and stream the correct amount of bytes
    for(uint32_t row = 0; row < h; row++) {
        for(uint8_t b = 0; b < bytes_per_row; b++) {
            // Target the precise byte inside the row
            uint32_t memory_address = base + (row * bytes_per_row) + b;
            uint8_t data_byte = pgm_read_byte(&font_array[memory_address]);

            st7789_draw_bits_fast(par, data_byte, 8, fg, bg);
        }
    }
    st7789_spi_flush(par);
}

void st7789_draw_line(ST7789_par* par, int x0, int y0, int x1, int y1, uint16_t color)
{
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy; // error term

	while (1) {
		st7789_draw_pixel(par, x0, y0, color); // draw the pixel
		if (x0 == x1 && y0 == y1) break;
		int e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; } // move in x
		if (e2 <= dx) { err += dx; y0 += sy; } // move in y
	}
}

// Draw line using y = m*x + b
void st7789_draw_line_eq(ST7789_par* par, float m, float b, int x_start, int x_end, uint16_t color){
	if(x_end < x_start) {
		// swap to ensure x_start <= x_end
		int tmp = x_start; x_start = x_end; x_end = tmp;
	}

	for(int x = x_start; x <= x_end; x++) {
		float y_f = (par->height - 1) - m * x + b;
		
		int y = (int)(y_f + 0.5f); // round to nearest integer

		if(x < 0 || x >= (int)par->width) continue;
		if(y < 0 || y >= (int)par->height) continue;

		st7789_draw_pixel(par, x, y, color);
	}
}

void st7789_draw_circle( ST7789_par* par, int x0, int y0, int r, uint16_t color ){
	if(r <= 0) return;

	int x = r;
	int y = 0;
	int err = 1 - x;

	while(x >= y) {
		st7789_draw_pixel(par, x0 + x, y0 + y, color);
		st7789_draw_pixel(par, x0 + y, y0 + x, color);
		st7789_draw_pixel(par, x0 - y, y0 + x, color);
		st7789_draw_pixel(par, x0 - x, y0 + y, color);
		st7789_draw_pixel(par, x0 - x, y0 - y, color);
		st7789_draw_pixel(par, x0 - y, y0 - x, color);
		st7789_draw_pixel(par, x0 + y, y0 - x, color);
		st7789_draw_pixel(par, x0 + x, y0 - y, color);

		y++;

		if(err < 0) {
			err += 2*y + 1;
			} else {
			x--;
			err += 2*(y - x) + 1;
		}
	}
}

// Draw circle in real time using equation y = sqrt(r^2 - x^2)
void st7789_draw_circle_eq(ST7789_par* par, int cx, int cy, int r, uint16_t color){
	for (int x = 0; x <= r; x++) {
		int y = (int)(sqrt(r*r - x*x) + 0.5f); // round to nearest integer

		// plot all 8 symmetric points
		st7789_draw_pixel(par, cx + x, cy + y, color);
		st7789_draw_pixel(par, cx - x, cy + y, color);
		st7789_draw_pixel(par, cx + x, cy - y, color);
		st7789_draw_pixel(par, cx - x, cy - y, color);

		st7789_draw_pixel(par, cx + y, cy + x, color);
		st7789_draw_pixel(par, cx - y, cy + x, color);
		st7789_draw_pixel(par, cx + y, cy - x, color);
		st7789_draw_pixel(par, cx - y, cy - x, color);
	}
}

void st7789_fill_circle_v1( ST7789_par* par, int x0, int y0, int r, uint16_t color ){
	if(r <= 0) return;

	int x = r;
	int y = 0;
	int err = 1 - x;

	while(x >= y) {
		st7789_draw_line(par, x0 - x, y0 + y, x0 + x, y0 + y, color);
		st7789_draw_line(par, x0 - y, y0 + x, x0 + y, y0 + x, color);
		st7789_draw_line(par, x0 - x, y0 - y, x0 + x, y0 - y, color);
		st7789_draw_line(par, x0 - y, y0 - x, x0 + y, y0 - x, color);

		y++;

		if(err < 0) {
			err += 2*y + 1;
			} else {
			x--;
			err += 2*(y - x) + 1;
		}
	}
}

void st7789_fill_circle_v2( ST7789_par* par, int x0, int y0, int r, uint16_t color ){
	int x = r;
	int y = 0;
	int err = 1 - x;

	while(x >= y) {
		st7789_draw_line(par, x0 + x, y0 - y, x0 + x, y0 + y, color);
		st7789_draw_line(par, x0 - x, y0 - y, x0 - x, y0 + y, color);
		st7789_draw_line(par, x0 + y, y0 - x, x0 + y, y0 + x, color);
		st7789_draw_line(par, x0 - y, y0 - x, x0 - y, y0 + x, color);

		y++;

		if(err < 0) {
			err += 2*y + 1;
			} else {
			x--;
			err += 2*(y - x) + 1;
		}
	}
}

void draw_random_circles(ST7789* lcd, uint8_t num){
	for(int i = 0; i < num; i++) {
		// Random position
		int x = rand() % lcd->par.width;
		int y = rand() % lcd->par.height;

		// Random size 1, 2, or 3 pixels
		int size = 1 + (rand() % 8);

		// Random color based on size
		uint16_t color;
		if(size < 3) color = ST77XX_WHITE;
		else if(size < 6) color = ST77XX_YELLOW;
		else color = ST77XX_ORANGE;

		// Draw the star (use your circle function for size >1, pixel for size==1)
		if(size == 1) lcd->draw_pixel(&lcd->par, x, y, color);
		else lcd->fill_circle_v1(&lcd->par, x, y, size, color);
	}
}

void st7789_draw_star5( ST7789_par* par, int cx, int cy, int r_outer, int r_inner, uint16_t color ){
	int x[10];
	int y[10];

	// Start pointing up
	float angle = -M_PI / 2.0f;
	float step  = M_PI / 5.0f; // 36�

	for(int i = 0; i < 10; i++) {
		int r = (i & 1) ? r_inner : r_outer;
		x[i] = cx + (int)(r * cosf(angle));
		y[i] = cy + (int)(r * sinf(angle));
		angle += step;
	}

	// Connect points
	for(int i = 0; i < 10; i++) {
		int j = (i + 1) % 10;
		st7789_draw_line(par, x[i], y[i], x[j], y[j], color);
	}
}

void st7789_draw_raw_bitmap_fg(ST7789_par* par, const uint8_t* bitmap, uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t fg_color){
	uint16_t total_pixel = w * h;

	uint16_t current_byte_index = 0xFFFF; // invalid initially
	uint8_t byte = 0;

	for (uint16_t pixel = 0; pixel < total_pixel; pixel++) {
		uint16_t x = pixel % w;
		uint16_t y = pixel / w;

		uint16_t byte_index = pixel >> 3;

		// Only read progmem when entering a new byte
		if (byte_index != current_byte_index) {
			current_byte_index = byte_index;
			byte = pgm_read_byte(bitmap + byte_index);
		}

		uint8_t bit = 7 - (pixel & 7);

		if (byte & (1 << bit)) {
			int16_t sx = x0 + x;
			int16_t sy = y0 + y;

			// ignore out-of-bound
			if ((uint16_t)sx >= par->width || (uint16_t)sy >= par->height) continue;

			st7789_draw_pixel(par, sx, sy, fg_color);
		}
	}
}

void st7789_draw_adjust_bitmap_fg(ST7789_par* par, const uint8_t* bitmap, uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t fg_color){
	uint16_t width = _pad_width8(w);
	uint16_t total_pixel = width * h;

	uint16_t current_byte_index = 0xFFFF; // invalid initially
	uint8_t byte = 0;

	for (uint16_t pixel = 0; pixel < total_pixel; pixel++) {
		uint16_t x = pixel % width;
		uint16_t y = pixel / width;

		uint16_t byte_index = pixel >> 3;

		// Only read progmem when entering a new byte
		if (byte_index != current_byte_index){ // oneshot
			current_byte_index = byte_index;
			byte = pgm_read_byte(bitmap + byte_index);
		}

		uint8_t bit = 7 - (pixel & 7);

		if (byte & (1 << bit)) {
			int16_t sx = x0 + x;
			int16_t sy = y0 + y;

			// ignore out-of-bound
			if ((uint16_t)sx >= par->width || (uint16_t)sy >= par->height) continue;

			st7789_draw_pixel(par, sx, sy, fg_color);
		}
	}
}

void st7789_dump_buffer( ST7789_par* par, const uint16_t* buf, uint16_t bw, uint16_t bh, uint16_t x0, uint16_t y0, uint16_t transparent ){
	if(!buf) return;

	for(uint16_t y = 0; y < bh; y++){
		uint16_t sy = y0 + y;
		if(sy >= par->height) continue;

		for(uint16_t x = 0; x < bw; x++){
			uint16_t sx = x0 + x;
			if(sx >= par->width) continue;

			uint16_t color = buf[y * bw + x];

			if(color == transparent) continue;

			st7789_draw_pixel(par, sx, sy, color);
		}
	}
}

void st7789_dump_image( ST7789_par* par, uint16_t x0, uint16_t y0, const uint16_t *img, uint16_t w, uint16_t h, uint16_t transparent ){
	for (uint16_t y = 0; y < h; y++) {
		for (uint16_t x = 0; x < w; x++) {

			uint16_t color = pgm_read_word(img + (y * w + x));

			if (color == transparent)
			continue;   // ?? leave background untouched

			st7789_draw_pixel(par, x0 + x, y0 + y, color);
		}
	}
}

// Test pin blink for debugging
void st7789_test_pin(ST7789_par* par, uint8_t pin) {
	if(pin >= 8) return;
	for(uint8_t repeat = 0; repeat < 10; repeat++) {
		set_pin(par->scl_gpio, pin);
		_delay_ms(200);
		clear_pin(par->scl_gpio, pin);
		_delay_ms(200);
	}
}

/*** Default Setup ***/
/*** GPIO Setup ***/
void st7789_setup_gpio(ST7789_par* par)
{
    // Enable GPIO clocks
    if(par->scl_gpio) GPIO_clock(par->scl_gpio, 1);  // SCL port also holds CS/DC/RST
    if(par->sda_gpio) GPIO_clock(par->sda_gpio, 1);  // SDA port

    // CS, DC, RST -> Output
    if(par->cmd_gpio) {
        GPIO_moder(par->cmd_gpio, par->cs_pin, MODE_OUTPUT);
        GPIO_moder(par->cmd_gpio, par->dc_pin, MODE_OUTPUT);
        GPIO_moder(par->cmd_gpio, par->rst_pin, MODE_OUTPUT);
        //GPIO_moder(par->scl_gpio, par->miso, MODE_INPUT);

        GPIO_otype(par->cmd_gpio, par->cs_pin, 0);
        GPIO_otype(par->cmd_gpio, par->dc_pin, 0);
        GPIO_otype(par->cmd_gpio, par->rst_pin, 0);
        //GPIO_otype(par->scl_gpio, par->miso, 1);

        GPIO_pupd(par->cmd_gpio, par->cs_pin, 0);
        GPIO_pupd(par->cmd_gpio, par->dc_pin, 0);
        GPIO_pupd(par->cmd_gpio, par->rst_pin, 0);
        //GPIO_pupd(par->scl_gpio, par->miso, 1);
    }

    // SPI pins -> Alternate Function
    if(par->sda_gpio) {
        GPIO_moder(par->sda_gpio, par->sda_pin, MODE_AF);
        GPIO_otype(par->sda_gpio, par->sda_pin, 0);
        GPIO_ospeed(par->sda_gpio, par->sda_pin, 3);
        GPIO_pupd(par->sda_gpio, par->sda_pin, 0);
        GPIO_af(par->sda_gpio, par->sda_pin, par->af);
    }

    if(par->scl_gpio) {
        GPIO_moder(par->scl_gpio, par->scl_pin, MODE_AF);
        GPIO_otype(par->scl_gpio, par->scl_pin, 0);
        GPIO_ospeed(par->scl_gpio, par->scl_pin, 3);
        GPIO_pupd(par->scl_gpio, par->scl_pin, 0);
        GPIO_af(par->scl_gpio, par->scl_pin, par->af);
    }

    // Initial pin states
    if(par->cmd_gpio) {
        set_hpin(par->cmd_gpio, (1 << par->cs_pin) | (1 << par->rst_pin)); // CS & RST high
        clear_hpin(par->cmd_gpio, (1 << par->dc_pin));                     // DC low
    }
}

/*** SPI Setup ***/
void st7789_setup_spi(ST7789_par* par)
{
    if(!par->spi) return;

    const STM32_DEVICE* device = dev();
    SPI_TypeDef* spi = par->spi;

    // F - Enable clock
    //if(spi == SPI1) device->system->rcc->APB2ENR |= RCC_APB2ENR_SPI1EN_Msk;
    //else if(spi == SPI2) device->system->rcc->APB1ENR |= RCC_APB1ENR_SPI2EN_Msk;
    //else if(spi == SPI3) device->system->rcc->APB1ENR |= RCC_APB1ENR_SPI3EN_Msk;

    // G
    if(spi == SPI1)
    	device->sys->rcc->APB2ENR |= RCC_APB2ENR_SPI1EN_Msk;
    else if(spi == SPI2)
    	device->sys->rcc->APB1ENR1 |= RCC_APB1ENR1_SPI2EN_Msk;
    else if(spi == SPI3)
    	device->sys->rcc->APB1ENR1 |= RCC_APB1ENR1_SPI3EN_Msk;



    spi->CR1 &= ~SPI_CR1_SPE_Msk;

    // G - FULL RESET of CR1 (important on G4 to avoid inherited state)
    spi->CR1 = 0;

    spi->CR1 =
        SPI_CR1_MSTR_Msk |   // master
        SPI_CR1_SSM_Msk  |   // software slave
        SPI_CR1_SSI_Msk;     // internal NSS high

    // fastest safe default (adjust later if needed)
    //spi->CR1 &= ~SPI_CR1_BR_Msk;  // fPCLK / 2
    set_reg_field_value(&spi->CR1, SPI_CR1_BR_Msk, SPI_CR1_BR_Pos,0); // fastest fPCLK / 2
    //set_reg_field_value(&spi->CR1, SPI_CR1_BR_Msk, SPI_CR1_BR_Pos,7); // slowest

    // F - 8-bit, MSB first, 2-line full duplex
    //spi->CR1 &= ~(SPI_CR1_DFF_Msk | SPI_CR1_LSBFIRST_Msk | SPI_CR1_BIDIMODE_Msk);

    // G
    spi->CR1 &= ~(SPI_CR1_LSBFIRST_Msk | SPI_CR1_BIDIMODE_Msk);
    spi->CR2 &= ~SPI_CR2_DS_Msk;
    spi->CR2 |= (7U << SPI_CR2_DS_Pos);

    // mode 0 (safe default for ST7789)
    spi->CR1 &= ~(SPI_CR1_CPOL_Msk | SPI_CR1_CPHA_Msk);

    spi->CR1 |= SPI_CR1_SPE_Msk;
}

/*** Initial Screen ***/
void boot_screen(ST7789_par* par){
	//U_word color = { .var = 0x0340 };
	U_word color = { .var = ST77XX_GREEN };
	//U_word color = { .var = ST77XX_WHITE };
	st7789_cs_low(par);
	st7789_set_window(par, 0, 0, 239, 239);
	for (uint32_t i = 0; i < 240UL * 240; i++) {
		st7789_data(par, color.par.h);
		st7789_data(par, color.par.l);
	}
	st7789_spi_flush(par);
	st7789_cs_high(par);
}

void welcome_screen(ST7789_par* par){
    st7789_cs_low(par);
    st7789_drawstring16x24(par,"Welcome",60,90,ST77XX_GOLD,ST77XX_GREEN);
    st7789_cs_high(par);
}

/***** Enable ST7789 handler *****/
ST7789 st7789_enable(SPI_TypeDef* spi, uint8_t cs_pin, uint8_t dc_pin, uint8_t rst_pin, uint16_t *fb) {
    ST7789 st;

    // -------------------------
    // Fill fixed parameters
    // -------------------------
    st.par.spi     = spi;
    st.par.cs_pin  = cs_pin;
    st.par.dc_pin  = dc_pin;
    st.par.rst_pin = rst_pin;
    st.par.width   = 240;
    st.par.height  = 240;
    st.par.fb      = fb;

    // -------------------------
    // Auto-detect GPIOs/pins
    // -------------------------
    if (spi == SPI1) { // AF5
		st.par.sda_gpio = GPIOA; // MOSI
		st.par.scl_gpio = GPIOA; // SCK
		st.par.cmd_gpio = GPIOA; // cs,dc,rst
		st.par.sda_pin  = 7;     // PA7 = SPI1_MOSI
		st.par.af  = 5;
		st.par.scl_pin  = 5;     // PA5 = SPI1_SCK
	}
	else if (spi == SPI2) { // AF5
		st.par.sda_gpio = GPIOB; // MOSI
		st.par.scl_gpio = GPIOB; // SCK
		st.par.cmd_gpio = GPIOB; // cs,dc,rst
		st.par.sda_pin  = 15;    // PB15 = SPI2_MOSI
		st.par.af  = 5;
		st.par.scl_pin  = 13;     // PB13 = SPI2_SCK
	}
	else if (spi == SPI3) { // AF6
		st.par.sda_gpio = GPIOC; // MOSI
		st.par.scl_gpio = GPIOC; // SCK
		st.par.cmd_gpio = GPIOC; // cs,dc,rst
		st.par.sda_pin  = 12;    // PC12 = SPI3_MOSI
		st.par.af  = 6;
		st.par.scl_pin  = 10;    // PC10 = SPI3_SCK
	}
	else {
		st.par.sda_gpio = NULL;
		st.par.scl_gpio = NULL;
		st.par.cmd_gpio = NULL;
		st.par.sda_pin  = 0;
		st.par.scl_pin  = 0;
	}

    st.setup.gpio = st7789_setup_gpio;
    st.setup.spi  = st7789_setup_spi;

    // -------------------------
    // Assign V-table functions
    // -------------------------
    st.reset           = st7789_reset;
    st.start           = st7789_cs_low;
    st.stop            = st7789_cs_high;
    st.draw_pixel      = st7789_draw_pixel;
    st.fill_screen     = st7789_fill_screen;
    st.drawfont8x12    = st7789_drawfont8x12;
    st.drawstring8x12  = st7789_drawstring8x12;
    st.drawstring8x12_size  = st7789_drawstring8x12_size;
    st.drawfont12x16   = st7789_drawfont12x16;
    st.drawstring12x16 = st7789_drawstring12x16;
    st.drawstring12x16_size = st7789_drawstring12x16_size;
    st.drawfont16x24   = st7789_drawfont16x24;
    st.drawstring16x24 = st7789_drawstring16x24;
    st.drawstring16x24_size = st7789_drawstring16x24_size;
    st.drawfont32x32   = st7789_drawfont32x32;
    st.drawstring32x32_size = st7789_drawstring32x32_size;
    st.drawfont18x32   = st7789_drawfont18x32;
    st.drawstring18x32_size = st7789_drawstring18x32_size;
    st.drawfont48x48   = st7789_drawfont48x48;
    st.drawstring48x48_size = st7789_drawstring48x48_size;
    st.drawfont24x48   = st7789_drawfont24x48;
    st.drawstring24x48_size = st7789_drawstring24x48_size;
    //st.drawfont64x64   = st7789_drawfont64x64;
    //st.drawstring64x64_size = st7789_drawstring64x64_size;
    st.drawfont64x64   = NULL;
    st.drawstring64x64_size = NULL;
    st.draw_line       = st7789_draw_line;
    st.draw_line_eq    = st7789_draw_line_eq;
    st.draw_circle     = st7789_draw_circle;
    st.draw_circle_eq  = st7789_draw_circle_eq;
    st.fill_circle_v1  = st7789_fill_circle_v1;
    st.fill_circle_v2  = st7789_fill_circle_v2;
    st.draw_random_circles = draw_random_circles;
    st.draw_star5      = st7789_draw_star5;
    st.draw_raw_bitmap_fg    = st7789_draw_raw_bitmap_fg;
    st.draw_adjust_bitmap_fg = st7789_draw_adjust_bitmap_fg;
    st.dump_buffer     = st7789_dump_buffer;
    st.dump_image      = st7789_dump_image;
    st.test_pin        = st7789_test_pin;

    if (st.setup.gpio) st.setup.gpio(&st.par);
    if (st.setup.spi)  st.setup.spi(&st.par);

	st7789_reset(&st.par);

	st7789_init_seq(&st.par);

    boot_screen(&st.par);

    //welcome_screen(&st.par);

    return st;
}

/*** EOF ***/

