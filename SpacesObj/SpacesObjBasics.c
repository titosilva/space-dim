#include "SpacesObjBasics.h"
#include <stdlib.h>

DimObject newObject(int dimension){
    DimObject object;

    object.dimension = dimension;
    object.adjacency = NULL;
    object.deleted = 0;
    object.points = NULL;
    object.pointquantity = 0;
    object.error = 0;

    return object;
}

int deleteObject(DimObject *obj){
    // Return codes:
    // 0: all went well :)
    // 1: The object has some error, so the deletion operation won't be realizaed
    // 2: The object has been deleted
    // -1: the object doesn't have points
    if(!obj->error){
        if(!obj->deleted){
            if(obj->points!=NULL && obj->adjacency!=NULL){
                for(; obj->pointquantity>0; obj->pointquantity--){
                    free(obj->points[obj->pointquantity-1]);
                    free(obj->adjacency[obj->pointquantity-1]);
                }
                free(obj->points);
                free(obj->adjacency);
                obj->deleted = 1;
                return 0;
            }else{
                return -1;
            }
        }else{
            return 2;
        }
    }else{
        return 1;
    }
}