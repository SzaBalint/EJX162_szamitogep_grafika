#include "ball.h"

#include <GL/gl.h>

#include <math.h>

void init_ball(Ball* ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
    ball->radius = 50;
    ball->speed_x = 200;
    ball->speed_y = 200;
    ball->increase_speed =0;
}

void set_ball_position(Ball* ball,float x, float y){
    ball->x = x;
    ball->y = y;
}

void incrise_ball_size(Ball* ball, int radius)
{
     ball->radius += radius;
}

void decrease_ball_size(Ball* ball,int radius)
{
    ball->radius -=radius;
}

void update_ball(Ball* ball, double time)
{
    ball->x += ball->speed_x * time;
    ball->y += ball->speed_y * time;
    ball->radius += ball->increase_speed*time;
}

void render_ball(Ball* ball)
{
    double angle;
    double x;
    double y;

    glPushMatrix();
    glTranslatef(ball->x, ball->y, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.9, 0.8);
    glVertex2f(0, 0);
    angle = 0;
    while (angle < 2.0 * M_PI + 1) {
        x = cos(angle) * ball->radius;
        y = sin(angle) * ball->radius;
        glVertex2f(x, y);
        angle += 0.8;
    }
    glEnd();
    glPopMatrix();
}
