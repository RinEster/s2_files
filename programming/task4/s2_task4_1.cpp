#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

//быстрая сортировка "разделяй и властвуй"
void quickSort(std::vector<int>& arr, int left, int right) {
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            int t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
            i++;
            j--;
        }
    }
    if (left < j) quickSort(arr, left, j);
    if (i < right) quickSort(arr, i, right);
}
//сортировка столбцов
void sortColumns(std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    for (int j = 0; j < n; j++) {
        std::vector<int> column(n);
        for (int i = 0; i < n; i++) {
            column[i] = matrix[i][j];
        }
        quickSort(column, 0, n - 1);
        for (int i = 0; i < n; i++) {
            matrix[i][j] = column[i];
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
    sortColumns(matrix);

    //запись матрицы в файд
    writeMatrix(matrix, outputFilename);

    return 0;
}