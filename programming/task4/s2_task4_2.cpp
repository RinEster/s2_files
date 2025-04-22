#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

//слияние двух отсортированных массивов
void merge(std::vector<int>& arr, int left, int m, int right) {
    //проверка границ
    if (left > right || m < left || m > right) {
        throw std::runtime_error("boundary error");
    }
    //дополнительный массив buf
    std::vector<int> buf(right - left + 1);
    int cur = 0; //индекс для buf
    int i = left; //yказатель для первого подмассива
    int j = m + 1; //yказатель для второго подмассива

    //слиянике
    while (cur < buf.size()) {
        if (i > m) {
            while (j <= right) {
                buf[cur++] = arr[j++];//дописываем оставшиеся элементы от j до r
            }
            break;
        }
        else if (j > right) {
            while (i <= m) {
                buf[cur++] = arr[i++];//дописываем оставшиеся элементы от i до m
            }
            break; // Выходим из цикла
        }
        else if (arr[i] <= arr[j]) {
            buf[cur++] = arr[i++];
        }
        else {
            buf[cur++] = arr[j++];
        }
    }
    //запись отсортированного массива buf в arr
    for (int k = 0; k < buf.size(); k++) {
        arr[left + k] = buf[k];
    }
}

//функция сортировки слиянием
void mergeSort(std::vector<int>& a, int left, int right) {
    if (left < right) {
        int m = (right + left) / 2;
        mergeSort(a, left, m);
        mergeSort(a, m + 1, right);
        merge(a, left, m, right);
    }
}

//функция для сортировки матрицы
void sortMatrix(std::vector<std::vector<int>>& matrix) {
    for (size_t i = 0; i < matrix.size(); i++) {
        if ((i + 1) % 3 == 0) {
            //сортировка каждоой третьей строки по убыванию
            mergeSort(matrix[i], 0, matrix[i].size() - 1);
            std::reverse(matrix[i].begin(), matrix[i].end());
        }
        else {
            //остальные строки по возрастанию
            mergeSort(matrix[i], 0, matrix[i].size() - 1);
        }
    }
}

//считывание матрицы из файла
std::vector<std::vector<int>> inputMatrix(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::vector<int>> matrix;
    std::string line;
    try {
        if (!file.is_open()) {
            throw std::runtime_error("Open error");
        }        
        //считывание строк из файоа
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::vector<int> row; //вектор для значений строк
            int value;
            //считывание значний
            while (ss >> value) {
                row.push_back(value);
            }
            //если счтрока не пустачя, добавляем ее в матрицу
            if (!row.empty()) {
                matrix.push_back(row);
            }
        }
        file.close();

        //проверка, является ли матрица квадратной
        int n = matrix.size();
        for (const auto& row : matrix) {
            if (row.size() != n) {
                throw std::runtime_error( "matrix is not square");
            }
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return {};
    }  
    return matrix;
}

//запись матрицы в файл
void writeMatrix(const std::vector<std::vector<int>>& matrix, const std::string& filename) {
    try{
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Open error");
        }
        int n = matrix.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                file << matrix[i][j] << " ";
            }
            file << std::endl;
        }
        file.close();
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

int main() {
    std::string inputFilename = "D:\\array.txt";
    std::string outputFilename = "D:\\output.txt";

    //считывание матрицы
    std::vector<std::vector<int>> matrix = inputMatrix(inputFilename);

    //сортировка матрицы
    sortMatrix(matrix);

    //запись матрицы в файд
    writeMatrix(matrix, outputFilename);

    return 0;
}