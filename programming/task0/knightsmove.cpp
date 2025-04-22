//Дана шахматная доска. Вывести кратчайший путь конем от клетки А до клетки В.
//Должны быть введены две клетки в виде, например, А2 и Е6. 
//Путь должен быть выведен в виде списка клеток А2 В4 С6 D8 E6
#include <iostream>
#include <cctype>
#include <vector>
#include <string>
struct Cell {
    int x, y;
    int prev; //индекс предыдущей ячейки
};

struct queue {
    int inf;
    queue* next;
};

void push(queue*& head, queue*& tail, int x) {
    queue* r = new queue;
    r->inf = x;
    r->next = NULL;
    if (!head && !tail) {
        head = tail = r;         
    }
    else {
        tail->next = r; 
        tail = r; 
    }
}

int pop(queue*& head, queue*& tail) {
    queue* r = head;
    int i = head->inf;
    head = head->next;
    if (!head) {
        tail = NULL;
    }
    delete r;
    return i;
}

// преобразование букв в цифры
int letterToNumber(char a) {
    int aInt;
    a = toupper(a);
    if (a >= 'A' && a <= 'H') {
        aInt = a - 'A' + 1;
    }
    else {
        std::cout << "Error! Letter must be in the range from A to H.";
        return 1;
    }
    return aInt;
}

//преобразование цифр в букв
char numberToLetter(int aInt) {
    return 'A' + aInt - 1;
}

//находится ли клетка в пределах доски
bool cellInChess(int x, int y) {
    return x >= 1 && x <= 8 && y >= 1 && y <= 8;
}

//восстановление пути
void reconstructPath(Cell* cells, int value, std::vector<std::string>& path) {
    if (cells[value].prev != -1) { //если не конечная
        reconstructPath(cells, cells[value].prev, path);
    }

    std::string cellStr;
    cellStr += numberToLetter(cells[value].x);
    cellStr += std::to_string(cells[value].y);

    path.push_back(cellStr);
}

int main() {
    std::cout << "Enter coordinates: (A2 H4):";
    std::string start, end;
    std::cin >> start >> end;
    int startX, startY, endX, endY;
    //преобразование букв в цифры для координат
    startX = letterToNumber(start[0]);
    endX = letterToNumber(end[0]);
    startY = start[1] - '0';
    endY = end[1] - '0';
    //ошибка ввода 
    if (startY < 1 || startY > 8 || endY < 1 || endY > 8) {
        std::cout << "Error! Number must be in the range from 1 to 8.";
        return 1;
    }

    //посещенные
    bool visited[9][9] = {false};

    //возможные ходы конем
    int knightMoves[8][2] = {
        {2,1}, {2,-1}, {-2,-1}, {-2,1}, {-1, -2}, {1,-2}, {1, 2}, {-1,2}
    };

    Cell cells[65];
    int cellCount = 0;
   
    queue* head = NULL;
    queue *tail = NULL;

    //добавление стартовой клетки
    cells[cellCount] = {startX, startY, -1};
    push(head, tail, cellCount); //добавление в очередь
    visited[startX][startY] = true;
    cellCount++;
    bool found = false; //достигнута конечная клетка
    int endIndex = -1;

    //обход в ширину
    while (head && !found) {
        int value = pop(head, tail);
        int x = cells[value].x;
        int y = cells[value].y;

        // Проверяем все возможные ходы
        for (int i = 0; i < 8; i++) {
            int newX = x + knightMoves[i][0];
            int newY = y + knightMoves[i][1];

            //клетка в пределах доски и не посещена
            if (cellInChess(newX, newY) && !visited[newX][newY]) {
                visited[newX][newY] = true;
                cells[cellCount] = { newX, newY, value };

                //достигнута конечная клетка
                if (newX == endX && newY == endY) {
                    endIndex = cellCount;
                    found = true;
                    break;
                }

                push(head, tail, cellCount);
                cellCount++;
            }
        }
    }

    //восстановление пути
    std::vector<std::string> path;
    reconstructPath(cells, endIndex, path);

    // Вывод пути
    for (const auto& cell : path) {
        std::cout << cell << " ";
    }
    std::cout << std::endl;

    return 0;
}