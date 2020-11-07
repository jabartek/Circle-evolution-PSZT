#include "simulation.hpp"

Simulation::Simulation(unsigned int windowSizeX, unsigned int windowSizeY) : gui_(windowSizeX, windowSizeY),
                                                                             evolutionModule_(windowSizeX, windowSizeY){
                                                                                 circles_ = std::shared_ptr<std::vector<Circle>>(new std::vector<Circle>);
                                                                                 rectangles_ = std::shared_ptr<std::vector<Rectangle>>(new std::vector<Rectangle>);
                                                                                 evolutionModule_.setVectors(circles_, rectangles_);
                                                                             };

Simulation::Simulation(unsigned int windowSizeX, unsigned int windowSizeY, unsigned int populationSize) : gui_(windowSizeX, windowSizeY),
                                                                                                          populationSize(populationSize),
                                                                                                          evolutionModule_(windowSizeX, windowSizeY, populationSize){
                                                                                                            circles_ = std::shared_ptr<std::vector<Circle>>(new std::vector<Circle>);
                                                                                                            rectangles_ = std::shared_ptr<std::vector<Rectangle>>(new std::vector<Rectangle>);
                                                                                                            evolutionModule_.setVectors(circles_, rectangles_);
                                                                                                            evolutionModule_.init(100.0f); // <-- THIS IS NOT FINAL (DEBUG) 
                                                                                                          };

Gui * Simulation::getGui()
{
    return &gui_;
};

EvolutionModule * Simulation::getEvolutionModule(){
    return &evolutionModule_;
};

Circle Simulation::meanCircle()
{
    auto totalRadius = 0.0f;
    auto totalCenterX = 0.0f;
    auto totalCenterY = 0.0f;
    for (auto c : *circles_)
    {
        totalRadius += c.getRadius();
        totalCenterX += c.getCenterX();
        totalCenterY += c.getCenterY();
    }
    totalRadius /= circles_->size();
    totalCenterX /= circles_->size();
    totalCenterY /= circles_->size();
    return Circle(totalRadius, totalCenterX, totalCenterY, 0.0f);
};

Circle Simulation::medianCircle()
{
    float medianRadius = 0;
    float medianCenterX = 0;
    float medianCenterY = 0;
    std::sort(
        circles_->begin(),
        circles_->end(),
        [](Circle &a, Circle &b) {
            return (a.getRadius() < b.getRadius());
        });
    if (circles_->size() % 2 == 0)
    {
        medianRadius += 0.5f * (*circles_)[circles_->size() / 2 - 1].getRadius();
        medianRadius += 0.5f * (*circles_)[circles_->size() / 2].getRadius();
    }
    else
    {
        medianRadius = (*circles_)[circles_->size() / 2].getRadius();
    }
    std::sort(circles_->begin(), circles_->end(),
              [](Circle &a, Circle &b) {
                  return (a.getCenterX() < b.getCenterX());
              });
    if (circles_->size() % 2 == 0)
    {
        medianCenterX += 0.5f * (*circles_)[circles_->size() / 2 - 1].getCenterX();
        medianCenterX += 0.5f * (*circles_)[circles_->size() / 2].getCenterX();
    }
    else
    {
        medianCenterX = (*circles_)[circles_->size() / 2].getCenterX();
    }
    std::sort(circles_->begin(), circles_->end(),
              [](Circle &a, Circle &b) {
                  return (a.getCenterY() < b.getCenterY());
              });
    if (circles_->size() % 2 == 0)
    {
        medianCenterY += 0.5f * (*circles_)[circles_->size() / 2 - 1].getCenterY();
        medianCenterY += 0.5f * (*circles_)[circles_->size() / 2].getCenterY();
    }
    else
    {
        medianCenterY = (*circles_)[circles_->size() / 2].getCenterY();
    }
    return Circle(medianRadius, medianCenterX, medianCenterY, 0.0f);
};

Circle Simulation::bestCircle(){
    std::sort(
        circles_->begin(),
        circles_->end(),
        [](Circle &a, Circle &b) {
            return (a.getFunctionValue() > b.getFunctionValue());
        });
    return (*circles_)[0];
}


void Simulation::addRectangle(Rectangle rectangle){
    rectangles_->emplace_back(Rectangle(rectangle));
    gui_.addRectangle(rectangle);
};

void Simulation::drawToScreen(circle_types circleType){
    gui_.clear();
    gui_.drawDrawables();
    switch (circleType)
    {
    case MEAN:
        gui_.draw(gui_.shapeFromCircle(meanCircle(), sf::Color(255, 0, 255, 200)));
        break;
    case MEDIAN:
        gui_.draw(gui_.shapeFromCircle(medianCircle(), sf::Color(0, 255, 255, 200)));
        break;
    case ALL:
        for(auto &c : *circles_){
            gui_.draw(gui_.shapeFromCircle(c));
        }
    case BEST:
        gui_.draw(gui_.shapeFromCircle(bestCircle()));
        std::cout<<"\n"<<bestCircle().getFunctionValue()<<"\n"; //DEBUG
        break;
    default:
        break;
    }
    gui_.display();
};

void Simulation::drawToPic(circle_types circleType, std::string filename){
    gui_.clear();
    gui_.drawDrawables();
    switch (circleType)
    {
    case MEAN:
        gui_.draw(gui_.shapeFromCircle(meanCircle()));
        break;
    case MEDIAN:
        gui_.draw(gui_.shapeFromCircle(medianCircle()));
        break;
    case BEST:
        gui_.draw(gui_.shapeFromCircle(bestCircle()));
        break;
    default:
        break;
    }
    gui_.renderAndSave(filename);
};