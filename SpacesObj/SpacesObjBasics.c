#include "SpacesObjBasics.h"
#include <stdlib.h>
#include <stdio.h>

ObjectScheme newObject(unsigned int dimension){
    ObjectScheme object;

    object.dimension = dimension;
    object.adjacency = NULL;
    object.deleted = 0;
    object.points = NULL;
    object.pointquantity = 0;
    object.error = 0;

    return object;
}

int deleteObject(ObjectScheme *obj){
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

ObjectScheme copyObject(ObjectScheme *obj){
    if(!obj->deleted){
        ObjectScheme object = newObject(obj->dimension);
        object.deleted = obj->deleted;

        if(obj->points==NULL || obj->adjacency==NULL){
            object.adjacency = NULL;
            object.points = NULL;
            object.points = 0;
            object.error = obj->error;
        }else{
            for(int i=0; i<obj->pointquantity; i++){
                addPoint(&object, obj->points[i]);
            }

            for(int i=0; i<obj->pointquantity; i++){
                for(int j=i; j<obj->pointquantity; j++){
                    if(obj->adjacency[i][j]){
                        addEdge(&object, i, j);
                    }
                }
            }

        }

        return object;
    }else{
        ObjectScheme object = newObject(obj->dimension);
        object.error = DIMOBJ_ERROR_DELETED;
        object.deleted = 1;
        return object;
    }
}

ObjectScheme cloneObject(ObjectScheme *obj){
    ObjectScheme object = newObject(obj->dimension);

    object.adjacency = obj->adjacency;
    object.deleted = obj->deleted;
    object.error = obj->error;
    object.pointquantity = obj->pointquantity;
    object.points = obj->points;
    
    return object;
}

int addPoint(ObjectScheme *obj, float *point){
    if(!obj->error && !obj->deleted){
        float **newpointmat = (float**) calloc(obj->pointquantity+1, sizeof(float*));
        char **newadjmat = (char**) calloc(obj->pointquantity+1, sizeof(char*));
        if(newadjmat != NULL && newpointmat != NULL){
            for(int i=0; i<obj->pointquantity+1 && obj->error==0; i++){
                newpointmat[i] = (float*) calloc(obj->dimension, sizeof(float));
                newadjmat[i] = (char*) calloc(obj->pointquantity+1, sizeof(char));
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

int removePoint(ObjectScheme *obj, int pointindex){
    if(!obj->error && !obj->deleted){ 
        float **newpointmat = (float**) calloc(obj->pointquantity-1, sizeof(float*));
        char **newadjmat = (char**) calloc(obj->pointquantity-1, sizeof(char*));
        if(newadjmat != NULL && newpointmat != NULL){
            int j=0;
            for(int i=0; i<obj->pointquantity && obj->error==0; i++){
                if(i==pointindex) continue;
                newpointmat[j] = (float*) calloc(obj->dimension, sizeof(float));
                newadjmat[j] = (char*) calloc(obj->pointquantity-1, sizeof(char));
                if(newadjmat[j] != NULL && newpointmat[j] != NULL){
                    for(int k=0; k<obj->dimension; k++){
                        newpointmat[j][k] = obj->points[i][k];
                    }
                    int n=0;
                    for(int k=0; k<obj->pointquantity; k++){
                        if(k==pointindex) continue;
                        newadjmat[j][n] = obj->adjacency[i][k];
                        n++;
                    }
                }else{
                    obj->error = DIMOBJ_ERROR_ALLOC | 0xB1000000;
                }

                j++;
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
                obj->pointquantity--;
            }
        }else{
            obj->error = DIMOBJ_ERROR_ALLOC | 0xB0000000;
        }
    }else{
        if(obj->deleted){
            obj->error = DIMOBJ_ERROR_DELETED;
        }
    }

    return obj->error;
}

void printPoints(ObjectScheme *obj){
    printf("Points(%d):\n", obj->pointquantity);
    for(int i=0; i<obj->pointquantity; i++){
        for(int j=0; j<obj->dimension; j++){
            printf("%f\t", obj->points[i][j]);
        }
        putchar('\n');
    }
}

int addEdge(ObjectScheme *obj, int point1, int point2){
    if(!obj->deleted && !obj->error){
        if(point1!=point2){
            if(point1>=0 && point1<obj->pointquantity && point2>=0 && point2<obj->pointquantity){
                obj->adjacency[point1][point2] = 1;
                obj->adjacency[point2][point1] = 1;
                return 0;
            }else{
                return -2;
            }
        }else{
            return -1;
        }
    }else{
        if(obj->deleted){
            obj->error = DIMOBJ_ERROR_DELETED;
        }
        return obj->error;
    }
}

int removeEdge(ObjectScheme *obj, int point1, int point2){
    if(!obj->deleted && !obj->error){
        if(point1>=0 && point2>=0 && point1<obj->pointquantity && point2<obj->pointquantity){
            obj->adjacency[point1][point2] = 0;
            obj->adjacency[point2][point1] = 0;
        }else{
            return -1;
        }
    }else{
        if(obj->deleted){
            obj->error = DIMOBJ_ERROR_DELETED;
        }
    }

    return obj->error;
}

int countEdges(ObjectScheme *obj){
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

void printEdges(ObjectScheme *obj){
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
