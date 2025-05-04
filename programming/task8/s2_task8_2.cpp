//Дан неориентированный граф. Удалить ребро, соединяющее вершины А и B.
#include <iostream>
#include <vector>
#include <algorithm>

//вывод списка смежности
void adjacencyList(std::vector<std::vector<int>> graph, int N) {
    std::cout << "\nAdjacency list:\n";
    for (int i = 0; i < N; i++) {
        std::cout << "Vertex " << i << ": ";
        for (int neighbor : graph[i]) {
            std::cout << neighbor << " ";
        }
        std::cout << "\n";
    }
}


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

    adjacencyList(graph, N);

    //ввод вершин, ребро между которыми необходимо удалить
    std::cout << "Enter vertex A: ";
    int A;
    std::cin >> A;
    std::cout << "Enter vertex B: ";
    int B;
    std::cin >> B;
    // Проверка на допустимость вершин
    if (A >= N || A < 0 || B >= N || B < 0) {
        std::cout << "Invalid vertex number!\n";
        return 1;
    }

    bool edgeExists = false;
    if (std::find(graph[A].begin(), graph[A].end(), B) != graph[A].end()) {
        edgeExists = true;
    }

    if (!edgeExists) {
        std::cout << "Error\n";
        return 1;
    }

    //нахождение и удаление В в А
    auto it = std::find(graph[A].begin(), graph[A].end(), B);
    graph[A].erase(it);



    //нахождение и удаление А в В
    it = std::find(graph[B].begin(), graph[B].end(), A);
    graph[B].erase(it);

    adjacencyList(graph, N);

    return 0;
}