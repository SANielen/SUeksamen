#include <cmath>
#include <string>
#include "hero.hpp"
#include <iostream>

class displays{

public:
displays(){};

void bootMenuDefault(){
    std::cout << "--------------" << std::endl;
    std::cout << "Please enter a valid number" << std::endl;
    std::cout << "(1) New Game" << std::endl;
    std::cout << "(2) Load Game" << std::endl;
    std::cout << "(0) Exit game" << std::endl;
    std::cout << "--------------" << std::endl;
};

void bootMenu(){
    std::cout << "--------------" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "(1) New Game" << std::endl;
    std::cout << "(2) Load Game" << std::endl;
    std::cout << "(0) Exit game" << std::endl;
    std::cout << "--------------" << std::endl;
}


void startMenu(hero player){
    std::cout << "--------------" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "Enter your Hero's name" << std::endl;
    std::cout << " " << std::endl;
    std::cout << " " << std::endl;
    std::cout << "--------------" << std::endl;
};

void mainMenu(hero player){
    std::cout << "--------------" << std::endl;
    std::cout << player.getHeroName() << " is currently has: " << player.getXP() << "XP, at lvl: " << player.getLvl() <<std::endl;
    std::cout << "(1) Fight monsters" << std::endl;
    std::cout << "(0) Pause Menu" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "--------------" << std::endl;
};



private:



};

