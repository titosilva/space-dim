#include "SpacesObjTransform3D.h"
#include <math.h>

int rotation3D(ObjectScheme *obj, int axis, float angle, float *center){
    if(!obj->error && !obj->deleted){
        if(obj->dimension==3){
            for(int i=0; i<obj->pointquantity; i++){
                float x1 = obj->points[i][(axis-1)%3] - center[(axis-1)%3];
                float x2 = obj->points[i][(axis+1)%3] - center[(axis+1)%3];

                obj->points[i][(axis-1)%3] = x1*cos(angle) - x2*sin(angle) + center[(axis-1)%3];
                obj->points[i][(axis+1)%3] = x1*sin(angle) + x2*cos(angle) + center[(axis+1)%3];
            }
        }else{
            return -1;
        }
    }else{
        if(obj->deleted) obj->error = DIMOBJ_ERROR_DELETED;
    }

    return obj->error;
}