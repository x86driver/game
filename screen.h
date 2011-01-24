#ifndef _SCREEN_H
#define _SCREEN_H

#include <string.h>

unsigned char *screen_init();
void screen_destroy(unsigned char *rgb565);
void screen_capture(unsigned char *rgb565);

#endif

