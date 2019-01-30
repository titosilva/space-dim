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

#endif