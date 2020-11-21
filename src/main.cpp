#include "main.hpp"
#include <string>

int main(int argc, char **argv)
{
    //RECTANGLES PARAMETERS
    float posX;
    float posY;
    float sizeX;
    float sizeY;
    std::vector<Rectangle> rectangles;
    //SIMULATION PARAMETERS
    unsigned int windowWidth;
    unsigned int windowHeight;
    unsigned int populationSize;
    unsigned int numberOfIterations;
    float radiusMutationStrength;
    float positionMutationStrength;
    float mutationThreshold;
    float eliteSize;
    //SPAWNING CIRCLES PARAMETERS
    float maximumRadius;
    float minX;
    float maxX;
    float minY;
    float maxY;
    //SAVING PARAMETERS
    bool toPictures;
    std::string pathToFile;
    std::string delimiter;
    std::string ans;
    if (argc < 2)
    {
        return 0;
    }
    std::string settingsFile(argv[1]);

    // if (argv[1] != "auto")
    // {
    std::cout << "Witaj PSZTY!" << std::endl;
    std::ifstream inputFile(settingsFile);
    if (inputFile.is_open())
    {
        unsigned int rectangleNum;
        inputFile >> rectangleNum;
        for (unsigned int i = 0; i < rectangleNum; i++)
        {
            inputFile >> posX;
            inputFile >> posY;
            inputFile >> sizeX;
            inputFile >> sizeY;
            rectangles.emplace_back(Rectangle(posX, posY, sizeX, sizeY));
        }
        inputFile >> maximumRadius;
        inputFile >> minX;
        inputFile >> maxX;
        inputFile >> minY;
        inputFile >> maxY;
        inputFile >> windowWidth;
        inputFile >> windowHeight;
        inputFile >> populationSize;
        inputFile >> numberOfIterations;
        inputFile >> radiusMutationStrength;
        inputFile >> positionMutationStrength;
        inputFile >> mutationThreshold;
        inputFile >> eliteSize;
        inputFile >> pathToFile;
        inputFile >> ans;
        std::transform(ans.begin(), ans.end(), ans.begin(), ::toupper);
        if (ans == "T")
            toPictures = true;
        else
            toPictures = false;
    }
    else
    {
        std::cout << "Failed to open file: " << settingsFile << "\n";
        return 0;
    }

    Simulation sim(windowWidth, windowHeight, populationSize, radiusMutationStrength, positionMutationStrength,
                     numberOfIterations,maximumRadius, minX, maxX, minY, maxY);
    for (auto v : rectangles)
    {
        sim.addRectangle(v);
    }
    sim.setMutationThreshholdForEvolutionModule(mutationThreshold);
    sim.setEliteSizeForEvolutionModule(eliteSize);
    sim.setPathForWriterModule(pathToFile);
    sim.setDelimiterForWriterModule("\t");
    sim.setPictures(toPictures);
    sim.run();

    return 0;
}