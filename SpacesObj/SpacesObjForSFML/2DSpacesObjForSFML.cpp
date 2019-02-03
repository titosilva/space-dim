#include "2DSpacesObjForSFML.h"
#include "../SpacesObjBasics.h"
#include <SFML/Graphics.hpp>

// used for tests:
//#include <iostream>

bool DrawableObject2d::setObject(ObjectScheme *obj)
{
  if(obj->dimension==2){
    if(this->objectIsSet){
      deleteObject(&this->object);
    }
    this->object = copyObject(obj);
    this->objectIsSet = true;
    return true;
  }
}

void DrawableObject2d::setColor(sf::Color color)
{
  this->pointcolor = color;
}

void DrawableObject2d::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Verifies in the matrix for the 1's, which represents the edges
  // Just one half of the matrix is verified, because it is a undirected graph
  // The undirected graphs have symmetric matrices
  // The elements in the main diagonal are not taken into account
  // because we won't use loops
  if(this->objectIsSet==true){
    sf::VertexArray vertices(sf::Points, this->object.pointquantity);
    for(int i=0; i<this->object.pointquantity; i++){
      vertices[i].position = sf::Vector2f(this->object.points[i][0], this->object.points[i][1]);
      vertices[i].color = this->pointcolor;
    }
    target.draw(vertices);

    for(int i=0; i<this->object.pointquantity; i++){
      for(int j=i+1; j<this->object.pointquantity; j++){
        if(this->object.adjacency[i][j]>0){
          sf::Vertex points[2] = {
            sf::Vertex(sf::Vector2f(this->object.points[i][0], this->object.points[i][1]), this->pointcolor),
            sf::Vertex(sf::Vector2f(this->object.points[j][0], this->object.points[j][1]), this->pointcolor)
          };
          target.draw(points, 2, sf::Lines);
          //used for tests:
          //std::cout<< points[0].position.x << ", " << points[0].position.y << "\t" << points[1].position.x << ", " << points[1].position.y << "\n";
        }
      }
    }
  }
}

DrawableObject2d::DrawableObject2d()
{
  this->objectIsSet = false;
  this->setColor(sf::Color::Red);
}

DrawableObject2d::~DrawableObject2d()
{
  if(this->objectIsSet) deleteObject(&this->object);
}