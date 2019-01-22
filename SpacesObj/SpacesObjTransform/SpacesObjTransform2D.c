#include "SpacesObjTransform2D.h"
#include <math.h>

int rotation2D(DimObject *obj, float angle, float centerx, float centery){
    if(obj->dimension==2){
        for(int i=0; i<obj->pointquantity; i++){
            float vector[2];
            vector[0] = obj->points[i][0] - centerx;
            vector[1] = obj->points[i][1] - centery;
            obj->points[i][0] = centerx + vector[0]*cos(angle) - vector[1]*sin(angle);
            obj->points[i][1] = centerx + vector[0]*sin(angle) + vector[1]*cos(angle);
        }
    }else{
        return 1;
    }
}

int translation2D(DimObject *obj, float deltax, float deltay){
    if(obj->dimension==2){
        for(int i=0; i<obj->pointquantity; i++){
            obj->points[i][0] += deltax;
            obj->points[i][0] += deltay;
            return 0;
        }
    }else{
        return 1;
    }
}