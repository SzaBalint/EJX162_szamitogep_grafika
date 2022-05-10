#include "world.h"
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "camera.h"
#include <obj/load.h>
#include <obj/draw.h>

float timer = 0;
int isFired = FALSE;

void init_entities(World* world) {

    //Initialize Skybox Entity.
    init_entity(&(world->scene.skybox), 200, 0, 0, 0, load_texture("textures\\skybox.png"));

    //Initialize Sniper entity.
    init_entity(&(world->scene.sniper), 1, 0, 0, 0, load_texture("textures\\awp.png"));
    load_model(&world->scene.sniper.model, "objects\\awp.obj");

    //Initialize Rifle entity.
    init_entity(&(world->scene.rifle), 1, 0, 0, 0, load_texture("textures\\rifle.png"));
    load_model(&world->scene.rifle.model, "objects\\rifle.obj");

    //Initialize Target entities.
    init_entity(&(world->scene.target), 0.5, 0, 0, 0, load_texture("textures\\target.png"));
    load_model(&world->scene.target.model, "objects\\target.obj");

    //Load Help screen texture.
    world->scene.help_texture = load_texture("textures\\help.png");
    world->scene.floor_texture = load_texture("textures\\floor2.png");
    world->scene.scope_texture = load_texture("textures\\scope.png");
}

void draw_origin()
{
	glBegin(GL_LINES);

	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);

	glEnd();
}

void draw_environment(World world) {
    double elapsed_time = calc_elapsed_time();
    glEnable(GL_TEXTURE_2D);
    
    draw_origin();
    set_lights();
    draw_skybox();
    draw_targets();
    if(!world.scene.is_scoped_in && !world.scene.is_gun_changed) draw_sniper(elapsed_time);
    if(world.scene.is_gun_changed) draw_rifle(elapsed_time);
    draw_targets();
    draw_floor();
    
}

void draw_floor(){
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, world.scene.floor_texture);
	glTranslatef(0,-10,10);	
          glBegin(GL_QUADS);
		//bl
		glVertex3f(-4000.0,0,500);
		//br
		glVertex3f(4000.0,500,0);
		//str
		glVertex3f(4000.0,500,0);
		//tl
		glVertex3f(-4000.0,500,0);
	glEnd();

	
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void draw_sniper(double elapsed_time) {

    glPushMatrix();
        glEnable(GL_BLEND);
        glTranslatef(camera.position.x, camera.position.y, camera.position.z);

        glRotatef(90.0,1.0,0.0,0.0);
        glRotatef(camera.rotation.z, 0, 1, 0);
	    glRotatef(camera.rotation.x, 0, 0, 1);
        glTranslatef(0.8, -2.6, -1.5);
        
        if (world.scene.isFired == TRUE) {
		    timer += 1 * elapsed_time;
		        if (timer > 1) {
			        world.scene.isFired = FALSE;
                    
		        }
	    }
	    else {
		    if (timer > 0) timer -= 1 * elapsed_time;
	    }
	    glRotatef(timer * 5, 0, 0.2, 1);
        
        glMaterialfv(GL_FRONT, GL_AMBIENT, world.scene.sniper.material_ambient);
        glBindTexture(GL_TEXTURE_2D, world.scene.sniper.texture);
        glScalef(world.scene.sniper.size, world.scene.sniper.size, world.scene.sniper.size);
        draw_model(&world.scene.sniper.model);
    glPopMatrix();
    glDisable(GL_BLEND);
}

void draw_rifle(elapsed_time){
    
    glPushMatrix();
        glEnable(GL_BLEND);
        glTranslatef(camera.position.x, camera.position.y, camera.position.z);

        glRotatef(90.0,1.0,0.0,0.0);
        glRotatef(camera.rotation.z, 0, 1, 0);
	    glRotatef(camera.rotation.x, 0, 0, 1);
        glTranslatef(0.8, -2.6, 1.8);
        
        glMaterialfv(GL_FRONT, GL_AMBIENT, world.scene.rifle.material_ambient);
        glBindTexture(GL_TEXTURE_2D, world.scene.rifle.texture);
        glScalef(world.scene.rifle.size, world.scene.rifle.size, world.scene.rifle.size);
        draw_model(&world.scene.rifle.model);
    glPopMatrix();
    glDisable(GL_BLEND);
}

void draw_targets(){
    glPushMatrix();
        glEnable(GL_BLEND);
        glTranslatef(-40, 50, -1.5);
        glRotatef(90,1.0,0.0,0.0);

        glMaterialfv(GL_FRONT, GL_AMBIENT, world.scene.target.material_ambient);
        glBindTexture(GL_TEXTURE_2D, world.scene.target.texture);
        glScalef(world.scene.sniper.size, world.scene.target.size, world.scene.target.size);
        draw_model(&world.scene.target.model);
    glPopMatrix();
    glPushMatrix();
        glEnable(GL_BLEND);
        glTranslatef(-30, 70, -1.5);
        glRotatef(90,1.0,0.0,0.0);

        glMaterialfv(GL_FRONT, GL_AMBIENT, world.scene.target.material_ambient);
        glBindTexture(GL_TEXTURE_2D, world.scene.target.texture);
        glScalef(world.scene.sniper.size, world.scene.target.size, world.scene.target.size);
        draw_model(&world.scene.target.model);
    glPopMatrix();
    glPushMatrix();
        glEnable(GL_BLEND);
        glTranslatef(10, 50, -1.5);
        glRotatef(90,1.0,0.0,0.0);

        glMaterialfv(GL_FRONT, GL_AMBIENT, world.scene.target.material_ambient);
        glBindTexture(GL_TEXTURE_2D, world.scene.target.texture);
        glScalef(world.scene.sniper.size, world.scene.target.size, world.scene.target.size);
        draw_model(&world.scene.target.model);
    glPopMatrix();
    glPushMatrix();
        glEnable(GL_BLEND);
        glTranslatef(40, 30, -1.5);
        glRotatef(90,1.0,0.0,0.0);

        glMaterialfv(GL_FRONT, GL_AMBIENT, world.scene.target.material_ambient);
        glBindTexture(GL_TEXTURE_2D, world.scene.target.texture);
        glScalef(world.scene.sniper.size, world.scene.target.size, world.scene.target.size);
        draw_model(&world.scene.target.model);
    glPopMatrix();
    glDisable(GL_BLEND);
}

void draw_skybox()
{
    double theta, phi1, phi2;
    double x1, y1, z1;
    double x2, y2, z2;
    double u, v1, v2;

    int n_slices, n_stacks;
    double radius;
    int i, k;

    n_slices = 12;
    n_stacks = 6;

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, world.scene.skybox.texture);
    glScaled(world.scene.skybox.size, world.scene.skybox.size, world.scene.skybox.size);

    glColor3f(1, 1, 1);

    glBegin(GL_TRIANGLE_STRIP);

    for (i = 0; i < n_stacks; ++i) {
        v1 = (double)i / n_stacks;
        v2 = (double)(i + 1) / n_stacks;
        phi1 = v1 * M_PI / 2.0;
        phi2 = v2 * M_PI / 2.0;
        for (k = 0; k <= n_slices; ++k) {
            u = (double)k / n_slices;
            theta = u * 2.0 * M_PI;
            x1 = cos(theta) * cos(phi1);
            y1 = sin(theta) * cos(phi1);
            z1 = sin(phi1);
            x2 = cos(theta) * cos(phi2);
            y2 = sin(theta) * cos(phi2);
            z2 = sin(phi2);
            glTexCoord2d(u, 1.0 - v1);
            glVertex3d(x1, y1, z1);
            glTexCoord2d(u, 1.0 - v2);
            glVertex3d(x2, y2, z2);
        }
    }

    glEnd();
    glPopMatrix();
}

void set_lights() {
    
    float n = change_light_intensity(0);
    float light_position[] = { 0, 0, 0, 0 };
    float light_ambient[] = { n, n, n, 0 };
    float light_diffuse[] = { 0.5, 0.5, 0, 0 };
    float light_specular[] = { 1, 1, 1, 0 };

    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
}

float change_light_intensity(char i) {
    static float n = 0.5;

    switch (i) {
    case '+':
        if (n < 1);
        n += 0.01;
        break;
    case '-':
        if (n > -0.51);
        n -= 0.01;
        break;
    }

    return n;
}