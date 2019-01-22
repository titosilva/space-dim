#include "SpacesObjTransformMultiD.h"
#include <stdlib.h>

float *getCenter(DimObject *obj){
    float *center = (float*) calloc(obj->dimension, sizeof(float));
    if(center != NULL){
        for(int i=0; i<obj->dimension; i++){
            float soma = 0;
            for(int j=0; j<obj->pointquantity; j++){
                soma += obj->points[j][i];
            }
            center[i] = soma;
        }
        return center;
    }else{
        return NULL;
    }
}

void scaleObject(DimObject *obj, float factor, float *center){
    for(int i=0; i<obj->pointquantity; i++){
        for(int j=0; j<obj->dimension; j++){
            obj->points[i][j] += factor*(obj->points[i][j] - center[j]);
        }
    }
}