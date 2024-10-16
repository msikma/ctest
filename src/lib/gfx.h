#include <dos.h>

#ifndef GFX_H
#define GFX_H

#define COLOR_BG 0
#define MODE_TEXT 0x03
#define MODE_320x200 0x04
#define VIDEO_INTERRUPT 0x10
#define VIDEO_MEMORY_OFFSET 0xB800  // CGA graphics memory starting point
#define BIOS_FONT_ADDRESS 0xF000FA6EL
#define BIOS_FONT_WIDTH 8
#define BIOS_FONT_HEIGHT 8

void set_video_mode(unsigned char mode);
void set_video_mode_cga();
void reset_video_mode();
void put_pixel(int x, int y, unsigned char color);
void print_char(int x, int y, char c, unsigned char color, int clear);
void print_string(int x, int y, const char *str, unsigned char color, int clear);

#endif
