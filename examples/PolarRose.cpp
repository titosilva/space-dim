/*
    Polar Rose example for SpaceDim project
    Author: Tito Silva

    The polar rose has equation
    r = radius*sin(factor*teta) or
    r = radius*cos(factor*teta)

    It results in a rose drawing for factors 
    in the natural numbers set

    To compile, you can use

    $ g++ PolarRose.cpp ../SpacesObj/SpacesObjBasics.c \
    ../SpacesObj/SpacesObjForSFML/2DSpacesObjForSFML.cpp \
    ../SpacesObj/SpacesObjTransform/SpacesObjTransform2D.c \
    ../SpacesObj/SpacesObjForSFML/SpacesObjForSFML.cpp \
    -lm -lsfml-graphics -lsfml-window -lsfml-system

    on your command line, setting this example directory as the current directory
*/


#include "../SpaceDim.h"
#include <SFML/Graphics.hpp>
#include <math.h>
#include <time.h>
#include <iostream>

#define STARTANGLE 2*M_PI
#define ENDANGLE 0
#define RADIUS 100
// Number of points used to build the rose
#define NUMBEROFPOINTS 200
// Position of the rose
#define CENTERPOSITION 150
// Use sine in the equation of the rose
#define USESINE 1
// Animation of rotating rose
// If set to 1, the rose will be rotating
#define ANIMATION 1
// Number of frames per second
#define FRAMERATE 5

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode(500.f, 500.f), "Square");
    DrawableObject2d rose;
    float factor;
    float point[2];
    
    std::cout << "What is the factor? " << std::endl;

    std::cin >> factor;

    for(int i=0; i<NUMBEROFPOINTS;i++){
        float angle = STARTANGLE+i*(ENDANGLE-STARTANGLE)/NUMBEROFPOINTS;
        if(USESINE){
            point[0] = RADIUS*sin(factor*(angle))*cos(angle);
            point[1] = RADIUS*sin(factor*(angle))*sin(angle);
        }else{
            point[0] = RADIUS*cos(factor*(angle))*cos(angle);
            point[1] = RADIUS*cos(factor*(angle))*sin(angle);
        }

        addPoint(&rose.object, point);
        if(i!=0) addEdge(&rose.object, i-1, i);
    }

    addEdge(&rose.object, 0, NUMBEROFPOINTS-1);

    translation2D(&rose.object, CENTERPOSITION, CENTERPOSITION);
    window.clear();
    window.draw(rose);
    window.display();

    sf::Event event;
    while(window.isOpen()){
        if(ANIMATION){
            rotation2D(&rose.object, 0.1, CENTERPOSITION, CENTERPOSITION);
            window.clear();
            window.draw(rose);
            window.display();
            clock_t start = clock();
            while((double)(clock()-start)/CLOCKS_PER_SEC<(double)1/FRAMERATE);
        }

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) window.close();
        }
    }

    return 0;
}
