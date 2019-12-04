#include "dictionary.h"
#include <vector>
#include <fstream>
#include <stdlib.h>


dictionary::dictionary(double rate)
{
    std::ifstream file;
    winRate = rate;
    vDict.resize(30);
    srand(time(NULL));
    int winPoint = winRate*100;
    int random = rand() % 100 + 1;
    std::string word;

    if(random < winPoint){
        file.open(NGSL_FILENAME.c_str());

        if(file.is_open()){
            while(std::getline(file, word))
                vDict.at(word.size()).push_back(word);
        }
    }

    else{
        file.open(DICTIONARY_FILENAME.c_str());

        if(file.is_open()){

            while(std::getline(file, word))
                vDict.at(word.size()).push_back(word);
        }
    }
    file.close();

}

bool dictionary::isValidLength(int len){
    if(vDict.at(len).empty()) return false;
    return true;
}

void dictionary::setWordList(int len){
    list = vDict.at(len);
}

void dictionary::updateList(){
    std::vector< std::vector<std::string> > newList;

    for(int i = 0; i < list.size(); i++){
        bool added = false;

        for(int j = 0; j < newList.size(); j++){
            if(sameFamily(list.at(i), newList.at(j).at(0))){
                newList.at(j).push_back(list.at(i));
                added = true;
            }
        }

        if( !added ){
            std::vector<std::string> temp;
            temp.push_back(list.at(i));
            newList.push_back(temp);
        }
    }

    srand(time(NULL));
    int winPoint = winRate*100;
    int random = rand() % 100 + 1;
    if(random < winPoint){
        int minIndex = 0;
        for(int i = 1; i < newList.size(); i++){
            if(newList.at(minIndex).size() > newList.at(i).size())
                minIndex = i;
        }
        list = newList.at(minIndex);
    }

    else{
        int maxIndex = 0;
        for(int i = 1; i < newList.size(); i++){
            if(newList.at(maxIndex).size() < newList.at(i).size())
                maxIndex = i;
        }
        list = newList.at(maxIndex);
    }
    updateWord();
}

bool dictionary::sameFamily(std::string compare1, std::string compare2){
    bool isSameFamily = true;
    for(int i = 0; i < compare1.size(); i++){
        if(compare1.at(i) == lastGuess || compare2.at(i) == lastGuess)
            if( compare1.at(i) != compare2.at(i) )
                isSameFamily = false;
    }
    return isSameFamily;
}

void dictionary::constructBlankWord(int len){
    std::string str = "";
    for(int i = 0; i < len; i++)
        str = str + "-";

    word = str;
}

std::string dictionary::getWord(){
    return word;
}

void dictionary::setGuess(char guess){
    lastGuess = guess;
}

void dictionary::updateWord(){
    std::string newWord = "";
    for(int i = 0; i < list.at(0).size(); i++){
        if(list.at(0).at(i) == lastGuess)
            newWord += lastGuess;
        else if(word.at(i) != '-')
            newWord += word.at(i);
        else
            newWord += '-';
    }
    word = newWord;
}

bool dictionary::rightGuess(){
    for(int i = 0; i < word.size(); i++){
        if(word.at(i) == lastGuess) return true;
    }
    return false;
}

std::string dictionary::getAnswer(){
    return list.at(0);
}




