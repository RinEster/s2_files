//Во входном файле задан набор слов и целых чисел,
//разделенных пробелами. Найти все числа, встречающиеся столько же раз, сколько первое слово 
//(Первое слово - в первоначальном наборе данных, а не в итоговом).

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm> 

int main() {    
    std::ifstream inputFile;

    try {
        //открытие файла
        inputFile.open("C:\\inputData.txt");
        //обработка ошибки выполнения файла
        if (inputFile.fail()) {
            throw std::runtime_error("Couldn't open the file");
        }      

        std::map<std::string, int> wordCount;
        std::map<int, int> numberCount;
        std::string firstWord;
        std::string data;

        //считывание строки из файла и запись в переменную
        while (std::getline(inputFile, data)) {
            if (data.empty()) {
                throw std::runtime_error("File is empty");
            }
            //обработки строки как потока
            std::istringstream lineStream(data);
            //для хранения отдельных слов
            std::string element;
            //извлечение элемента из потока
            while (lineStream >> element) {
                //преобразование символов в нижний регистр
                std::transform(element.begin(), element.end(), element.begin(), ::tolower);
                //проверка, является ли числом
                if (std::isdigit(element[0]) || (element[0] == '-' && element.size() > 1)) {
                    int number = std::stoi(element); //stoi - преобразование в int
                    numberCount[number]++;
                }
                else {
                    if (wordCount.empty()) {
                        firstWord = element;
                    }
                    wordCount[element]++;
                }
            }
        }
        int firstWordCount = wordCount[firstWord];

        std::vector<int> result;
        for (const auto& n : numberCount) {
            if (n.second == firstWordCount) {
                result.push_back(n.first);
            }
        }
        std::cout << "result: " << firstWord << " ";
        for (int number : result) {
            std::cout << number << " ";
        }
        std::cout << std::endl;

        inputFile.close();
    }
    //ошибка во время выполнения
    catch (const std::runtime_error& ex){
        std::cout << ex.what() << std::endl;
        return 1;
    }      
    return 0;
}