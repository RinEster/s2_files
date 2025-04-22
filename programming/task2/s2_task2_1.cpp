//Дана последовательность целых чисел. 
// Найти все такие цифры, которые встречаются только в двузначных числах. 
// Работать только с цифрами, которые встречаются в данной последовательности, 
// а не со всеми цифрами от 0 до 9.

#include <iostream>
#include <set>

int main() {

    int count, v, n1, n2;
    std::set<int> numbers;
    std::set<int> twoDigitNumber;
    std::set<int> ostNumber;

    std::cout << "count: ";
    std::cin >> count;
    if (count <= 0) {
        std::cout << "input error";
        return 1;
    }

    std::cout << "1 - input; \n2 - random; \n";
    std::cin >> v;
    switch (v) {
    case 1: {
        for (int i = 0; i < count; i++) {
            int el;
            std::cin >> el;
            numbers.insert(el);
        }
        for (int n : numbers) {
            std::cout << n << " ";
        }
        break;
    }
    case 2: {
        srand((unsigned)time(NULL));
        for (int i = 0; i < count; i++) {
            numbers.insert(rand() % 150);
        }
        for (int n : numbers) {
            std::cout << n << " ";
        }
        break;
    }
    default: {
        std::cout << "error";
        return 1;
    }
    }

    if (!numbers.empty()) {
        for (int n : numbers) {
            if (n > 9 && n < 100) {
                n1 = n / 10;
                n2 = n % 10;
                twoDigitNumber.insert(n1);
                twoDigitNumber.insert(n2);
            }
            else {
                int ost;
                while (n>0) {
                    ost = n % 10;
                    ostNumber.insert(ost);
                    n = n / 10;
                }
                
            }
        }
        std::cout << std::endl;
        for (int n : ostNumber) {
            std::cout << n << " ";
        }
        std::cout << "rrr";
        std::set<int> result;
        for ( int word : twoDigitNumber) {
            if (ostNumber.find(word) == ostNumber.end()) {
                result.insert(word);
            }
        }
        if (twoDigitNumber.empty()) {
            std::cout << "\nTwo-digit numbers were not found.";
        }
        else {
            std::cout << "\ntw: ";
            for (int n : twoDigitNumber) {
                std::cout << n << " ";
            }
            std::cout << "\nres: ";
            for (int n : result) {
                std::cout << n << " ";
            }
        }
    }
    else {
        std::cout << "the sequence is empty";
        return 1;
    }
    return 0;
}