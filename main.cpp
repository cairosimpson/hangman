#include <iostream>
#include <fstream>
#include "dictionary.h"

using namespace std;

void playGame();

int getLength(dictionary &dict);
int getNumGuesses();
void playGame(dictionary &dict);
char getGuess(vector<char> &guessed);
void updateInfo(int &numGuess, vector<char> &guessed, dictionary &dict);
void displayGuessed(vector<char> &guessed);
bool vecContains(vector<char> &guessed, char letter);
bool hasWon(string word);
double scoreGame(string word, int numGuess);

const double WIN_RATE = 0;

int main()
{
    bool play = true;
    string input;

    while(play){
        dictionary dict(WIN_RATE);
        playGame(dict);
        cout << "Would you like play again? (y/n): ";
        cin >> input;
        char ch = tolower(input.at(0));
        if( ch == 'n') play = false;
    }
    cout << endl<< "Program Ending. Thanks for Playing!" << endl << endl;
}

int getLength(dictionary &dict){
    int len;
    cout << endl << endl<< "Big C Games Presents: Hangman" << endl;
    cout << "Please enter desired word length: ";
    cin >> len;

     while( !dict.isValidLength(len) ){
        cout << "Error: There are no words with " << len << " letters found." << endl;
        cout  << "Please enter a valid word length: ";
        cin >> len;
    }
    return len;

}

int getNumGuesses(){
    int numGuess;
    cout << "Please enter the number of guesses you would like to have: ";
    cin >> numGuess;
    while( numGuess < 1 || numGuess > 26){
        cout << "Error: Please enter an integer greater than 0 and less than 27" <<endl;
        cout << "Try again: ";
        cin >> numGuess;
    }
    return numGuess;

}

char getGuess(vector<char> &guessed){
    string input;
    cout << "Please enter a guess: ";
    cin >> input;
    while( vecContains(guessed, input.at(0)) ){
        cout << endl << "You have already guessed " << input.at(0);
        cout << endl << "Please enter a valid guess: ";
        cin >> input;
    }
    guessed.push_back(input.at(0));
    return input.at(0);
}

double scoreGame(string word, int numGuess){
    int numUnguessed = 0;
    int length = 0;

    for(int i = 0; i < word.size(); i++){
        if(word.at(i) == '-') numUnguessed++;
        length++;
    }
    int score = ( numUnguessed / length ) * 100;


    return numGuess;
}

void playGame(dictionary &dict){
    int length = getLength(dict);
    dict.constructBlankWord(length);
    int numGuess = getNumGuesses();
    dict.setWordList(length);
    vector<char> guessed;
    while( !hasWon(dict.getWord()) && numGuess > 0){
        char guess = getGuess(guessed);
        dict.setGuess(guess);
        dict.updateList();
        updateInfo(numGuess, guessed, dict);

    }
    if(numGuess == 0){
        cout<< endl << "L-O-S-E-R!!!!"<<endl;
        cout<<"The answer was: " << dict.getAnswer() << endl << endl;
    }
    else cout<< endl << "Congratulations! You Won!"<<endl << endl;

}

bool hasWon(string word){
    for(int i = 0; i < word.length(); i++){
        if(word.at(i) == '-') return false;
    }
    return true;
}

bool vecContains(vector<char> &guessed, char letter){
    for(int i = 0; i < guessed.size(); i++){
        if(guessed.at(i) == letter) return true;
    }
    return false;
}

void displayGuessed(vector<char> &guessed){
    cout << endl << "Guessed: ";
    for(int i = 0; i < guessed.size(); i++)
        cout << guessed.at(i) << ' ';
}

void updateInfo(int &numGuess, vector<char> &guessed, dictionary &dict){
    if(!dict.rightGuess()){
       numGuess--;
    }
    cout<<endl<<dict.getWord();
    displayGuessed(guessed);
    cout<<endl<<"Guesses Remaining: "<<numGuess<<endl;
}

