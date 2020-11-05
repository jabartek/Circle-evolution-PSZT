#include "area_calculation.hpp"

float calculateOverlap(Circle circle, Rectangle rectangle)
{
    return area(
        rectangle.getPosX(),
        rectangle.getPosX() + rectangle.getSizeX(),
        rectangle.getPosY(),
        rectangle.getPosY() + rectangle.getSizeY(),
        circle.getCenterX(),
        circle.getCenterY(),
        circle.getRadius());
}

float calculateFuctionValue(Circle circle, std::vector<Rectangle> rectangles)
{
    float totalOverlap = 0.0f;
    for (auto rectangle : rectangles)
    {
        totalOverlap += calculateOverlap(circle, rectangle);
    }
    Rectangle proxy(circle.getCenterX() - circle.getRadius() * 1.25f, circle.getCenterY() - circle.getRadius() * 1.25f, circle.getRadius() * 2.5f, circle.getRadius() * 2.5f);
    float offRec = calculateOverlap(circle, proxy) - totalOverlap;
    float result = totalOverlap - offRec * OFF_RECTANGLE_PENALTY;
    circle.setFunctionValue(result);
    return result;
}

void calculateFunctionValues(std::vector<Circle> circles, std::vector<Rectangle> rectangles)
{
    for (auto v : circles)
    {
        calculateFuctionValue(v, rectangles);
    }
}