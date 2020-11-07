#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#include "rectangle.hpp"
#include "circle.hpp"
#include "gui.hpp"

class Simulation{
    Gui gui_;
    std::vector<Rectangle> rectangles_;
    std::vector<Circle> circles_;
public:
    Simulation(unsigned int windowSizeX, unsigned int windowSizeY);
    Circle meanCircle();
    Circle medianCircle();
    Gui * getGui();
    
    void setCircles(const std::vector<Circle> circles);
    void setRectangles(const std::vector<Rectangle> rectangles);
};

#endif