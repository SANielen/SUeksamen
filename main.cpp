#include <iostream>
#include <string>
#include "displays.hpp"
#include "hero.hpp"
#include "enemy.hpp"
#include "caveFactory.hpp"
displays menu;
hero player;
caveFactory factory;

//Creating enemylist using a vectorlist. 
std::vector<enemy> enemyList = {
    enemy("Hest", 1, 4, 100),//                 [0]
    enemy("Weak Goblin", 2, 4, 200),//          [1]
    enemy("Strong Goblin", 3, 8, 400),//        [2]
    enemy("Stronger Goblin", 4, 10, 500),//     [3]
    enemy("Den staerkeste Goblin", 5, 15, 800),//[4]
    enemy("Abe Kongen", 5, 30, 1000),//         [5]
    enemy("Enhjeorning", 8, 5, 1500),//          [6]
    enemy("Balrog", 10, 100, 3000)//             [7]
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
                std::this_thread::sleep_for(std::chrono::seconds(1));
            } else {
                menu.loadSuccessful();
                player.resetHeroHealth();
                std::this_thread::sleep_for(std::chrono::seconds(1));
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
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    continue;
                } else {
                    menu.saveScreen();
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    continue;
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

void postFight(bool battleWon, hero& player, enemy& foe) {
    if (battleWon) {
        player.addXP(foe.getEnemyXP());
        player.checkLevelUp();
        menu.battleWon(foe);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    } else {
        menu.battleLost(foe);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}


bool battle(hero& player, enemy foe) {
    bool battleRun = true;
    bool battleWon = false;

    while (battleRun) {
        menu.battleMenu(player, foe);
        std::cin >> selection;

        switch (selection) {
            case 1: // Attack
                foe.takeDamage(player.getHeroDmg());
                if (foe.getEnemyHP() <= 0) {
                    battleWon = true;
                    battleRun = false;
                    continue;
                }

                player.takeDamage(foe.getEnemyDmg());
                if (player.getHeroHP() <= 0) {
                    battleWon = false;
                    battleRun = false;
                }
                break;

            case 2: // Flee
                battleRun = false;
                break;

            case 3: // Do nothing (debug)
                player.takeDamage(foe.getEnemyDmg());
                if (player.getHeroHP() <= 0) {
                    battleWon = false;
                    battleRun = false;
                }
                break;

            case 0: // Pause
                pause();
                break;

            default:
                break;
        }
    }

    postFight(battleWon, player, foe);
    return battleWon;
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
    player.resetHeroHealth();
}

void enterCave() {
    std::vector<Cave> caves;

    for (int i = 0; i < 8; ++i) {
        caves.push_back(factory.createCave(player, enemyList, i));
    }

    bool enterCaveRun = true;
    while (enterCaveRun) {
        menu.showCaves(caves);
        std::cin >> selection;

        if (selection == 0) return;

        if (selection > 0 && selection <= caves.size()) {
            Cave chosen = caves[selection - 1];
            bool cleared = true;

            for (int i = 0; i < chosen.enemies.size(); ++i) {
                if (!battle(player, chosen.enemies[i]) || player.getHeroHP() <= 0) {
                    cleared = false;
                    break;
                }
            }

            if (cleared) {
                player.addGold(chosen.goldReward);
                menu.caveWon(chosen);
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }

            enterCaveRun = false;
        }
    }
    player.resetHeroHealth();
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
                std::this_thread::sleep_for(std::chrono::seconds(1));
        };
    }
    

    //Playing game (mainMenu)
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
            case 2:
            {
                enterCave();
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

