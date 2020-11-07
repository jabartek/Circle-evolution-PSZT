#include "evolutionModule.hpp"
void successionTest();
void mutationTest();
void reproductionTest();


int main(void)
{
    std::cout << "Succession TEST: " << std::endl;
    successionTest();

    std::cout << "Mutation TEST: " << std::endl;
    mutationTest();

    std::cout<<"Reproduction TEST" <<std::endl;
    reproductionTest();
}

void successionTest()
{
    EvolutionModule mod = EvolutionModule(100.0f, 100.0f, 10);
    mod.init(5.0f);
    Circle circle1 = Circle(1, 1, 1, 1);
    Circle circle2 = Circle(2, 2, 3, 3);
    Circle circle3 = Circle(2, 3, 4, 4);
    Circle circle4 = Circle(5, 5, 5, 5);
    std::vector<Circle> circles;
    circles.push_back(circle1);
    circles.push_back(circle2);
    circles.push_back(circle3);
    circles.push_back(circle4);
    std::cout << "Before succession" << std::endl;
    for (Circle circle : mod.getCircles())
    {
        std::cout << "Circle: " << circle.getFunctionValue() << " " << circle.getCenterX() << " " << circle.getCenterY() << std::endl;
    }
    mod.succession(circles, 0.4);
    std::cout << "After succesion" << std::endl;
    for (Circle circle : mod.getCircles())
    {
        std::cout << "Circle: " << circle.getFunctionValue() << " " << circle.getCenterX() << " " << circle.getCenterY() << std::endl;
    }
}

void mutationTest()
{
    EvolutionModule mod = EvolutionModule(100.0f, 100.0f, 10);
    mod.init(5.0f);
    std::cout << "Before mutation" << std::endl;
    for (Circle circle : mod.getCircles())
    {
        std::cout << "Circle: " << circle.getFunctionValue() << " " << circle.getCenterX() << " " << circle.getCenterY() << " " << circle.getRadius() << std::endl;
    }
    mod.mutation(0.0, 1.0, 0.1, 0.3);
    std::cout << "After mutation" << std::endl;
    for (Circle circle : mod.getCircles())
    {
        std::cout << "Circle: " << circle.getFunctionValue() << " " << circle.getCenterX() << " " << circle.getCenterY() << " " << circle.getRadius() << std::endl;
    }
}


void reproductionTest(){
   EvolutionModule mod = EvolutionModule(100.0f, 100.0f, 10);
   mod.init(5.0f);   
   std::cout<<"Before reproduction"<<std::endl;
   for(Circle circle: mod.getCircles()){
       Circle child = mod.reproduction(true);
       std::cout<<"Child: "<< child.getFunctionValue() << " " << child.getCenterX() << " " << child.getCenterY() << " " << child.getRadius() << std::endl;
   }
}
