#include "gui.hpp"

sf::RectangleShape Gui::shapeFromRectangle(Rectangle rectangle)
{
    sf::RectangleShape ret(sf::Vector2f(rectangle.getSizeX(), rectangle.getSizeY()));
    ret.setPosition(rectangle.getPosX(), rectangle.getPosY());
    ret.setFillColor(sf::Color::Red);
    return ret;
}

sf::CircleShape Gui::shapeFromCircle(Circle circle, sf::Color color)
{
    sf::CircleShape ret(circle.getRadius());
    ret.setPosition(circle.getCenterX() - circle.getRadius(), circle.getCenterY() - circle.getRadius());
    ret.setFillColor(color);
    return ret;
}

void Gui::addRectangle(Rectangle rectangle)
{
    rectangleShapes_.push_back(shapeFromRectangle(rectangle));
}

void Gui::addRectangleShape(sf::RectangleShape rectangleShape)
{
    rectangleShapes_.push_back(rectangleShape);
}

void Gui::drawDrawables()
{
    for (auto v : rectangleShapes_)
    {
        draw(v);
    }
}

bool Gui::renderAndSave(std::string filename)
{
    sf::Texture texture;
    texture.create(getSize().x, getSize().y);
    texture.update(*this);
    return texture.copyToImage().saveToFile(filename);
}

Gui::Gui(unsigned int w, unsigned int h, std::string name) : sf::RenderWindow(sf::VideoMode(w, h), name){};
