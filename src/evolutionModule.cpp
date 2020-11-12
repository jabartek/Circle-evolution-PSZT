#include "evolutionModule.hpp"

EvolutionModule::EvolutionModule(float windowWidth, float windowHeight) : windowWidth_(windowWidth), windowHeight_(windowHeight){};

EvolutionModule::EvolutionModule(float windowWidth, float windowHeight, unsigned int populationStartSize, float mutationStrength) 
                : windowWidth_(windowWidth), windowHeight_(windowHeight), populationStartSize_(populationStartSize),
                mutationStrength_(mutationStrength){};

void EvolutionModule::setVectors(std::shared_ptr<std::vector<Circle>> circles, std::shared_ptr<std::vector<Rectangle>> rectangles)
{
    circles_ = circles;
    rectangles_ = rectangles;
}

void EvolutionModule::init(float minX, float maxX, float minY, float maxY,float maximumRadius)
{
    RandomNumberGenerator<float> gen(0.0f, maximumRadius);
    for (int i = 0; i < populationStartSize_; i++)
    {
        float radius = gen.get(0.0f, maximumRadius);
        float centerX = gen.get(minX, maxX);
        float centerY = gen.get(minY, maxY);
        circles_->emplace_back(Circle(radius, centerX, centerY));
    }
}

Circle EvolutionModule::mutation(float mutationLowerBound, float mutationUpperBound, Circle circle)
{
    RandomNumberGenerator<float> gen(mutationLowerBound, mutationUpperBound);
    RandomNumberGenerator<float> genAngle(0.0f, 2*pi);
        if (gen.get() < mutationThreshhold_)
            circle.setRadius(gen.getNormal(circle.getRadius(), circle.getRadius() * mutationStrength_));
        else {
            float angle = genAngle.get();
            float distance = gen.getNormal(0.0f, windowWidth_ * mutationStrength_);
            circle.setCenterX(circle.getCenterX() + distance * cos(angle));
            circle.setCenterY(circle.getCenterY() + distance * sin(angle));
        }
        return circle;
}

Circle EvolutionModule::reproduction(bool test)
{
    Circle circle = reproductionTournament();
    return mutation(0.0,1.0, circle);
}

Circle EvolutionModule::reproductionTournament()
{
    RandomNumberGenerator<int> gen(0, circles_->size() - 1);
    Circle knight1 = (*circles_)[gen.get()];
    Circle knight2 = (*circles_)[gen.get()];
    if ((knight1.getFunctionValue() - knight2.getFunctionValue()) > 0)
    {
        return knight1;
    }
    return knight2;
}

void EvolutionModule::succession(std::vector<Circle> childrenPopulation)
{
    int eliteSize = std::floor(eliteSize_ * circles_->size());
    std::sort(childrenPopulation.begin(), childrenPopulation.end(), &comparator);
    std::sort(circles_->begin(), circles_->end(), &comparator);
    auto firstChild = childrenPopulation.begin();
    for (auto i = circles_->size() - 1; i >= eliteSize; i--)
    {
        (*circles_)[i] = *(firstChild++);
    }
}

bool EvolutionModule::comparator(Circle &circle1, Circle &circle2)
{
    return circle1.getFunctionValue() > circle2.getFunctionValue();
}



void EvolutionModule::setWindowSize(float width, float height)
{
    windowWidth_ = width;
    windowHeight_ = height;
};

void EvolutionModule::setPopulationStartSize(unsigned int startSize)
{
    populationStartSize_ = startSize;
};

Circle EvolutionModule::meanCircle()
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

Circle EvolutionModule::bestCircle(){
    std::sort(circles_->begin(),circles_->end(),&comparator);
    return (*circles_)[0];
}

Circle EvolutionModule::worstCircle(){
    std::sort(circles_->begin(),circles_->end(),&comparator);
    return (*circles_)[(*circles_).size()-1];
}

Circle EvolutionModule::medianCircle()
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

void EvolutionModule::calculateFunctionValues()
{
    for (auto &v : *circles_)
    {
        calculateFuctionValue(&v);
    }
}

void EvolutionModule::calculateFunctionValues(std::vector<Circle> circles)
{
    for (auto &v : circles)
    {
        calculateFuctionValue(&v);
    }
}

float EvolutionModule::calculateFuctionValue(Circle *circle)
{
    float totalOverlap = 0.0f;
    for (auto rectangle : *rectangles_)
    {
        totalOverlap += calculateOverlap(*circle, rectangle);
    }
    Rectangle proxy(circle->getCenterX() - circle->getRadius() * 1.25f, circle->getCenterY() - circle->getRadius() * 1.25f, circle->getRadius() * 2.5f, circle->getRadius() * 2.5f);
    float offRec = calculateOverlap(*circle, proxy) - totalOverlap;
    float result = totalOverlap - offRec * OFF_RECTANGLE_PENALTY;
    circle->setFunctionValue(result);
    return result;
}


void EvolutionModule::setMutationThreshhold(float mutationThreshhold){
    this->mutationThreshhold_= mutationThreshhold;
}

void EvolutionModule::setEliteSize(float eliteSize){
    this->eliteSize_ = eliteSize;
}

float EvolutionModule::calculateOverlap(Circle circle, Rectangle rectangle)
{
    return area(
        rectangle.getPosX(),
        rectangle.getPosX() + rectangle.getSizeX(),
        rectangle.getPosY(),
        rectangle.getPosY() + rectangle.getSizeY(),
        circle.getCenterX(),
        circle.getCenterY(),
        circle.getRadius());
}

/*
    The following code is licensed under CC BY-SA 3.0 https://creativecommons.org/licenses/by-sa/3.0/
    from *the swine* on StackOverflow https://stackoverflow.com/a/32698993

    Changes include:
     * Reformatting
     * Removing asserts
     * Removal of default arguments as those stay in .hpp
*/

float EvolutionModule::section(float h, float r) // returns the positive root of intersection of line y = h with circle centered at the origin and radius r
{
    // assert(r >= 0);                           // assume r is positive, leads to some simplifications in the formula below (can factor out r from the square root)
    return (h < r) ? sqrt(r * r - h * h) : 0; // http://www.wolframalpha.com/input/?i=r+*+sin%28acos%28x+%2F+r%29%29+%3D+h
}

float EvolutionModule::g(float x, float h, float r) // indefinite integral of circle segment
{
    return .5f * (sqrt(1 - x * x / (r * r)) * x * r + r * r * asin(x / r) - 2 * h * x); // http://www.wolframalpha.com/input/?i=r+*+sin%28acos%28x+%2F+r%29%29+-+h
}

float EvolutionModule::area(float x0, float x1, float h, float r) // area of intersection of an infinitely tall box with left edge at x0, right edge at x1, bottom edge at h and top edge at infinity, with circle centered at the origin with radius r
{
    if (x0 > x1)
        std::swap(x0, x1); // this must be sorted otherwise we get negative area
    float s = section(h, r);
    return g(std::max(-s, std::min(s, x1)), h, r) - g(std::max(-s, std::min(s, x0)), h, r); // integrate the area
}

float EvolutionModule::area(float x0, float x1, float y0, float y1, float r) // area of the intersection of a finite box with a circle centered at the origin with radius r
{
    if (y0 > y1)
        std::swap(y0, y1); // this will simplify the reasoning
    if (y0 < 0)
    {
        if (y1 < 0)
            return area(x0, x1, -y0, -y1, r); // the box is completely under, just flip it above and try again
        else
            return area(x0, x1, 0, -y0, r) + area(x0, x1, 0, y1, r); // the box is both above and below, divide it to two boxes and go again
    }
    else
    {
        // assert(y1 >= 0);                                  // y0 >= 0, which means that y1 >= 0 also (y1 >= y0) because of the swap at the beginning
        return area(x0, x1, y0, r) - area(x0, x1, y1, r); // area of the lower box minus area of the higher box
    }
}

float EvolutionModule::area(float x0, float x1, float y0, float y1, float cx, float cy, float r) // area of the intersection of a general box with a general circle
{
    x0 -= cx;
    x1 -= cx;
    y0 -= cy;
    y1 -= cy;
    // get rid of the circle center

    return area(x0, x1, y0, y1, r);
}

/*
    End of code licensed from *the swine*
*/
