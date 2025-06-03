#inlcude <iostream>
#include "displays.hpp"
#include "hero.hpp"

displays menu;
hero player;

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

int main(){
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
                /*Awaits implementation*/
            }
                
            case 0:
            {
                pause();
            }

            default:
                continue;
        }
    }
}
