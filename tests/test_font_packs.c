#include <stdio.h>
#include <string.h>

#include "bigletters.h"

static int glyph_has_pixels(const BiglettersGlyph *glyph)
{
    for (int row = 0; row < MAX_HEIGHT; row++) {
        if (glyph->rows[row] != 0) {
            return 1;
        }
    }

    return 0;
}

static int check_font(const BiglettersFontPack *font)
{
    if (font == NULL
        || font->name == NULL
        || font->description == NULL
        || font->glyphs == NULL
        || font->replacement == NULL
        || font->attribution == NULL
        || font->license == NULL) {
        fprintf(stderr, "font pack metadata is incomplete\n");
        return 0;
    }

    for (int character = ' '; character <= '~'; character++) {
        const BiglettersGlyph *glyph = bigletters_font_pack_glyph(
            font,
            (unsigned char)character
        );

        if (glyph != &font->glyphs[character - ' ']) {
            fprintf(stderr, "%s: incorrect lookup for ASCII %d\n", font->name, character);
            return 0;
        }
        if (character == ' ' && glyph_has_pixels(glyph)) {
            fprintf(stderr, "%s: space glyph is not empty\n", font->name);
            return 0;
        }
        if (character != ' ' && !glyph_has_pixels(glyph)) {
            fprintf(stderr, "%s: ASCII %d has no pixels\n", font->name, character);
            return 0;
        }
    }

    if (font->replacement != &font->glyphs['?' - ' ']) {
        fprintf(stderr, "%s: replacement is not the question mark\n", font->name);
        return 0;
    }
    if (bigletters_font_pack_glyph(font, 0) != font->replacement
        || bigletters_font_pack_glyph(font, 0xff) != font->replacement) {
        fprintf(stderr, "%s: unsupported input does not use replacement\n", font->name);
        return 0;
    }

    return 1;
}

static int check_reference_glyphs(void)
{
    static const uint8_t cga_a[MAX_HEIGHT] = {
        0x18, 0x24, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x00
    };
    static const uint8_t ega_a[MAX_HEIGHT] = {
        0x30, 0x78, 0xcc, 0xcc, 0xfc, 0xcc, 0xcc, 0x00
    };
    static const uint8_t phoenix_a[MAX_HEIGHT] = {
        0x7c, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6, 0xc6, 0x00
    };

    return memcmp(
        bigletters_font_pack_glyph(&bigletters_font_cga_thin, 'A')->rows,
        cga_a,
        sizeof(cga_a)
    ) == 0
        && memcmp(
            bigletters_font_pack_glyph(&bigletters_font_ega, 'A')->rows,
            ega_a,
            sizeof(ega_a)
        ) == 0
        && memcmp(
            bigletters_font_pack_glyph(&bigletters_font_phoenix, 'A')->rows,
            phoenix_a,
            sizeof(phoenix_a)
        ) == 0;
}

static int check_half_blocks(void)
{
    return strcmp(bigletters_half_block(0, 0), " ") == 0
        && strcmp(bigletters_half_block(1, 0), "▀") == 0
        && strcmp(bigletters_half_block(0, 1), "▄") == 0
        && strcmp(bigletters_half_block(1, 1), "█") == 0;
}

static uint32_t font_hash(const BiglettersFontPack *font)
{
    uint32_t hash = UINT32_C(2166136261);

    for (int character = ' '; character <= '~'; character++) {
        const BiglettersGlyph *glyph = bigletters_font_pack_glyph(
            font,
            (unsigned char)character
        );

        for (int row = 0; row < MAX_HEIGHT; row++) {
            hash ^= glyph->rows[row];
            hash *= UINT32_C(16777619);
        }
    }

    return hash;
}

int main(void)
{
    if (MAX_WIDTH != 8
        || MAX_HEIGHT != 8
        || PRINT_HEIGHT != 4
        || sizeof(BiglettersGlyph) != 8) {
        fprintf(stderr, "font geometry is not 8x8 packed into four rows\n");
        return 1;
    }
    if (bigletters_font_pack_count() != 3) {
        fprintf(stderr, "expected three built-in font packs\n");
        return 1;
    }

    for (size_t index = 0; index < bigletters_font_pack_count(); index++) {
        if (!check_font(bigletters_font_pack_at(index))) {
            return 1;
        }
    }

    if (bigletters_font_pack_at(bigletters_font_pack_count()) != NULL
        || bigletters_font_pack_find("missing") != NULL
        || bigletters_font_pack_glyph(NULL, 'A') != NULL) {
        fprintf(stderr, "invalid lookup should return null\n");
        return 1;
    }
    if (bigletters_font_pack_find("ega") != &bigletters_font_ega
        || bigletters_font_pack_find("phoenix") != &bigletters_font_phoenix
        || bigletters_font_pack_find("cga-thin") != &bigletters_font_cga_thin
        || bigletters_font_pack_find("normal") != &bigletters_font_cga_thin
        || bigletters_font_pack_find("bold") != &bigletters_font_ega) {
        fprintf(stderr, "font pack name or compatibility lookup failed\n");
        return 1;
    }
    if (memcmp(
        bigletters_font_ega.glyphs,
        bigletters_font_phoenix.glyphs,
        sizeof(BiglettersGlyph) * 95
    ) == 0) {
        fprintf(stderr, "EGA and Phoenix packs should remain distinct\n");
        return 1;
    }
    if (!check_reference_glyphs() || !check_half_blocks()) {
        fprintf(stderr, "reference raster or half-block packing changed\n");
        return 1;
    }
    if (font_hash(&bigletters_font_cga_thin) != UINT32_C(0x82eaa318)
        || font_hash(&bigletters_font_ega) != UINT32_C(0xabe4c20d)
        || font_hash(&bigletters_font_phoenix) != UINT32_C(0xea237466)) {
        fprintf(stderr, "generated legacy font data hash changed\n");
        return 1;
    }

    return 0;
}
