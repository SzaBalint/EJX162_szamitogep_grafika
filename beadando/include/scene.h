#ifndef SCENE_H
#define SCENE_H

#include <stdbool.h>
#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{
    Model awp;
    Model target;
    Model barrel;
    Model rifle;
    Material material;
    GLuint skybox_texture;
    GLuint awp_texture;
    GLuint rifle_texture;
    GLuint scope_texture;
    GLuint barrel_texture;
    GLuint target_texture;
    GLuint help_texture;
    GLuint floor_texture;
    bool is_help_visible;
    bool is_scoped_in;
    bool switched_weapon;
    
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

void load_models(Scene* scene);

void load_textures(Scene* scene);

void draw_skybox(Scene scene);

void draw_sniper(Scene scene);

void draw_rifle(Scene scene);

void draw_targets(Scene scene);

void draw_barrel(Scene scene);

void draw_floor(Scene scene);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, double time);

void update_weapon(Camera* camera);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

#endif /* SCENE_H */
