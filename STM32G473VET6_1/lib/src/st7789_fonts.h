/*************************************************************************
	ST7789_FONTS
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License     
Hardware: ST7789
Date:     23/01/2026
************************************************************************/
#ifndef ST7789_FONTS_H
	#define ST7789_FONTS_H

/*** Library ***/
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

#define PROGMEM
#define pgm_read_byte(addr) (*(const uint8_t*)(addr))
#define pgm_read_word(addr) (*(const uint16_t*)(addr))

// Some ready-made 16-bit ('565') color settings:
#define ST77XX_BLACK 0x0000
#define ST77XX_WHITE 0xFFFF
#define ST77XX_RED 0xF800
#define ST77XX_GREEN 0x07E0
#define ST77XX_BLUE 0x001F
#define ST77XX_CYAN 0x07FF
#define ST77XX_MAGENTA 0xF81F
#define ST77XX_YELLOW 0xFFE0
#define ST77XX_ORANGE 0xFC00
#define ST77XX_GOLD 0xFFD0

extern const uint8_t font8x12[] PROGMEM;
extern const uint8_t font16x16[] PROGMEM;
extern const uint8_t font24x24[] PROGMEM;
extern const uint8_t star36x36_outline[180] PROGMEM;
extern const uint8_t star36x36_filled[180] PROGMEM;
extern const uint8_t star42x42_filled[252] PROGMEM;

#endif
/*** EOF ***/

