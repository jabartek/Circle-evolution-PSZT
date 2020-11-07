#ifndef GUI_HPP
#define GUI_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include "rectangle.hpp"
#include "circle.hpp"

class Gui : public sf::RenderWindow
{
    std::vector<sf::RectangleShape> rectangleShapes_;
public:
    Gui(unsigned int w, unsigned int h, std::string name = "PSZT app");

    static sf::RectangleShape shapeFromRectangle(Rectangle rect);
    static sf::CircleShape shapeFromCircle(Circle circ);

    void addRectangle(Rectangle rectangle);
    void addRectangleShape(sf::RectangleShape rectangle);

    bool renderAndSave(std::string filename);

    void drawDrawables();
};

#endif