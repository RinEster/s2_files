//Граф представлен в виде списка смежности. 
//Реализовать обход в ширину, используя очередь, и нерекурсивный обход в глубину.

#include <iostream>
struct queue {
    int inf;
    queue* next;
};
struct stack {
    int inf;
    stack* next;
};


void pushQueue(queue*& head, queue*& tail, int x) {
    queue* r = new queue; //новый элемент
    r->inf = x;
    r->next = NULL;
    if (!head && !tail) {
        head = tail = r; //это и голова и хвост        
    }
    else {
        tail->next = r; //r - следующий для хвоста
        tail = r; //теперь r - хвост

    }
}

int popQueue(queue*& head, queue*& tail) {
    queue* r = head;
    int i = head->inf;
    head = head->next;
    if (!head) {
        tail = NULL;
    }
    delete r;
    return i;
}

void pushStack(stack*& head, int x) {
    stack* r = new stack;
    r->inf = x;
    r->next = head; //следующий элемент head
    head = r; //r - голова
}

int popStack(stack*& head) {
    int i = head->inf;
    stack* r = head;
    head = head->next;
    delete r;
    return i;
}

void reverseStack(stack*& head) {
    stack* head1 = NULL;
    while (head) {
        pushStack(head1, popStack(head));
    }
    head = head1;
}

int main() {
    int countVertex, countEdge; // количество вершин и ребер
    
    //ввод данных
    std::cout << "Enter the number of vertices: ";
    std::cin >> countVertex;
    std::cout << "Enter the number of edges: ";
    std::cin >> countEdge;

    //обработка ошибки, если ребра есть, а вершин нет
    if (countVertex == 0 && countEdge != 0) {
        std::cout << "Error! The number of vertices is zero, but the number of edges is not zero!";
        return 1;
    }

    //для каждой из вершин храним голову и хвост списка смежности
    queue** vertexHeads = new queue * [countVertex];
    queue** vertexTails = new queue * [countVertex];

    for (int i = 0; i < countVertex; i++) {
        vertexHeads[i] = NULL;
        vertexTails[i] = NULL;
    }

    //ввод ребер
    std::cout << "Enter edges (a b): ";
    for (int i = 0; i < countEdge; i++) {
        int a, b;
        std::cin >> a >> b;

        //граф неориентированный, из a есть путь в b, и из b есть путь в a  
        pushQueue(vertexHeads[a], vertexTails[a], b);
        pushQueue(vertexHeads[b], vertexTails[b], a);
    }

    //вывод списка смежности
    for (int i = 0; i < countVertex; i++, std::cout << std::endl) {
        std::cout << "Vertex " << i << ": ";
        queue* value = vertexHeads[i];
        while (value) {
            std::cout << value->inf << " ";
            value = value->next;
        }
    }

    //обход графа в ширинуну
    queue* head = NULL;
    queue* tail = NULL;

    //массив для отслеживания посещенных вершин
    bool* visited = new bool[countVertex];
    for (int i = 0; i < countVertex; i++) {
        visited[i] = false;
    }

    //переменная startVertex на случай, если вершина 0 изолирована. ищем неизолированную вершину
    int startVertex = 0;  
    if (vertexHeads[startVertex] == NULL) {
        for (int i = 0; i < countVertex; ++i) {
            if (vertexHeads[i] != NULL) {
                startVertex = i;
                break;
            }
        }
    }
    pushQueue(head, tail, startVertex);
    visited[startVertex] = true;

    std::cout << "Breadth First Search Result: ";
    while (head) {
        int v = popQueue(head, tail);
        std::cout << v << " ";

        queue* value = vertexHeads[v];
        while (value) {
            if (!visited[value->inf]) {
                pushQueue(head, tail, value->inf);
                visited[value->inf] = true;
            }
            value = value->next;
        }
    }
    std::cout << std::endl;
    delete[] visited;

   //нерекурсивный обход в глубину.

    stack* stackDFS = NULL;
    bool* visitedStack = new bool[countVertex];
    for (int i = 0; i < countVertex; i++) {
        visitedStack[i] = false;
    }

    //начало с той же стартовой вершины, что и при обходе в ширину
    int startVertexDFS = startVertex;
    pushStack(stackDFS, startVertexDFS);

    std::cout << "Depth First Search Result: ";
    while (stackDFS) {
        int v = popStack(stackDFS);
        if (!visitedStack[v]) {
            std::cout << v << " ";
            visitedStack[v] = true;

            stack* values = NULL;
            queue* temp = vertexHeads[v];
            while (temp) {
                pushStack(values, temp->inf);
                temp = temp->next;
            }
            reverseStack(values);
                        
            while (values) {
                int value = popStack(values);
                if (!visitedStack[value]) {
                    pushStack(stackDFS, value);
                }
            }
        }
    }
    std::cout << std::endl;
    delete[] visitedStack;

    //очищаем
    for (int i = 0; i < countVertex; i++) {
        queue* current = vertexHeads[i];
        while (current) {
            queue* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] vertexHeads;
    delete[] vertexTails;
    return 0;
}