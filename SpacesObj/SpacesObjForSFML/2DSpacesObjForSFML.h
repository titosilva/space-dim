#ifndef SPACEDIM_2DSpacesObjForSFML_H
#define SPACEDIM_2DSpacesObjForSFML_H
#include "../SpacesObjBasics.h"
#include <SFML/Graphics.hpp>

// Class that allows a DimObject from SpacesObj to be drawed by SFML
// Uses the Drawable class as base
class DrawableObject2d : public sf::Drawable
{
public:
  bool setObject(DimObject *obj);
  void setColor(sf::Color color);
  ~DrawableObject2d();
  DrawableObject2d(void);
  bool objectIsSet;
  DimObject object;
private:
  sf::Color pointcolor;
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif