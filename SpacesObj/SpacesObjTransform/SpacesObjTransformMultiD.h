#ifndef SPACEDIM_SPACESOBJTRANSFORM_MULTID_H
#define SPACEDIM_SPACESOBJTRANSFORM_MULTID_H
#include "../SpacesObjBasics.h"

// Multplies the vectors between the objects points and the center
// by the given factor
void scaleObject(DimObject *obj, float factor, float *center);

// Gets the "center of mass" of the object
int getCenter(DimObject *obj, float *center);

// Changes the position of the object
void translationMultiD(DimObject *obj, float *deltas);

// Applies a Givens Rotation in the plane (i, j)
// See more at https://en.wikipedia.org/wiki/Givens_rotation
// Givens Rotation to just one point:
// The result is stored in the point address passed
int GivensRotationToPoint(float *point, float angle, int i, int j, float *center);
// Gives Rotation to objects
int GivensRotationToObject(DimObject *obj, float angle, int i, int j, float *center);

#endif