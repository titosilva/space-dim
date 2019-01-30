#include "../SpacesObj.h"
#include <math.h>

DrawableSpace3d :: DrawableSpace3d(){
    this->numberOfObjects = 0;
    this->objects = NULL;
    this->camDirection = (float*) calloc(3, sizeof(float));
    this->camPosition = (float*) calloc(3, sizeof(float));
    this->camDirection[0] = 0;
    this->camDirection[1] = 0;
    this->camDirection[2] = 1;
    this->camPosition[0] = 0;
    this->camPosition[1] = 0;
    this->camPosition[2] = 0;
}

DrawableSpace3d :: ~DrawableSpace3d(){
    if(this->objects!=NULL){
        if(this->numberOfObjects>0){
            for(int i=0; i<this->numberOfObjects; i++){
                deleteObject(&this->objects[i]);
            }
        }
        free(this->objects);
        free(this->camDirection);
        free(this->camPosition);
    }
}

void DrawableSpace3d :: setCameraDirection(float x, float y, float z){
    // make unit vector from given direction
    float norm = sqrt(x*x + y*y + z*z);
    if(norm != 0){
        this->camDirection[0] = x/norm;
        this->camDirection[1] = y/norm;
        this->camDirection[2] = z/norm;
    }else{
        this->camDirection[0] = 0;
        this->camDirection[1] = 0;
        this->camDirection[2] = 1;
    }
}

void DrawableSpace3d :: setCameraPosition(float x, float y, float z){
    this->camPosition[0] = x;
    this->camPosition[1] = y;
    this->camPosition[2] = z;
}

int DrawableSpace3d :: addObject(DimObject *obj){
    if(obj->dimension==3 && !obj->deleted && !obj->error){
        this->objects = (DimObject*) realloc(this->objects, (this->numberOfObjects+1)*sizeof(DimObject));
        if(this->objects==NULL){
            return 1;
        }else{
            this->objects[numberOfObjects] = copyObject(obj);
            this->numberOfObjects++;
            return 0;
        }
    }else{
        return -1;
    }
}

int DrawableSpace3d :: removeObject(int objectindex){
    if(objectindex>=0 && objectindex<this->numberOfObjects){
        DimObject *newobjectsarray = (DimObject*) calloc(numberOfObjects-1, sizeof(DimObject));
        if(newobjectsarray!=NULL){
            int j=0;
            for(int i=0; i<numberOfObjects; i++){
                if(i!=objectindex){
                    newobjectsarray[j] = copyObject(&this->objects[i]);
                    j++;
                }
                deleteObject(&this->objects[i]);
            }
            free(this->objects);
            this->objects = newobjectsarray;
            this->numberOfObjects--;
            return 0;
        }else{
            return 1;
        }
    }
}

void DrawableSpace3d :: draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(int i=0; i<this->numberOfObjects; i++){
        DimObject object = perspective(&this->objects[i], this->camPosition, this->camDirection);
        DrawableObject2d dobj;
        translation2D(&object, this->displacement[0], this->displacement[1]);
        dobj.setObject(&object);
        target.draw(dobj);
        deleteObject(&object);
    }
}