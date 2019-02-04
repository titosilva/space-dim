#ifndef SPACEDIM_OBJECTPLACER_H
#include "../SpacesObjBasics.h"
#define SPACEDIM_OBJECTPLACER_H
#include <SFML/Graphics.hpp>

class ObjectPlacer : public sf::Drawable
{
public:
    // Saves the adress of some object, which will be drawn
    int linkToObject(ObjectScheme *obj);
    // If the object is linked, then removes the link and set
    // the linked adress to NULL
    int removeLink();
    // Set to one if any object has been linked
    bool linked;
    // if set to true, the projection goes to the second dimension
    // if set to false, the projection goes to the third dimension
    bool projectionToSecondDimension;
    // Constructor and Destructor
    ObjectPlacer(ObjectScheme *link = NULL, bool projectionToSecondDimension = false);
    ~ObjectPlacer();
private:
    ObjectScheme *link;
    // Position where the object will be drawn
    float *position;
    // Angles used in the transformations
    float *angles;
};

#endif