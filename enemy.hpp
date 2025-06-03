#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <iostream>
#include <string>

class enemy {
public:

    //Constructor with initializer, to create different types of enemies
    enemy(std::string name, int dmg, int hp, int xp)
        : enemyName(name), enemyDmg(dmg), enemyHP(hp), enemyXP(xp) {}

    //Copy constructor, so new enemies can be created from the template.
    enemy( const enemy & c) {
        enemyName = c.enemyName;
        enemyDmg = c.enemyDmg;
        enemyHP = c.enemyHP;
        enemyXP = c.enemyXP;
    };

    std::string getEnemyName() const {
        return enemyName; 
    }
    int getEnemyHP() const { 
        return enemyHP; 
    }
    int getEnemyDmg() const {
        return enemyDmg;
    }
    int getEnemyXP() const {
        return enemyXP;
    }

    void takeDamage(int dmg) {
        enemyHP -= dmg;
    }

private:
    std::string enemyName;
    double enemyDmg;
    double enemyHP;
    int enemyXP;
};

#endif
