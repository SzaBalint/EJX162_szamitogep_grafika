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
    Model hare;
    Material material;
    GLuint skybox_texture;
    GLuint awp_texture;
    GLuint rifle_texture;
    GLuint scope_texture;
    GLuint barrel_texture;
    GLuint target_texture;
    GLuint help_texture;
    GLuint floor_texture;
    GLuint hare_texture;
    float animation_path;
    bool animation;
    bool animation_direction;
    bool is_help_visible;
    bool is_scoped_in;
    bool switched_weapon;
    bool switch_animation;
    float switch_rotate;
    bool equip_weapon;
    float timer;
    bool isFired;
    
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
/**
 * Load models
 */
void load_models(Scene* scene);
/**
 * Load textures
 */
void load_textures(Scene* scene);
/**
 * Draw skybox over the map
 */
void draw_skybox(Scene scene);
/**
 * Draw sniper model,texture and add positions
 */
void draw_sniper(Scene scene);
/**
 * Draw rifle model,texture and add positions
 */
void draw_rifle(Scene scene);
/**
 * Draw target models,textures and add positions
 */
void draw_targets(Scene scene);
/**
 * Draw hare model,texture and add positions
 */
void draw_hare(Scene scene);
/**
 * Draw barrel models,textures and add positions
 */
void draw_barrel(Scene scene);
/**
 * Draw skybox under the map
 */
void draw_floor(Scene scene);
/**
 * Contains the animations
 */
void update_scene(Scene* scene, double time);
/**
 * Fix weapon position
 */
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
