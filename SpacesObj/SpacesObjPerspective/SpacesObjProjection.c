#include "SpacesObjProjection.h"
#include <stdlib.h>
#include <stdio.h>

ObjectScheme projection(ObjectScheme *obj, unsigned int finaldimension){
    ObjectScheme object = newObject(finaldimension);

    if(!obj->error && !obj->deleted){
        float *point = (float*) calloc(finaldimension, sizeof(float));
        for(int i=0; i<obj->pointquantity; i++){
            for(unsigned int j=0; j<finaldimension; j++){
                if(j<obj->dimension){
                    point[j] = obj->points[i][j];
                }else break;
            }
            addPoint(&object, point);
        }
        for(int i=0; i<obj->pointquantity; i++){
            for(int j=0; j<i; j++){
                if(obj->adjacency[i][j]) addEdge(&object, i, j);
            }
        }
        free(point);
    }else{
        if(obj->deleted) obj->error = DIMOBJ_ERROR_DELETED;
        object.error = DIMOBJ_ERROR_INVALID;
    }

    return object;
}