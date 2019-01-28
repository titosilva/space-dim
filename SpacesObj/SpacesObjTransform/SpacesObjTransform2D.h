#ifndef SPACEDIM_SPACESOBJTRANSFORM_2D_H
#define SPACEDIM_SPACESOBJTRANSFORM_2D_H
#include "../SpacesObjBasics.h"

// Rotates the points of the objects around the point "center"
// which coordinates are centerx, centery
int rotation2D(DimObject *obj, float angle, float centerx, float centery);

// Moves the object in the direction (deltax, deltay) one unity
int translation2D(DimObject *obj, float deltax, float deltay);

#endif