#include "code.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


int main(){

    
    std::vector<std::string> team_names = {"Ravens", "Bills", "Chiefs", "Texans", "49ers", "Cowboys", "Lions", "Buccaneers"};

    std::cout << "Do you want to play a game, modify the roster, or exit the program (game/roster/exit)?\n";
    while (true) {
        
        std::string choice;
        std::cin >> choice;
        if (choice == "exit") {
            break;
        } else if (choice == "game") {
            playGame(team_names);
        } else if (choice == "roster") {
            processRosterCommands();
        } else {
            std::cout << "The command provided is invalid. Please try again.\n";
        }
        std::cout << "\nDo you want to play a game, modify the roster, or exit the program (game/roster/exit)?\n";
    }

    return 0;
}