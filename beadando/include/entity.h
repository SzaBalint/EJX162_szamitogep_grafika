#ifndef ENTITY_H
#define ENTITY_H
#include <obj/model.h>
#include "utils.h"

typedef struct ENTITY_STRUCT {
	float size;
	vec3 position;
	vec3 dist_from_origo;
	Model model;
	int texture;
	float material_ambient[];
}Entity;

//Initialize entity struct.
void init_entity(Entity* entity, double size, float x, float y, float z, int texture);

#endif /* ENTITY_H */