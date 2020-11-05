#include "gui.hpp"

sf::RectangleShape shapeFromRectangle(Rectangle rectangle){
    sf::RectangleShape ret(sf::Vector2f(rectangle.getSizeX(), rectangle.getSizeY()));
    ret.setPosition(rectangle.getPosX(), rectangle.getPosY());
    ret.setFillColor(sf::Color::Red);
    return ret;
}

sf::CircleShape shapeFromCircle(Circle circle){
    sf::CircleShape ret(circle.getRadius());
    ret.setPosition(circle.getCenterX() - circle.getRadius(), circle.getCenterY() - circle.getRadius());
    ret.setFillColor(sf::Color(0,0,255,200));
    return ret;
}


void drawRectanglesFromVector(sf::RenderWindow * window, std::vector<sf::RectangleShape> drawables){
    for(auto v : drawables){
        window->draw(v);
    }
}