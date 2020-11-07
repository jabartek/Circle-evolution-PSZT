#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "main.hpp"

static const float OFF_RECTANGLE_PENALTY = 2.0f;

class Circle
{
    float radius_;
    float centerX_;
    float centerY_;
    float functionValue_;

public:
    Circle(float radius, float centerX, float centerY, float functionValue) : radius_(radius),
                                                                              centerX_(centerX), centerY_(centerY), functionValue_(functionValue) {}
    Circle(float radius, float centerX, float centerY):radius_(radius),centerX_(centerX), centerY_(centerY){}
    float getRadius() { return this->radius_; }
    float getCenterX() { return this->centerX_; }
    float getCenterY() { return this->centerY_; }
    float getFunctionValue() { return this->functionValue_; }
    void setRadius(float radius) { this->radius_ = radius; }
    void setCenterX(float centerX) { this->centerX_ = centerX; }
    void setCenterY(float centerY) { this->centerY_ = centerY; }
    void setFunctionValue(float functionValue) { this->functionValue_ = functionValue; }

};

#endif