#pragma once


/*ASSIGNMENT 6*/

#include <string>
#include <vector>

enum class PlayerPosition {
    QB,
    RB,
    WR,
    TE,
    NUM_POSITIONS
};

enum class Play {
    PASSING,
    RUSHING,
    NUM_PLAYS
};

struct PlayerStats {
    int num_pass_attempts = 0;
    int num_pass_completions = 0;
    int num_rush_attempts = 0;
    int num_touchdowns = 0;
    int yards_passing = 0;
    int yards_rushing = 0;
};

struct Player {
    std::string name = "missing";
    PlayerPosition position = PlayerPosition::NUM_POSITIONS;
    std::string team_name = "missing";
    int jersey_number = -1;                      
    int rating = 0;
    PlayerStats game_stats {};
};

struct Team {
    std::string name = "missing";
    std::vector<Player> roster;
};

struct Scoreboard {
    int home_score = 0;
    int away_score = 0; 
    int current_down = 0;
    int yards_to_go = 0;
    std::string possession = "missing";
};

enum class GameState {
    PREGAME,
    PLAYTIME,
    HALFTIME,
    END,
    MAX_STATES
};

struct Game {
    Team* home_team = nullptr;
    Team* away_team = nullptr;
    Scoreboard* scoreboard = nullptr;
};

bool observeBernoulli(double p, int seed);
int observeUniformInt(int min, int max, int seed);
double calcPlayProb(Team* team);
Player* getQB(Team* team);
Player* getPlayer(Team* team, Play play, int seed);
bool execPassingPlay(Player* qb, Player* receiver, Scoreboard* scoreboard, int seed);
bool execRushingPlay(Player* qb, Player* back, Scoreboard* scoreboard, int seed) ;
void displayScoreboard(const std::string& home_name, const std::string& away_name, const Scoreboard* scoreboard) ;
void displayTeamStats(const Team* team);
void simulatePossession(Team* team, Scoreboard* scoreboard);
void simulatePregame(Game* game, int seed);
void simulateHalftime(Game* game);
void simulateEndgame(Game* game);
void simulateGameDay(Game* game, int seed);


/*
==============ASSIGNMENT 7==============
*/


/*
==============ASSIGNMENT 8==============
*/

enum class Error {
    SUCCESS,
    INVALID,
    MISSING,
    UNAVAILABLE,
    NUM_ERRORS = 4
};

// Function prototypes for Assignment 8
void loadTeam(Team* team, std::ifstream& fin);
std::string chooseOpponent(const std::string& current_team, std::vector<std::string>& available_teams, int seed);
void saveGameStats(const Team* home_team, const Team* opponent_team);
Error playGame(std::vector<std::string>& team_names);
void help();
Error displayPlayers(const std::string& team_name);
Error addPlayer(const std::string& team_name, const std::string& player_name, const std::string& position, int jersey_number, int rating);
Error processRosterCommands();

