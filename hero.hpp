#ifndef HERO_HPP
#define HERO_HPP
#include <string>   //Ability to use strings
#include <fstream>  //Save functions
#include <sstream>  //Load functions
#include <filesystem> //Creates save folder

class hero{

public:
    const int starterHP = 10;
    const int starterDmg = 2;
    const int starterLvl = 0;

    hero() {
    heroHP = starterHP;
    heroLvl = starterLvl;
    heroDmg = starterDmg + heroLvl;
    maxHP = starterHP + (2 * heroLvl);
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

    int getMaxHP(){
        return (10 + (2 * heroLvl));
    }
    
    int getHeroHP(){
        return heroHP;
    }

    int getHeroDmg(){
        return (2 + heroLvl);
    }

    void takeDamage(int dmg) {
        heroHP -= dmg;
    }

    void addXP(int xp) {
        heroXP += xp;
    }

    int getXP(){
        if (heroXP >= 1000)
        {
            ++heroLvl;
            heroXP -= 1000;
        }
        
        return heroXP;
    }



private:

    std::string heroName;
    int heroHP;
    int heroLvl;
    int heroDmg;
    int maxHP;
    int heroXP;

};

#endif
