#ifndef GUI_HPP
#define GUI_HPP
#include <SFML/Graphics.hpp>
#include "rectangle.hpp"
#include "circle.hpp"

sf::RectangleShape shapeFromRectangle(Rectangle rect);
sf::CircleShape shapeFromCircle(Circle circ);

void drawRectanglesFromVector(sf::RenderWindow * window, std::vector<sf::RectangleShape> drawables);

#endif