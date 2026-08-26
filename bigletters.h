#ifndef BIGLETTERS_H
#define BIGLETTERS_H

#include <stddef.h>

#define MAX_WIDTH 6
#define MAX_HEIGHT 6
#define MAX_CHARS 20

typedef struct BiglettersGlyph {
    const char *rows[MAX_HEIGHT];
} BiglettersGlyph;

typedef struct BiglettersFontPack {
    const char *name;
    const char *description;
    const BiglettersGlyph *uppercase;
    const BiglettersGlyph *lowercase;
    const BiglettersGlyph *numbers;
    const BiglettersGlyph *symbols;
    const BiglettersGlyph *replacement;
} BiglettersFontPack;

extern const char *colors_fg[];
extern const char *colors_bg[];

extern const BiglettersFontPack bigletters_font_normal;
extern const BiglettersFontPack bigletters_font_bold;
extern const BiglettersGlyph bigletters_ascii_symbols[33];
extern const BiglettersGlyph bigletters_replacement_glyph;

size_t bigletters_font_pack_count(void);
const BiglettersFontPack *bigletters_font_pack_at(size_t index);
const BiglettersFontPack *bigletters_font_pack_find(const char *name);
const BiglettersGlyph *bigletters_font_pack_glyph(
    const BiglettersFontPack *font,
    unsigned char character
);

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
