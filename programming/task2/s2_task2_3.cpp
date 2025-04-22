//Дан текст, состоящий из предложений, 
// разделенных знаками препинания из набора «.?!». 
// Предложения в свою очередь состоят из слов, отделенных друг 
// от друга пробелами. Найти слова (без учета регистра), 
// которые встречаются одновременно и в повествовательных, 
// и в вопросительных предложениях

#include <iostream>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <vector>

//для очищения слов от знаков препинания
std::set<std::string> cleanWords(const std::set<std::string>& words) {
    std::set<std::string> cleanedWords;

    for (const auto& pW : words) {
        std::string cleanedWord;
        for (char ch : pW) {
            //если символ не является знаком препинания добалвяем его в новео слово
            if (!std::ispunct(ch)) {
                cleanedWord += ch;
            }
        }
        if (!cleanedWord.empty()) {
            cleanedWords.insert(cleanedWord);
        }
    }
    return cleanedWords;
}

int main() {

    std::string text;

    std::cout << "input text: ";

    if (!std::getline(std::cin, text)) {
        std::cerr << "error!" << std::endl;
        return 1;
    }
    if (text.empty()) {
        std::cout << "Error! string empty";
        return 1;
    }
    //переводим в нижний регистр
    for (char& ch : text) {
        ch = std::tolower(ch);
    }

    std::set<std::string> povSentences; //для повествовательных
    std::set<std::string> voprSentences; //для вопросительных
    std::set<std::string> vosklSentences; //для восклицательных (по сути всех остальных)

    std::string currentSentence;
    //распределительная шляпа по сетам
    for (char ch : text) {
        currentSentence += ch;

        if (ch == '.') {
            povSentences.insert(currentSentence);
            currentSentence.clear();
        }
        else if (ch == '!') {
            vosklSentences.insert(currentSentence);
            currentSentence.clear();
        }
        else if (ch == '?') {
            voprSentences.insert(currentSentence);
            currentSentence.clear();
        }
    }
    if (!currentSentence.empty()) {
        vosklSentences.insert(currentSentence); // Добавляем в восклиц, т.к. они по сути не интересуют
    }
    /*
    std::cout << "povSentences: \n";
    for (auto s : povSentences) {
        std::cout << s << " \n";
    }
    std::cout << "\n\n\nvosklSentences: \n";
    for (auto s : vosklSentences) {
        std::cout << s << " \n";
    }
    std::cout << "\n\n\nvoprSentences: \n";
    for (auto s : voprSentences) {
        std::cout << s << " \n";
    }
    */

    //делим все предложения на отдельные слова
    std::set<std::string> povWords;
    for (const auto s : povSentences) {
        std::istringstream iss(s);
        std::string word;
        while (iss >> word) {
            povWords.insert(word);
        }
    }
    //очистка слов
    povWords = cleanWords(povWords);
    
    //аналогичное для вопросительных предложений
    std::set<std::string> voprWords;
    for (const auto s : voprSentences) {
        std::istringstream iss(s);
        std::string word;
        while (iss >> word) {
            voprWords.insert(word);
        }
    }
    //очистка
    voprWords = cleanWords(voprWords);
    if (!povWords.empty()) {
        std::cout << "povWords: \n";
        for (auto s : povWords) {
            std::cout << s << " \n";
        }
    }
    else {
        std::cout << "povWords is empty";
        return 1;
    }
    if (!voprWords.empty()) {
        std::cout << "\n\nvoprWords: \n";
        for (auto s : voprWords) {
            std::cout << s << " \n";
        }
    }
    else {
        std::cout << "voprWords is empty";
        return 1;
    }   
    //общие слова
    std::set<std::string> commonWords;
    for (const auto word : povWords) {
        if (voprWords.find(word) != voprWords.end()) {
            commonWords.insert(word);
        }
    }
    std::cout << "\n\n\n\nresult:\n";
    for (const auto& word : commonWords) {
        std::cout << word << std::endl;
    }

    return 0;

    //
}
