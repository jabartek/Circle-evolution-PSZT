#include "main.hpp"
#include "evolutionModule.hpp"

    void EvolutionModule::init(float maximumRadius){
        RandomNumberGenerator<float> gen(0.0f, maximumRadius);
        for(int i =0; i< populationStartSize; i++){
            float radius = gen.get();
            float centerX = gen.get(0.0f, windowWidth);
            float centerY = gen.get(0.0f, windowHeight);
            circles_.emplace_back(Circle(radius,centerX, centerY));
        }
    }

    void EvolutionModule::mutation(float mutationLowerBound, float mutationUpperBound, float mutationStrength,float mutationThreshHold){
        RandomNumberGenerator<float> gen(mutationLowerBound,mutationLowerBound);
        for(Circle circle: circles_){
        //We check if we can start mutation for this particular circle
            if (gen.get() > mutationThreshHold)
                circle.setRadius(gen.getNormal(circle.getRadius(),circle.getRadius()*mutationStrength));
            if(gen.get() > mutationThreshHold)
                 circle.setCenterX(gen.getNormal(circle.getCenterX(),circle.getCenterX()*mutationStrength));
            if(gen.get() > mutationThreshHold)
                circle.setCenterY(gen.getNormal(circle.getCenterY(),circle.getCenterY()*mutationStrength));
        }
   
    }
    Circle EvolutionModule::reproduction(){
        RandomNumberGenerator<int> gen(0,circles_.size());
        Circle parent1 = reproductionTournament();
        Circle parent2 = reproductionTournament();
        float childRadius = parent1.getRadius()*gen.getNormal() + parent2.getRadius()*(1-gen.getNormal());
        float childCenterX = parent1.getCenterX()* gen.getNormal() + parent2.getCenterX()*(1-gen.getNormal());
        float childCenterY = parent1.getCenterY()*gen.getNormal() + parent2.getCenterY()*(1-gen.getNormal());
        return Circle(childRadius, childCenterX, childCenterY);
    }

    Circle  EvolutionModule::reproductionTournament(){
        RandomNumberGenerator<int> gen(0,circles_.size());
        Circle knight1 = circles_[gen.get()];
        Circle knight2 = circles_[gen.get()];
        if ((knight1.getFunctionValue() - knight2.getFunctionValue())>0){
            return knight1;
        }
        return knight2;

    }
    void EvolutionModule::succession(std::vector<Circle> childrenPopulation,float elitePercentage){
        int eliteSize = std::floor(elitePercentage * circles_.size());
        std::sort(childrenPopulation.begin(), childrenPopulation.end(), &comparator);
        std::sort(circles_.begin(), circles_.end(), &comparator);
        auto firstChild = childrenPopulation.begin();
        for(auto i = circles_.size()-1; i > circles_.size()-(eliteSize+1); i--){
            circles_[i] = *(firstChild++);
        }
    }
    
    bool EvolutionModule::comparator(Circle& circle1, Circle& circle2){
        return circle1.getFunctionValue() < circle2.getFunctionValue();
    }