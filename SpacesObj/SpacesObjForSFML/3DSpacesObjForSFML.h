#ifndef SPACEDIM_SPACESOBJFORSFML_3D_H
#define SPACEDIM_SPACESOBJFORSFML_3D_H

#include <SFML/Graphics.hpp>
#include "../SpacesObj.h"

class DrawableSpace3d : public sf::Drawable
{
public:
    DrawableSpace3d();
    ~DrawableSpace3d();
    int addObject(DimObject *obj);
    int removeObject(int objectindex);
    void setCameraPosition(float x, float y, float z);
    void setCameraDirection(float x, float y, float z);
    int numberOfObjects;
    // Array of objects contained in the space
    DimObject *objects;
private:
    float camPosition[3];
    float camDirection[3];
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
}

#endif