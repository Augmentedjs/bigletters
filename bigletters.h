#ifndef BIGLETTERS_H
#define BIGLETTERS_H

#include <stddef.h>
#include <stdint.h>

#define MAX_WIDTH 8
#define MAX_HEIGHT 8
#define PRINT_HEIGHT (MAX_HEIGHT / 2)
#define MAX_CHARS 20
#define BIGLETTERS_ANSI_COLOR_MAX 48

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

typedef struct BiglettersRgbColor {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} BiglettersRgbColor;

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
int bigletters_parse_rgb(
    const char *text,
    BiglettersRgbColor *color
);
int bigletters_format_rgb_escape(
    char *buffer,
    size_t buffer_size,
    const BiglettersRgbColor *color,
    int inverse
);

void print_large_text_with_font(
    const char *text,
    int color_code,
    const BiglettersFontPack *font,
    int rainbow,
    int underline,
    int inverse,
    int slant
);
void print_large_text_with_rgb(
    const char *text,
    const BiglettersRgbColor *color,
    const BiglettersFontPack *font,
    int underline,
    int inverse,
    int slant
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
    BiglettersRgbColor *rgb_color,
    int *use_rgb,
    const char **font_name,
    int *rainbow,
    int *underline,
    int *inverse,
    int *slant,
    int *list_fonts
);
int validate_input(
    const char *text,
    int color_code,
    int rainbow,
    int use_rgb,
    const BiglettersFontPack *font
);
void display_usage(void);
void display_font_packs(void);

#endif
