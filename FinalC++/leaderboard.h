// -----------------------------------------------------------------------------
// This class holds all of the information for the leaderboard information that
// goes on the top and bottom of the game board.b It is able to add points
// when the player hits an enemy with a laser and display a current high score
// from a file.
// -----------------------------------------------------------------------------
#include "header.h"
#include "record.h"

const int TOP5 = 5;

class Leaderboard
{
private:
    Record recorder;                    //Holds hi-score information
    int size;                           //Size of all hi-score records from file.
    int index;                          // variable to hold an index
    int scoreOne;                       //Player One's score.
    int hiScore;                        //High Score.
    int credit;                         //Credits player has.
public:
    Leaderboard();                      //Default constructor.
    void addScore(int);                 //Add score for kills.
    void setHiScore();                  //Set Hi-Score.
    int getScore(){ return scoreOne; }  //Display Player One's score.
    int getHiScore(){ return hiScore; } //Display Hi-Score.
    void getLeaderboard();              //Display scores neatly.
    void getBtmBoard();                 //Display lives & credits
    void displayLives();                //Determine how many lives to display.
    int lives;                          //The number of lives the player has.
    bool hiScores();                    // high scores function
    void displayHiscores();             // display high scores function
    void registration();                //Get name from user if hi-score reached.
    void setScoreOne(int);              //For resetting the game
    void lostLife() { --lives; }        //Lose a life
    int getLives() { return lives; }    //Get current number of lives
};

Leaderboard::Leaderboard(){                 //Default constructor.
    index=0;
    scoreOne=0;
    hiScore=0;
    lives=3;
    credit=0;
}

void Leaderboard::setScoreOne(int s) { scoreOne = s; }   //lets the board class reset the score

void Leaderboard::addScore(int score){      //Accepts score for the kill and
    scoreOne+=score;                        //Adds score to scoreOne.
}

void Leaderboard::setHiScore(){
    if(hiScore<=scoreOne)
    hiScore=scoreOne;
    if(hiScores()){
        registration();
    }
}

void Leaderboard::getLeaderboard(){         //Display the top UI.
    cout<<"SCORE<1>"<<"\tHI-SCORE\n  ";
    cout<<setw(4)<<setfill('0')<<scoreOne<<"\t\t "<<setw(4)<<setfill('0')<<hiScore<<endl<<endl;
}

void Leaderboard::getBtmBoard(){            //Display lives & credits below
    cout<<endl<<lives;                            //game board.
    displayLives();     //Call separate function to display lives
    cout<<"\t\tCREDIT "<<credit<<endl;
}

void Leaderboard::displayLives(){
    switch(lives){                          //Determine how many lives to
        case 3: cout<<" PP";                //display based on lives left
                break;                      //in Space Invaders Theme.
        case 2: cout<<" P";
                break;
        case 1: cout<<" ";
                break;
    }
}

bool Leaderboard::hiScores(){
    fstream hiscoreFile;
    hiscoreFile.open("hiscores.dat", ios::in | ios::binary);//Check if file exists.
    if(hiscoreFile.fail()){
        hiscoreFile.open("hiscores.dat", ios::out|ios::binary);//create a new file.
        cout<<"NO HI-SCORES RECORDED YET."<<endl;
        cout<<"NEW HI-SCORE!"<<endl;
        hiscoreFile.close();
        return true;
    }
    else{
        long numBytes;
        hiscoreFile.seekg(0L, ios::end);
        numBytes=hiscoreFile.tellg();
        hiscoreFile.seekg(0L, ios::beg);
        hiscoreFile.close();
        displayHiscores();
        return true;
    }
}

void Leaderboard::displayHiscores(){
    fstream hiscoreFile;
    Record temp[size];
    hiscoreFile.open("hiscores.dat", ios::in|ios::binary);
    hiscoreFile.read(reinterpret_cast<char *>(&temp), sizeof(temp));
    for(int count=0;count<size;count++){
        cout<<"***********************"<<endl;
        cout<<setw(12)<<temp[count].name<<setw(6)<<temp[count].score<<endl;
    }
    cout<<"***********************"<<endl;
}

void Leaderboard::registration(){
    fstream hiscoresFile;
    char name[NAME_SIZE];
    size++;
    getLeaderboard();
    //reevaluateScores();
    cout<<"\t\tHI-SCORER REGISTRATION\n";
    
    cout<<"ENTER NAME (10 letters max): ";
    cin.getline(recorder.name, NAME_SIZE);
    recorder.score=hiScore;
    hiscoresFile.open("hiscores.dat", ios::out | ios::app | ios::binary);
    hiscoresFile.write(reinterpret_cast<char *>(&recorder),sizeof(recorder));
}
