#include <string.h>

#include "bigletters.h"

static const BiglettersFontPack *font_packs[] = {
    &bigletters_font_normal,
    &bigletters_font_bold
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

    return NULL;
}

static int symbol_index(unsigned char character)
{
    if (character >= ' ' && character <= '/') {
        return character - ' ';
    }
    if (character >= ':' && character <= '@') {
        return 16 + character - ':';
    }
    if (character >= '[' && character <= '`') {
        return 23 + character - '[';
    }
    if (character >= '{' && character <= '~') {
        return 29 + character - '{';
    }

    return -1;
}

const BiglettersGlyph *bigletters_font_pack_glyph(
    const BiglettersFontPack *font,
    unsigned char character
)
{
    int index;

    if (font == NULL) {
        return &bigletters_replacement_glyph;
    }
    if (character >= 'A' && character <= 'Z') {
        return &font->uppercase[character - 'A'];
    }
    if (character >= 'a' && character <= 'z') {
        return &font->lowercase[character - 'a'];
    }
    if (character >= '0' && character <= '9') {
        return &font->numbers[character - '0'];
    }

    index = symbol_index(character);
    if (index >= 0) {
        return &font->symbols[index];
    }

    return font->replacement;
}
