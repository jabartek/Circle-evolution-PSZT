#ifndef EVOLUTION_MODULE
#define EVOLUTION_MODULE
#include "circle.hpp"
#include "rectangle.hpp"
#include "randomNumberGenerator.hpp"

#include <vector>
#include <memory>
#include <iostream>

const float MUTATIONSTRENGTH = 0.2f;
const float MUTATIONLOWERBOUND = 0.0f;
const float MUTATIONUPPERBOUND = 1.0f;
const float MUTATIONTHRESHHOLD = 0.35f;

class EvolutionModule
{
    unsigned int populationStartSize_;
    float windowWidth_;
    float windowHeight_;
    std::shared_ptr<std::vector<Circle>> circles_;
    std::shared_ptr<std::vector<Rectangle>> rectangles_;

    Circle reproductionTournament();
    static bool comparator(Circle &circle1, Circle &circle2);
    float calculateOverlap(Circle circle, Rectangle rectangle);
    float section(float h, float r = 1);
    float g(float x, float h, float r = 1);
    float area(float x0, float x1, float h, float r);
    float area(float x0, float x1, float y0, float y1, float r);
    float area(float x0, float x1, float y0, float y1, float cx, float cy, float r);
    float calculateFuctionValue(Circle * circle);

public:
    EvolutionModule(float windowWidth, float windowHeight);
    EvolutionModule(float windowWidth, float windowHeight, unsigned int populationStartSize);
    void setWindowSize(float width, float height);
    void setVectors(std::shared_ptr<std::vector<Circle>> circles, std::shared_ptr<std::vector<Rectangle>> rectangles);
    void init(float maximumRadius);
    void mutation(float mutationLowerBound, float mutationUpperBound, float mutationStrength, float mutationThreshHold);
    Circle reproduction(bool test = false);
    void succession(std::vector<Circle> childrenPopulation, float elitePercentage);
    void calculateFunctionValues();
    void calculateFunctionValues(std::vector<Circle> circles);
    void setPopulationStartSize(unsigned int startSize);
    
    Circle meanCircle();
    Circle medianCircle();
    Circle bestCircle();
    Circle worstCircle();

    inline std::shared_ptr<std::vector<Circle>> getCircles(){return circles_;};
};

#endif