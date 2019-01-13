#ifndef SPACESANDOBJECTSTRANSFORMATIONS_H
#define SPACESANDOBJECTSTRANSFORMATIONS_H
#include "SpacesObj.h"
#include <stdarg.h>

// Takes the set of points of an object and apply a simple matrix
// to each point. It is a linear tranformation that takes some vector
// in Rn, where n is the dimension of the object, and gives a vector
// in Rm, where m is the "finaldimension", as result
// The matrix used is just composed by 1's and 0's, like a
// identity matrix, but this time it may have some lines removed or added
// The function returns a object that has dimension "finaldimension" and
// whose set of points is the result of applying the matrix to all points
// of the original matrix.
// The final effect is:
// If obj->dimension<finaldimension, the final object will have points whose
// Coordinates are the same as the original object, but with some 0's added,
// because the dimension has increased
// If obj->dimension>finaldimension, the final object will have points whose
// Coordinates are the same as the original object, but with the last Coordinates
// removed. Example: a point (0.1,0.2,0.3) projected to a 2-dimensional point
// will be (0.1,0.2); if we project the point (2,3) to a 3-dimensional point,
// the result will be (2,3,0).
Object projection(Object *obj, int finaldimension);

// just multplies the vector and the matrix
// m and n are the size of the matrix
float *applyMatrix(int m, int n, float **matrix, float *vector);

float **newMatrix(int m, int n, ...);
void deleteMatrix(int m, float **matrix);

#endif
