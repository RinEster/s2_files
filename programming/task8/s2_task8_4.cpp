//Дан неориентированный граф. Выяснить, является ли граф связным.
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

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
//в глубину
bool isConnected(std::vector<std::vector<int>>& graph) {
    if (graph.empty()) return true; 

    int n = graph.size();
    std::vector<bool> visited(n, false);
    std::stack<int> s;

    s.push(0);
    visited[0] = true;

    int visitedCount = 0;

    while (!s.empty()) {
        int value = s.top();
        s.pop();
        visitedCount++;
        for (int neighbor : graph[value]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                s.push(neighbor);
            }
        }
    }

    return visitedCount == n;
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

    if (isConnected(graph)) {
        std::cout << "The graph is connected\n";
    }
    else {
        std::cout << "The graph is not connected\n";
    }

    return 0;
}