#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

std::vector<std::string> wordsForGame = {
    "PROGRAMMING",
    "INTELLECT",
    "FUNCTION",
    "CYCLE",
    "CONDITION",
    "OPERATOR",
    "EXPERIMENT",
    "LIBRARY",
    "INTERFACE"
};
int main() {
    srand(time(0));

    std::string word = wordsForGame[rand() % wordsForGame.size()];
    std::string displayWord(word.size(), '_');
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int maxAttempts = 10;
    int wrongAttempts = 0;
    bool ygadan = false;
    //цикл пока попытки не кончились и слово не угадано
    while (wrongAttempts < maxAttempts && !ygadan) {
      //  system("cls"); //очистка окна консоли

        std::cout << "Attempts: " << maxAttempts - wrongAttempts << std::endl;
        std::cout << "\nWord: " << displayWord << std::endl;
        std::cout << "Alphabet: " << alphabet << "\n\n";
        //ввод буквы или слова пользователем
        std::cout << "Enter a letter or word: ";
        std::string input;
        std::getline(std::cin, input);
        transform(input.begin(), input.end(), input.begin(), ::toupper); //преобразование введенного в верхний регистр
        //введена буква
        if (input.size() == 1) {
            char letter = input[0];
            size_t pos = alphabet.find(letter);
            //буква уже была исползована
            if (pos == std::string::npos) {
                std::cout << "Wrong letter\n";
                continue;
            }
            alphabet[pos] = ' ';
            size_t letterPos = word.find(letter);
            //буква не была использована
            if (letterPos != std::string::npos) {
                for (size_t i = 0; i < word.size(); i++) {
                 
                    if (word[i] == letter) {
                        displayWord[i] = letter;
                    }
                }
                if (displayWord == word) {
                    ygadan = true;
                }
            }
            else {
                std::cout << "Wrong letter\n";
                wrongAttempts++;
            }
        }
        //введено слово
        else if (input.size() == word.size()) {
            //слово угадано
            if (input == word) {
                ygadan = true;
                displayWord = word;
            }
            //неправильное слово
            else {
                std::cout << "Wrong word! Game over.\n";
                return 1;
            }
        }
        else {
            std::cout << "Invalid input!\n";
        }
    }

  //  system("cls");
    if (ygadan) {
        std::cout << "You won! The word was: " << word << std::endl;
    }
    else {
        std::cout << "Game over! The word was: " << word << std::endl;
    }
    return 0;
}