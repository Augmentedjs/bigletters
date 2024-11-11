#ifndef BIGLETTERS_H
#define BIGLETTERS_H

#define MAX_WIDTH 6
#define MAX_HEIGHT 6
#define MAX_CHARS 20

extern const char *colors[16];

// Define letter patterns for A-Z
extern const char *letters[26][MAX_HEIGHT];

// Define number patterns for 0-9
extern const char *numbers[10][MAX_HEIGHT];

#endif // BIGLETTERS_H
