#include <stdbool.h>
#include <stdio.h>

#include "line.h"
#include "color.h"
#include <SDL2/SDL.h>

int main(int argc, char* argv[])
{
    Color color;
    set_color(&color, 0, 180, 321, SDL_ALPHA_OPAQUE);
    Line line;
    set_line_data(&line, 10, 10, 200, 200);
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;
			
		while (!done) {
        SDL_Event event;
				SDL_SetRenderDrawColor(renderer, color.r, color.b, color.g, color.a);
				draw_line(&line,renderer);

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
                    }
                }
            }
        }

		if (renderer) {
            SDL_DestroyRenderer(renderer);
		}
		if (window) {
            SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();

	return 0;
}
