#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "code.h"
#include <iostream>
#include <sstream>

#include <fstream>
#include <filesystem>





TEST_CASE("Test01: GameState enum class", "[10 points]") 
{
    {
    INFO("Check if GameState is an enum");
        STATIC_REQUIRE(std::is_enum<GameState>::value);
    }    
    {
    INFO("Check if GameState is an enum class and not a plain enum");
        STATIC_REQUIRE(!std::is_convertible<GameState, int>::value);
    }
    INFO("Check if GameState enum has 5 elements.");
        CHECK(static_cast<int>(GameState::MAX_STATES) == 4);
}



TEST_CASE("Test02: Game struct", "[10 points]") {
    {
    INFO("Check if Game is a class/struct type");
        STATIC_REQUIRE(std::is_class<Game>::value);
    }
    {
    INFO("Check if Game has correct element names and default initialization");
        Game game;
        CHECK(game.home_team == nullptr);
        CHECK(game.away_team == nullptr);
        CHECK(game.scoreboard == nullptr);
    }
    {
    INFO("Check the number of elements in Game");
        struct TestGame {
            Team* home_team;
            Team* away_team;
            Scoreboard* scoreboard;
        } test_game;
        Game game;
        CHECK(sizeof(test_game) == sizeof(game));
    }
}



TEST_CASE("Test03: simulatePregame() function", "[20 points]")
{
    Team chiefs;
    chiefs.name = "Chiefs";
    std::ifstream fin_chiefs("Chiefs.csv");
    loadTeam(&chiefs, fin_chiefs);
    Team bills;
    bills.name = "Bills";
    std::ifstream fin_bills("Bills.csv");
    loadTeam(&bills, fin_bills);
    Scoreboard scoreboard;
    Game game = {&chiefs, &bills, &scoreboard};
    {
    INFO("simulatePregame() function - seed = 0.");
        // Redirect cout to our std::stringstream buffer
        std::streambuf* coutBuf = std::cout.rdbuf();
        std::stringstream out;
        std::cout.rdbuf(out.rdbuf());
        // Redirect cin to a std::stringstream   
        std::streambuf* cinBuf = std::cin.rdbuf();
        std::stringstream input;
        input << std::string(100, '\n');
        std::cin.rdbuf(input.rdbuf());
        simulatePregame(&game, 0);        
        std::string str = out.str();
        // Restore the original buffer so further cout calls are normal
        std::cout.rdbuf(coutBuf);

        CHECK(str.find("Bills @Chiefs") != std::string::npos);
        CHECK(game.scoreboard->possession == "away");
        CHECK(str.find("Bills starts the game.") != std::string::npos);
        CHECK(str.find("Pregame is over.") != std::string::npos);
    }

    {
    INFO("simulatePregame() function - seed = 2.");
        // Redirect cout to our std::stringstream buffer
        std::streambuf* coutBuf = std::cout.rdbuf();
        std::stringstream out;
        std::cout.rdbuf(out.rdbuf());
        // Redirect cin to a std::stringstream   
        std::streambuf* cinBuf = std::cin.rdbuf();
        std::stringstream input;
        input << std::string(100, '\n');
        std::cin.rdbuf(input.rdbuf());
        simulatePregame(&game, 2);        
        std::string str = out.str();
        // Restore the original buffer so further cout calls are normal
        std::cout.rdbuf(coutBuf);

        CHECK(str.find("Bills @Chiefs") != std::string::npos);
        CHECK(game.scoreboard->possession == "home");
        CHECK(str.find("Chiefs starts the game.") != std::string::npos);
        CHECK(str.find("Pregame is over.") != std::string::npos);
    }
}



TEST_CASE("Test04: simulateHalftime() function", "[10 points]")
{
    Team chiefs;
    chiefs.name = "Chiefs";
    std::ifstream fin_chiefs("Chiefs.csv");
    loadTeam(&chiefs, fin_chiefs);
    Team bills;
    bills.name = "Bills";
    std::ifstream fin_bills("Bills.csv");
    loadTeam(&bills, fin_bills);
    Scoreboard scoreboard;
    Game game = {&chiefs, &bills, &scoreboard};
    {
    INFO("simulateHalftime() function.");
        // Redirect cout to our std::stringstream buffer
        std::streambuf* coutBuf = std::cout.rdbuf();
        std::stringstream out;
        std::cout.rdbuf(out.rdbuf());
        // Redirect cin to a std::stringstream   
        std::streambuf* cinBuf = std::cin.rdbuf();
        std::stringstream input;
        input << std::string(100, '\n');
        std::cin.rdbuf(input.rdbuf());
        simulateHalftime(&game);        
        std::string str = out.str();
        // Restore the original buffer so further cout calls are normal
        std::cout.rdbuf(coutBuf);

        CHECK((str.find("First half is over.") != std::string::npos || str.find("first half is over.") != std::string::npos));
        CHECK((str.find("Score") != std::string::npos || str.find("score") != std::string::npos));
        CHECK(str.find("Patrick Mahomes") != std::string::npos);
        CHECK(str.find("Kareem Hunt") != std::string::npos);
        CHECK(str.find("James Cook") != std::string::npos);
        CHECK(str.find("Curtis Samuel") != std::string::npos);
    }
}



TEST_CASE("Test05: simulateEndgame() function", "[10 points]")
{
    Team chiefs;
    chiefs.name = "Chiefs";
    std::ifstream fin_chiefs("Chiefs.csv");
    loadTeam(&chiefs, fin_chiefs);
    Team bills;
    bills.name = "Bills";
    std::ifstream fin_bills("Bills.csv");
    loadTeam(&bills, fin_bills);
    Scoreboard scoreboard;
    Game game = {&chiefs, &bills, &scoreboard};
    {
    INFO("simulateEndgame() function.");
        // Redirect cout to our std::stringstream buffer
        std::streambuf* coutBuf = std::cout.rdbuf();
        std::stringstream out;
        std::cout.rdbuf(out.rdbuf());
        // Redirect cin to a std::stringstream   
        std::streambuf* cinBuf = std::cin.rdbuf();
        std::stringstream input;
        input << std::string(100, '\n');
        std::cin.rdbuf(input.rdbuf());
        simulateEndgame(&game);        
        std::string str = out.str();
        // Restore the original buffer so further cout calls are normal
        std::cout.rdbuf(coutBuf);

        CHECK((str.find("Game is over.") != std::string::npos || str.find("game is over.") != std::string::npos));
        CHECK((str.find("Score") != std::string::npos || str.find("score") != std::string::npos));
        CHECK(str.find("Patrick Mahomes") != std::string::npos);
        CHECK(str.find("Kareem Hunt") != std::string::npos);
        CHECK(str.find("James Cook") != std::string::npos);
        CHECK(str.find("Curtis Samuel") != std::string::npos);
        CHECK(str.find("draw") != std::string::npos);
    }
}




int count(std::string str, std::string target) {
    std::stringstream out(str);
    int count = 0;
    std::string word;
    while (out >> word) {
    if (word == target) {
        ++count;
    }
    }
    return count;    
}
TEST_CASE("Test06: simulateGameDay() function", "[40 points]")
{
    Team chiefs;
    chiefs.name = "Chiefs";
    std::ifstream fin_chiefs("Chiefs.csv");
    loadTeam(&chiefs, fin_chiefs);
    Team bills;
    bills.name = "Bills";
    std::ifstream fin_bills("Bills.csv");
    loadTeam(&bills, fin_bills);
    Scoreboard scoreboard;
    Game game = {&chiefs, &bills, &scoreboard};
    {
    INFO("simulateGameDay() function - seed = 0.");

        // Redirect cout to our std::stringstream buffer
        std::streambuf* coutBuf = std::cout.rdbuf();
        std::stringstream out;
        std::cout.rdbuf(out.rdbuf());
        // Redirect cin to a std::stringstream   
        std::streambuf* cinBuf = std::cin.rdbuf();
        std::stringstream input;
        input << std::string(100, '\n');
        std::cin.rdbuf(input.rdbuf());
        simulateGameDay(&game, 0);        
        std::string str = out.str();
        // Restore the original buffer so further cout calls are normal
        std::cout.rdbuf(coutBuf);


        CHECK(str.find("Bills @Chiefs") != std::string::npos);
        CHECK(game.scoreboard->possession == "home");
        CHECK(str.find("Bills starts the game.") != std::string::npos);
        CHECK(str.find("Pregame is over.") != std::string::npos);


        CHECK(str.find("Bills have the possession") != std::string::npos);


        CHECK((str.find("First half is over.") != std::string::npos || str.find("first half is over.") != std::string::npos));
        CHECK((str.find("Score") != std::string::npos || str.find("score") != std::string::npos));
        CHECK(str.find("Patrick Mahomes") != std::string::npos);
        CHECK(str.find("Kareem Hunt") != std::string::npos);
        CHECK(str.find("James Cook") != std::string::npos);
        CHECK(str.find("Curtis Samuel") != std::string::npos);


        CHECK(str.find("Chiefs have the possession") != std::string::npos);
        CHECK(count(str, "Possession") == 2);

        CHECK((str.find("Game is over.") != std::string::npos || str.find("game is over.") != std::string::npos));
        CHECK((str.find("Score") != std::string::npos || str.find("score") != std::string::npos));
        CHECK(str.find("Patrick Mahomes") != std::string::npos);
        CHECK(str.find("Kareem Hunt") != std::string::npos);
        CHECK(str.find("James Cook") != std::string::npos);
        CHECK(str.find("Curtis Samuel") != std::string::npos);
    }
}












void DeleteFilesWithPrefix(const std::string& prefix) {
    // Get the current working directory
    std::filesystem::path folder_path = std::filesystem::current_path();

    // Check if the folder exists and is a directory
    if (std::filesystem::exists(folder_path) && std::filesystem::is_directory(folder_path)) {
        // Iterate over all files in the directory
        for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(folder_path)) {
            // Check if it's a regular file
            if (std::filesystem::is_regular_file(entry.path())) {
                // Get the file name as a string
                std::string file_name = entry.path().filename().string();
                
                // Check if the file name starts with the given prefix
                if (file_name.rfind(prefix, 0) == 0) {  // rfind with '0' checks prefix at start
                    std::filesystem::remove(entry.path());
                }
            }
        }
    } 
}

TEST_CASE("Dummy test case to delete player files") {
    DeleteFilesWithPrefix("home");
    DeleteFilesWithPrefix("away");
    DeleteFilesWithPrefix("49ers_");
    DeleteFilesWithPrefix("Bills_");
    DeleteFilesWithPrefix("Buccaneers_");
    DeleteFilesWithPrefix("Chiefs_");
    DeleteFilesWithPrefix("Cowboys_");
    DeleteFilesWithPrefix("Lions_");
    DeleteFilesWithPrefix("Ravens_");
    DeleteFilesWithPrefix("Texans_");
}


