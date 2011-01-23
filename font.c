#include <string.h>
#include "image.h"


void create_font_image(struct image *image)
{
	struct image *block = image_new(BLOCK_X, BLOCK_Y);
	struct image *font = image_new(BLOCK_X*25, BLOCK_Y);

	int img_array1[][2] = {
		{1, 0}, {4, 0}, {2, 0}, {2, 3}, {0, 2},
		{3, 1}, {4, 2}, {3, 2}, {0, 4}, {4, 1},
		{1, 4}, {1, 2}, {1, 3}, {4, 3}, {2, 1},
		{3, 4}, {3, 3}, {1, 1}, {0, 3}, {2, 2},
		{4, 4}, {0, 0}, {3, 0}, {2, 4}, {0, 1}};

	int img_array2[][2] = {
		{2, 2}, {3, 4}, {1, 1}, {0, 1}, {4, 4},
		{2, 0}, {4, 0}, {3, 1}, {3, 3}, {2, 3},
		{3, 0}, {2, 1}, {1, 3}, {3, 2}, {0, 2},
		{0, 3}, {0, 0}, {1, 0}, {4, 1}, {1, 4},
		{2, 4}, {4, 2}, {0, 4}, {1, 2}, {4, 3}};
/*
	image_getblock(image, block, 0, 0);
	image_append(font, block, 0);
	image_getblock(image, block, 1, 0);
	image_append(font, block, 1);
*/

	int i;
	for (i = 0; i < 25; ++i) {
		image_getblock(image, block, img_array1[i][0], img_array1[i][1]);
		image_append(font, block, i);
	}

	image_save(font, "font.raw");

	image_destroy(block);
	image_destroy(font);
}

void font_getimage(struct image *input, struct image *output, int idx)
{
	memcpy(output->buf, input->buf + BLOCK_X*BLOCK_Y*PIXEL*idx, BLOCK_X*BLOCK_Y*PIXEL);
}
