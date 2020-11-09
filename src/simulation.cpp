#include "simulation.hpp"

Simulation::Simulation(unsigned int windowSizeX, unsigned int windowSizeY) : gui_(windowSizeX, windowSizeY),
                                                                             evolutionModule_(windowSizeX, windowSizeY)
{
    circles_ = std::shared_ptr<std::vector<Circle>>(new std::vector<Circle>);
    rectangles_ = std::shared_ptr<std::vector<Rectangle>>(new std::vector<Rectangle>);
    evolutionModule_.setVectors(circles_, rectangles_);
};

Simulation::Simulation(unsigned int windowSizeX, unsigned int windowSizeY,
                       unsigned int populationSize, unsigned int numberOfIterations) : gui_(windowSizeX, windowSizeY),
                                                                                       populationSize_(populationSize),
                                                                                       evolutionModule_(windowSizeX, windowSizeY, populationSize),
                                                                                       numberOfIterations_(numberOfIterations)

{
    circles_ = std::shared_ptr<std::vector<Circle>>(new std::vector<Circle>);
    rectangles_ = std::shared_ptr<std::vector<Rectangle>>(new std::vector<Rectangle>);
    evolutionModule_.setVectors(circles_, rectangles_);
    evolutionModule_.init(100.0f); // <-- THIS IS NOT FINAL (DEBUG)
};

void Simulation::run()
{

    while (gui_.isOpen() && numberOfIterations_ > 0)
    {
        evolutionModule_.calculateFunctionValues();
        drawToScreen(ALL);
        sf::sleep(sf::Time(sf::milliseconds(30)));
        drawToScreen(MEAN);
        sf::sleep(sf::Time(sf::milliseconds(30)));
        drawToScreen(MEDIAN);
        sf::sleep(sf::Time(sf::milliseconds(30)));
        drawToScreen(BEST);
        sf::sleep(sf::Time(sf::milliseconds(100)));

        iteration();
        
        sf::Event event;
        while (gui_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                gui_.close();
        }
        numberOfIterations_--;
    }
}

Gui *Simulation::getGui()
{
    return &gui_;
};

void Simulation::addRectangle(Rectangle rectangle)
{
    rectangles_->emplace_back(Rectangle(rectangle));
    gui_.addRectangle(rectangle);
};

void Simulation::drawToScreen(circle_types circleType)
{
    gui_.clear();
    gui_.drawDrawables();
    switch (circleType)
    {
    case MEAN:
        gui_.draw(gui_.shapeFromCircle(evolutionModule_.meanCircle(), sf::Color(255, 0, 255, 200)));
        break;
    case MEDIAN:
        gui_.draw(gui_.shapeFromCircle(evolutionModule_.medianCircle(), sf::Color(0, 255, 255, 200)));
        break;
    case ALL:
        for (auto &c : *circles_)
        {
            gui_.draw(gui_.shapeFromCircle(c));
        }
    case BEST:
        gui_.draw(gui_.shapeFromCircle(evolutionModule_.bestCircle()));
        std::cout << "\n"
                  << evolutionModule_.bestCircle().getFunctionValue() << "\n"; //DEBUG
        break;
    default:
        break;
    }
    gui_.display();
};

void Simulation::saveResults(circle_types circleType, std::string filename)
{
    gui_.clear();
    gui_.drawDrawables();
    switch (circleType)
    {
    case MEAN:
        gui_.draw(gui_.shapeFromCircle(evolutionModule_.meanCircle()));
        break;
    case MEDIAN:
        gui_.draw(gui_.shapeFromCircle(evolutionModule_.medianCircle()));
        break;
    case BEST:
        gui_.draw(gui_.shapeFromCircle(evolutionModule_.bestCircle()));
        break;
    default:
        break;
    }
    gui_.renderAndSave(filename);
};

void Simulation::iteration()
{
    std::vector<Circle> children;

    for (int i = 0; i < 300; ++i)
    {
        children.emplace_back(evolutionModule_.reproduction());
    }

    evolutionModule_.calculateFunctionValues(children);
    evolutionModule_.mutation(0.0f, 1.0f, 0.2f, 0.80f);
    evolutionModule_.succession(children, .2f);
}

void Simulation::setDelimiterForWriterModule(std::string delimiter)
{
    writerModule_.setDelimiter(delimiter);
}

void Simulation::setPathForWriterModule(std::string path)
{
    writerModule_.setPathToFile(path);
}