#ifndef SPACEDIM_SPACESOBJTRANSFORM_MULTID_H
#define SPACEDIM_SPACESOBJTRANSFORM_MULTID_H
#include "../SpacesObjBasics.h"

// Gets the "center of mass" of the object
float *getCenter(DimObject *obj);

// Multplies the vectors between the objects points and the center
// by the given factor
void scaleObject(DimObject *obj, float factor, float *center);

#endif