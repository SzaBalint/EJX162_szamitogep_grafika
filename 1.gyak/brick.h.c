#ifndef BRICK_H
#define BRICK_H

/**
 * Data of a brick object in Descartes coordinate system
 */
typedef struct Brick
{
    double x;
    double y;
    double z;
} Brick;

/**
 * Set the data of the brick
 */
void set_brick_data(Brick* brick, double x, double y, double z);

/**
 * Calculate the area of the brick.
 */
double calc_brick_area(const Brick* brick);
double calc_brick_surface(const Brick* brick);
void has_square_surface(const Brick* brick);

#endif // BRICK_H

