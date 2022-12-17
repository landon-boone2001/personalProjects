#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
class Dictionary {
    public:
        std::string input;
        std::string getWord(std::string);
        void importDictionary();
        void listWords(char);
        int numWords(char);
        int numWordsTotal();
        struct word {
            std::string name;
            std::string definition;
        };
        std::vector<std::vector<word>> allWords;

};