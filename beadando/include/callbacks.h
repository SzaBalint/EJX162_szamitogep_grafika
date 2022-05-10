#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "camera.h"
#include "world.h"

//Handles 'F1' keypress.
void special_key_handler(int key, int x, int y);

//Call after windows resizing.
void reshape(GLsizei width, GLsizei height);

//Call when need to display the graphical content.
void display();

//Call after mouse button event.
void mouse_handler(int button, int state, int x, int y);

//Call after mouse event.
void motion_handler(int x, int y);

//Call after keyboard event.
void key_handler(unsigned char key, int x, int y);

//Call after keyboard release event.
void key_up_handler(unsigned char key, int x, int y);

//Call when there is no other event.
void idle();

#endif /* CALLBACKS_H */