#include "../../../space-dim/SpaceDim.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

#define SCREENSIZE 500.f

int main(int argc, char const *argv[])
{
    float x=0, y=0;
    float scale = SCREENSIZE/50;
    float displacement = SCREENSIZE/20;

    cout << "What is the value of x?" << endl;
    cin >> x;
    cout << "What is the value of y?" << endl;
    cin >> y;

    x *= scale;
    y *= scale;

    DimObject rectangle = newObject(2, 4, 4,
        0+displacement, 0+displacement,
        0+displacement, y+displacement,
        x+displacement, 0+displacement,
        x+displacement, y+displacement,
        "0-1", "0-2",
        "3-1", "3-2"
    );

    if(x>0&&y>0){
        sf::RenderWindow window(sf::VideoMode(SCREENSIZE, SCREENSIZE), "Rectangle");

        DrawableObject2d drawablerect;
        drawablerect.setObject(&rectangle);

        window.clear();
        window.draw(drawablerect);
        window.display();
        
        while(window.isOpen()){
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) window.close();
            }
        }
    }

    deleteObject(&rectangle);

    return 0;
}
