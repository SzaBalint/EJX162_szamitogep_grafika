#include "scene.h"
#include <math.h>

#include <obj/load.h>
#include <obj/draw.h>

float x=0;
float y=0;
float z=0;

float x_rotate=0;
float y_rotate=0;
float z_rotate=0;

void init_scene(Scene* scene)
{
    load_models(scene);
    load_textures(scene);

    scene->is_help_visible = false;
    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 0.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;
}

void set_lighting()
{
    float ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 50.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void draw_skybox(Scene scene)
{
    glDisable(GL_LIGHTING);

    glBindTexture(GL_TEXTURE_2D, scene.skybox_texture);

    double theta, phi1, phi2;
    double x1, y1, z1;
    double x2, y2, z2;
    double u, v1, v2;
    int n_slices, n_stacks;
    double radius;
    int i, k;
    n_slices = 15;
    n_stacks = 15;
    radius = 200;

    glPushMatrix();

    glScaled(radius, radius, radius);

    glColor3f(1, 1, 1);

    glBegin(GL_TRIANGLE_STRIP);

    for (i = 0; i < n_stacks; ++i) {
        v1 = (double) i / n_stacks;
        v2 = (double) (i + 1) / n_stacks;
        phi1 = v1 * M_PI / 2.0;
        phi2 = v2 * M_PI / 2.0;
        for (k = 0; k <= n_slices; ++k) {
            u = (double) k / n_slices;
            theta = u * 2.0 * M_PI;
            x1 = cos(theta) * cos(phi1);
            y1 = sin(theta) * cos(phi1);
            z1 = sin(phi1) - 0.25;
            x2 = cos(theta) * cos(phi2);
            y2 = sin(theta) * cos(phi2);
            z2 = sin(phi2) - 0.25;
            glTexCoord2d(u, 1.0 - v1);
            glVertex3d(x1, y1, z1);
            glTexCoord2d(u, 1.0 - v2);
            glVertex3d(x2, y2, z2);
        }
    }

    glEnd();

    glPopMatrix();

    glEnable(GL_LIGHTING);
}

void load_models(Scene* scene){
    load_model(&(scene->awp), "assets/models/awp.obj");
    load_model(&(scene->target), "assets/models/target.obj");

}

void load_textures(Scene* scene){
    scene->skybox_texture = load_texture("assets/textures/skybox2.jpg");
    scene->awp_texture = load_texture("assets/textures/awp.jpg");
    scene->target_texture = load_texture("assets/textures/target.jpg");
    scene->floor_texture = load_texture("assets/textures/grass.jpg");
    scene->help_texture = load_texture("assets/textures/help2.jpg");

}

void draw_sniper(Scene scene) {
    glPushMatrix();
    glTranslatef(x-1.8, y-1.0, z-2.8);
    //glRotatef(90.0,1.0,0.0,0.0);
    //glTranslatef(0.8, 7.6, 1.8);
    glRotatef(90.0,1.0, 0.0, 0.0);

    glRotatef(-10, 0, 1, 0);
    //glRotatef(45, 0, 0, 1);
    glRotatef(z_rotate, 0, 1, 0);
    glRotatef(x_rotate, 0, 0, 1);

    glBindTexture(GL_TEXTURE_2D,scene.awp_texture);

    draw_model(&(scene.awp));
    glPopMatrix();
}

void draw_floor(Scene scene) {
    glPushMatrix();
    glTranslatef(-2.0, -3.0, -3.0);
    /*glRotatef(90.0,1.0,0.0,0.0);
    glRotatef(camera.rotation.z, 0, 0, 0);
    glRotatef(camera.rotation.x, 0, 0, 0);
    
    glTranslatef(0.0, 0.0, 0.0);*/

    glBindTexture(GL_TEXTURE_2D,scene.floor_texture);
 
    glPopMatrix();
}


void draw_targets(Scene scene){
    glPushMatrix();
        glEnable(GL_BLEND);
        glTranslatef(-40, 50, -1.5);
        glRotatef(90,1.0,0.0,0.0);

        glBindTexture(GL_TEXTURE_2D, scene.target_texture);

        draw_model(&(scene.target));
    glPopMatrix();
    glPushMatrix();
        glEnable(GL_BLEND);
        glTranslatef(-30, 70, -1.5);
        glRotatef(90,1.0,0.0,0.0);

        glBindTexture(GL_TEXTURE_2D, scene.target_texture);

        draw_model(&(scene.target));
    glPopMatrix();
    glPushMatrix();
        glEnable(GL_BLEND);
        glTranslatef(10, 50, -1.5);
        glRotatef(90,1.0,0.0,0.0);

        glBindTexture(GL_TEXTURE_2D, scene.target_texture);

        draw_model(&(scene.target));
    glPopMatrix();
    glPushMatrix();
        glEnable(GL_BLEND);
        glTranslatef(40, 30, -1.5);
        glRotatef(90,1.0,0.0,0.0);

        glBindTexture(GL_TEXTURE_2D, scene.target_texture);
        draw_model(&(scene.target));

    glPopMatrix();
    glDisable(GL_BLEND);
}

void show_help(GLuint help_texture) {
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    //glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, help_texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-2, 1.5, -3);
    glTexCoord2f(1, 0);
    glVertex3d(2, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3d(2, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-2, -1.5, -3);
    glEnd();


    //glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

}


void update_scene(Scene* scene)
{

}


void update_weapon(Camera* camera){
    x=camera->position.x;
    y=camera->position.y;
    z=camera->position.z;

    x_rotate=camera->rotation.x;
    y_rotate=camera->rotation.y;
    z_rotate=camera->rotation.z;
}

void render_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting();
    draw_origin();
    draw_skybox(*scene);
    draw_sniper(*scene);
    draw_targets(*scene);
    draw_floor(*scene);
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(130, 200, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(100, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 100, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 100);

    glEnd();
}
