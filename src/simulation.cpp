#include "simulation.hpp"

Simulation::Simulation(unsigned int windowSizeX, unsigned int windowSizeY) : gui_(windowSizeX, windowSizeY){

};


Gui * Simulation::getGui(){
    return &gui_;
};

Circle Simulation::meanCircle()
{
    auto totalRadius = 0.0f;
    auto totalCenterX = 0.0f;
    auto totalCenterY = 0.0f;
    for(auto c : circles_){
        totalRadius += c.getRadius();
        totalCenterX += c.getCenterX();
        totalCenterY += c.getCenterY();
    }
    totalRadius /= circles_.size();
    totalCenterX /= circles_.size();
    totalCenterY /= circles_.size();
    return Circle(totalRadius, totalCenterX, totalCenterY, 0.0f);
};

Circle Simulation::medianCircle()
{
    float medianRadius = 0;
    float medianCenterX = 0;
    float medianCenterY = 0;
    std::sort(
        circles_.begin(),
        circles_.end(),
        [](Circle &a, Circle &b) {
            return (a.getRadius() < b.getRadius());
        });
    if (circles_.size() % 2 == 0)
    {
        medianRadius += 0.5f * circles_[circles_.size() / 2 - 1].getRadius();
        medianRadius += 0.5f * circles_[circles_.size() / 2].getRadius();
    }
    else
    {
        medianRadius = circles_[circles_.size() / 2].getRadius();
    }
    std::sort(circles_.begin(), circles_.end(),
              [](Circle &a, Circle &b) {
                  return (a.getCenterX() < b.getCenterX());
              });
    if (circles_.size() % 2 == 0)
    {
        medianCenterX += 0.5f * circles_[circles_.size() / 2 - 1].getCenterX();
        medianCenterX += 0.5f * circles_[circles_.size() / 2].getCenterX();
    }
    else
    {
        medianCenterX = circles_[circles_.size() / 2].getCenterX();
    }
    std::sort(circles_.begin(), circles_.end(),
              [](Circle &a, Circle &b) {
                  return (a.getCenterY() < b.getCenterY());
              });
    if (circles_.size() % 2 == 0)
    {
        medianCenterY += 0.5f * circles_[circles_.size() / 2 - 1].getCenterY();
        medianCenterY += 0.5f * circles_[circles_.size() / 2].getCenterY();
    }
    else
    {
        medianCenterY = circles_[circles_.size() / 2].getCenterY();
    }
    return Circle(medianRadius, medianCenterX, medianCenterY, 0.0f);
};


void Simulation::setCircles(const std::vector<Circle> circles){
    circles_ = circles;
};
void Simulation::setRectangles(const std::vector<Rectangle> rectangles){
    rectangles_ = rectangles;
};