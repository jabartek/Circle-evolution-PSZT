#include "simulation.hpp"

Simulation::Simulation(unsigned int windowSizeX, unsigned int windowSizeY) : gui_(windowSizeX, windowSizeY),
                                                                             evolutionModule_(windowSizeX, windowSizeY)
{
    circles_ = std::shared_ptr<std::vector<Circle>>(new std::vector<Circle>);
    rectangles_ = std::shared_ptr<std::vector<Rectangle>>(new std::vector<Rectangle>);
    evolutionModule_.setVectors(circles_, rectangles_);
};

Simulation::Simulation(unsigned int windowSizeX, unsigned int windowSizeY,
                       unsigned int populationSize, float mutationStrength, 
                       unsigned int numberOfIterations,
                       float maximumRadius, float minX, float maxX, float minY, float maxY) 
                       : gui_(windowSizeX, windowSizeY),
                        populationSize_(populationSize),
                        evolutionModule_(windowSizeX, windowSizeY, populationSize,mutationStrength),
                        numberOfIterations_(numberOfIterations)

{
    circles_ = std::shared_ptr<std::vector<Circle>>(new std::vector<Circle>);
    rectangles_ = std::shared_ptr<std::vector<Rectangle>>(new std::vector<Rectangle>);
    evolutionModule_.setVectors(circles_, rectangles_);
    evolutionModule_.init(minX, maxX, minY, maxY,maximumRadius);
};

void Simulation::run()
{

    if(pictures){
        std::filesystem::create_directory("img/");
    }

    for(int i = 0; i < numberOfIterations_ && gui_.isOpen(); i++){
        evolutionModule_.calculateFunctionValues();

        Circle meanCircle = evolutionModule_.meanCircle();
        Circle medianCircle = evolutionModule_.medianCircle();
        Circle bestCircle = evolutionModule_.bestCircle();
        Circle worstCircle = evolutionModule_.worstCircle();

        std::vector<float> data = {};

        evolutionModule_.calculateFuctionValue(&meanCircle);
        data.emplace_back(meanCircle.getCenterX());
        data.emplace_back(meanCircle.getCenterY());
        data.emplace_back(meanCircle.getRadius());
        data.emplace_back(meanCircle.getFunctionValue());

        evolutionModule_.calculateFuctionValue(&medianCircle);
        data.emplace_back(medianCircle.getCenterX());
        data.emplace_back(medianCircle.getCenterY());
        data.emplace_back(medianCircle.getRadius());
        data.emplace_back(medianCircle.getFunctionValue());

        data.emplace_back(bestCircle.getCenterX());
        data.emplace_back(bestCircle.getCenterY());
        data.emplace_back(bestCircle.getRadius());
        data.emplace_back(bestCircle.getFunctionValue());

        data.emplace_back(worstCircle.getCenterX());
        data.emplace_back(worstCircle.getCenterY());
        data.emplace_back(worstCircle.getRadius());
        data.emplace_back(worstCircle.getFunctionValue());

        if(pictures){
            std::stringstream iteratorSs;
            iteratorSs << std::setw(8) << std::setfill('0') << i;
            std::string fileNum = iteratorSs.str();
            gui_.clear();
            gui_.drawDrawables();
            gui_.draw(gui_.shapeFromCircle(meanCircle, sf::Color(127, 255, 127, 160)));
            gui_.renderAndSave("img/" + fileNum + "_mean.tga");

            
            gui_.clear();
            gui_.drawDrawables();
            gui_.draw(gui_.shapeFromCircle(medianCircle, sf::Color(0, 255, 0, 160)));
            gui_.renderAndSave("img/" + fileNum + "_median.tga");

            
            gui_.clear();
            gui_.drawDrawables();
            gui_.draw(gui_.shapeFromCircle(bestCircle, sf::Color(0, 255, 255, 160)));
            gui_.renderAndSave("img/" + fileNum + "_best.tga");

            
            gui_.clear();
            gui_.drawDrawables();
            for(auto v : *circles_){
                gui_.draw(gui_.shapeFromCircle(v, sf::Color(255, 0, 255, 50)));
            }
            gui_.renderAndSave("img/" + fileNum + "_all.tga");
        }

        // drawToScreen(ALL);
        // sf::sleep(sf::Time(sf::milliseconds(30)));
        // drawToScreen(MEAN);
        // sf::sleep(sf::Time(sf::milliseconds(30)));
        // drawToScreen(MEDIAN);
        // sf::sleep(sf::Time(sf::milliseconds(30)));
        drawToScreen(BEST);
        // sf::sleep(sf::Time(sf::milliseconds(100)));

        auto lineData = packLine(i, data);

        writerModule_.writeLine(lineData);

        iteration();
        
        sf::Event event;
        while (gui_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                gui_.close();
        }
    }
}

std::vector<std::string> Simulation::packLine(int iteration, std::vector<float> data){
    std::vector<std::string> ret = {};
    ret.emplace_back(std::to_string(iteration));
    for(auto v : data){
        ret.emplace_back(std::to_string(v));
    }
    return ret;
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
        // std::cout << "\n"
        //           << evolutionModule_.bestCircle().getFunctionValue() << "\n"; //DEBUG
        break;
    default:
        break;
    }
    gui_.display();
};

void Simulation::drawToScreen(Circle circle, sf::Color color)
{
    gui_.clear();
    gui_.drawDrawables();
    gui_.draw(gui_.shapeFromCircle(circle, color));
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

    for (int i = 0; i < populationSize_; ++i)
    {
        children.emplace_back(evolutionModule_.reproduction());
    }

    evolutionModule_.calculateFunctionValues(children);
    evolutionModule_.succession(children);
}

void Simulation::setDelimiterForWriterModule(std::string delimiter)
{
    writerModule_.setDelimiter(delimiter);
}

void Simulation::setPathForWriterModule(std::string path)
{
    writerModule_.setPathToFile(path);
}

void Simulation::setEliteSizeForEvolutionModule(float eliteSize){
    evolutionModule_.setEliteSize(eliteSize);
}

void Simulation::setMutationThreshholdForEvolutionModule(float mutationThreshhold){
    evolutionModule_.setMutationThreshhold(mutationThreshhold);
}