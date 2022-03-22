#ifndef LINE_H
#define LINE_H
#include <SDL2/SDL.h>

typedef struct Line
{
	double x1;
	double x2;
	double y1;
	double y2;
} Line;

void draw_line(Line* line, SDL_Renderer* renderer);

void set_line_data(Line* line, double x1, double x2, double y1, double y2);
#endif // LINE_H
