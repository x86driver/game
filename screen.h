#ifndef _SCREEN_H
#define _SCREEN_H

#include <string.h>

unsigned short *screen_init();
void screen_destroy(unsigned short *rgb565);
void screen_capture(unsigned short *rgb565);

#endif

