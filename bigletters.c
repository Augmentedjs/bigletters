#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bigletters.h"

#ifndef PACKAGE_VERSION
#define PACKAGE_VERSION "development"
#endif

const char *colors_fg[] = {
    "\x1b[30m", "\x1b[31m", "\x1b[32m", "\x1b[33m", "\x1b[34m",
    "\x1b[35m", "\x1b[36m", "\x1b[37m", "\x1b[90m", "\x1b[91m",
    "\x1b[92m", "\x1b[93m", "\x1b[94m", "\x1b[95m", "\x1b[96m",
    "\x1b[97m"
};

const char *colors_bg[] = {
    "\x1b[40m", "\x1b[41m", "\x1b[42m", "\x1b[43m", "\x1b[44m",
    "\x1b[45m", "\x1b[46m", "\x1b[47m", "\x1b[100m", "\x1b[101m",
    "\x1b[102m", "\x1b[103m", "\x1b[104m", "\x1b[105m", "\x1b[106m",
    "\x1b[107m"
};

static void set_row_color(int color_code, int inverse)
{
    if (inverse) {
        printf(
            "%s%s",
            colors_bg[color_code],
            color_code > 6 ? colors_fg[0] : colors_fg[7]
        );
        return;
    }

    printf("%s", colors_fg[color_code]);
}

static int row_color(int color_code, int rainbow, int row)
{
    if (rainbow) {
        return (row % 6) + 1;
    }

    return color_code;
}

static void print_half_block_glyph_row(
    const BiglettersGlyph *glyph,
    int print_row
)
{
    uint8_t top = glyph->rows[print_row * 2];
    uint8_t bottom = glyph->rows[print_row * 2 + 1];

    for (int column = 0; column < MAX_WIDTH; column++) {
        uint8_t mask = (uint8_t)(0x80U >> column);
        fputs(bigletters_half_block(top & mask, bottom & mask), stdout);
    }
}

static void print_full_block_glyph_row(
    const BiglettersGlyph *glyph,
    int print_row
)
{
    uint8_t pixels = glyph->rows[print_row];

    for (int column = 0; column < MAX_WIDTH; column++) {
        uint8_t mask = (uint8_t)(0x80U >> column);
        fputs(pixels & mask ? "██" : "  ", stdout);
    }
}

static void print_glyph_row(
    const BiglettersGlyph *glyph,
    int print_row,
    BiglettersRenderMode render_mode
)
{
    if (render_mode == BIGLETTERS_RENDER_FULL_BLOCKS) {
        print_full_block_glyph_row(glyph, print_row);
        return;
    }

    print_half_block_glyph_row(glyph, print_row);
}

static int render_height(BiglettersRenderMode render_mode)
{
    return render_mode == BIGLETTERS_RENDER_FULL_BLOCKS
        ? MAX_HEIGHT
        : PRINT_HEIGHT;
}

static void set_render_color(
    int color_code,
    int rainbow,
    int row,
    const BiglettersRgbColor *rgb_color,
    int inverse
)
{
    char escape[BIGLETTERS_ANSI_COLOR_MAX];

    if (rgb_color != NULL) {
        if (bigletters_format_rgb_escape(
            escape,
            sizeof(escape),
            rgb_color,
            inverse
        )) {
            fputs(escape, stdout);
        }
        return;
    }

    set_row_color(row_color(color_code, rainbow, row), inverse);
}

static void print_large_text_with_color(
    const char *text,
    int color_code,
    const BiglettersRgbColor *rgb_color,
    const BiglettersFontPack *font,
    int rainbow,
    int underline,
    int inverse,
    int slant,
    BiglettersRenderMode render_mode
)
{
    size_t text_length = strlen(text);
    int output_height = render_height(render_mode);

    for (int row = 0; row < output_height; row++) {
        int slant_offset = slant ? output_height - row - 1 : 0;

        for (int column = 0; column < slant_offset; column++) {
            putchar(' ');
        }
        set_render_color(
            color_code,
            rainbow,
            row,
            rgb_color,
            inverse
        );

        for (size_t index = 0; index < text_length; index++) {
            const BiglettersGlyph *glyph = bigletters_font_pack_glyph(
                font,
                (unsigned char)text[index]
            );
            print_glyph_row(glyph, row, render_mode);
        }

        printf("\x1b[0m\n");
    }

    if (underline) {
        set_render_color(
            color_code,
            rainbow,
            output_height,
            rgb_color,
            inverse
        );
        for (size_t index = 0; index < text_length; index++) {
            if (render_mode == BIGLETTERS_RENDER_FULL_BLOCKS) {
                printf("████████████████");
            } else {
                printf("▄▄▄▄▄▄▄▄");
            }
        }
        printf("\x1b[0m\n");
    }
}

void print_large_text_with_font(
    const char *text,
    int color_code,
    const BiglettersFontPack *font,
    int rainbow,
    int underline,
    int inverse,
    int slant,
    BiglettersRenderMode render_mode
)
{
    print_large_text_with_color(
        text,
        color_code,
        NULL,
        font,
        rainbow,
        underline,
        inverse,
        slant,
        render_mode
    );
}

void print_large_text_with_rgb(
    const char *text,
    const BiglettersRgbColor *color,
    const BiglettersFontPack *font,
    int underline,
    int inverse,
    int slant,
    BiglettersRenderMode render_mode
)
{
    print_large_text_with_color(
        text,
        0,
        color,
        font,
        0,
        underline,
        inverse,
        slant,
        render_mode
    );
}

void print_large_text(
    const char *text,
    int color_code,
    int bold,
    int rainbow,
    int underline,
    int inverse
)
{
    const BiglettersFontPack *font = bold
        ? &bigletters_font_ega
        : &bigletters_font_cga_thin;

    print_large_text_with_font(
        text,
        color_code,
        font,
        rainbow,
        underline,
        inverse,
        0,
        BIGLETTERS_RENDER_HALF_BLOCKS
    );
}

static int option_matches(
    const char *argument,
    const char *short_name,
    const char *long_name
)
{
    return strcmp(argument, short_name) == 0
        || strcmp(argument, long_name) == 0;
}

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
    BiglettersRenderMode *render_mode,
    int *show_version,
    int *list_fonts
)
{
    *color = 7;
    rgb_color->red = 0;
    rgb_color->green = 0;
    rgb_color->blue = 0;
    *use_rgb = 0;
    *font_name = "cga-thin";
    *rainbow = 0;
    *underline = 0;
    *inverse = 0;
    *slant = 0;
    *render_mode = BIGLETTERS_RENDER_HALF_BLOCKS;
    *show_version = 0;
    *list_fonts = 0;
    text[0] = '\0';

    for (int index = 1; index < argc; index++) {
        if (option_matches(argv[index], "-t", "--text")
            && index + 1 < argc) {
            strncpy(text, argv[++index], MAX_CHARS);
            text[MAX_CHARS] = '\0';
        } else if (option_matches(argv[index], "-c", "--color")
            && index + 1 < argc) {
            if (strcmp(argv[index + 1], "r") == 0) {
                *rainbow = 1;
                index++;
            } else {
                *color = atoi(argv[++index]);
            }
        } else if (option_matches(argv[index], "-r", "--rgb")
            && index + 1 < argc) {
            if (!bigletters_parse_rgb(argv[++index], rgb_color)) {
                return 0;
            }
            *use_rgb = 1;
        } else if (option_matches(argv[index], "-f", "--font")
            && index + 1 < argc
        ) {
            *font_name = argv[++index];
        } else if (option_matches(argv[index], "-b", "--bold")) {
            *font_name = "ega";
        } else if (option_matches(argv[index], "-u", "--underline")) {
            *underline = 1;
        } else if (option_matches(argv[index], "-i", "--inverse")) {
            *inverse = 1;
        } else if (option_matches(argv[index], "-s", "--slant")) {
            *slant = 1;
        } else if (option_matches(argv[index], "-x", "--extra-large")) {
            *render_mode = BIGLETTERS_RENDER_FULL_BLOCKS;
        } else if (option_matches(argv[index], "-v", "--version")) {
            *show_version = 1;
        } else if (strcmp(argv[index], "--list-fonts") == 0) {
            *list_fonts = 1;
        } else {
            return 0;
        }
    }

    return 1;
}

int validate_input(
    const char *text,
    int color_code,
    int rainbow,
    int use_rgb,
    const BiglettersFontPack *font
)
{
    size_t text_length = strlen(text);

    return text_length > 0
        && text_length <= MAX_CHARS
        && (use_rgb || rainbow || (color_code >= 1 && color_code <= 15))
        && font != NULL;
}

void display_usage(void)
{
    printf(
        "Usage: bigletters -t text [-c color | -r R,G,B] "
        "[-f font] [-b] [-s] [-x] [-u] [-i] [-v]\n"
    );
    printf("Options:\n");
    printf(
        "  -t, --text text       Text to display (max %d bytes)\n",
        MAX_CHARS
    );
    printf("  -c, --color color     Color 1-15, or 'r' for rainbow\n");
    printf("  -r, --rgb R,G,B       True color; takes precedence over -c\n");
    printf("  -f, --font name       Select a named font pack\n");
    printf("      --list-fonts      List available font packs\n");
    printf("  -b, --bold            Use the bold EGA face\n");
    printf("  -s, --slant           Slant without changing glyph data\n");
    printf("  -x, --extra-large     Double size using full blocks\n");
    printf("  -u, --underline       Underline the text\n");
    printf("  -i, --inverse         Use inverse background color\n");
    printf("  -v, --version         Print the BigLetters version\n");
}

void display_version(void)
{
    printf("bigletters %s\n", PACKAGE_VERSION);
}

void display_font_packs(void)
{
    for (size_t index = 0; index < bigletters_font_pack_count(); index++) {
        const BiglettersFontPack *font = bigletters_font_pack_at(index);
        printf("%-8s %s\n", font->name, font->description);
    }
}

int main(int argc, char *argv[])
{
    char text[MAX_CHARS + 1];
    const char *font_name;
    const BiglettersFontPack *font;
    BiglettersRgbColor rgb_color;
    int color;
    int use_rgb;
    int rainbow;
    int underline;
    int inverse;
    int slant;
    BiglettersRenderMode render_mode;
    int show_version;
    int list_fonts;

    if (!parse_arguments(
        argc,
        argv,
        text,
        &color,
        &rgb_color,
        &use_rgb,
        &font_name,
        &rainbow,
        &underline,
        &inverse,
        &slant,
        &render_mode,
        &show_version,
        &list_fonts
    )) {
        display_usage();
        return 1;
    }

    if (show_version) {
        display_version();
        return 0;
    }

    if (list_fonts) {
        display_font_packs();
        return 0;
    }

    font = bigletters_font_pack_find(font_name);
    if (!validate_input(text, color, rainbow, use_rgb, font)) {
        display_usage();
        if (font == NULL) {
            fprintf(stderr, "Unknown font pack: %s\n", font_name);
            display_font_packs();
        }
        return 1;
    }

    if (use_rgb) {
        print_large_text_with_rgb(
            text,
            &rgb_color,
            font,
            underline,
            inverse,
            slant,
            render_mode
        );
    } else {
        print_large_text_with_font(
            text,
            color,
            font,
            rainbow,
            underline,
            inverse,
            slant,
            render_mode
        );
    }
    return 0;
}
