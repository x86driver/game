#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "image.h"
#include "font.h"

#define RGB565_MASK_RED        0xF800
#define RGB565_MASK_GREEN                         0x07E0
#define RGB565_MASK_BLUE                         0x001F

#define THRESHOLD 247

void rgb565_2_rgb24(unsigned char *rgb24, unsigned short *rgb565)
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
	if (argc < 4) {
		printf("Usage: %s [file]\n", argv[0]);
		exit(1);
	}

	FILE *fp = fopen(argv[1], "rb");
	if (!fp) {
		perror(argv[1]);
		exit(1);
	}

	int size565 = WIDTH*HEIGHT*2;
	unsigned short *image565 = (unsigned short*)malloc(size565);
//	unsigned char *image888 = (unsigned char*)malloc(size888);
	struct image *image = image_new(WIDTH, HEIGHT);

	fread(image565, size565, 1, fp);
	rgb565_2_rgb24(image->buf, image565);

	threshold(THRESHOLD, image->buf);

	image_save(image, "out.raw");
	printf("Output: out.raw (RGB888) with threshold %d\n", THRESHOLD);

	struct image *block = image_new(BLOCK_X, BLOCK_Y);
	image_getblock(image, block, atoi(argv[2]), atoi(argv[3]));
	image_save(block, "block.raw");
	image_destroy(block);

	create_font_image(image);

	free(image565);
	image_destroy(image);
	fclose(fp);
	return 0;
}

