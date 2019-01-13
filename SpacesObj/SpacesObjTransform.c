#include "SpacesObj.h"
#include "SpacesObjTransform.h"
#include <stdarg.h>
#include <stdlib.h>

Object projection(Object *obj, int finaldimension){
  Object temp;
  temp.dimension = finaldimension;
  temp.points = (float**) calloc(obj->pointquantity, sizeof(float*));

  // Matrix to be applied to the set of points
  float **matrix = (float**) calloc(finaldimension, sizeof(float*));
  for(int i=0; i<obj->dimension; i++){
    matrix[i] = (float*) calloc(obj->dimension, sizeof(float));
  }
  for(int i=0; i<obj->dimension && i<finaldimension; i++){
    matrix[i][i] = 1;
  }

  for(int i=0; i<obj->pointquantity; i++){
    temp.points[i] = applyMatrix(finaldimension, obj->dimension, matrix, obj->points[i]);
  }

  temp.pointquantity = obj->pointquantity;

  // Copy the adjacency matrix from obj
  temp.adjacency = (int**) calloc(obj->pointquantity, sizeof(int*));
  for(int i=0; i<obj->pointquantity; i++){
    temp.adjacency[i] = (int*) calloc(obj->pointquantity, sizeof(int));
    for(int j=0; j<obj->pointquantity; j++){
      temp.adjacency[i][j] = obj->adjacency[i][j];
    }
  }

  return temp;
}

float *applyMatrix(int m, int n, float **matrix, float *vector){
  float *res = (float*) calloc(m, sizeof(float));

  for(int i=0; i<m; i++){
    float s=0;
    for(int j=0; j<n; j++){
      s += matrix[i][j]*vector[j];
    }
    res[i] = s;
  }

  return res;
}

float **newMatrix(int m, int n, ...){
  float **temp = (float**) calloc(m, sizeof(float*));
  va_list args;
  va_start(args, n);
  for(int i=0; i<m; i++){
    temp[i] = (float*) calloc(n, sizeof(float));
    for(int j=0; j<n; j++){
      temp[i][j] = (float) va_arg(args, double);
    }
  }
  return temp;
}

void deleteMatrix(int m, float **matrix){
  for(int i=0; i<m; i++){
    free(*(matrix+i));
  }
  free(matrix);
}
