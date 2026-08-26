#include <stdio.h>
#include <string.h>

#include "bigletters.h"

static size_t utf8_columns(const char *text)
{
    size_t columns = 0;

    for (size_t index = 0; text[index] != '\0'; index++) {
        unsigned char byte = (unsigned char)text[index];
        if ((byte & 0xc0) != 0x80) {
            columns++;
        }
    }

    return columns;
}

static int check_font(const BiglettersFontPack *font)
{
    for (int character = ' '; character <= '~'; character++) {
        const BiglettersGlyph *glyph = bigletters_font_pack_glyph(
            font,
            (unsigned char)character
        );

        if (glyph == NULL) {
            fprintf(stderr, "%s: missing glyph for ASCII %d\n", font->name, character);
            return 0;
        }
        if (glyph == font->replacement) {
            fprintf(
                stderr,
                "%s: printable ASCII %d resolved to the replacement glyph\n",
                font->name,
                character
            );
            return 0;
        }

        for (int row = 0; row < MAX_HEIGHT; row++) {
            if (glyph->rows[row] == NULL) {
                fprintf(
                    stderr,
                    "%s: null row %d for ASCII %d\n",
                    font->name,
                    row,
                    character
                );
                return 0;
            }
            if (utf8_columns(glyph->rows[row]) != MAX_WIDTH) {
                fprintf(
                    stderr,
                    "%s: row %d for ASCII %d is not %d columns: '%s'\n",
                    font->name,
                    row,
                    character,
                    MAX_WIDTH,
                    glyph->rows[row]
                );
                return 0;
            }
        }
    }

    return 1;
}

static int glyphs_equal(
    const BiglettersGlyph *left,
    const BiglettersGlyph *right
)
{
    for (int row = 0; row < MAX_HEIGHT; row++) {
        if (strcmp(left->rows[row], right->rows[row]) != 0) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    if (bigletters_font_pack_count() != 2) {
        fprintf(stderr, "expected two built-in font packs\n");
        return 1;
    }

    for (size_t index = 0; index < bigletters_font_pack_count(); index++) {
        const BiglettersFontPack *font = bigletters_font_pack_at(index);
        if (font == NULL || !check_font(font)) {
            return 1;
        }
    }

    if (bigletters_font_pack_at(bigletters_font_pack_count()) != NULL) {
        fprintf(stderr, "out-of-range font pack lookup should return null\n");
        return 1;
    }
    if (bigletters_font_pack_find("missing") != NULL) {
        fprintf(stderr, "unknown font pack lookup should return null\n");
        return 1;
    }
    if (bigletters_font_pack_find("normal") != &bigletters_font_normal
        || bigletters_font_pack_find("bold") != &bigletters_font_bold) {
        fprintf(stderr, "font pack lookup returned the wrong built-in pack\n");
        return 1;
    }
    if (bigletters_font_pack_glyph(&bigletters_font_normal, 0) !=
        &bigletters_replacement_glyph) {
        fprintf(stderr, "unsupported bytes should use the replacement glyph\n");
        return 1;
    }
    if (glyphs_equal(
        bigletters_font_pack_glyph(&bigletters_font_normal, 'A'),
        bigletters_font_pack_glyph(&bigletters_font_normal, 'a')
    )) {
        fprintf(stderr, "lowercase glyphs must remain distinct from uppercase\n");
        return 1;
    }

    return 0;
}
