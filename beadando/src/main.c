#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#include "init.h"
#include "callbacks.h"

//Set the callbacks for GLUT.
void set_callbacks() {
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key_handler);
	glutKeyboardUpFunc(key_up_handler);
	glutMouseFunc(mouse_handler);
	glutMotionFunc(motion_handler);
	glutIdleFunc(idle);
	glutSpecialFunc(special_key_handler);
}

//Main function
int main(int argc, char** argv) {
	
	glutInit(&argc, argv);

	glutInitWindowSize(1280, 720);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	
	int wnd = glutCreateWindow("Shooting range");
	glutSetWindow(wnd);
	
	initialize();
	init_camera(&camera);
	init_entities(&world);
	set_callbacks();

	glutMainLoop();
	return 0;
}


