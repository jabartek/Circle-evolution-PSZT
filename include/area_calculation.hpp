#ifndef AREA_CALCULATION_HPP
#define AREA_CALCULATION_HPP
#include <algorithm>
#include <vector>

#include "circle.hpp"
#include "rectangle.hpp"

float calculateOverlap(Circle circle, Rectangle rectangle);

float section(float h, float r = 1);
float g(float x, float h, float r = 1);
float area(float x0, float x1, float h, float r);
float area(float x0, float x1, float y0, float y1, float r);
float area(float x0, float x1, float y0, float y1, float cx, float cy, float r);

float calculateFuctionValue(const Circle circle, const std::vector<Rectangle> rectangles);
void calculateFunctionValues(const std::vector<Circle> circles, const std::vector<Rectangle> rectangles);

#endif