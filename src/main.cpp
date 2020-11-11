#include "main.hpp"
#include <string>

int main(int argc, char** argv)
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
    float mutationStrength;
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
    std::cout<<"Dlugosc prostokata:"<<std::endl;
    std::cin>>sizeY;
    rectangles.emplace_back(Rectangle(posX, posY, sizeX, sizeY));
    }
    
    std::cout<<"----------------------------------------------------"<<std::endl;
    std::cout<< " KONIEC inicjalizacji zmiennych prostokatow"<<std::endl;
    std::cout<<"----------------------------------------------------"<<std::endl;

    std::cout<<"----------------------------------------------------"<<std::endl;
    std::cout<< "Inicjalizacja zmiennych kolek"<<std::endl;
    std::cout<<"----------------------------------------------------"<<std::endl;
    std::cout<<"Podaj maksymalny poczatkowy promien kola"<<std::endl;
    std::cin>>maximumRadius;
    std::cout<<"Podaj wymiary obszaru poczatkowego kolek:"<<std::endl;
    std::cout<<"Minimalny rozmiar X: " <<std::endl;
    std::cin>>minX;
    std::cout<<"Maksymalny rozmiar X: " <<std::endl;
    std::cin>>maxX;
    std::cout<<"Minimalny rozmiar Y: " <<std::endl;
    std::cin>>minY;
    std::cout<<"Maksymalny rozmiar Y: " <<std::endl;
    std::cin>>maxY;
    std::cout<<"----------------------------------------------------"<<std::endl;
    std::cout<< "KONIEC inicjalizacji zmiennych kółek"<<std::endl;
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
    std::cout<<"Sila mutacji: (parametr odchylenia standardowego w przypadku rozkladu normalnego - liczba zmiennoprzecinkowa):"<<std::endl;
    std::cin>>mutationStrength;
    std::cout<<"Jak duzo osobnikow (srednio) ma mutowac: (liczba z zakresu 0.0-1.0)"<<std::endl;
    std::cin>> mutationThreshold;
    std::cout<<"Jaki procent najgorszych osobnikow z populacji rodzicielskiej ma byc zastepowane przez najlepsze osobniki z populacji potomnej: "<<std::endl;
    std::cout<<"liczba z zakresu (0.0 - 1.0)"<<std::endl;
    std::cin>> eliteSize;

    std::cout<<"----------------------------------------------------"<<std::endl;
    std::cout<< " KONIEC inicjalizacji zmiennych symulacji"<<std::endl;
    std::cout<<"----------------------------------------------------"<<std::endl;

    std::cout<<"----------------------------------------------------"<<std::endl;
    std::cout<< "Inicjalizacja zmiennych zapisywania wynikow"<<std::endl;
    std::cout<<"----------------------------------------------------"<<std::endl;
    std::cout<<"Podaj sciezke do pliku:"<<std::endl;
    std::cin>> pathToFile;
    // std::cout<<"Podaj separator w pliku: "<<std::endl;
    // std::cin>> delimiter;
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
    mutationStrength = 0.3;
    mutationThreshold=0.3;
    eliteSize= 0.2;
    maximumRadius = 100.0f;
    minX = 0.0;
    maxX= windowWidth;
    minY = 0.0;
    maxY = windowHeight;
    toPictures = false;
    }

    Simulation sim(windowWidth, windowHeight, populationSize, mutationStrength, numberOfIterations,
                    maximumRadius,minX, maxX,  minY, maxY);
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