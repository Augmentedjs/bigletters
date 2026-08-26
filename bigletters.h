#ifndef BIGLETTERS_H
#define BIGLETTERS_H

#include <stddef.h>
#include <stdint.h>

#define MAX_WIDTH 8
#define MAX_HEIGHT 8
#define PRINT_HEIGHT (MAX_HEIGHT / 2)
#define MAX_CHARS 20

typedef struct BiglettersGlyph {
    uint8_t rows[MAX_HEIGHT];
} BiglettersGlyph;

typedef struct BiglettersFontPack {
    const char *name;
    const char *description;
    const BiglettersGlyph *glyphs;
    const BiglettersGlyph *replacement;
    const char *attribution;
    const char *license;
} BiglettersFontPack;

extern const char *colors_fg[];
extern const char *colors_bg[];

extern const BiglettersFontPack bigletters_font_cga_thin;
extern const BiglettersFontPack bigletters_font_ega;
extern const BiglettersFontPack bigletters_font_phoenix;

size_t bigletters_font_pack_count(void);
const BiglettersFontPack *bigletters_font_pack_at(size_t index);
const BiglettersFontPack *bigletters_font_pack_find(const char *name);
const BiglettersGlyph *bigletters_font_pack_glyph(
    const BiglettersFontPack *font,
    unsigned char character
);
const char *bigletters_half_block(int top_pixel, int bottom_pixel);

void print_large_text_with_font(
    const char *text,
    int color_code,
    const BiglettersFontPack *font,
    int rainbow,
    int underline,
    int inverse
);
void print_large_text(
    const char *text,
    int color_code,
    int bold,
    int rainbow,
    int underline,
    int inverse
);
int parse_arguments(
    int argc,
    char *argv[],
    char *text,
    int *color,
    const char **font_name,
    int *rainbow,
    int *underline,
    int *inverse,
    int *list_fonts
);
int validate_input(
    const char *text,
    int color_code,
    int rainbow,
    const BiglettersFontPack *font
);
void display_usage(void);
void display_font_packs(void);

#endif
