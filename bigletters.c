#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bigletters.h"

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

static void print_glyph_row(const BiglettersGlyph *glyph, int print_row)
{
    uint8_t top = glyph->rows[print_row * 2];
    uint8_t bottom = glyph->rows[print_row * 2 + 1];

    for (int column = 0; column < MAX_WIDTH; column++) {
        uint8_t mask = (uint8_t)(0x80U >> column);
        fputs(bigletters_half_block(top & mask, bottom & mask), stdout);
    }
}

void print_large_text_with_font(
    const char *text,
    int color_code,
    const BiglettersFontPack *font,
    int rainbow,
    int underline,
    int inverse
)
{
    size_t text_length = strlen(text);

    for (int row = 0; row < PRINT_HEIGHT; row++) {
        set_row_color(row_color(color_code, rainbow, row), inverse);

        for (size_t index = 0; index < text_length; index++) {
            const BiglettersGlyph *glyph = bigletters_font_pack_glyph(
                font,
                (unsigned char)text[index]
            );
            print_glyph_row(glyph, row);
        }

        printf("\x1b[0m\n");
    }

    if (underline) {
        set_row_color(
            row_color(color_code, rainbow, PRINT_HEIGHT),
            inverse
        );
        for (size_t index = 0; index < text_length; index++) {
            printf("▄▄▄▄▄▄▄▄");
        }
        printf("\x1b[0m\n");
    }
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
        inverse
    );
}

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
)
{
    *color = 7;
    *font_name = "cga-thin";
    *rainbow = 0;
    *underline = 0;
    *inverse = 0;
    *list_fonts = 0;
    text[0] = '\0';

    for (int index = 1; index < argc; index++) {
        if (strcmp(argv[index], "-t") == 0 && index + 1 < argc) {
            strncpy(text, argv[++index], MAX_CHARS);
            text[MAX_CHARS] = '\0';
        } else if (strcmp(argv[index], "-c") == 0 && index + 1 < argc) {
            if (strcmp(argv[index + 1], "r") == 0) {
                *rainbow = 1;
                index++;
            } else {
                *color = atoi(argv[++index]);
            }
        } else if (
            (strcmp(argv[index], "-f") == 0
                || strcmp(argv[index], "--font") == 0)
            && index + 1 < argc
        ) {
            *font_name = argv[++index];
        } else if (strcmp(argv[index], "-b") == 0) {
            *font_name = "ega";
        } else if (strcmp(argv[index], "-u") == 0) {
            *underline = 1;
        } else if (strcmp(argv[index], "-i") == 0) {
            *inverse = 1;
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
    const BiglettersFontPack *font
)
{
    size_t text_length = strlen(text);

    return text_length > 0
        && text_length <= MAX_CHARS
        && (rainbow || (color_code >= 1 && color_code <= 15))
        && font != NULL;
}

void display_usage(void)
{
    printf("Usage: bigletters -t text [-c color] [-f font] [-b] [-u] [-i]\n");
    printf("Options:\n");
    printf("  -t text       Text to display (max %d bytes)\n", MAX_CHARS);
    printf("  -c color      Color code 1-15, or 'r' for rainbow\n");
    printf("  -f, --font    Select a named font pack\n");
    printf("  --list-fonts  List available font packs\n");
    printf("  -b            Use the bold EGA face\n");
    printf("  -u            Underline the text\n");
    printf("  -i            Use inverse background color\n");
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
    int color;
    int rainbow;
    int underline;
    int inverse;
    int list_fonts;

    if (!parse_arguments(
        argc,
        argv,
        text,
        &color,
        &font_name,
        &rainbow,
        &underline,
        &inverse,
        &list_fonts
    )) {
        display_usage();
        return 1;
    }

    if (list_fonts) {
        display_font_packs();
        return 0;
    }

    font = bigletters_font_pack_find(font_name);
    if (!validate_input(text, color, rainbow, font)) {
        display_usage();
        if (font == NULL) {
            fprintf(stderr, "Unknown font pack: %s\n", font_name);
            display_font_packs();
        }
        return 1;
    }

    print_large_text_with_font(
        text,
        color,
        font,
        rainbow,
        underline,
        inverse
    );
    return 0;
}
