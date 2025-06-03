#ifndef CAVEFACTORY_HPP
#define CAVEFACTORY_HPP

#include "hero.hpp"
#include "enemy.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <cstdlib>  // For rand()
#include <ctime>    // For time()

// Template for cave
struct Cave {
    std::string name;
    int goldReward;
    std::vector<enemy> enemies;
};

// Factory class that generates caves based on hero level
class caveFactory {
public:
    caveFactory();

    // Creates a cave based on the hero's current level
    Cave createCave(const hero& player, const std::vector<enemy>& foeList, int scalingFactor);

    ~caveFactory();

private:
    // Generates a level-appropriate enemy
    enemy generateEnemy(int heroLvl, std::vector<enemy> foe);
    //Picks cave name
    std::string pickCaveName(int index);

    std::vector<std::string> namePool;
};

// Constructor
caveFactory::caveFactory() {
    srand(static_cast<unsigned>(time(nullptr))); // Seed random generator once

    namePool = {
        "Abandoned Mine", "Angband", "Torech Ungol", "Menegroth", 
        "Henneth Annun", "Caves of the Forgotten", 
        "The Cave Beneath the Rainbow", "Khazad-dum"
    };
}

std::string caveFactory::pickCaveName(int index) {
    return namePool[index];
}

// Destructor
caveFactory::~caveFactory() {
}

// Creates a cave with enemies scaled to the hero’s level, including the list of foes to generate from.
Cave caveFactory::createCave(const hero& player, const std::vector<enemy>& foeList, int scalingFactor) {
    Cave cave;
    int lvl = player.getLvl();

    cave.name = pickCaveName(scalingFactor % namePool.size());
    cave.goldReward = 100 + scalingFactor * 50;

    int enemyCount = 3 + (lvl / 2) + scalingFactor;
    for (int i = 0; i < enemyCount; ++i) {
        cave.enemies.push_back(generateEnemy(lvl, foeList));
    }

    return cave;
}

/*
    Generates a random enemy with stats based on hero level
    For a more imersive RPG experience, you can only see new monster types compared to what level you are.
    The modifier for the chosen monster is based on a random factor
*/
enemy caveFactory::generateEnemy(int heroLvl, std::vector<enemy> foeList) {

    std::vector<std::string> baseNames;

    //Clearing out existing names, to get a fresh list compared to lvl
    baseNames.clear();
    for (int i = 0; i <= heroLvl; i++)
    {
     baseNames.push_back({foeList[i].getEnemyName()});   
    }

    //Initializing the different modifiers
    std::vector<std::string> modifiers = { "Weak", "Strong", "Elite", "Abnormal" };

    //chosing a random enemy from the baseNames:
    int foeType;
    foeType = (rand() % baseNames.size());

    //Getting the modifier
    int modifierSize = rand() % modifiers.size();
    std::string mod = modifiers[modifierSize];
    
    std::string name = mod + " " + foeList[foeType].getEnemyName();
    //serting the modified enemyvalues
    double hp = (foeList[foeType].getEnemyHP() + modifierSize * 0.4);
    double dmg = (foeList[foeType].getEnemyDmg() + modifierSize * 0.4);
    double xp =  (foeList[foeType].getEnemyXP() + modifierSize * 0.4);

    //Initializing the new enemytype and returning
    return enemy(name, dmg, hp, static_cast<int>(std::round(xp)));
}

#endif
