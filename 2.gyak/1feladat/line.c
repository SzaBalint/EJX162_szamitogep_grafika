#include "line.h"
#include <SDL2/SDL.h>

void set_line_data(Line* line, double x1, double x2, double y1, double y2)
{
	line->x1 = x1;
	line->x2 = x2;
	line->y1 = y1;
	line->y2 = y2;
}

void draw_line(Line* line, SDL_Renderer* renderer)
{
	SDL_RenderDrawLine(renderer, line->x1, line->x2, line->y1, line->y2);
	SDL_RenderPresent(renderer);
}
