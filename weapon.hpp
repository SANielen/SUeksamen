#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>
#include <iostream>

class weapon {
public:
    weapon(std::string name = "Haender", int baseDmg = 0, int strMod = 0, int durability = 0)
        : name(name), baseDamage(baseDmg), strengthModifier(strMod), durability(durability) {}

    int getDamage(int heroStrength) const {
        return baseDamage + strengthModifier * heroStrength;
    }

    void use() {
        if (durability > 0) durability--;
    }

    bool isBroken() const {
        return durability <= 0;
    }

    int getBaseDamage() const { 
        return baseDamage; 
    }
    
    int getStrengthModifier() const { 
        return strengthModifier; 
    }

    std::string getName() const { return name; }
    int getDurability() const { return durability; }

private:
    std::string name;
    int baseDamage;
    int strengthModifier;
    int durability;
};


#endif
