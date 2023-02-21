#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "geometry.h"
#include <vector>
#include <math.h>
#include "utils.h"
#include "texture2d.h"
Geometry *newAxesGeometry();

Geometry *newPlaneGeometry(glm::vec2 size, glm::vec3 color);

Geometry* newBoxGeometry(glm::vec3 size, glm::vec3 color);

Geometry* newGrassGeometry(glm::vec3 size, glm::vec3 color);

Geometry *newSphereGeometry(glm::vec3 size, glm::vec3 color, float radius, int sectorCount, int stackCount);

Geometry *newSphereLineGeometry(glm::vec3 size, glm::vec3 color, float radius, int sectorCount, int stackCount);



#endif // PRIMITIVES_H
