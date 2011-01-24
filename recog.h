#ifndef _RECOG_H
#define _RECOG_H

#include "image.h"

int recognize_font(struct image *block, struct image *font);
void recognize(struct image *image, struct image *font, struct Glyph *glyph);

#endif