#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>

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
                throw std::runtime_error("matrix is not square");
            }
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return {};
    }
    return matrix;
}

void writeMatrix(std::vector<std::vector<int>>& matrix, const std::string& filename) {
    try {
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

void insertionSort(std::vector<int>& a) {
    int n = a.size();
    for (int i = 1; i < n; i++) {
        int j = i;
        while (j > 0 && a[j] < a[j - 1]) {
            std::swap(a[j], a[j - 1]);
            j--;
        }
    }
}

void extractNadDiagonal(std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    for (int col = 0; col < n; col++) { //проходим по столбцам
        std::vector<int> diagonal;
        int startCol = col, startRow = 0;
        while (startCol >= 0 && startRow < n) {
            diagonal.push_back(matrix[startRow][startCol]);
            startCol--;
            startRow++;
        }
        insertionSort(diagonal);
        startCol = col; startRow = 0;
        int idx = 0;
        while (startCol >= 0 && startRow < n) {
            matrix[startRow][startCol] = diagonal[idx++];
            startCol--;
            startRow++;
        }
    }
}

void extractPodDiagonal(std::vector<std::vector<int>>&matrix) {
    int n = matrix.size();
    for (int row = 1; row < n; row++) {
        std::vector<int> diagonal;
        int startCol = n - 1, startRow = row;
        while (startRow < n && startCol >= 0) {
            diagonal.push_back(matrix[startRow][startCol]);
            startCol--;
            startRow++;
        }
        insertionSort(diagonal);
        startCol = n - 1; startRow = row;
        int idx = 0;
        while (startRow < n && startCol >= 0) {
            matrix[startRow][startCol] = diagonal[idx++];
            startCol--;
            startRow++;
        }
    }
}

int main() {
    std::string inputFilename = "D:\\array.txt";
    std::string outputFilename = "D:\\output.txt";

    try {
        std::vector<std::vector<int>> matrix = inputMatrix(inputFilename);
        extractNadDiagonal(matrix);
        extractPodDiagonal(matrix);
        writeMatrix(matrix, outputFilename);
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what();
        return 1;
    }

    return 0;
}