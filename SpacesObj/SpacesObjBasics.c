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
                }
                free(obj->points);
                free(obj->adjacency);
                obj->deleted = 1;
                obj->pointquantity = 0;
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
        if(obj->points==NULL || obj->adjacency==NULL){
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
    if(!obj->error && !obj->deleted){
        float **newpointmat = (float**) calloc(obj->pointquantity+1, sizeof(float*));
        int **newadjmat = (int**) calloc(obj->pointquantity+1, sizeof(int*));
        if(newadjmat != NULL && newpointmat != NULL){
            for(int i=0; i<obj->pointquantity+1 && obj->error==0; i++){
                newpointmat[i] = (float*) calloc(obj->dimension, sizeof(float));
                newadjmat[i] = (int*) calloc(obj->pointquantity+1, sizeof(int));
                if(newadjmat[i] != NULL && newpointmat[i] != NULL){
                    for(int j=0; j<obj->dimension; j++){
                        if(i==obj->pointquantity){
                            newpointmat[i][j] = point[j];
                        }else{
                            newpointmat[i][j] = obj->points[i][j];
                        }
                    }
                    for(int j=0; j<obj->pointquantity; j++){
                        if(i!=obj->pointquantity){
                            newadjmat[i][j] = obj->adjacency[i][j];
                        }
                    }
                }else{
                    obj->error = DIMOBJ_ERROR_ALLOC | 0xA1000000;
                }
            }

            if(!obj->error){
                for(int i=0; i<obj->pointquantity; i++){
                    free(obj->points[i]);
                    free(obj->adjacency[i]);
                }
                free(obj->points);
                free(obj->adjacency);

                obj->adjacency = newadjmat;
                obj->points = newpointmat;
                obj->pointquantity++;
            }
        }else{
            obj->error = DIMOBJ_ERROR_ALLOC | 0xA0000000;
        }
    }else{
        if(obj->deleted){
            obj->error = DIMOBJ_ERROR_DELETED;
        }
    }

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

void printEdges(DimObject *obj){
    // Searchs in the top half of the adjacency matrix for edges
    printf("Edges(%d):\n", countEdges(obj));
    for(int i=0; i<obj->pointquantity; i++){
        for(int j=i; j<obj->pointquantity; j++){
            if(obj->adjacency[i][j]){
                printf("%d\t%d\n", i, j);
            }
        }
    }
}

int countEdges(DimObject *obj){
    int sum=0;
    for(int i=0; i<obj->pointquantity; i++){
        for(int j=i; j<obj->pointquantity; j++){
            if(obj->adjacency[i][j]){
                sum++;
            }
        }
    }
    return sum;
}