#include <dos.h>
#include "gfx.h"
#include "../util/bin.h"

void set_video_mode_cga() {
  set_video_mode(MODE_320x200);
}

void reset_video_mode() {
  set_video_mode(MODE_TEXT);
}

void set_video_mode(unsigned char mode) {
  union REGS regs;
  regs.h.ah = 0x00;
  regs.h.al = mode;
  int86(VIDEO_INTERRUPT, &regs, &regs);
}

void put_pixel(int x, int y, unsigned char color) {
  // Get pointer to the start of the CGA video memory.
  unsigned char far *video_memory = (unsigned char far *)MK_FP(VIDEO_MEMORY_OFFSET, 0);
  unsigned char mask, shift;
  unsigned int offset;

  // Precompute whether the pixel is in the even or odd field.
  unsigned int y_halved = y >> 1; // (y / 2)
  unsigned int field_offset = (y & 1) << 13; // (y & 1) ? 0x2000 : 0

  // Calculate the offset in video memory.
  // (y_halved * 64) + (y_halved * 16) + (x / 4) + the even/odd field offset.
  offset = (y_halved << 6) + (y_halved << 4) + (x >> 2) + field_offset;

  // Determine the bit position within the byte.
  shift = (3 - (x & 3)) << 1; // (3 - (x % 4)) * 2

  // Create a mask to clear the existing pixel.
  mask = 0x03 << shift;

  // Write the new color to video memory.
  video_memory[offset] = (video_memory[offset] & ~mask) | ((color & 0x03) << shift);
}

void print_char(int x, int y, char c, unsigned char color, int clear) {
  unsigned char far *font = (unsigned char far *)BIOS_FONT_ADDRESS;
  unsigned char far *char_bitmap = font + (c << 3);
  unsigned int a, b;

  for (a = 0; a < BIOS_FONT_WIDTH; a++) {
    unsigned char row = char_bitmap[a];
    
    for (b = 0; b < BIOS_FONT_HEIGHT; b++) {
      if (row & (0x80 >> b)) {
        put_pixel(x + b, y + a, color);
      }
      else if (clear) {
        put_pixel(x + b, y + a, COLOR_BG);
      }
    }
  }
}

void print_string(int x, int y, const char *str, unsigned char color, int clear) {
  while (*str) {
    print_char(x, y, *str++, color, clear);
    x += BIOS_FONT_WIDTH;
  }
}
