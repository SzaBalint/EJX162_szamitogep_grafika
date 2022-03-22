#ifndef COLOR_H
#define COLOR_H

typedef struct Color{
    int r;
    int g;
    int b;
    int a;
} Color;

void set_color(Color* color, int r, int b, int g, int a);
#endif
