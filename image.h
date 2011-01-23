#ifndef _IMAGE_H
#define _IMAGE_H

#include <stdlib.h>

#define WIDTH 320
#define HEIGHT 480

#define BLOCK_X 52
#define BLOCK_Y 46

#define PIXEL 3

struct image {
	int width, height;
	unsigned char *buf;
};

void image_load(struct image *img, const char *file);
void image_save(struct image *img, const char *file);
void image_getblock(const struct image * const img, struct image *block, int ix, int iy);
void image_append(struct image *dst, const struct image * const src, int ix);
int image_weight(struct image *src, struct image *dst);

static inline struct image *image_new(int width, int height)
{
	struct image *img = (struct image*)malloc(sizeof(struct image));
	img->buf = (unsigned char*)malloc(width*height*PIXEL);
	img->width = width;
	img->height = height;
	return img;
}

static inline void image_destroy(struct image *img)
{
	if (img != NULL) {
		if (img->buf != NULL)
			free(img->buf);
		free(img);
	}
}

static inline void getpixel(const struct image * const image, int x, int y,
        unsigned char *r, unsigned char *g, unsigned char *b)
{
	unsigned char *image888 = image->buf;
        image888 += (x+y*image->width)*PIXEL;
        *b = *image888++;
        *g = *image888++;
        *r = *image888;
}

static inline void setpixel(struct image *image, int x, int y,
        unsigned char r, unsigned char g, unsigned b)
{
	unsigned char *image888 = image->buf;
        image888 += (x+y*image->width)*PIXEL;
        *image888++ = b;
        *image888++ = g;
        *image888 = r;
}

#endif
