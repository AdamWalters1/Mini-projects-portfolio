#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int NO_OF_QUESTIONS = 20;
char ID[11];
char examGrade(int score);
int processAnswer(const char answerString[], const char keyString[]);

int main()
{
    
    ifstream inFile("../data/exam.txt");
    char keyString[21];
    char answerString[21];
    inFile.get(keyString,21);
    inFile.get();

    while (inFile >> ID){
        inFile.get();
        inFile.get(answerString, 21);
        inFile.get();

        int score = processAnswer(answerString,keyString);

        cout << ID << " " << answerString << "  " << score << "  " << examGrade(score) << endl;
    }


    return 0;
}

/**
 * Calculates the score based on the given answer string and key string.
 * 
 * @param answerString The answer string provided by the user.
 * @param keyString The key string containing the correct answers.
 * @return The calculated score.
 */
int processAnswer(const char answerString[], const char keyString[])
{
    int score = 0;
    for(int i = 0;i < 20;++i){
        if(answerString[i] == keyString[i]){
            score += 2;
        }
        else if (answerString[i] != ' ')
            score -= 1;
        else{
            score -= 1;
        }
    }
    return score;
}


/**
 * Calculates the exam grade based on the given score.
 * 
 * @param score The score obtained in the exam.
 * @return The corresponding grade based on the score.
 */
char examGrade(int score)
{
    char grade;
    double dec = static_cast<double>(score)/40;
    if(dec > .9)
        grade = 'A';
    else if(.9 > dec && dec > .8)
        grade = 'B';
    else if(.8 > dec && dec >.7)
        grade  = 'C';
    else if(.7 > dec && dec > .6)
        grade = 'D';
    else
        grade = 'F';

    return grade;
}
