#ifndef _RECOG_H
#define _RECOG_H

#include "image.h"

void recognize_init();
int recognize_font(struct image *block, struct image *font, int range);
void recognize(struct image *image, struct image *font, struct Glyph *glyph, int range);

#endif
