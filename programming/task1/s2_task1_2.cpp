//Дана последовательность целых чисел. Создать новую последовательность, 
//удалив все нечетные числа. Создать новую последовательность, применив циклический сдвиг так, 
//чтобы на первом месте стоял минимальный элемент. Отсортировать последовательность. 
//Вставить новый элемент в отсортированную последовательность так, чтобы последовательность осталась отсортированной 
//(Добавление элемента в конец и последующая сортировка не является оптимальным вариантом).

#include <iostream>
#include <deque>
#include <algorithm>

void OutPutDeque(std::deque<int> numbers);

int main() {
    int n;
    std::cout << "dequa size: ";
    std::cin >> n;
    std::deque<int> numbers;

    //заполнение деки
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        numbers.push_back(rand() % 7);
    }

    OutPutDeque(numbers);  
    std::cout << std::endl;

    //Создать новую последовательность, удалив все нечетные числа.
    std::deque<int> newNumbers;
    newNumbers.assign(numbers.begin(), numbers.end());
    //удаление
    newNumbers.erase(std::remove_if(newNumbers.begin(), newNumbers.end(),
        [](int x) { return x % 2 != 0;}), newNumbers.end());
    std::cout << std::endl << "result 1: "; 
    OutPutDeque(newNumbers);
    std::cout << std::endl;

    //Создать новую последовательность, применив циклический сдвиг так, 
    //чтобы на первом месте стоял минимальный элемент. Отсортировать последовательность. 
    //Вставить новый элемент в отсортированную последовательность так, чтобы последовательность осталась отсортированной 
    //(Добавление элемента в конец и последующая сортировка не является оптимальным вариантом).

    std::deque<int> secondNewNumbers;
   // secondNewNumbers.assign(numbers.begin(), numbers.end());

    auto minN = min_element(numbers.begin(), numbers.end());
    int minIndex = distance(numbers.begin(), minN);

    for (size_t i = 0; i < numbers.size(); ++i) {
        secondNewNumbers.push_back(numbers[(minIndex + i) % numbers.size()]);
    }
    std::cout << std::endl << "after sdvig: ";
    OutPutDeque(secondNewNumbers);
    std::cout << std::endl;

    sort(secondNewNumbers.begin(), secondNewNumbers.end());

    std::cout << std::endl << "after sort: ";
    OutPutDeque(secondNewNumbers);
    std::cout << std::endl;

    int c;
    std::cout << "new element: ";
    std::cin >> c;

    auto insert_pos = upper_bound(secondNewNumbers.begin(), secondNewNumbers.end(), c);
    secondNewNumbers.insert(insert_pos, c);

    std::cout << std::endl << "with new element: ";
    OutPutDeque(secondNewNumbers);
    std::cout << std::endl;

    system("pause");
    return 0;
}

void OutPutDeque(std::deque<int> numbers) {
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
}