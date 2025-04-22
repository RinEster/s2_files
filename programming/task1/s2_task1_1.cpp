//Дан набор целых чисел. Заменить все четные числа минимальным.

#include <iostream>
#include <vector>

int main(){
    int n;
    std::cout << "vector size: ";
    std::cin >> n;
    std::vector<int> numbers;
    
    //заполнение вектора
    srand ((unsigned)time(NULL));
    for(int i = 0; i < n; i++){
        numbers.push_back(rand()%7);
    }

    int minc = numbers[0];

    //вывод вектора и поиск минимального
    for(int i = 0; i < n; i++){
        std::cout << numbers[i] << " ";
        if(minc > numbers[i]){
            minc = numbers[i];
        }
    }

    //замена четных чисел минимальным
    for(int i = 0; i < n; i++){
        if(numbers[i] % 2 == 0){
            numbers[i] = minc;
        }
    }
    std::cout << std::endl << "result: ";
    //вывод результата
    for(int i = 0; i < n; i++){
        std::cout << numbers[i] << " ";
    }

    system("pause");
    return 0;
}