#ifndef _IMAGE_H
#define _IMAGE_H

#include <stdlib.h>

#define WIDTH 320
#define HEIGHT 480

struct image {
	int width, height;
	unsigned char *buf;
};

void image_load(struct image *img, const char *file);
void image_save(struct image *img, const char *file);

static inline struct image *image_new(int width, int height)
{
	struct image *img = (struct image*)malloc(sizeof(struct image));
	img->buf = (unsigned char*)malloc(width*height*3);
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

#endif
