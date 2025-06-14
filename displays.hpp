#include <cmath>
#include <string>
#include <vector>
#include "hero.hpp"
#include "enemy.hpp"
#include "caveFactory.hpp"
#include <iostream>
#include <chrono>       //used for sleep
#include <thread>       //used for sleep
#include <filesystem>   //Used for locating saves

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

void loadSuccessful() {
    std::cout << "--------------" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "LOAD SUCCESSFUL" << std::endl;
    std::cout << " " << std::endl;
    std::cout << " " << std::endl;
    std::cout << "--------------" << std::endl;
    
}

void loadFailedMenu() {
    std::cout << "--------------" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "LOAD FAILED" << std::endl;
    std::cout << " " << std::endl;
    std::cout << " " << std::endl;
    std::cout << "--------------" << std::endl;
    
}

void loadFailedMenu2() {
    std::cout << "--------------" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "NO SAVE FOLDER FOUND" << std::endl;
    std::cout << " " << std::endl;
    std::cout << " " << std::endl;
    std::cout << "--------------" << std::endl;

}

bool loadMenu() {
    std::cout << "--------------" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "Type in the name of the game file you want to load:" << std::endl;

    std::string folder = "saves";
    int count = 0;

    if (!std::filesystem::exists(folder)) {
        loadFailedMenu2();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return false;
    } else {
        std::vector<std::filesystem::directory_entry> entries;

        // get saves
        for (std::filesystem::directory_iterator it(folder); it != std::filesystem::directory_iterator(); ++it) {
            if (it->path().extension() == ".txt") {
                entries.push_back(*it);
            }
        }
        //show saves
        for (size_t i = 0; i < entries.size(); ++i) {
            std::cout << "- " << entries[i].path().stem().string() << std::endl;
            count++;
        }

        if (count == 0) {
            loadFailedMenu();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return false;
        }
    }

    std::cout << "--------------" << std::endl;
    return true;
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
    std::cout << player.getHeroName() << " has: "
          << player.getXP() << " XP | "
          << "Gold: " << player.getGold() << " | "
          << "Level: " << player.getLvl() << std::endl;
    std::cout << " current weapon: " << player.getWeapon().getName()
    << " (Durability: " << player.getWeapon().getDurability() << ")" << std::endl;
    std::cout << "(1) Fight monsters" << std::endl;
    std::cout << "(2) Enter Cave" << std::endl;
    std::cout << "(3) Show statistics" << std::endl;
    std::cout << "(0) Pause Menu" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "--------------" << std::endl;
};

void fightMonsters(std::vector<enemy> list){
    std::cout << "--------------" << std::endl;
    std::cout << "Choose your opponent" <<  std::endl;
    for (int i = 0; i < list.size(); i++)
    {
        std::cout << "(" << i + 1 << ") " << list[i].getEnemyName() <<  std::endl;
        std::cout << "   DMG:" << list[i].getEnemyDmg() 
                  << " Health: " << list[i].getEnemyHP() 
                  << " XP: " << list[i].getEnemyXP() << std::endl;
    }
    std::cout << " " << std::endl;
    std::cout << "(0) nevermind. I'm a chicken" << std::endl;
    std::cout << "--------------" << std::endl;
};

void battleMenu(hero player, enemy foe){
    std::cout << "--------------" << std::endl;
    std::cout << player.getHeroName() << " HP: " << player.getHeroHP() << " | " <<  std::endl;
    std::cout << foe.getEnemyName() << " HP: " << foe.getEnemyHP() << " | " <<  std::endl;
    std::cout << "(1) Attack!" << std::endl;
    std::cout << "(2) Flee" << std::endl;
    std::cout << "(0) Pause" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "--------------" << std::endl;
};

void pauseMenu(){
    std::cout << "--------------" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "(1) Resume game" << std::endl;
    std::cout << "(2) Save game" << std::endl;
    std::cout << "(3) Load game" << std::endl;
    std::cout << "(0) Exit Game" << std::endl;
    std::cout << "--------------" << std::endl;
};

void saveScreen(){
    std::cout << "--------------" << std::endl;
    std::cout << " GAME SAVED" << std::endl;
    std::cout << "--------------" << std::endl;
};
void saveFailedScreen(){
    std::cout << "--------------" << std::endl;
    std::cout << " GAME FAILED TO SAVE" << std::endl;
    std::cout << "--------------" << std::endl;
};

void battleWon(enemy foe){
    std::cout << "--------------" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "    VICTORY   " << std::endl;
    std::cout << "You have slain a " << foe.getEnemyName() 
    << " Earning: " << foe.getEnemyXP() << " XP" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "--------------" << std::endl;
};
void caveWon1(Cave cave){
    std::cout << "--------------" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "    CONGRATS   " << std::endl;
    std::cout << "You cleared the cave! " << cave.name << std::endl;
    std::cout << " " << std::endl;
    std::cout << "--------------" << std::endl;
};
void caveWon2(Cave cave, weapon foundWeapon){
    std::cout << "--------------" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "    CONGRATS   " << std::endl;
    std::cout << "You cleared the cave! " << cave.name 
    << " Earning: " << cave.goldReward << " Gold" << std::endl;
    std::cout << "You have found a: " << foundWeapon.getName() << std::endl;
    std::cout << "--------------" << std::endl;
};
void battleLost(enemy foe){
    std::cout << "--------------" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "womp womp, you lost to a " << foe.getEnemyName() << std::endl;
    std::cout << " " << std::endl;
    std::cout << " " << std::endl;
    std::cout << "--------------" << std::endl;
};

void showCaves(std::vector<Cave>& caves) {
    std::cout << "--------------" << std::endl;
    std::cout << "Available Caves:" << std::endl;
    for (size_t i = 0; i < caves.size(); ++i) {
        std::cout << "(" << i + 1 << ") " << caves[i].name
                  << " | Enemies: " << caves[i].enemies.size()
                  << " | Gold Reward: " << caves[i].goldReward << std::endl;
    }
    std::cout << "(0) You know what. Naaah" << std::endl;
    std::cout << "--------------" << std::endl;
}


private:



};

