#include "main.hpp"

int main()
{
    std::cout << "Witaj PSZTY!" << std::endl;

    std::vector<Rectangle> rectangles;
    rectangles.emplace_back(Rectangle(650, 650, 300, 300));
    // rectangles.emplace_back(Rectangle(50, 50, 300, 900));
    // rectangles.emplace_back(Rectangle(450, 50, 200, 200));
    // rectangles.emplace_back(Rectangle(400, 400, 550, 550));

    Simulation sim(1000, 1000, 100);

    for (auto v : rectangles)
    {
        sim.addRectangle(v);
    }
    int i = 0;
    sf::Clock clock;
    while (sim.getGui()->isOpen() && i < 1000)
    {
        sim.getEvolutionModule()->calculateFunctionValues();
        sim.drawToScreen(ALL);
        sf::sleep(sf::Time(sf::milliseconds(30)));
        sim.drawToScreen(MEAN);
        sf::sleep(sf::Time(sf::milliseconds(30)));
        sim.drawToScreen(MEDIAN);
        sf::sleep(sf::Time(sf::milliseconds(30)));
        sim.drawToScreen(BEST);
        sf::sleep(sf::Time(sf::milliseconds(100)));
        
        std::vector<Circle> children;

        for(int i =0; i< 300; ++i){
            children.emplace_back(sim.getEvolutionModule()->reproduction());
        }

        sim.getEvolutionModule()->calculateFunctionValues(children);
        sim.getEvolutionModule()->mutation(0.0f, 1.0f, 0.2f, 0.80f);
        sim.getEvolutionModule()->succession(children, .2f);
        
        sf::Event event;
        while (sim.getGui()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                sim.getGui()->close();
        }
    }

    auto time1 = clock.getElapsedTime();
    std::cout << "\n"
              << time1.asSeconds();
    return 0;
}