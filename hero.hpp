#ifndef HERO_HPP
#define HERO_HPP
#include <string>   //Ability to use strings
#include <fstream>  //Save functions
#include <sstream>  //Load functions
#include <filesystem> //Creates save folder
#include "weapon.hpp"

class hero{

public:
    const int starterHP = 10;
    const int starterDmg = 2;
    const int starterLvl = 0;
    const int starterGold = 0;

    hero() {
    heroHP = starterHP;
    heroLvl = starterLvl;
    heroDmg = starterDmg + heroLvl;
    maxHP = starterHP + (2 * heroLvl);
    heroGold = starterGold;
    }

    void setName(std::string hName){
        heroName = hName;
    };

    std::string getHeroName(){
        return heroName;
    }

    int getLvl(){
        return heroLvl;
    }

    int getLvl() const{
        return heroLvl;
    }

    int getMaxHP(){
        return (10 + (2 * heroLvl));
    }
    
    int getHeroHP(){
        return heroHP;
    }

   int getHeroDmg() {
        if (currentWeapon.isBroken()) {
            return 2 + heroLvl;
        } else {
            return currentWeapon.getDamage(heroLvl);
        }
    }


    void equipWeapon(const weapon& w) {
        currentWeapon = w;
    }

    weapon getWeapon() const {
        return currentWeapon;
    }


    void useWeapon() {
        currentWeapon.use();
    }

    void takeDamage(int dmg) {
        heroHP -= dmg;
    }

    void addXP(int xp) {
        heroXP += xp;
    }

    int getXP() const {
        return heroXP;
    }

    void checkLevelUp() {
        while (heroXP >= 1000) {
            heroXP -= 1000;
            heroLvl++;
        }
    }


    void resetHeroHealth(){
        heroHP = getMaxHP();
    }

    int getGold() {
        return heroGold;
    }

    void addGold(int amount) {
        heroGold += amount;
    }

    bool saveHero() {
    std::string folder = "saves";
    std::filesystem::create_directory(folder);

    std::string filename = folder + "/" + heroName + ".txt";
    std::ofstream saveFile(filename);

    if (saveFile.is_open()) {
        saveFile << heroName << "\n";
        saveFile << heroXP << "\n";
        saveFile << heroLvl << "\n";
        saveFile << heroGold << "\n";
        saveFile << currentWeapon.getName() << "\n";
        saveFile << currentWeapon.getBaseDamage() << "\n";
        saveFile << currentWeapon.getStrengthModifier() << "\n";
        saveFile << currentWeapon.getDurability() << "\n";
        saveFile.close();
        return true;
    } else {
        //std::cerr << "Error: Could not save hero data to " << filename << "\n";
        return false;
    }
    };

    bool loadHero(std::string loadName) {
    std::string filename = "saves/" + loadName + ".txt";
    std::ifstream loadFile(filename);

    if (!loadFile.is_open()) {
        //std::cerr << "Error: Could not open save file: " << filename << std::endl;
        return false;
    }

    std::string line;
    
    std::getline(loadFile, line);
    heroName = line;

    std::getline(loadFile, line);
    heroXP = std::stoi(line);

    std::getline(loadFile, line);
    heroLvl = std::stoi(line);

    std::getline(loadFile, line);
    heroGold = std::stoi(line);

    std::string weaponName;
    int baseDmg, strMod, durability;

    std::getline(loadFile, weaponName);
    std::getline(loadFile, line); baseDmg = std::stoi(line);
    std::getline(loadFile, line); strMod = std::stoi(line);
    std::getline(loadFile, line); durability = std::stoi(line);

    currentWeapon = weapon(weaponName, baseDmg, strMod, durability);

    return true;
    };

private:

    std::string heroName;
    double heroHP;
    int heroLvl;
    double heroDmg;
    double maxHP;
    int heroXP;
    int heroGold;
    weapon currentWeapon;

};

#endif
