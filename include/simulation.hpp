#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#include "rectangle.hpp"
#include "circle.hpp"
#include "gui.hpp"
#include "evolutionModule.hpp"


enum circle_types{
    MEDIAN, MEAN, BEST, ALL
};

class Simulation{
    Gui gui_;
    unsigned int populationSize;
    std::shared_ptr<std::vector<Rectangle>> rectangles_;
    std::shared_ptr<std::vector<Circle>> circles_;
    EvolutionModule evolutionModule_;
public:
    Simulation(unsigned int windowSizeX, unsigned int windowSizeY);
    Simulation(unsigned int windowSizeX, unsigned int windowSizeY, unsigned int);
    Circle meanCircle();
    Circle medianCircle();
    Circle bestCircle();
    Gui * getGui();
    
    // void setCircles(const std::vector<Circle> circles);
    // void setRectangles(const std::vector<Rectangle> rectangles);

    void addRectangle(Rectangle rectangle);

    void drawToScreen(circle_types circleType);
    void drawToPic(circle_types circleType, std::string filename);
    

    EvolutionModule * getEvolutionModule();
};

#endif