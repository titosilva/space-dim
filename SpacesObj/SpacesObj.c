#include "SpacesObj.h"
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
//for tests
#include <stdio.h>

Space newSpace(int dimension, int objectquantity, ...){
  Space space;
  space.dimension = dimension;
  space.objectquantity = 0;
  space.objects = NULL;

  va_list args;
  va_start(args, objectquantity);
  for(int i=0; i<objectquantity; i++){
    // If there is any error, the object just wont be added
    addObject(&space, va_arg(args, DimObject));
  }
  va_end(args);

  return space;
}

DimObject newObject(int dimension, int pointquantity, int edgequantity, ...){
  DimObject space;
  space.dimension = dimension;
  space.points = (float**) calloc(pointquantity, sizeof(float*));
  space.pointquantity = pointquantity;
  space.adjacency = (int**) calloc(pointquantity, sizeof(int*));

  va_list args;
  va_start(args, edgequantity);
  for(int i=0; i<pointquantity; i++){
    *(space.points+i) = (float*) calloc(dimension, sizeof(float));
    *(space.adjacency+i) = (int*) calloc(pointquantity, sizeof(int));
    for(int j=0; j<dimension; j++){
      *(*(space.points+i) + j) = (float)va_arg(args, double);
    }
  }
  for(int i=0; i<edgequantity; i++){
    // process the edges
    // represented as strings, the edges need to be tranformed
    // to numbers to be used with the adjacency matrix
    char s1[10], s2[10];
    int x=0;
    char *edge = va_arg(args, char*);
    for(int j=0; j<strlen(edge); j++){
      if(edge[j]!='-'){
        if(x==0){
          s1[j] = edge[j];
        }else{
          s2[j-x] = edge[j];
        }
      }else{
        s1[j] = '\0';
        x=j+1;
      }
    }
    s2[strlen(edge)-x] = '\0';
    int n1 = atoi(s1);
    int n2 = atoi(s2);
    if(pointquantity>n2 && n1>=0 && pointquantity>n2 && n2>=0){
      *(*(space.adjacency+n1)+n2) = 1;
      *(*(space.adjacency+n2)+n1) = 1;
    }
  }
  va_end(args);

  return space;
}

int addObject(Space *space, DimObject obj){
  if(space->dimension==obj.dimension){
    space->objects = (DimObject*) realloc(space->objects, (space->objectquantity+1)*sizeof(DimObject));
    if(space->objects==NULL){
      return 1;
    }else{
      *(space->objects+space->objectquantity) = obj;
      space->objectquantity++;
      return 0;
    }
  }else{
    return -1;
  }
}

DimObject copyObject(DimObject *obj){
  DimObject space;
  space.dimension = obj->dimension;
  space.pointquantity = obj->pointquantity;

  space.adjacency = (int**) calloc(space.pointquantity, sizeof(int*));
  space.points = (float**) calloc(space.pointquantity, sizeof(float*));
  for(int i=0; i<space.pointquantity; i++){
    space.adjacency[i] = (int*) calloc(space.pointquantity, sizeof(int));
    space.points[i] = (float*) calloc(space.dimension, sizeof(float));
    for(int j=0; j<space.pointquantity; j++){
      space.adjacency[i][j] = obj->adjacency[i][j];
    }
    for(int j=0; j<space.dimension; j++){
      space.points[i][j] = obj->points[i][j];
    }
  }

  return space;
}

void deleteObject(DimObject *obj){
  for(int i=0; i<obj->pointquantity; i++){
    free(*(obj->points+i));
    free(*(obj->adjacency+i));
  }
  free(obj->points);
  free(obj->adjacency);
}

void deleteSpace(Space *space){
  for(int i=0; i<space->objectquantity; i++){
    deleteObject(space->objects);
  }
  free(space->objects);
}
