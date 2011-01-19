#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 320
#define HEIGHT 480

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

static inline void getpixel(unsigned char *image888, int x, int y,
	unsigned char *r, unsigned char *g, unsigned char *b)
{
	image888 += (x+y*WIDTH)*3;
	*b = *image888++;
	*g = *image888++;
	*r = *image888;
}

static inline void setpixel(unsigned char *image888, int x, int y,
	unsigned char r, unsigned char g, unsigned b)
{
	image888 += (x+y*WIDTH)*3;
	*image888++ = b;
	*image888++ = g;
	*image888 = r;
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
	if (argc < 2) {
		printf("Usage: %s [file]\n", argv[0]);
		exit(1);
	}

	FILE *fp = fopen(argv[1], "rb");
	if (!fp) {
		perror(argv[1]);
		exit(1);
	}

	int size565 = WIDTH*HEIGHT*2;
	int size888 = WIDTH*HEIGHT*3;
	unsigned short *image565 = (unsigned short*)malloc(size565);
	unsigned char *image888 = (unsigned char*)malloc(size888);

	fread(image565, size565, 1, fp);
	rgb565_2_rgb24(image888, image565);
//test
	int x, y;
	unsigned char *my888 = (unsigned char*)malloc(size888);
	unsigned char r, g, b;
	for (y = 0; y < HEIGHT; ++y) {
		for (x = 0; x < WIDTH; ++x) {
			getpixel(image888, x, y, &r, &g, &b);
			setpixel(my888, x, y, r, g, b);
		}
	}
	FILE *out888 = fopen("same.raw", "wb");
	fwrite(my888, size888, 1, out888);
	fclose(out888);
	free(my888);
//end test

//	threshold(THRESHOLD, image888);

	FILE *fpout = fopen("out.raw", "wb");
	if (!fpout) {
		perror("out.raw");
		goto _error;
	}

	fwrite(image888, size888, 1, fpout);
	fclose(fpout);
	printf("Output: out.raw (RGB888) with threshold %d\n", THRESHOLD);
_error:
	free(image565);
	free(image888);
	fclose(fp);
	return 0;
}

