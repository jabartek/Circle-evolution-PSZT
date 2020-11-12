#ifndef EVOLUTION_MODULE
#define EVOLUTION_MODULE
#include "circle.hpp"
#include "rectangle.hpp"
#include "randomNumberGenerator.hpp"

#include <vector>
#include <memory>
#include <iostream>

const float pi = 3.14159267f;

class EvolutionModule
{
    unsigned int populationStartSize_;
    float windowWidth_;
    float windowHeight_;
    float radiusMutationStrength_;
    float positionMutationStrength_;
    float eliteSize_;
    float mutationThreshhold_;
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


public:
    EvolutionModule(float windowWidth, float windowHeight);
    EvolutionModule(float windowWidth, float windowHeight, unsigned int populationStartSize, float radiusMutationStrength,
    float positionMutationStrength);
    void setWindowSize(float width, float height);
    void setVectors(std::shared_ptr<std::vector<Circle>> circles, std::shared_ptr<std::vector<Rectangle>> rectangles);
    void init(float minX, float maxX, float minY, float maxY, float maximumRadius);
    Circle mutation(float mutationLowerBound, float mutationUpperBound, Circle circle);
    Circle reproduction(bool test = false);
    void succession(std::vector<Circle> childrenPopulation);
    void calculateFunctionValues();
    void calculateFunctionValues(std::vector<Circle> circles);
    void setPopulationStartSize(unsigned int startSize);
    void setEliteSize(float eliteSize);
    void setMutationThreshhold(float mutationThreshhold);
    float calculateFuctionValue(Circle * circle);
    
    Circle meanCircle();
    Circle medianCircle();
    Circle bestCircle();
    Circle worstCircle();

    inline std::shared_ptr<std::vector<Circle>> getCircles(){return circles_;};
};

#endif