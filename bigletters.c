#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bigletters.h"

// Define ANSI color codes for foreground and background colors (1-15)
const char *colors_fg[] = {
    "\x1b[30m", "\x1b[31m", "\x1b[32m", "\x1b[33m", "\x1b[34m",
    "\x1b[35m", "\x1b[36m", "\x1b[37m", "\x1b[90m", "\x1b[91m",
    "\x1b[92m", "\x1b[93m", "\x1b[94m", "\x1b[95m", "\x1b[96m", "\x1b[97m"
};

const char *colors_bg[] = {
    "\x1b[40m", "\x1b[41m", "\x1b[42m", "\x1b[43m", "\x1b[44m",
    "\x1b[45m", "\x1b[46m", "\x1b[47m", "\x1b[100m", "\x1b[101m",
    "\x1b[102m", "\x1b[103m", "\x1b[104m", "\x1b[105m", "\x1b[106m", "\x1b[107m"
};

void print_large_text(const char *text, int color_code, int bold, int rainbow, int underline, int inverse) {
    const char *(*letters)[MAX_HEIGHT] = bold ? letters_bold : letters_normal;
    const char *(*numbers)[MAX_HEIGHT] = bold ? numbers_bold : numbers_normal;

    for (int row = 0; row < MAX_HEIGHT - 1; row++) { // Exclude last row for underline handling
        int current_color_code = color_code;

        // If rainbow is enabled, set current_color_code based on the row
        if (rainbow) {
            current_color_code = ((row % 6) + 1); // Cycle through colors 1-6
        }

        // Set the color at the beginning of the line
        const char *color;
        if (inverse) {
            color = colors_bg[current_color_code];
            printf("%s%s", color, current_color_code > 6 ? colors_fg[0] : colors_fg[7]);
        } else {
            color = colors_fg[current_color_code];
            printf("%s", color);
        }

        // Now print all characters in the line without changing color
        for (size_t i = 0; i < strlen(text); i++) {
            char ch = toupper(text[i]);

            if (ch >= 'A' && ch <= 'Z') {
                printf("%s ", letters[ch - 'A'][row]);
            } else if (ch >= '0' && ch <= '9') {
                printf("%s ", numbers[ch - '0'][row]);
            } else {
                printf("       "); // Space for unsupported characters
            }
        }

        // Reset color after each line
        printf("\x1b[0m\n");
    }

    // Handle the last row
    if (underline) {
        int current_color_code = color_code;
        if (rainbow) {
            current_color_code = ((MAX_HEIGHT - 1) % 6) + 1;
        }

        const char *underline_color;
        if (inverse) {
            underline_color = colors_bg[current_color_code];
            printf("%s%s", underline_color, current_color_code > 6 ? colors_fg[0] : colors_fg[7]);
        } else {
            underline_color = colors_fg[current_color_code];
            printf("%s", underline_color);
        }

        for (size_t i = 0; i < strlen(text); i++) {
            printf("▄▄▄▄▄▄▄"); // Underline pattern
        }
        printf("\x1b[0m\n"); // Reset color after underline row
    } else {
        // Print the actual last row from the font if underline is off
        int current_color_code = color_code;
        if (rainbow) {
            current_color_code = ((MAX_HEIGHT - 1) % 6) + 1;
        }

        const char *color;
        if (inverse) {
            color = colors_bg[current_color_code];
            printf("%s%s", color, current_color_code > 6 ? colors_fg[0] : colors_fg[7]);
        } else {
            color = colors_fg[current_color_code];
            printf("%s", color);
        }

        for (size_t i = 0; i < strlen(text); i++) {
            char ch = toupper(text[i]);
            if (ch >= 'A' && ch <= 'Z') {
                printf("%s ", letters[ch - 'A'][MAX_HEIGHT - 1]);
            } else if (ch >= '0' && ch <= '9') {
                printf("%s ", numbers[ch - '0'][MAX_HEIGHT - 1]);
            } else {
                printf("       ");
            }
        }
        printf("\x1b[0m\n"); // Reset color after last line
    }
}


int parse_arguments(int argc, char *argv[], char *text, int *color, int *bold, int *rainbow, int *underline, int *inverse) {
    *color = 7; // Default to white
    *bold = 0; *rainbow = 0; *underline = 0; *inverse = 0; // Default flags
    text[0] = '\0';

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            strncpy(text, argv[++i], MAX_CHARS);
            text[MAX_CHARS] = '\0';
        } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            if (strcmp(argv[i + 1], "r") == 0) {
                *rainbow = 1;
                i++;
            } else {
                *color = atoi(argv[++i]);
            }
        } else if (strcmp(argv[i], "-b") == 0) {
            *bold = 1;
        } else if (strcmp(argv[i], "-u") == 0) {
            *underline = 1;
        } else if (strcmp(argv[i], "-i") == 0) {
            *inverse = 1;
        } else {
            return 0; // Invalid argument
        }
    }

    return 1;
}

int validate_input(const char *text, int color_code, int rainbow) {
    if (strlen(text) == 0 || strlen(text) > MAX_CHARS || (color_code < 1 || color_code > 15) && !rainbow) {
        return 0;
    }
    return 1;
}

void display_usage() {
    printf("Usage: bigletters [-t text] [-c color] [-b] [-u] [-i]\n");
    printf("Options:\n");
    printf("  -t text    Specify the text to display (max %d characters)\n", MAX_CHARS);
    printf("  -c color   Specify the color code (1-15) or 'r' for rainbow\n");
    printf("  -b         Use bold font\n");
    printf("  -u         Underline the text\n");
    printf("  -i         Inverse color (background instead of foreground)\n");
}

int main(int argc, char *argv[]) {
    char text[MAX_CHARS + 1];
    int color, bold, rainbow, underline, inverse;

    if (!parse_arguments(argc, argv, text, &color, &bold, &rainbow, &underline, &inverse) || !validate_input(text, color, rainbow)) {
        display_usage();
        return 1;
    }

    print_large_text(text, color, bold, rainbow, underline, inverse);
    return 0;
}
