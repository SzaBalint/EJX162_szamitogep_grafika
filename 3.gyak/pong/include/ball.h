#ifndef BALL_H
#define BALL_H

/**
 * Ball position and speed
 */
typedef struct Ball
{
    float x;
    float y;
    float radius;
    float speed_x;
    float speed_y;
    float increase_speed;
} Ball;

/**
 * Move the ball to the given position.
 */
void init_ball(Ball* ball, float x, float y);

/**
 * Update the ball.
 * @param time elapsed time in seconds.
 */
void update_ball(Ball* ball, double time);

/**
 * Render the ball.
 */
void render_ball(Ball* ball);

void increase_ball_size(Ball* ball, int radius);

void decrease_ball_size(Ball* ball, int radius);

void set_ball_position(Ball* ball, float x, float y);

#endif /* BALL_H */