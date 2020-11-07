#include "evolutionModule.hpp"

void EvolutionModule::init(float maximumRadius)
{
    RandomNumberGenerator<float> gen(0.0f, maximumRadius);
    for (int i = 0; i < populationStartSize_; i++)
    {
        float radius = gen.get();
        float centerX = gen.get(0.0f, windowWidth_);
        float centerY = gen.get(0.0f, windowHeight_);
        circles_.emplace_back(Circle(radius, centerX, centerY));
    }
}

void EvolutionModule::mutation(float mutationLowerBound, float mutationUpperBound, float mutationStrength, float mutationThreshHold)
{
    RandomNumberGenerator<float> gen(mutationLowerBound, mutationUpperBound);
    for (Circle &circle : circles_)
    {
        if (gen.get() > mutationThreshHold)
            circle.setRadius(gen.getNormal(circle.getRadius(), circle.getRadius() * mutationStrength));
        if (gen.get() > mutationThreshHold)
            circle.setCenterX(gen.getNormal(circle.getCenterX(), circle.getCenterX() * mutationStrength));
        if (gen.get() > mutationThreshHold)
            circle.setCenterY(gen.getNormal(circle.getCenterY(), circle.getCenterY() * mutationStrength));
    }                  
}
Circle EvolutionModule::reproduction(bool test = false)
{
    Circle parent1 = reproductionTournament();
    Circle parent2 = reproductionTournament();
    if (test){
        std::cout << "Parent1: " << parent1.getFunctionValue() << " " << parent1.getCenterX() << " " << parent1.getCenterY() << " " << parent1.getRadius() << std::endl;
        std::cout << "Parent2: " << parent2.getFunctionValue() << " " << parent2.getCenterX() << " " << parent2.getCenterY() << " " << parent2.getRadius() << std::endl;
    }
    RandomNumberGenerator<int> gen(0, circles_.size() - 1,0.5,0.1);
    float weightRadius = gen.getNormal();
    float weightCentercX = gen.getNormal();
    float weightCentercY = gen.getNormal();
    float childRadius = parent1.getRadius() * weightRadius + parent2.getRadius() * (1 - weightRadius);
    float childCenterX = parent1.getCenterX() * weightCentercX + parent2.getCenterX() * (1 - weightCentercX);
    float childCenterY = parent1.getCenterY() * weightCentercY + parent2.getCenterY() * (1 - weightCentercY);
    return Circle(childRadius, childCenterX, childCenterY);
}

Circle EvolutionModule::reproductionTournament()
{
    RandomNumberGenerator<int> gen(0, circles_.size() - 1);
    Circle knight1 = circles_[gen.get()];
    Circle knight2 = circles_[gen.get()];
    if ((knight1.getFunctionValue() - knight2.getFunctionValue()) > 0)
    {
        return knight1;
    }
    return knight2;
}
void EvolutionModule::succession(std::vector<Circle> childrenPopulation, float elitePercentage)
{
    int eliteSize = std::floor(elitePercentage * circles_.size());
    std::sort(childrenPopulation.begin(), childrenPopulation.end(), &comparator);
    std::sort(circles_.begin(), circles_.end(), &comparator);
    auto firstChild = childrenPopulation.begin();
    for (auto i = circles_.size() - 1; i > circles_.size() - (eliteSize + 1); i--)
    {
        circles_[i] = *(firstChild++);
    }
}

bool EvolutionModule::comparator(Circle &circle1, Circle &circle2)
{
    return circle1.getFunctionValue() > circle2.getFunctionValue();
}

std::vector<Circle> EvolutionModule::getCircles()
{
    return this->circles_;
}