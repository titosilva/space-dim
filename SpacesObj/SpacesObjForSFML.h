#ifndef SPACESANDOBJECTSFORSFML_H
#define SPACESANDOBJECTSFORSFML_H
#include <SFML/Graphics.hpp>
#include "SpacesObj.h"

// Class that allows a Object from SpacesObj to be drawed by SFML
// Uses the Drawable class as base
class DrawableObject2d : public sf::Drawable, public sf::Transformable
{
public:
  bool setObject(Object *obj);
  void setColor(sf::Color color);
  ~DrawableObject2d();
  DrawableObject2d();
  bool objectIsSet;
private:
  sf::Color pointcolor;
  Object object;
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
