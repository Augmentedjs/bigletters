#include <stdio.h>

#include "bigletters.h"

static int parse_rgb_component(
    const char **cursor,
    uint8_t *component,
    char terminator
)
{
    unsigned int value = 0;
    int digits = 0;

    while (**cursor >= '0' && **cursor <= '9') {
        value = value * 10U + (unsigned int)(**cursor - '0');
        if (value > 255U) {
            return 0;
        }
        (*cursor)++;
        digits++;
    }

    if (digits == 0 || **cursor != terminator) {
        return 0;
    }

    *component = (uint8_t)value;
    if (terminator != '\0') {
        (*cursor)++;
    }
    return 1;
}

int bigletters_parse_rgb(
    const char *text,
    BiglettersRgbColor *color
)
{
    const char *cursor = text;
    BiglettersRgbColor parsed;

    if (text == NULL || color == NULL) {
        return 0;
    }
    if (!parse_rgb_component(&cursor, &parsed.red, ',')) {
        return 0;
    }
    if (!parse_rgb_component(&cursor, &parsed.green, ',')) {
        return 0;
    }
    if (!parse_rgb_component(&cursor, &parsed.blue, '\0')) {
        return 0;
    }

    *color = parsed;
    return 1;
}

int bigletters_format_rgb_escape(
    char *buffer,
    size_t buffer_size,
    const BiglettersRgbColor *color,
    int inverse
)
{
    int length;

    if (buffer == NULL || buffer_size == 0 || color == NULL) {
        return 0;
    }

    if (inverse) {
        unsigned int luminance = 299U * color->red
            + 587U * color->green
            + 114U * color->blue;
        int foreground = luminance >= 128000U ? 30 : 97;

        length = snprintf(
            buffer,
            buffer_size,
            "\x1b[48;2;%u;%u;%um\x1b[%dm",
            color->red,
            color->green,
            color->blue,
            foreground
        );
    } else {
        length = snprintf(
            buffer,
            buffer_size,
            "\x1b[38;2;%u;%u;%um",
            color->red,
            color->green,
            color->blue
        );
    }

    return length >= 0 && (size_t)length < buffer_size;
}
