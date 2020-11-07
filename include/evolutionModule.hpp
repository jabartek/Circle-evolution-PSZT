#ifndef EVOLUTION_MODULE
#define EVOLUTION_MODULE

#include "main.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "randomNumberGenerator.hpp"

const float MUTATIONSTRENGTH = 0.2f;
const float MUTATIONLOWERBOUND = 0.0f;
const float MUTATIONUPPERBOUND = 1.0f;
const float MUTATIONTHRESHHOLD = 0.35f;

class EvolutionModule
{
    int populationStartSize;
    float windowWidth;
    float windowHeight;
    std::vector<Circle> circles_;
    std::vector<Rectangle> rectangles_;

    Circle reproductionTournament();
    static bool comparator(Circle &circle1, Circle &circle2);
    float calculateOverlap(Circle circle, Rectangle rectangle);
    float section(float h, float r = 1);
    float g(float x, float h, float r = 1);
    float area(float x0, float x1, float h, float r);
    float area(float x0, float x1, float y0, float y1, float r);
    float area(float x0, float x1, float y0, float y1, float cx, float cy, float r);

public:
    void init(float maximumRadius);
    void mutation(float mutationLowerBound, float mutationUpperBound, float mutationStrength, float mutationThreshHold);
    Circle reproduction();
    void succession(std::vector<Circle> childrenPopulation, float elitePercentage);
    float calculateFuctionValue(const Circle circle, const std::vector<Rectangle> rectangles);
    void calculateFunctionValues(const std::vector<Circle> circles, const std::vector<Rectangle> rectangles);
};

#endif