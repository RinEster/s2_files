//Дан неориентированный граф. Вывести количество вершин, смежных с данной.
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int N, M; // N - количество вершин; M - количество ребер;

    std::cout << "Enter the number of vertices: ";
    std::cin >> N;
    std::cout << "Enter the number of edges: ";
    std::cin >> M;

    if (N == 0 && M != 0) {
        std::cout << "Error! The number of vertices is zero, but the number of edges is not.";
        return 1;
    }

    std::vector<std::vector<int>> graph(N);
    std::cout << "Enter x y:\n";
    for (int i = 0; i < M; i++) {
        int x, y;
        std::cin >> x >> y;

        if (x >= N || y >= N || x < 0 || y < 0) {
            std::cout << "Invalid edge!\n";
            continue;
        }

        //так как граф неориентированный, добавляем в обе стороны
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    //удаление дубликатов
    for (auto& edges : graph) {
        std::sort(edges.begin(), edges.end());
        edges.erase(std::unique(edges.begin(), edges.end()), edges.end());
    }

    //ввод вершины, количество смежных вершин которой, необходимо вывести
    std::cout << "Enter vertex X: ";
    int X;
    std::cin >> X;

    // Проверка на допустимость вершины X
    if (X >= N || X < 0) {
        std::cout << "Invalid vertex number!\n";
        return 1;
    }

    std::cout << "Number of vertices adjacent to " << X << ": " << graph[X].size() << "\n";

    return 0;
}