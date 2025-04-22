//Дан список точек в пространстве (например, vector<vector<double>> a,
// где внутренний вектор - это координаты точки в пространстве.).
//  Дана точка  Х в пространстве. Используя библиотеки numeric и functional,
//  найти максимальное расстояние от точки X  до  остальных точек в пространстве.


#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <functional>
#include <algorithm>

//вычисление дистанции
double calculateDistance(const std::vector<double>& point1, const std::vector<double>& point2) {
    double sum = 0.0;
    for (size_t i = 0; i < point1.size(); ++i) {
        sum += std::pow(point1[i] - point2[i], 2);
    }
    return std::sqrt(sum);
}

int main() {
    std::cout << "count tocheck: ";
    int countPoints;
    std::cin >> countPoints;

    //ввод координат, расстояния до которых необходимо найти
    std::vector<std::vector<double>> points;
    std::cout << "Coord tocheck ((x y) or (x y z)): " << std::endl;
    for (int i = 0; i < countPoints; ++i) {
        std::vector<double> point;
        double coordinate;
        while (std::cin >> coordinate) {
            point.push_back(coordinate);
            if (std::cin.peek() == '\n') break;
        }
        points.push_back(point);
    }

    std::vector<double> X;
    std::cout << "Coord X ((x y) or (x y z)): ";
    double coordinate;
    while (std::cin >> coordinate) {
        X.push_back(coordinate);
        if (std::cin.peek() == '\n') break;
    }

    std::vector<double> distances(points.size());

    //transform - чтобы применить ко всем точкам points функцию, вычисояющую расстояние и сохраняем усе в distances 
    std::transform(points.begin(), points.end(), distances.begin(),
        //бинд создает новый объект, котор вызывает calculateDistance и передает в нее точка из points и X
        //std::placeholders::_1, чтобы сказать, что позже в calculateDistance будет передана точка из points, и фиксированная X
        std::bind(calculateDistance, std::placeholders::_1, X));

    //максимальное расстояние
    double maxDistance = *std::max_element(distances.begin(), distances.end());

    //вывод результата
    std::cout << "Max rasst ot X do ost tocheck: " << maxDistance << std::endl;

    return 0;
}
