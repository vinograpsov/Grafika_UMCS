#ifndef PRIMITIVES_H
#define PRIMITIVES_H
#include <vector>
#include <math.h>
#include "geometry.h"
#include "utils.h"
#include "geometry.h"
#include "texture2d.h"


Geometry *newAxesGeometry();

Geometry *newPlaneGeometry(glm::vec2 size, glm::vec3 color);

Geometry* newBoxGeometry(glm::vec3 size, glm::vec3 color);

Geometry *create_pyramid(glm::vec3 size, glm::vec3 color);

Geometry *newSphereGeometry(glm::vec3 size, glm::vec3 color, float radius, int sectorCount, int stackCount);

Geometry *newSphereLineGeometry(glm::vec3 size, glm::vec3 color, float radius, int sectorCount, int stackCount);

Geometry* newBoxLineGeometry(glm::vec3 size);


#endif // PRIMITIVES_H
