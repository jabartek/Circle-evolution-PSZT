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
#include "writerModule.hpp"

enum circle_types{
    WORST,MEDIAN, MEAN, BEST, ALL
};

class Simulation{

    bool pictures;
    unsigned int populationSize_;
    unsigned int numberOfIterations_;
    std::shared_ptr<std::vector<Rectangle>> rectangles_;
    std::shared_ptr<std::vector<Circle>> circles_;
    EvolutionModule evolutionModule_;
    WriterModule writerModule_;
    Gui gui_;

public:
    Simulation(unsigned int windowSizeX, unsigned int windowSizeY);
    Simulation(unsigned int windowSizeX, unsigned int windowSizeY, unsigned int populationSize, unsigned int numberOfIterations);
    Gui * getGui();
    void iteration();
    void run();
    
    // void setCircles(const std::vector<Circle> circles);
    // void setRectangles(const std::vector<Rectangle> rectangles);

    void addRectangle(Rectangle rectangle);
    void drawToScreen(circle_types circleType);
    void saveResults(circle_types circleType, std::string filename);
    void setPathForWriterModule(std::string path);
    void setDelimiterForWriterModule(std::string delimiter);
    
};

#endif