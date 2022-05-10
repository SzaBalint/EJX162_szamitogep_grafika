#include <GL/glut.h>
#include <math.h>

#include "camera.h"
#include "world.h"

#define M_PI 3.14159265358979323846

void init_camera(Camera* camera)
{
	camera->position.x = 0.0;
	camera->position.y = 0.0;
	camera->position.z = 5.0;
	camera->rotation.x = 0.0;
	camera->rotation.y = 0.0;
	camera->rotation.z = 180.0;
	camera->speed.x = 0.0;
	camera->speed.y = 0.0;
	camera->speed.z = 0.0;

	world.scene.is_help_on == FALSE;
}
void update_camera(Camera* camera)
{
	double angle;
	double side_angle;
	double time = calc_elapsed_time();

	angle = degree_to_radian(camera->rotation.z);
	side_angle = degree_to_radian(camera->rotation.z + 90.0);

	camera->position.x += cos(angle) * camera->speed.y * time;
	camera->position.y += sin(angle) * camera->speed.y * time;
	camera->position.x += cos(side_angle) * camera->speed.x * time;
	camera->position.y += sin(side_angle) * camera->speed.x * time;
	camera->position.z += camera->speed.z * time;
}

void set_view(const Camera* camera)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
	glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
	glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
	camera->rotation.z += horizontal/CAMERA_SPEED;
	camera->rotation.x += vertical/CAMERA_SPEED;

	if (camera->rotation.z < 0) {
		camera->rotation.z += 360.0;
	}

	if (camera->rotation.z > 360.0) {
		camera->rotation.z -= 360.0;
	}

	if (camera->rotation.x < 0) {
		camera->rotation.x += 360.0;
	}

	if (camera->rotation.x > 360.0) {
		camera->rotation.x -= 360.0;
	}
}

void set_camera_speed(Camera* camera, double speed)
{
	camera->speed.y = speed*MOVE_SPEED;
}

void set_camera_side_speed(Camera* camera, double speed)
{
	camera->speed.x = speed*MOVE_SPEED;
}

int set_camera_vertical_speed(Camera* camera, double speed) {
	camera->speed.z = speed * MOVE_SPEED;
}


double calc_elapsed_time() {
	static int last_frame_time = 0;
	int current_time;
	double elapsed_time;

	current_time = glutGet(GLUT_ELAPSED_TIME);
	elapsed_time = (double)(current_time - last_frame_time) / 1000;
	last_frame_time = current_time;
	return elapsed_time;
}

void show_scope(){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, world.scene.scope_texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-1.66, 0.95, -2);
	glTexCoord2f(1, 0);
	glVertex3f(1.66, 0.95, -2);
	glTexCoord2f(1, 1);
	glVertex3f(1.66, -1, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-1.66, -1, -2);
	glEnd();

	
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void show_help(){
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1, 1, 1);

	glBindTexture(GL_TEXTURE_2D, world.scene.help_texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-1.66, 0.95, -2);
	glTexCoord2f(1, 0);
	glVertex3f(1.66, 0.95, -2);
	glTexCoord2f(1, 1);
	glVertex3f(1.66, -1, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-1.66, -1, -2);
	glEnd();

	
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}