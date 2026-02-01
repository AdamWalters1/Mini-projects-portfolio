#include "code.h"

#include <iostream>
#include <random>
#include <chrono>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iomanip>

// Helper function to find a string in a vector
bool findStringInVector(const std::vector<std::string>& vec, const std::string& target) {
    for (const auto& item : vec) {
        if (item == target) {
            return true;
        }
    }
    return false;
}

// Helper Functions for calculations
bool observeBernoulli(double p, int seed) {
    if (p < 0 || p > 1) throw std::runtime_error("Bernoulli parameter must be between 0 and 1.");
    std::mt19937 gen(seed);
    std::bernoulli_distribution dist(p);
    return dist(gen);
}

int observeUniformInt(int min, int max, int seed) {
    if (min > max) throw std::runtime_error("Uniform range is invalid.");
    if (min == max) return min;  // If min equals max, just return that value
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

double calcPlayProb(Team* team) {
    double r_passing = 0, r_rushing = 0;
    int count_passing = 0, count_rushing = 0;

    for (const auto& player : team->roster) {
        if (player.position == PlayerPosition::WR || player.position == PlayerPosition::TE) {
            r_passing += player.rating;
            count_passing++;
        }
        if (player.position == PlayerPosition::RB || player.position == PlayerPosition::QB || player.position == PlayerPosition::TE) {
            r_rushing += player.rating;
            count_rushing++;
        }
    }

    if (count_passing == 0 || count_rushing == 0) throw std::runtime_error("Invalid team composition.");
    return (r_passing / count_passing) / ((r_passing / count_passing) + (r_rushing / count_rushing));
}

Player* getQB(Team* team) {
    for (auto& player : team->roster) {
        if (player.position == PlayerPosition::QB) return &player;
    }
    throw std::runtime_error("No quarterback found in the team.");
}

Player* getPlayer(Team* team, Play play, int seed) {
    std::vector<Player*> eligible_players;
    for (auto& player : team->roster) {
        if (play == Play::PASSING && (player.position == PlayerPosition::WR || player.position == PlayerPosition::TE)) {
            eligible_players.push_back(&player);
        } else if (play == Play::RUSHING && (player.position == PlayerPosition::RB || player.position == PlayerPosition::QB || player.position == PlayerPosition::TE)) {
            eligible_players.push_back(&player);
        }
    }

    if (eligible_players.empty()) throw std::runtime_error("No eligible players for the play.");
    int index = observeUniformInt(0, static_cast<int>(eligible_players.size()) - 1, seed);
    return eligible_players[index];
}

bool execPassingPlay(Player* qb, Player* receiver, Scoreboard* scoreboard, int seed) {
    double p_pass = (qb->rating + receiver->rating) / 300.0;
    bool success = observeBernoulli(p_pass, seed);

    qb->game_stats.num_pass_attempts++;
    receiver->game_stats.num_pass_attempts++;

    if (success) {
        int yards = observeUniformInt(1, 10, seed);
        qb->game_stats.num_pass_completions++;
        qb->game_stats.yards_passing += yards;
        receiver->game_stats.num_pass_completions++;
        receiver->game_stats.yards_passing += yards;

        scoreboard->yards_to_go -= yards;
        if (scoreboard->yards_to_go <= 0) {
            if (scoreboard->possession == "home") {
                scoreboard->home_score += 6;
            } else {
                scoreboard->away_score += 6;
            }
            qb->game_stats.num_touchdowns++;
            receiver->game_stats.num_touchdowns++;
        }
    }

    return success;
}

bool execRushingPlay(Player* qb, Player* rusher, Scoreboard* scoreboard, int seed) {
    double p_run = (qb->rating + rusher->rating) / 300.0;
    bool success = observeBernoulli(p_run, seed);

    if (success) {
        int yards = observeUniformInt(1, 5, seed);
        rusher->game_stats.num_rush_attempts++;
        rusher->game_stats.yards_rushing += yards;

        scoreboard->yards_to_go -= yards;
        if (scoreboard->yards_to_go <= 0) {
            if (scoreboard->possession == "home") {
                scoreboard->home_score += 6;
            } else {
                scoreboard->away_score += 6;
            }
            if (rusher == qb) {
                qb->game_stats.num_touchdowns++;
            } else {
                qb->game_stats.num_touchdowns++;
                rusher->game_stats.num_touchdowns++;
            }
        }
    } else {
        rusher->game_stats.num_rush_attempts++;
    }

    return success;
}

void displayScoreboard(const std::string& home_name, const std::string& away_name, const Scoreboard* scoreboard) {
    std::cout << "Final score:\n" << home_name << ": " << scoreboard->home_score << " - " << away_name << ": " << scoreboard->away_score << "\n";
}

void displayTeamStats(const Team* team) {
    std::cout << "Game statistics of " << team->name << " players:\n";
    for (const auto& player : team->roster) {
        std::cout << player.name << " contributed to " << player.game_stats.num_touchdowns << " touchtown(s). ";
        if (player.position == PlayerPosition::QB) {
            std::cout << "He threw " << player.game_stats.num_pass_completions << " successful pass(es) out of "
                      << player.game_stats.num_pass_attempts << " attempt(s) with " << player.game_stats.yards_passing
                      << " passed yard(s). He had " << player.game_stats.num_rush_attempts << " rush attempt(s) with "
                      << player.game_stats.yards_rushing << " rushed yard(s).\n";
        } else {
            std::cout << "He caught " << player.game_stats.num_pass_completions << " pass(es) out of "
                      << player.game_stats.num_pass_attempts << " attempt(s) with " << player.game_stats.yards_passing
                      << " passed yard(s). He had " << player.game_stats.num_rush_attempts << " rush attempt(s) with "
                      << player.game_stats.yards_rushing << " rushed yard(s).\n";
        }
    }
}

void simulatePossession(Team* team, Scoreboard* scoreboard) {
    std::cout << team->name << " have the possession.\nPress Enter to continue...\n";
    std::cin.get();

    scoreboard->current_down = 1;
    scoreboard->yards_to_go = 10;

    while (scoreboard->current_down <= 4) {
        std::string down_text;
        switch(scoreboard->current_down) {
            case 1: down_text = "First"; break;
            case 2: down_text = "Second"; break;
            case 3: down_text = "Third"; break;
            case 4: down_text = "Fourth"; break;
            default: down_text = std::to_string(scoreboard->current_down);
        }
        std::cout << down_text << " down and " << scoreboard->yards_to_go << "\nPress Enter to continue...\n";
        std::cin.get();

        int seed = static_cast<int>(std::chrono::steady_clock::now().time_since_epoch().count());
        double p_play = calcPlayProb(team);
        Play play = observeBernoulli(p_play, seed) ? Play::PASSING : Play::RUSHING;

        Player* qb = getQB(team);
        Player* selected_player = getPlayer(team, play, seed);

        if (play == Play::PASSING) {
            std::cout << "Passing play is called.\nPress Enter to continue...\n";
            std::cin.get();

            bool success = execPassingPlay(qb, selected_player, scoreboard, seed);
            if (success) {
                std::cout << "Passing play is successful.\nPress Enter to continue...\n";
                std::cin.get();
                if ((scoreboard->possession == "home" && scoreboard->home_score > 0) || 
                    (scoreboard->possession == "away" && scoreboard->away_score > 0)) {
                    std::cout << "Touchdown scored.\nPossession is over...\nPress Enter to continue...\n";
                    std::cin.get();
                    break;
                } else {
                    std::cout << scoreboard->yards_to_go << " yards gained.\nPress Enter to continue...\n";
                    std::cin.get();
                }
            } else {
                std::cout << "Passing play is NOT successful.\nPress Enter to continue...\n";
                std::cin.get();
            }
        } else {
            std::cout << "Rushing play is called.\nPress Enter to continue...\n";
            std::cin.get();

            bool success = execRushingPlay(qb, selected_player, scoreboard, seed);
            if (success) {
                std::cout << "Rushing play is successful.\nPress Enter to continue...\n";
                std::cin.get();
                if ((scoreboard->possession == "home" && scoreboard->home_score > 0) || 
                    (scoreboard->possession == "away" && scoreboard->away_score > 0)) {
                    std::cout << "Touchdown scored.\nPossession is over...\nPress Enter to continue...\n";
                    std::cin.get();
                    break;
                } else {
                    std::cout << scoreboard->yards_to_go << " yards gained.\nPress Enter to continue...\n";
                    std::cin.get();
                }
            } else {
                std::cout << "Rushing play is NOT successful.\nPress Enter to continue...\n";
                std::cin.get();
            }
        }
        scoreboard->current_down++;
        if (scoreboard->yards_to_go <= 0) {
            scoreboard->yards_to_go = 10;
            scoreboard->current_down = 1;
        }
    }

    if (scoreboard->current_down > 4) {
        std::cout << "No more downs, possession is turned over to the other team.\nPossession over...\n";
    }
}

// Helper function to convert string to PlayerPosition
PlayerPosition stringToPosition(const std::string& pos) {
    if (pos == "QB") return PlayerPosition::QB;
    if (pos == "RB") return PlayerPosition::RB;
    if (pos == "WR") return PlayerPosition::WR;
    if (pos == "TE") return PlayerPosition::TE;
    return PlayerPosition::NUM_POSITIONS;
}

// Helper function to convert PlayerPosition to string
std::string positionToString(PlayerPosition pos) {
    switch (pos) {
        case PlayerPosition::QB: return "QB";
        case PlayerPosition::RB: return "RB";
        case PlayerPosition::WR: return "WR";
        case PlayerPosition::TE: return "TE";
        default: return "UNKNOWN";
    }
}

void loadTeam(Team* team, std::ifstream& fin) {
    std::string line;
    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string name, position, team_name;
        int jersey_number, rating;
        std::string temp;

        std::getline(ss, name, ',');
        std::getline(ss, position, ',');
        std::getline(ss, temp, ',');
        jersey_number = std::stoi(temp);
        std::getline(ss, temp);
        rating = std::stoi(temp);

        Player player;
        player.name = name;
        player.position = stringToPosition(position);
        player.team_name = team->name;
        player.jersey_number = jersey_number;
        player.rating = rating;

        team->roster.push_back(player);
    }
}

std::string chooseOpponent(const std::string& current_team, std::vector<std::string>& available_teams, int seed) {
    std::vector<std::string> opponents;
    for (const auto& team : available_teams) {
        if (team != current_team) {
            opponents.push_back(team);
        }
    }
    
    if (opponents.empty()) {
        throw std::runtime_error("No available opponents");
    }
    
    int index = observeUniformInt(0, static_cast<int>(opponents.size() - 1), seed);
    return opponents[index];
}

void saveGameStats(const Team* home_team, const Team* opponent_team) {
    for (const auto& player : home_team->roster) {
        std::string filename = player.team_name + "_" + std::to_string(player.jersey_number) + ".csv";
        std::ofstream fout(filename, std::ios::app);
        
        std::string opponent = opponent_team->name;
        fout << opponent << "," 
             << player.game_stats.num_pass_attempts << ","
             << player.game_stats.num_pass_completions << ","
             << player.game_stats.num_rush_attempts << ","
             << player.game_stats.num_touchdowns << ","
             << player.game_stats.yards_passing << ","
             << player.game_stats.yards_rushing << "\n";
    }

    for (const auto& player : opponent_team->roster) {
        std::string filename = player.team_name + "_" + std::to_string(player.jersey_number) + ".csv";
        std::ofstream fout(filename, std::ios::app);
        
        std::string opponent = "@" + home_team->name;
        fout << opponent << ","
             << player.game_stats.num_pass_attempts << ","
             << player.game_stats.num_pass_completions << ","
             << player.game_stats.num_rush_attempts << ","
             << player.game_stats.num_touchdowns << ","
             << player.game_stats.yards_passing << ","
             << player.game_stats.yards_rushing << "\n";
    }
}

// New functions for Assignment 9
void simulatePregame(Game* game, int seed) {
    // Display team introductions
    std::cout << game->away_team->name << " @" << game->home_team->name << "\n\n";
    
    // Display home team roster
    std::cout << game->home_team->name << " roster:\n";
    for (const auto& player : game->home_team->roster) {
        std::cout << player.name << " (" << positionToString(player.position) << ", #" << player.jersey_number << ")\n";
    }
    std::cout << "\n";
    
    // Display away team roster
    std::cout << game->away_team->name << " roster:\n";
    for (const auto& player : game->away_team->roster) {
        std::cout << player.name << " (" << positionToString(player.position) << ", #" << player.jersey_number << ")\n";
    }
    std::cout << "\n";
    
    // Simulate coin toss
    bool home_wins_toss = observeBernoulli(0.5, seed);
    if (home_wins_toss) {
        std::cout << game->home_team->name << " wins the coin toss.\n";
        game->scoreboard->possession = "home";
        std::cout << game->home_team->name << " starts the game.\n";
    } else {
        std::cout << game->away_team->name << " wins the coin toss.\n";
        game->scoreboard->possession = "away";
        std::cout << game->away_team->name << " starts the game.\n";
    }
    
    std::cout << "Pregame is over. Press Enter to start the game.\n";
    std::cin.get();
}

void simulateHalftime(Game* game) {
    std::cout << "First half is over.\n";
    
    // Display score
    std::cout << "Score: " << game->home_team->name << " " << game->scoreboard->home_score 
              << " - " << game->away_team->name << " " << game->scoreboard->away_score << "\n\n";
    
    // Display player statistics
    displayTeamStats(game->home_team);
    std::cout << "\n";
    displayTeamStats(game->away_team);
    
    // Switch possession for the second half
    if (game->scoreboard->possession == "home") {
        game->scoreboard->possession = "away";
    } else {
        game->scoreboard->possession = "home";
    }
    
    std::cout << "Press Enter to continue...\n";
    std::cin.get();
}

void simulateEndgame(Game* game) {
    std::cout << "Game is over.\n";
    
    // Display final score
    std::cout << "Final score: " << game->home_team->name << " " << game->scoreboard->home_score 
              << " - " << game->away_team->name << " " << game->scoreboard->away_score << "\n\n";
    
    // Display player statistics
    displayTeamStats(game->home_team);
    std::cout << "\n";
    displayTeamStats(game->away_team);
    
    // Announce the winner
    if (game->scoreboard->home_score > game->scoreboard->away_score) {
        std::cout << game->home_team->name << " wins the game!\n";
    } else if (game->scoreboard->away_score > game->scoreboard->home_score) {
        std::cout << game->away_team->name << " wins the game!\n";
    } else {
        std::cout << "The game ends in a draw.\n";
    }
}

void simulateGameDay(Game* game, int seed) {
    // Start with pregame
    simulatePregame(game, seed);
    
    // First half (playtime)
    if (game->scoreboard->possession == "home") {
        simulatePossession(game->home_team, game->scoreboard);
    } else {
        simulatePossession(game->away_team, game->scoreboard);
    }
    
    // Halftime
    simulateHalftime(game);
    
    // Second half (playtime)
    if (game->scoreboard->possession == "home") {
        simulatePossession(game->home_team, game->scoreboard);
    } else {
        simulatePossession(game->away_team, game->scoreboard);
    }
    
    // End game
    simulateEndgame(game);
}

Error playGame(std::vector<std::string>& team_names) {
    std::string team_name;
    std::cout << "Choose a team to start the game. Available teams: ";
    for (size_t i = 0; i < team_names.size(); ++i) {
        std::cout << team_names[i];
        if (i < team_names.size() - 1) std::cout << ", ";
    }
    std::cout << "\n> ";
    std::getline(std::cin, team_name);

    if (!findStringInVector(team_names, team_name)) {
        std::cout << "The team provided is not available. Please try again.\n\n";
        return Error::UNAVAILABLE;
    }

    std::cout << "The " << team_name << " are successfully selected.\n";

    int seed = static_cast<int>(std::chrono::steady_clock::now().time_since_epoch().count());
    std::string opponent = chooseOpponent(team_name, team_names, seed);
    std::cout << "You are playing against the " << opponent << ".\nPress Enter to continue...\n";
    std::cin.get();

    // Load teams from CSV files
    Team* home_team = new Team();
    Team* away_team = new Team();
    Scoreboard* scoreboard = new Scoreboard();
    
    try {
        home_team->name = team_name;
        away_team->name = opponent;

        std::ifstream home_fin(team_name + ".csv");
        std::ifstream away_fin(opponent + ".csv");
        if (!home_fin || !away_fin) {
            delete home_team;
            delete away_team;
            delete scoreboard;
            return Error::UNAVAILABLE;
        }

        loadTeam(home_team, home_fin);
        loadTeam(away_team, away_fin);

        // Create a game object
        Game game;
        game.home_team = home_team;
        game.away_team = away_team;
        game.scoreboard = scoreboard;
        
        // Simulate the game day
        simulateGameDay(&game, seed);

        // Save statistics
        saveGameStats(home_team, away_team);
        std::cout << "Player statistics are saved.\nGame over.\n\n";

        // Cleanup
        delete home_team;
        delete away_team;
        delete scoreboard;
        return Error::SUCCESS;
    }
    catch (const std::exception&) {
        // Cleanup in case of any exception
        delete home_team;
        delete away_team;
        delete scoreboard;
        return Error::UNAVAILABLE;
    }
}

void help() {
    std::cout << "\nEnter \"display\" followed by a team's name to print all players on the team.\n"
              << "Usage example: \"display Chiefs\"\n\n"
              << "Enter \"add\" followed by a team's name and the new player's name, position, jersey number, and rating using the comma symbol as a delimiter.\n"
              << "Usage example: \"add Chiefs John Doe, QB, 99, 81\"\n\n"
              << "Enter \"exit\" to stop interaction with rosters.\n\n";
}

Error displayPlayers(const std::string& team_name) {
    std::ifstream fin(team_name + ".csv");
    if (!fin) {
        return Error::UNAVAILABLE;
    }

    Team team;
    team.name = team_name;
    loadTeam(&team, fin);

    std::cout << "\nName                     Position  Number    Rating\n";
    for (const auto& player : team.roster) {
        std::cout << std::left 
                  << std::setw(25) << player.name
                  << std::setw(10) << positionToString(player.position)
                  << std::setw(10) << player.jersey_number
                  << std::setw(10) << player.rating << "\n";
    }
    std::cout << "\n";

    return Error::SUCCESS;
}

Error addPlayer(const std::string& team_name, const std::string& player_name, 
                const std::string& position, int jersey_number, int rating) {
    // Validate position
    PlayerPosition pos = stringToPosition(position);
    if (pos == PlayerPosition::NUM_POSITIONS) {
        return Error::INVALID;
    }

    // Validate jersey number and rating
    if (jersey_number <= 0 || rating < 0 || rating > 100) {
        return Error::INVALID;
    }

    // Check if jersey number is already taken
    std::ifstream fin(team_name + ".csv");
    if (!fin) {
        return Error::UNAVAILABLE;
    }

    Team team;
    team.name = team_name;
    loadTeam(&team, fin);
    fin.close();

    for (const auto& player : team.roster) {
        if (player.jersey_number == jersey_number) {
            return Error::UNAVAILABLE;
        }
    }

    // Read the entire file content
    std::ifstream fin2(team_name + ".csv");
    std::string content((std::istreambuf_iterator<char>(fin2)), std::istreambuf_iterator<char>());
    fin2.close();

    // Add new player to CSV file
    std::ofstream fout(team_name + ".csv");
    if (!content.empty()) {
        // Remove trailing newlines
        while (!content.empty() && (content.back() == '\n' || content.back() == '\r')) {
            content.pop_back();
        }
        fout << content << "\n";
    }
    fout << player_name << "," << position << "," << jersey_number << "," << rating;
    fout.close();

    return Error::SUCCESS;
}

Error processRosterCommands() {
    std::string command;
    std::cout << "You can choose from the following commands: help, display, add, exit\n> ";
    std::getline(std::cin, command);

    if (command == "help") {
        help();
        return Error::SUCCESS;
    }
    else if (command == "exit") {
        std::cout << "You successfully exited the modify roster menu.\n\n";
        return Error::SUCCESS;
    }
    else if (command.substr(0, 7) == "display") {
        std::string team_name = command.substr(7);
        if (team_name.empty()) {
            std::cout << "The team name is missing. Please enter a team name. Type \"help\" for help.\n\n";
            return Error::MISSING;
        }
        // Remove leading whitespace
        team_name = team_name.substr(team_name.find_first_not_of(" "));
        Error result = displayPlayers(team_name);
        if (result == Error::UNAVAILABLE) {
            std::cout << "The team provided is not available. Please try again.\n\n";
            return Error::UNAVAILABLE;
        }
        return Error::SUCCESS;
    }
    else if (command.substr(0, 3) == "add") {
        std::string rest = command.substr(3);
        if (rest.empty()) {
            std::cout << "The team name is missing. Please enter a team name. Type \"help\" for help.\n\n";
            return Error::MISSING;
        }
        // Remove leading whitespace
        rest = rest.substr(rest.find_first_not_of(" "));
        
        // Parse team name
        size_t comma_pos = rest.find(',');
        if (comma_pos == std::string::npos) {
            std::cout << "The player name is missing. Please enter a player name. Type \"help\" for help.\n\n";
            return Error::MISSING;
        }
        std::string team_name = rest.substr(0, comma_pos);
        rest = rest.substr(comma_pos + 1);
        
        // Remove leading whitespace
        team_name = team_name.substr(team_name.find_first_not_of(" "));
        rest = rest.substr(rest.find_first_not_of(" "));
        
        // Parse player name
        comma_pos = rest.find(',');
        if (comma_pos == std::string::npos) {
            std::cout << "The player position is missing.\n\n";
            return Error::MISSING;
        }
        std::string player_name = rest.substr(0, comma_pos);
        rest = rest.substr(comma_pos + 1);
        
        // Remove leading whitespace
        player_name = player_name.substr(player_name.find_first_not_of(" "));
        rest = rest.substr(rest.find_first_not_of(" "));
        
        // Parse position
        comma_pos = rest.find(',');
        if (comma_pos == std::string::npos) {
            std::cout << "The player jersey number is missing.\n\n";
            return Error::MISSING;
        }
        std::string position = rest.substr(0, comma_pos);
        rest = rest.substr(comma_pos + 1);
        
        // Remove leading whitespace
        position = position.substr(position.find_first_not_of(" "));
        rest = rest.substr(rest.find_first_not_of(" "));
        
        // Parse jersey number
        comma_pos = rest.find(',');
        if (comma_pos == std::string::npos) {
            std::cout << "The player rating is missing.\n\n";
            return Error::MISSING;
        }
        std::string jersey_str = rest.substr(0, comma_pos);
        std::string rating_str = rest.substr(comma_pos + 1);
        
        // Remove leading whitespace
        jersey_str = jersey_str.substr(jersey_str.find_first_not_of(" "));
        rating_str = rating_str.substr(rating_str.find_first_not_of(" "));
        
        try {
            int jersey_number = std::stoi(jersey_str);
            int rating = std::stoi(rating_str);
            
            Error result = addPlayer(team_name, player_name, position, jersey_number, rating);
            if (result == Error::SUCCESS) {
                std::cout << player_name << " is added to the " << team_name << "\n\n";
                return Error::SUCCESS;
            }
            else if (result == Error::UNAVAILABLE) {
                std::cout << "The jersey number is not available.\n\n";
                return Error::UNAVAILABLE;
            }
            else if (result == Error::INVALID) {
                std::cout << "The player position, jersey number, or rating is invalid. Please try again.\n\n";
                return Error::INVALID;
            }
        }
        catch (const std::exception&) {
            std::cout << "The player position, jersey number, or rating is invalid. Please try again.\n\n";
            return Error::INVALID;
        }
    }
    else {
        std::cout << "The command provided is invalid. Please try again.\n\n";
        return Error::INVALID;
    }
    return Error::SUCCESS;
}

