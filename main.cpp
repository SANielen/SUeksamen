#include <iostream>
#include <string>
#include "displays.hpp"
#include "hero.hpp"
#include "enemy.hpp"
displays menu;
hero player;

//Creating enemylist using a vectorlist.
std::vector<enemy> enemyList = {
    enemy("Hest", 1, 4, 100),//                 [0]
    enemy("Weak Goblin", 2, 4, 200),//          [1]
    enemy("Strong Goblin", 3, 8, 400),//        [2]
    enemy("Stronger Goblin", 4, 10, 500),//     [3]
    enemy("Den stærkeste Goblin", 5, 15, 800),//[4]
    enemy("Abe Kongen", 5, 30, 1000),//         [5]
    enemy("Enhjørning", 8, 5, 1500),//          [6]
    enemy("Drage", 10, 100, 3000)//             [7]
};

int selection;
bool running = true;


bool load(){
    
    while (running){
    if (menu.loadMenu()){
        std::string loadName;
        std::cin >> loadName;
            if(!player.loadHero(loadName)){
                menu.loadFailedMenu();
                std::this_thread::sleep_for(std::chrono::seconds(3));
            } else {
                menu.loadSuccessful();
                std::this_thread::sleep_for(std::chrono::seconds(3));
                return true;
            }
        } else {
            return false;
        }
    };
    return true;
}
    
void pause(){
    bool pauseRun = true;
    while (pauseRun){
    menu.pauseMenu();    
    std::cin >> selection;
        switch (selection){
            case 1:                     //Resume
            {
                return;
            }
            case 2:                     //Save Game
            {
                if (!player.saveHero()){
                    menu.saveFailedScreen();
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                    continue;
                } else {
                    menu.saveScreen();
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                    pauseRun = false;
                    break;
                }
            } 
            case 3:                     //Load Game
            {
                if (load()){
                    pauseRun = false;
                }
                continue;
            }              
            case 0:                     //Exit the game
            {
                exit(0);
            }
        }
    }
    return;
};

void postFight(bool battleWon, hero& player, enemy foe){
    if(battleWon){
        menu.battleWon(foe);
        player.addXP(foe.getEnemyXP());
        player.getXP();
        player.resetHeroHealth();
    } else {
        menu.battleLost(foe);
    }
}

void battle(hero& player, enemy foe){
    bool battleRun = true;
    bool battleWon = false;

    while (battleRun)
    {
        //Updating player and foe stats
        int heroDmg = player.getHeroDmg();
        int heroHP = player.getHeroHP();
        int enemyDmg = foe.getEnemyDmg();
        int enemyHP = foe.getEnemyHP();
        menu.battleMenu(player, foe);
        std::cin >> selection;
        switch (selection)
        {
        case 1:                         //Attack
            foe.takeDamage(player.getHeroDmg());
            if (foe.getEnemyHP() <= 0){
                battleWon = true;
                    battleRun = false;
            };

            player.takeDamage(foe.getEnemyDmg());
            if (player.getHeroHP() <= 0) {
                    battleWon = false;
                    battleRun = false;
            };

            continue;
        case 2:                         //Flee
            battleRun = false;
            continue;
        case 3:                         //Do nothing (This is for debugging)
            player.takeDamage(foe.getEnemyDmg());
            if (player.getHeroHP() <= 0) {
                    battleWon = false;
                    battleRun = false;
            };
            continue;
        default:
            continue;
        }
    }
    postFight(battleWon, player, foe);
    return;
}

void fightMonsters() {
    bool fightRun = true;
    while (fightRun) {
        menu.fightMonsters(enemyList);
        std::cin >> selection;
        if (selection == 0) {
            return;
        }

        if (selection > 0 && selection < enemyList.size()) {
            //Calling a copy constructor during initialization
            enemy chosenEnemy = enemyList[selection - 1];

            battle(player, chosenEnemy);
            fightRun = false;
        } else {
            continue;
        }
    }
}

int main(int argc, char *argv[])
{
    
    //Startup of the game
    while (running)
    {
        menu.bootMenu();
        std::cin >> selection;

        switch (selection)
        {
            case 1:
            {
                menu.startMenu(player);
                std::string nameHolder;
                std::cin >> nameHolder;
                player.setName(nameHolder);
                running = false;
                break;
            }
            case 2:
            {
                if (load()){
                    running = false;
                }
                break;
            } 
            case 0:
            {
                exit (0);
            }

            default:
                menu.bootMenuDefault();
                std::this_thread::sleep_for(std::chrono::seconds(3));
        };
    }
    

    //Playing game
    running = true;
    while (running)
    {
    menu.mainMenu(player);
    std::cin >> selection;
        switch (selection)
        {
            case 1:
            {
                fightMonsters();
                continue;
            }
                
            case 0:
            {
                pause();
            }

            default:
                continue;
        }
    }
    
    

    return 0;
}

