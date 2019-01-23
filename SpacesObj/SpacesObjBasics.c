#include "SpacesObjBasics.h"
#include <stdlib.h>
#include <stdio.h>

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
                for(int i=0; i<obj->pointquantity; i++){
                    free(obj->points[i]);
                    free(obj->adjacency[i]);
                    printf("%d\n", i);
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

DimObject copyObject(DimObject *obj){
    if(!obj->deleted){
        DimObject object;
        if(obj->points==NULL && obj->adjacency==NULL){
            object.adjacency = NULL;
            object.points = NULL;
            object.points = 0;
            object.error = obj->error;
            object.dimension = obj->dimension;
            object.deleted = obj->deleted;
        }else{
            for(int i=0; i<obj->pointquantity; i++){

            }
        }
    }else{
        DimObject object = newObject(obj->dimension);
        object.error = DIMOBJ_ERROR_DELETED;
        object.deleted = 1;
        return object;
    }
}

int addPoint(DimObject *obj, float *point){
    if(!obj->deleted && !obj->error){
        if(obj->adjacency==NULL && obj->points==NULL && obj->pointquantity==0){
            obj->points = (float**) calloc(1, sizeof(float*));
            obj->adjacency = (int**) calloc(1, sizeof(int*));
            if(obj->adjacency!=NULL && obj->points!=NULL){
                obj->points[0] = (float*) calloc(obj->dimension, sizeof(float));
                obj->adjacency[0] = (int*) calloc(1, sizeof(int));
                if(obj->points[0]!=NULL && obj->adjacency[0]!=NULL){
                    for(int i=0; i<obj->dimension; i++){
                        obj->points[0][i] = point[i];
                    }
                    obj->pointquantity++;
                }else{
                    obj->error = DIMOBJ_ERROR_ALLOC | 0xA2000000;
                }
            }else{
                obj->error = DIMOBJ_ERROR_ALLOC | 0xA1000000;
            }
        }else{
            // New adjacency matrix
            printf("K: %d\n", obj->pointquantity);
            obj->adjacency = (int**) realloc(obj->adjacency, obj->pointquantity+1);
            if(obj->adjacency==NULL){
                obj->error = DIMOBJ_ERROR_ALLOC | 0xA3000000;
            }else{
                obj->adjacency[obj->pointquantity] = (int*) calloc(obj->pointquantity, sizeof(int));
                if(obj->adjacency==NULL){
                    obj->error = DIMOBJ_ERROR_ALLOC | 0xA4000000;
                }else{
                    for(int i=0; i<obj->pointquantity+1 && obj->error==0; i++){
                        obj->adjacency[i] = (int*) realloc(obj->adjacency[i], obj->pointquantity+1);
                        if(obj->adjacency[i]==NULL) obj->error = DIMOBJ_ERROR_ALLOC | 0xA5000000;
                        else obj->adjacency[i][obj->pointquantity] = 0;
                    }
                }
            }

            if(!obj->error){
                // New points matrix
                obj->points = (float**) realloc(obj->points, obj->pointquantity+1);
                if(obj->points!=NULL){
                    obj->points[obj->pointquantity] = (float*) calloc(obj->dimension, sizeof(float));
                    if(obj->points[obj->pointquantity]==NULL){
                        obj->error = DIMOBJ_ERROR_ALLOC | 0xA7000000;
                    }else{
                        for(int i=0; i<obj->dimension; i++){
                            obj->points[obj->pointquantity][i] = point[i];
                        }
                        obj->pointquantity++;
                    }
                }else{
                    obj->error = DIMOBJ_ERROR_ALLOC | 0xA6000000;
                }
            }
        }
    }else{
        if(obj->deleted){
            obj->error = DIMOBJ_ERROR_DELETED;
        }
    }

    printf("%d\n", obj->pointquantity);
    return obj->error;
}

void printPoints(DimObject *obj){
    printf("Points(%d):\n", obj->pointquantity);
    for(int i=0; i<obj->pointquantity; i++){
        for(int j=0; j<obj->dimension; j++){
            printf("%f\t", obj->points[i][j]);
        }
        putchar('\n');
    }
}