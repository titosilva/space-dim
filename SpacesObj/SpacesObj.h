#ifndef SPACESANDOBJECTS
#define SPACESANDOBJECTS

typedef struct spaceobj_strobject{
  // Number of dimensions
  int dimension;
  // Quantity of points
  int pointquantity;
  // Matrix that has the coordinates of each point
  float **points;
  // The object is treated as a tridimensional graph
  // So, there is a adjacency matrix
  // When the object is displayed, this matrix
  // is used to build the edges
  int **adjacency;
<<<<<<< HEAD
  // Space where it is placed
}DimObject;
=======
}Object;
>>>>>>> 84597b1039d93187c3195623d000a8044dd2c526

typedef struct spaceobj_strspace{
  // Struct that has information about the space
  // where the objects are placed
  // It is better to use the function newSpace to define a Space
  // instead of using the type Space alone

  // Number of dimensions
  int dimension;
  // Quantity of Objects in the space
  int objectquantity;
  // Vector of pointers to the objects contained in the space
  DimObject *objects;
}Space;

// This function acts like a "constructor"
// The other arguments (in the "...") are DimObject
// Returns the new Space created
Space newSpace(int dimension, int objectquantity, ...);
// This acts like a "constructor" too
// The "..." are float values
// You can just type coordinates in the order you want and
// the function will divide them in points
// To create the edges, use strings
// In the adjacency matrix, the vertices will be in the order you inserted them here
// Example:
// newObject(3, 2, 4.0, 5.2, 6.5, 4.3, 5.6, 6.4, "0-1");
// will create an object that has points
// (4.0, 5.2, 6.5) and
// (4.3, 5.6, 6.4)
// this object has an edge between the points
// 0(4.0, 5.2, 6.5) and
// 1(4.3, 5.6, 6.4)
DimObject newObject(int dimension, int pointquantity, int edgequantity, ...);
// Adds some object to some Space
// Returns 0 if it went well
// Returns 1 if there was some allocation error
// Returns -1 if space has different dimension to objpnt
int addObject(Space *space, DimObject objpnt);
// Copies an object that already exists
<<<<<<< HEAD
DimObject copyObject(DimObject *obj);
// Desallocates the memory to the Objects
void deleteObject(DimObject *obj);
// Desallocates the memory to the Spaces
=======
Object copyObject(Object *obj);
// Desallocates the memory to the Object
void deleteObject(Object *obj);
// Desallocates the memory to the Space
>>>>>>> 84597b1039d93187c3195623d000a8044dd2c526
void deleteSpace(Space *space);

#endif
