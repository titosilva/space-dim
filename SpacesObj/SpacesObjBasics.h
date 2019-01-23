#ifndef SPACEDIM_SPACEANDOBJECTS_BASICS_H
#define SPACEDIM_SPACEANDOBJECTS_BASICS_H

// OBJECT ERROR CODES

// Object deleted
#define DIMOBJ_ERROR_DELETED 0x0000DEAD

// Allocation Fail
#define DIMOBJ_ERROR_ALLOC 0x000000AF
// 0xA_0000AF - Errors in function addPoint


// Used to store the object information
typedef struct spacedim_strdimobject{
    // Number of "dimensions"
    // Represents the space where the vectors
    // in the object are placed, e.g. R2("x and y coordinates")
    // or R3(x, y and z coordinates)
    int dimension;

    // Quantity of vectors in the object
    int pointquantity;

    // Matrix that represents the points
    float **points;

    // Adjacency matrix
    // The object is treated as a graph, so this matrix is used
    // to define which are the existing edges
    int **adjacency;

    // 0 if the object was not deleted
    // 1 if the object was deleted
    char deleted;

    // error codes
    int error;

} DimObject;

// sets up an object
DimObject newObject(int dimension);
// destroys an object (desallocates memory)
int deleteObject(DimObject *obj);

// makes a copy of some object
// the clone has the same adresses of the original object
// this means that what happes with the original happens
// with the clone and vice-versa
DimObject copyObject(DimObject *obj);
// It is not recommended to use a clone object
// because there can be allocation problems
DimObject cloneObject(DimObject *obj);

// Adds points to some object
int addPoint(DimObject *obj, float *point);
// Removes the point with index
int removePoint(DimObject *obj, int pointindex);
// Prints all the points of the object to stdout
void printPoints(DimObject *obj);

// Changes the adjacency matrix to create an edge between
// the points with indices point1 and point2
int addEdge(DimObject *obj, int point1, int point2);
// Changes the adjacency matrix, removing some edge
int removeEdge(DimObject *obj, int point1, int point2);
// Counts how many edges are there in the object
int countEdges(DimObject *obj);
// Prints all the edges of the object to stdout
void printEdges(DimObject *obj);

#endif