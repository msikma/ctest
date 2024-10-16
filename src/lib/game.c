#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "gfx.h"

int run_game() {
  int a, x, y;
  unsigned int b;
  char final_str[50];

  b = 0;
  x = 0;
  y = 0;

  // points = 0;
  
  set_video_mode_cga();

  for (a = 0; a < 320; ++a) {
    put_pixel(a, 0, 1);
  }
  for (a = 1; a < 200; ++a) {
    put_pixel(0, a, 1);
    put_pixel(319, a, 1);
  }
  for (a = 0; a < 320; ++a) {
    put_pixel(a, 199, 1);
  }

  while (1) {
    if (b > (316 * 196)) {
      //b = 0;
    }
    x = b % 316;
    y = b / 316 << 0;
    put_pixel(x + 2, y + 2, 2);
    b += 1;

    // points += 150;
    // sprintf(final_str, "Points: %d", b);
    // print_string(2, 2, final_str, 1, 1);
    //delay(1);
  }

  getch();

  reset_video_mode();
  return 0;
}
