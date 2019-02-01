#include "SpacesObjTransformMultiD.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

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

int GivensRotationToPoint(float *point, float angle, int i, int j, float *center){
    if(point!=NULL){
        if(i!=j){
            float x1 = point[i]-center[i];
            float x2 = point[j]-center[j];

            point[i] = x1*cos(angle) - x2*sin(angle) + center[i];
            point[j] = x1*sin(angle) + x2*cos(angle) + center[j];
            return 0;
        }else{
            return 1;
        }
    }else{
        return -1;
    }
}

int GivensRotationToObject(DimObject *obj, float angle, int i, int j, float *center){
    if(!obj->deleted && !obj->error && i>=0 && j>=0 && i<obj->dimension && j<obj->dimension){
        if(i>=0 && j>=0 && i<obj->dimension && j<obj->dimension){
            for(int k=0; k<obj->pointquantity; k++){
                GivensRotationToPoint(obj->points[k], angle, i, j, center);
            }
        }
    }else{
        return -1;
    }
}