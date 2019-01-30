#include "SpacesObjTransformMultiD.h"
#include <stdlib.h>
#include <math.h>

int getCenter(DimObject *obj, float *center){
    if(center != NULL){
        for(int i=0; i<obj->dimension; i++){
            float soma = 0;
            for(int j=0; j<obj->pointquantity; j++){
                soma += obj->points[j][i];
            }
            *(center+i) = soma/obj->pointquantity;
        }
        return 0;
    }else{
        return 1;
    }
}

void scaleObject(DimObject *obj, float factor, float *center){
    for(int i=0; i<obj->pointquantity; i++){
        for(int j=0; j<obj->dimension; j++){
            obj->points[i][j] = factor*(obj->points[i][j] - center[j]) + center[j];
        }
    }
}

void translationMultiD(DimObject *obj, float *deltas){
    if(!obj->deleted && !obj->error){
        for(int i=0; i<obj->pointquantity; i++){
            for(int j=0; j<obj->dimension; j++){
                obj->points[i][j] += deltas[j];
            }
        }
    }else{
        if(obj->deleted) obj->error = DIMOBJ_ERROR_DELETED;
    }
}