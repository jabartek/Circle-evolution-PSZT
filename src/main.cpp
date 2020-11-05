#include "main.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "area_calculation.hpp"
#include "gui.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <cstdlib>

int main(){
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    std::cout<<"Witaj PSZTY!"<<std::endl;

    std::vector<Rectangle> rectangles;
    std::vector<sf::RectangleShape> rectangleShapes;
    rectangles.emplace_back(Rectangle(50, 50, 300, 900));
    rectangles.emplace_back(Rectangle(450, 50, 200, 200));
    rectangles.emplace_back(Rectangle(400, 400, 550, 550));
    
    for(auto v : rectangles){
        rectangleShapes.emplace_back(shapeFromRectangle(v));
    }
    
    while (window.isOpen())
    {
        Circle circ(rand()*50/RAND_MAX, rand()*1000/RAND_MAX,rand()*1000/RAND_MAX,0);
        
        float val = calculateFuctionValue(circ, rectangles);

        // std::cout<<val<<std::endl;
        if(val>0.01){
            sf::CircleShape cShape = shapeFromCircle(circ);
            window.clear();

            drawRectanglesFromVector(&window, rectangleShapes);
            
            window.draw(cShape);
            window.display();
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    return 0;
}