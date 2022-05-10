#ifndef SCENE_H
#define SCENE_H

#include "entity.h"
#include "texture.h"

#include <obj/model.h>

typedef struct SCENE_STRUCT
{
	int help_texture;
	int scope_texture;
	int floor_texture;
	int is_help_on;
	int is_scoped_in;
	int is_gun_changed;
	int isFired;
	Entity skybox;
	Entity floor;
	Entity sniper;
	Entity rifle;
	Entity target;
} Scene;

typedef struct WORLD_STRUCT{
	Scene scene;
}World;

World world;

//Initialize the entities of the world.
void init_entities(World* world);

//Draw origin
void draw_origin();

//Draw the floor.
void draw_floor();

//Draw the entities to the world.
void draw_environment(World world);

//Draw the skybox.
void draw_skybox();

//Draw the sniper object.
void draw_sniper();

//Draw the rifle object.
void draw_rifle();

//Draw the target objects.
void draw_targets();

//Set current lighting.
void set_lights();

//Change the intensity of lighting.
float change_light_intensity(char i);

#endif /* WORLD_H */