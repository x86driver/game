#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "image.h"
#include "font.h"
#include "recog.h"
#include "event.h"
#include "screen.h"

#define RGB565_MASK_RED        0xF800
#define RGB565_MASK_GREEN                         0x07E0
#define RGB565_MASK_BLUE                         0x001F

#define THRESHOLD 247

void rgb565_to_rgb24(unsigned char *rgb24, unsigned short *rgb565)
{
	unsigned int i = 0;
	unsigned char R, G, B;
	for (i = 0; i < WIDTH*HEIGHT; ++i) {
		R = (*rgb565 & RGB565_MASK_RED) >> 11;
		G = (*rgb565 & RGB565_MASK_GREEN) >> 5;
		B = (*rgb565 & RGB565_MASK_BLUE);

		R <<= 3;
		G <<= 2;
		B <<= 3;
		*rgb24++ = R;
		*rgb24++ = G;
		*rgb24++ = B;
		++rgb565;
	}
}

void threshold(int thres, unsigned char *rgb24)
{
	unsigned int i = 0;
	unsigned char R, G, B;
	for (i = 0; i < WIDTH*HEIGHT; ++i) {
		R = *rgb24;
		G = *(rgb24+1);
		B = *(rgb24+2);
		if (R > thres && G > thres && B > thres) {
			*rgb24++ = 0xff;
			*rgb24++ = 0xff;
			*rgb24++ = 0xff;
		} else {
			*rgb24++ = 0;
			*rgb24++ = 0;
			*rgb24++ = 0;
		}
	}
}

void smooth(unsigned char *image888)
{
#define BLOCK 3
	int x, y, i, j, val;
	int ix, iy;
	for (y = BLOCK/2; y < HEIGHT - BLOCK/2; ++y) {
		for (x = BLOCK/2; x < WIDTH - BLOCK/2; ++x) {
			val = 0;
			for (i = 0; i < BLOCK; ++i) {
				for (j = 0; j < BLOCK; ++j) {
					ix = x + j - BLOCK / 2;
					iy = y + i - BLOCK / 2;
//					val += (*(rgb24+ix)
				}
			}
		}
	}
}

int main(int argc, char **argv)
{
	unsigned short *image565 = screen_init();
	struct image *image = image_new(WIDTH, HEIGHT);
	struct image *font = image_new(BLOCK_X, BLOCK_Y*50);
	struct Glyph glyph[50];
	int i;

	event_init();
	image_load(font, "data.raw");
	memset(glyph, 0, sizeof(glyph));

	screen_capture(image565);
	rgb565_to_rgb24(image->buf, image565);
	threshold(THRESHOLD, image->buf);
	recognize(image, font, glyph, 0);

	for (i = 0; i < 25; ++i) {
		send_touch(glyph[i].x, glyph[i].y);
		usleep(100);
	}

/*
	screen_capture(image565);

	for (i = 24; i < 50; ++i) {
		send_touch(glyph[i].x, glyph[i].y);
		usleep(100);
	}
*/

	image_destroy(font);
	event_destroy();
	free(image565);
	image_destroy(image);
	return 0;
}

