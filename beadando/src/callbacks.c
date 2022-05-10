#include "callbacks.h"
#include "world.h"

#define VIEWPORT_RATIO (16.0 / 9.0)
#define VIEWPORT_ASPECT 50.0

struct {
	int x;
	int y;
} mouse_position;

void mouse_handler(int button, int state, int x, int y)
{
	mouse_position.x = x;
	mouse_position.y = y;
}

void motion_handler(int x, int y)
{
	double horizontal, vertical;

	horizontal = mouse_position.x - x;
	vertical = mouse_position.y - y;

	rotate_camera(&camera, horizontal, vertical);

	mouse_position.x = x;
	mouse_position.y = y;

	glutPostRedisplay();
}

void key_handler(unsigned char key, int x, int y)
{
		switch (key) {
		case 'w':
			set_camera_speed(&camera, 30);
			break;
		case 's':
			set_camera_speed(&camera, -30);
			break;
		case 'a':
			set_camera_side_speed(&camera, 30);
			break;
		case 'd':
			set_camera_side_speed(&camera, -30);
			break;
		case 'e':
			set_camera_vertical_speed(&camera, 30);
			break;
		case 'c':
			set_camera_vertical_speed(&camera, -30);
			break;
		case '+':
			change_light_intensity('+');
			break;
		case '-':
			change_light_intensity('-');
			break;
		case 'r':
			if(world.scene.is_gun_changed == FALSE)
			world.scene.is_gun_changed = TRUE;
			world.scene.is_scoped_in = FALSE;
			break;
		case 't':
			if(world.scene.is_gun_changed == TRUE)
			world.scene.is_gun_changed = FALSE;
			break;
		case 32:
			if (world.scene.isFired == FALSE)
			world.scene.isFired = TRUE;
		break;
		case 27:
			exit(0);
		}

	glutPostRedisplay();
}

void key_up_handler(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
	case 's':
		set_camera_speed(&camera, 0.0);
		break;
	case 'a':
	case 'd':
		set_camera_side_speed(&camera, 0.0);
		break;
	case 'e':
	case 'c':
		set_camera_vertical_speed(&camera, 0.0);
		break;
	case 27:
		exit(0);
	}
	

	glutPostRedisplay();
}

void special_key_handler(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_F1:
		if (world.scene.is_help_on)
		{
			world.scene.is_help_on = FALSE;
		}
		else {
			world.scene.is_help_on = TRUE;
		}
		break;
	case GLUT_KEY_F2:
		if (world.scene.is_scoped_in)
		{
			world.scene.is_scoped_in = FALSE;
			//camera.position.x -= 20;
			//world.scene.target.size += 5;
			//world.scene.skybox.size += 10; 
		}
		else if (!world.scene.is_scoped_in && !world.scene.is_gun_changed){
			world.scene.is_scoped_in = TRUE;
			//camera.position.x += 20;
			//world.scene.target.size -= 5;
			//world.scene.skybox.size -= 10; 
		}
	}
}

void reshape(GLsizei width, GLsizei height) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	int x, y, w, h;
	double ratio;

	ratio = (double)width / height;
	if (ratio > VIEWPORT_RATIO) {
		w = (int)((double)height * (VIEWPORT_RATIO));
		h = height;
		x = (width - w) / 2;
		y = 0;
	}
	else {
		w = width;
		h = (int)((double)width / (VIEWPORT_RATIO));
		x = 0;
		y = (height - h) / 2;
	}

	glViewport(x, y, w, h);
	gluPerspective(VIEWPORT_ASPECT, 1.0 * w / h, 0.1, 20000.0);

	glMatrixMode(GL_MODELVIEW);
	
}

void display() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	set_view(&camera);
	draw_environment(world);
	
	if(world.scene.is_help_on) {
		show_help();
	}
	if(world.scene.is_scoped_in){
		show_scope();
	}

	glutSwapBuffers();
}

void idle()
{
	update_camera(&camera);
	glutPostRedisplay();
}
