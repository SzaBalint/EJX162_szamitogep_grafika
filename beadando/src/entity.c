#include "entity.h"

void init_entity(Entity* entity, double size, float x, float y, float z, int texture) {
    entity->size = size;
    entity->position.x = x;
    entity->dist_from_origo.x = x;
    entity->position.y = y;
    entity->dist_from_origo.y = y;
    entity->position.z = z;
    entity->dist_from_origo.z = z;
    entity->texture = texture;
}
