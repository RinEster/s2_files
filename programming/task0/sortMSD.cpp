//Поразрядная  от старшего разряда к младшему.  
#include <iostream>
#include <vector>
#include <string>

//максимальный разряд числа в массиве
int maxR(std::vector<int> arr) {
    int max = 0; //переменная для хранения максимального разряда числа 
    for (int num : arr) {  
        int count = 0; //количество цифр данного числа
        int temp = num;    
        if (temp == 0) count = 1;  
        while (temp != 0) {
            count++;
            temp /= 10;
        }
        if (count > max) {
            max = count;
        }
    }
    return max;
}

//преобразование чисел в тип string с добавлением недостающих разрядов в начале
std::vector<std::string> numberWithMaxR(std::vector<int> arr, int max) {
    std::vector<std::string> strNumber;
    for (int num : arr) {
        std::string t = std::to_string(num);
        while (t.length() < max) { 
            t = "0" + t; //добавление нулей
        }
        strNumber.push_back(t);
    }
    return strNumber;
}

//получение цифры стоящей в заданном разряде
int getNum(std::string num, int razr) {
    return num[razr] - '0';//преобразование в число
}

//поразрядная сортировка
void sortMSD(std::vector<std::string>& arr, int razr, int max) {
    if (razr >= max || arr.size() <= 1) {
        return;
    }

    std::vector<std::vector<std::string>> vectArr(10); //вектор векторов для распределения по цифре разряда

    for (auto& num : arr) { 
        int ch = getNum(num, razr); //получение цифры заданного разряда
        vectArr[ch].push_back(num);//распределение
    }

    for (auto& vect : vectArr) {
        if (!vect.empty()) {
            sortMSD(vect, razr + 1, max);
        }
    }

    arr.clear();
    for (auto& v : vectArr) {
        arr.insert(arr.end(), v.begin(), v.end());
    }
}

int main() {

    int n;
    std::cout << "Enter size of array: ";
    std::cin >> n;
    //заполнение последовательности чисел
    std::vector<int> arr;
    for (int i = 0; i < n; i++) {
        int k;
        std::cin >> k;
        arr.push_back(k);
    }
    //получение максимального разряда числа
    int max = maxR(arr);

    //преобразование в строковый тип и добавление недостающих разрядов
    std::vector<std::string> strArr = numberWithMaxR(arr, max);

    //сортировка
    sortMSD(strArr, 0, max);

    //вывод результата
    std::cout << "Result: \n";
    for (auto& n : strArr) {
        std::cout << std::stoi(n) << " ";
    }
    std::cout << std::endl;

    return 0;
}