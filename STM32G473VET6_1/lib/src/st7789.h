/************************************************************************
	ST7789
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: ST7789 on stm32f411ceu6
Date:     23/01/2026
************************************************************************/
#ifndef ST7789_H
	#define ST7789_H

/*** Library ***/
#include "stm32g473vet6.h"
#include "armsystick.h"
#include "st7789_fonts.h"

/*** Define & Macro ***/
// RGB to RGB656
#define ST7789_RGB565(r,g,b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

typedef struct
{
	GPIO_TypeDef*  sda_gpio;
	GPIO_TypeDef*  scl_gpio;
	SPI_TypeDef* spi;
	uint8_t cs_pin;
	uint8_t dc_pin;
	uint8_t rst_pin;
	uint8_t sda_pin;
	uint8_t af;
	uint8_t scl_pin;
	uint16_t width;
	uint16_t height;
	uint16_t *fb;
}ST7789_par;

typedef struct
{
	void (*gpio)(ST7789_par* par);
	void (*spi)(ST7789_par* par);
}ST7789_setup;

/*** Handler ***/
typedef struct ST7789
{
	ST7789_par par;
	ST7789_setup setup;
	// V-table
	void (*reset)(ST7789_par* par);
	void (*start)(ST7789_par* par);
	void (*stop)(ST7789_par* par);
	void (*cmd)(ST7789_par* par, uint8_t c);
	void (*data)(ST7789_par* par, uint8_t d);
	void (*draw_pixel)(ST7789_par* par, uint16_t x, uint16_t y, uint16_t color);
	void (*fill_screen)(ST7789_par* par, uint16_t color);
	void (*drawfont8x12)( ST7789_par *par, char c, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg);
	void (*drawstring8x12)(ST7789_par* par, const char* str, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg);
	void (*drawstring8x12_size)(ST7789_par* par, const char* str, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg, uint16_t size);
	void (*drawfont12x16)(ST7789_par* par, char c, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg);
	void (*drawstring12x16)(ST7789_par* par, const char* str, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg);
	void (*drawstring12x16_size)(ST7789_par* par, const char* str, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg, uint16_t size);
	void (*drawfont16x24)( ST7789_par* par, char c, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg );
	void (*drawstring16x24)(ST7789_par* par, const char* str, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg);
	void (*drawstring16x24_size)(ST7789_par* par, const char* str, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg, uint16_t size);
	void (*draw_line)(ST7789_par* par, int x0, int y0, int x1, int y1, uint16_t color);
	void (*draw_line_eq)(ST7789_par* par, float m, float b, int x_start, int x_end, uint16_t color);
	void (*draw_circle)( ST7789_par* par, int x0, int y0, int r, uint16_t color);
	void (*draw_circle_eq)(ST7789_par* par, int cx, int cy, int r, uint16_t color);
	void (*fill_circle_v1)(ST7789_par* par, int x0, int y0, int r, uint16_t color);
	void (*fill_circle_v2)(ST7789_par* par, int x0, int y0, int r, uint16_t color);
	void (*draw_random_circles)(struct ST7789* st7789, uint8_t num);
	void (*draw_star5)(ST7789_par* par, int cx, int cy, int r_outer, int r_inner, uint16_t color );
	void (*draw_raw_bitmap_fg)(ST7789_par* par, const uint8_t* bitmap, uint16_t x0, uint16_t y0, uint16_t w, uint16_t h,uint16_t fg_color);
	void (*draw_adjust_bitmap_fg)(ST7789_par* par, const uint8_t* bitmap, uint16_t x0, uint16_t y0, uint16_t w, uint16_t h,uint16_t fg_color);
	void (*dump_buffer)(ST7789_par* par, const uint16_t* buf, uint16_t bw, uint16_t bh, uint16_t x0, uint16_t y0, uint16_t transparent);
	void (*dump_image)(ST7789_par* par, uint16_t x0, uint16_t y0, const uint16_t *img, uint16_t w, uint16_t h, uint16_t transparent);
	void (*test_pin)(ST7789_par* par, uint8_t pin);
}ST7789;

ST7789 st7789_enable(SPI_TypeDef* spi, uint8_t cs_pin, uint8_t dc_pin, uint8_t rst_pin, uint16_t *fb);

uint16_t _pad_width8(uint16_t width);
uint16_t _glyph_size_bytes(uint16_t width, uint16_t height);

/*** Setup ***/
void st7789_setup_gpio(ST7789_par* par);
void st7789_setup_spi(ST7789_par* par);

#endif
/*** EOF ***/

