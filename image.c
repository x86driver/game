#include <stdio.h>
#include "image.h"

void image_load(struct image *img, const char *file)
{
	FILE *fp = fopen(file, "rb");
	if (!fp)
		perror(file);
	fread(img->buf, img->width*img->height*3, 1, fp);
	fclose(fp);
}

void image_save(struct image *img, const char *file)
{
	FILE *fp = fopen(file, "wb");
	if (!fp)
		perror(file);
	fwrite(img->buf, img->width*img->height*3, 1, fp);
	fclose(fp);
}

void getblock(struct image *img, struct image *block, int i, int j)
{
	
}
