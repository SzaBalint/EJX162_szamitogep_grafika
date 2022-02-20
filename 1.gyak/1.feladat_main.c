#include "brick.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
    Brick brick;
    double area;
    double surface;
    int has_square_suface;
    
    set_brick_data(&brick, 2, 3, 4);
    area = calc_brick_area(&brick);
    surface = calc_brick_surface(&brick);
    has_square_suface = has_square_suface(&brick);
    
    printf("Brick area: %lf\n", area);
    printf("Brick surface: %lf\n",surface);
    //printf("Brick square surface: %i\n",square_surface);
    
    if(has_square_suface==1)
    {
        printf("Brick has square surface!");
    }
    else
    {
        printf("Brick hasn't square surface!");
    }

    return 0;
}
