#ifndef CAMERA_H
#define CAMERA_H

#include "world.h"

#define MOVE_SPEED 1.0  //BIGGER IS FASTER
#define CAMERA_SPEED 5.0 //BIGGER IS SLOWER

//Camera, as a moving point with direction.
typedef struct Camera
{
    struct vec3 position;
    struct vec3 rotation;
    struct vec3 speed;
}Camera;

struct Camera camera;

//Initialize the camera to the start position.
void init_camera(Camera* camera);

// Update the position of the camera.
void update_camera(Camera* camera);

//Apply the camera settings to the view transformation.
void set_view(const Camera* camera);

//Set the horizontal and vertical rotation of the view angle.
void rotate_camera(Camera* camera, double horizontal, double vertical);

//Set the speed of forward and backward motion.
void set_camera_speed(Camera* camera, double speed);

//Set the speed of left and right side steps.
void set_camera_side_speed(Camera* camera, double speed);

//Set the speed of moving up and down. 
int set_camera_vertical_speed(Camera* camera, double speed);

//Calculate the elapsed time for camera updates.
double calc_elapsed_time();

//Show help screen.
void show_help();

//Show scope image.
void show_scope();

#endif /* CAMERA_H */
