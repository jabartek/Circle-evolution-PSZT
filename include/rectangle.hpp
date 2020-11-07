#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "main.hpp"

class Rectangle
{
    float posX_;
    float posY_;
    float sizeX_;
    float sizeY_;

public:
    Rectangle(float posX, float posY, float sizeX, float sizeY) : posX_(posX), posY_(posY), sizeX_(sizeX), sizeY_(sizeY) {}
    const float getPosX() { return this->posX_; }
    const float getPosY() { return this->posY_; }
    const float getSizeX() { return this->sizeX_; }
    const float getSizeY() { return this->sizeY_; }
    void setPosX(float posX) { this->posX_ = posX; }
    void setPosY(float posY) { this->posY_ = posY; }
    void setSizeX(float sizeX) { this->sizeX_ = sizeX; }
    void setSizeY(float sizeY) { this->sizeY_ = sizeY; }
};

#endif