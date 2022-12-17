// dictionary txt from https://raw.githubusercontent.com/sujithps/Dictionary/master/Oxford%20English%20Dictionary.txt
#include "dictionary.h"

using namespace std;

void Dictionary::importDictionary() {
    string input;
    ifstream fin;
    vector<word> wordInput;
    wordInput.resize(1);
    int inputNum = 0;
    int i = 0;
    allWords.resize(26);
    fin.open("dictionary.txt");
    cout << "Opened" << endl;
    while (getline(fin, input)) {
        if (input.size() != 0) {
            if (input.compare("~") ==0) {
                i++;
                inputNum = 0;
            }
            else if (inputNum == 0) {
                wordInput[0].name = input;
                inputNum++;

            }
            else if (inputNum == 1){
                wordInput[0].definition = input;
                allWords.at(i).push_back(wordInput.at(0));
                inputNum = 0;
            }
        }
    } 
    fin.close();
}

string Dictionary::getWord(string input) {
    string def;
    def == "TEST";
    int letterIndex;
    bool wordInDictionary = false;
    letterIndex = input[0]-65;
    if (letterIndex < 0) {
        letterIndex+=22;
    }
    for (int i; i < allWords.at(letterIndex).size(); i++) {
        if (input.compare(allWords.at(letterIndex).at(i).name) == 0) {
            def = allWords.at(letterIndex).at(i).definition;
            wordInDictionary = true;
        }
    }
    if(wordInDictionary == true) {
        return def;
    }
    else {
        return "Error: Word not known.";
    }

}

void Dictionary::listWords(char input) {
    int letterIndex = input-65;
    if (letterIndex > 25) {
        letterIndex-=32;
    }
    cout << letterIndex << endl;
    for (int i = 0; i < allWords.at(letterIndex).size(); i++) {
        cout << allWords.at(letterIndex).at(i).name << endl;
    }
}

int Dictionary::numWords(char input) {
    int letterIndex = input-65;
    if (letterIndex > 25) {
        letterIndex-=32;
    }
    return allWords.at(letterIndex).size();
}
int Dictionary::numWordsTotal() {
    int totalWords = 0;
    for (int i = 0; i < allWords.size(); i++) {
        totalWords += allWords.at(i).size();
    }
    return totalWords;
}
int main() {
    char userInput;
    string wordInput;
    char letterInput;
    Dictionary dic;
    dic.importDictionary();
    bool running = true;
    while (running) {
        cout << "Enter an input: " ;
        cin >> userInput;
        switch(userInput) {
            case 'q':
            case 'Q':
                running = false;
                cout << "Quitting..." << endl;
                break;
            case 'l':
            case 'L':
                cout << "Enter a letter to list words of (Capitalize): ";
                cin >> letterInput;
                dic.listWords(letterInput);
                break;
            case 'd':
            case 'D':
                cout << "Enter a word to define (Capitalize first letter): ";
                cin >> wordInput;
                cout << dic.getWord(wordInput) << endl;
                break;
            case 'h':
            case 'H':
                cout << "~~~~~Command Menu~~~~~ " << endl;
                cout << "L -- List known words beginning with followup letter provided."  << endl;
                cout << "D -- Define a followup word." << endl;
                cout << "N -- Number of words  indexed at a given Letter." << endl;
                cout << "T -- Total Number of Words indexed. " << endl;
                cout << "Q -- Quits program." << endl;
                break;
            case 'n':
            case 'N':
                cout << "Enter a letter to find the number of words indexed: ";
                cin >> letterInput;
                cout << letterInput << " has " << dic.numWords(letterInput) << " words indexed." << endl;
                break;
            case 't':
            case 'T':
                cout << "The total number of words indexed is " << dic.numWordsTotal() << ". " << endl;
                break;                    
            default:
                cout << "Unknown input. type 'H' for a list of commands." << endl;
                break;
        }

    }
    return 0;
}