#include "image.h"
#include "font.h"

#include <stdio.h>

int recognize_font(struct image *block, struct image *font, int range)
{
	int i, ret = 0;
	unsigned int weight = ~0U, w;
	struct image *tmpblk = image_new(BLOCK_X, BLOCK_Y);
	int from, stop;

	if (range == 0) {
		from = 0;
		stop = 25;
	} else {
		from = 24;
		stop = 50;
	}

	for (i = from; i < stop; ++i) {
//	for (i = 0; i < 50; ++i) {
		font_getimage(font, tmpblk, i);
		w = image_weight(tmpblk, block);
//		printf("[%d] weight: %d\n", i, w);
		if (w < weight) {
			weight = w;
			ret = i;
		}
	}
//	printf("[%d] = %d\n", ret+1, w);
	image_destroy(tmpblk);
	return ret;
}

void recognize(struct image *image, struct image *font, struct Glyph *glyph, int range)
{
	int i, j, number;
	struct Glyph *glyptr;
	struct image *outblk = image_new(BLOCK_X, BLOCK_Y);

	for (j = 0; j < 5; ++j) {
		for (i = 0; i < 5; ++i) {
			image_getblock(image, outblk, i, j);
			number = recognize_font(outblk, font, range);
			glyptr = glyph + (number);
			glyptr->number = number+1;
			glyptr->x = i;
			glyptr->y = j;
			printf("%02d  ", number+1);
		}
		printf("\n");
	}

	image_destroy(outblk);
}
