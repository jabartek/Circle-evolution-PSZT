#include "main.hpp"

int main()
{
    std::cout << "Witaj PSZTY!" << std::endl;

    std::vector<Rectangle> rectangles;
    rectangles.emplace_back(Rectangle(50, 50, 900, 900));
    // rectangles.emplace_back(Rectangle(50, 50, 300, 900));
    // rectangles.emplace_back(Rectangle(450, 50, 200, 200));
    // rectangles.emplace_back(Rectangle(400, 400, 550, 550));

    Simulation sim(1000, 1000);

    // sim.circles_.emplace_back(Circle(100, 500, 500, 0));
    // sim.circles_.emplace_back(Circle(20, 100, 100, 0));
    // sim.circles_.emplace_back(Circle(480, 600, 600, 0));
    // sim.circles_.emplace_back(Circle(200, 400, 400, 0));

    // auto c_mean = sim.meanCircle();
    // auto c_median = sim.medianCircle();

    // std::cout<<"\nMean: "<<c_mean.getCenterX()<<" "<<c_mean.getCenterY()<<" "<<c_mean.getRadius();
    // std::cout<<"\nMedian: "<<c_median.getCenterX()<<" "<<c_median.getCenterY()<<" "<<c_median.getRadius();

    for (auto v : rectangles)
    {
        sim.getGui()->addRectangle(v);
    }
    int i = 0;
    sf::Clock clock;
    while (sim.getGui()->isOpen() && i < 1000)
    {
        Circle circ(rand() * 50 / RAND_MAX, rand() * 1000 / RAND_MAX, rand() * 1000 / RAND_MAX, 0);

        float val = calculateFuctionValue(circ, rectangles);

        // std::cout<<val<<std::endl;
        if (val > 0.01)
        {
            sf::CircleShape cShape = Gui::shapeFromCircle(circ);
            sim.getGui()->clear();

            sim.getGui()->drawDrawables();

            sim.getGui()->draw(cShape);
            sim.getGui()->display();
            // sim.getGui()->renderAndSave(std::to_string(i)+".tga");
        }
        i++;

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