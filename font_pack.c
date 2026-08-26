#include <string.h>

#include "bigletters.h"

static const BiglettersFontPack *font_packs[] = {
    &bigletters_font_cga_thin,
    &bigletters_font_ega,
    &bigletters_font_phoenix
};

size_t bigletters_font_pack_count(void)
{
    return sizeof(font_packs) / sizeof(font_packs[0]);
}

const BiglettersFontPack *bigletters_font_pack_at(size_t index)
{
    if (index >= bigletters_font_pack_count()) {
        return NULL;
    }

    return font_packs[index];
}

const BiglettersFontPack *bigletters_font_pack_find(const char *name)
{
    if (name == NULL) {
        return NULL;
    }

    for (size_t index = 0; index < bigletters_font_pack_count(); index++) {
        if (strcmp(font_packs[index]->name, name) == 0) {
            return font_packs[index];
        }
    }

    if (strcmp(name, "normal") == 0) {
        return &bigletters_font_cga_thin;
    }
    if (strcmp(name, "bold") == 0) {
        return &bigletters_font_ega;
    }

    return NULL;
}

const BiglettersGlyph *bigletters_font_pack_glyph(
    const BiglettersFontPack *font,
    unsigned char character
)
{
    if (font == NULL) {
        return NULL;
    }
    if (character >= ' ' && character <= '~') {
        return &font->glyphs[character - ' '];
    }

    return font->replacement;
}

const char *bigletters_half_block(int top_pixel, int bottom_pixel)
{
    if (top_pixel) {
        return bottom_pixel ? "█" : "▀";
    }

    return bottom_pixel ? "▄" : " ";
}
