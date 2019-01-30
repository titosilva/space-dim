#include "SpacesObjPerspective.h"
#include <stdlib.h>
#include <math.h>

DimObject perspective(DimObject *obj, float *cameraposition, float *cameradirection){
    DimObject result = newObject(obj->dimension-1);

    if(!obj->deleted && !obj->error){
        float normofdirection = 0;
        float *k = (float*) calloc(obj->dimension, sizeof(float));

        for(int j=0; j<obj->dimension; j++){
            normofdirection += pow(cameradirection[j], 2);
        }
        normofdirection = sqrt(normofdirection);

        char *pointadded = (char*) calloc(obj->pointquantity, sizeof(char));
        for(int i=0; i<obj->pointquantity; i++){
            float dotproduct = 0;
            float normofvector = 0;

            for(int j=0; j<obj->dimension; j++){
                dotproduct += (obj->points[i][j]-cameraposition[j])*cameradirection[j];
            }
            
            // Just draw things in front of the camera
            if(dotproduct>=0){
                for(int j=0; j<obj->dimension; j++){
                    k[j] = cameradirection[j]*dotproduct/(normofdirection*normofdirection);
                    normofvector += pow(k[j], 2);
                }

                normofvector = sqrt(normofvector);

                for(int j=0; j<obj->dimension; j++){
                    k[j] = (obj->points[i][j] - cameraposition[j] - k[j])/normofvector;
                }

                addPoint(&result, k);
                pointadded[i] = 1;
            }
        }

        int count = 0;
        for(int i=0; i<obj->pointquantity; i++){
            for(int j=0; j<obj->pointquantity; j++){
                if(pointadded[i]){
                    if(obj->adjacency[i][j]){
                        addEdge(&result, i-count, j-count);
                    }
                }else{
                    count++;
                }
            }
        }

        free(k);
    }else{
        if(obj->deleted) obj->error = DIMOBJ_ERROR_DELETED; 
    }

    return result;
}