//Дан ориентированный граф. Вывести все истоки графа.
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

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

// обход в ширину
bool isSource(std::vector<std::vector<int>>& graph, int start) {
    int n = graph.size();
    std::vector<bool> visited(n, false);
    std::queue<int> q;

    q.push(start);
    visited[start] = true;
    int visitedCount = 1; 

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                visitedCount++;
                q.push(neighbor);
            }
        }
    }

    return (visitedCount == n); 
}

int main() {
    int N, M; // N - количество вершин; M - количество ребер;

    std::cout << "Enter the number of vertices: ";
    std::cin >> N;
    std::cout << "Enter the number of edges: ";
    std::cin >> M;

    if (N == 0 && M == 0) {
        std::cout << "Error! The number of vertices is zero and the number of edges is zero.";
        return 1;
    }


    if (N == 0 && M != 0) {
        std::cout << "Error! The number of vertices is zero, but the number of edges is not.";
        return 1;
    }

    std::vector<std::vector<int>> graph(N);
    std::vector<int> inDegree(N, 0);
    std::cout << "Enter x y:\n";
    for (int i = 0; i < M; i++) {
        int x, y;
        std::cin >> x >> y;

        if (x >= N || y >= N || x < 0 || y < 0) {
            std::cout << "Invalid edge!\n";
            continue;
        }

        graph[x].push_back(y); inDegree[y]++;
    }

    //удаление дубликатов
    for (auto& edges : graph) {
        std::sort(edges.begin(), edges.end());
        edges.erase(std::unique(edges.begin(), edges.end()), edges.end());
    }

    adjacencyList(graph, N);
    std::cout << "Source:\n";
    bool hasSources = false;
    for (int i = 0; i < N; i++) {
        if (isSource(graph, i)) {
            hasSources = true;
            std::cout << i << " ";
        }
    }

    if (!hasSources) {
        std::cout << "There are no sources";
    }

    return 0;
}