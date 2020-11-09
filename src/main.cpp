#include "main.hpp"
#include <string>

int main(int argc, char* argv[])
{
    unsigned int posX;
    unsigned int posY;
    unsigned int sizeX;
    unsigned int sizeY;
    std::vector<Rectangle> rectangles;
    unsigned int windowWidth;
    unsigned int windowHeight;
    unsigned int populationSize;
    unsigned int numberOfIterations;
    bool toPictures;
    std::string pathToFile;
    std::string delimiter;
    std::string ans;

    if( argv[1] != "auto"){
    std::cout << "Witaj PSZTY!" << std::endl;
    std::cout<<"----------------------------------------------------"<<std::endl;
    std::cout<< "Inicjalizacja zmiennych prostokatow"<<std::endl;
    std::cout<<"----------------------------------------------------"<<std::endl;
    std::cout<<"Liczba prostokatow"<<std::endl;
    unsigned int rectangleNum;
    std::cin>>rectangleNum;
    for (int i=0; i<rectangleNum; i++){

    std::cout<<"Podaj parametry prostokata (liczby calkowite):"<<std::endl;
    std::cout<<"Wspolrzedna X lewego gornego rogu:"<<std::endl;
    std::cin>>posX;
    std::cout<<"Wspolrzedna Y lewego gornego rogu:"<<std::endl;
    std::cin>>posY;
    std::cout<<"Szerokosc prostokata:"<<std::endl;
    std::cin>>sizeX;
    std::cout<<"Dlugosc prostoksta:"<<std::endl;
    std::cin>>sizeY;
    rectangles.emplace_back(Rectangle(posX, posY, sizeX, sizeY));
    }
    std::cout<<"----------------------------------------------------"<<std::endl;
    std::cout<< " KONIEC inicjalizacji zmiennych prostokatow"<<std::endl;
    std::cout<<"----------------------------------------------------"<<std::endl;

    std::cout<<"----------------------------------------------------"<<std::endl;
    std::cout<< "Inicjalizacja zmiennych symulacji"<<std::endl;
    std::cout<<"----------------------------------------------------"<<std::endl;


    std::cout<<"Podaj parametry symulacji (liczby calkowite):"<<std::endl;
    std::cout<<"Szerokosc okna symulacji:"<<std::endl;
    std::cin>>windowWidth;
    std::cout<<"Wysokosc okna symulacji:"<<std::endl;
    std::cin>>windowHeight;
    std::cout<<"Wielkosc populacji: " <<std::endl;
    std::cin>>populationSize;
    std::cout<<"Ilosc iteracji: " <<std::endl;
    std::cin>>numberOfIterations;

    std::cout<<"----------------------------------------------------"<<std::endl;
    std::cout<< " KONIEC inicjalizacji zmiennych symulacji"<<std::endl;
    std::cout<<"----------------------------------------------------"<<std::endl;

    std::cout<<"----------------------------------------------------"<<std::endl;
    std::cout<< "Inicjalizacja zmiennych zapisywania wynikow"<<std::endl;
    std::cout<<"----------------------------------------------------"<<std::endl;
    std::cout<<"Podaj sciezke do pliku:"<<std::endl;
    std::cin>> pathToFile;
    std::cout<<"Podaj separator w pliku: "<<std::endl;
    std::cin>> delimiter;
    std::cout<<"Czy zapisywac obrazki do pliku? [T\\N]" <<std::endl;
    std::cin>>ans;
    std::transform(ans.begin(), ans.end(),ans.begin(), ::toupper);
    if(ans == "T"){
        toPictures = true;
    }else{
        toPictures = false;
    }

    } else{
    posX=650;
    posY=650;
    sizeX= 300;
    sizeY=300;
    std::vector<Rectangle> rectangles;
    rectangles.emplace_back(Rectangle(posX,posY,sizeX,sizeY));
    windowWidth = 1000;
    windowHeight = 1000;
    populationSize = 100;
    numberOfIterations = 300;
    toPictures = false;
    }

    Simulation sim(windowWidth, windowHeight, populationSize, numberOfIterations);
    for (auto v : rectangles)
    {
        sim.addRectangle(v);
    }

    sim.run();


    return 0;
}