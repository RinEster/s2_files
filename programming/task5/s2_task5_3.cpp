//Создать очередь из целых чисел. 
//Выполнить циклический сдвиг очереди так, чтобы на первом месте был первый минимальный элемент.
#include <iostream>
struct queue {
    int inf;
    queue *next;
};

void push(queue *&head, queue *&tail, int x) {
    queue *r = new queue; //новый элемент
    r -> inf = x;
    r -> next = NULL;
    if (!head && !tail) {
        head = tail = r; //это и голова и хвост        
    }
    else {
        tail-> next = r; //r - следующий для хвоста
        tail = r; //теперь r - хвост
        
    }
}

int pop(queue *&head, queue *&tail) {
    queue *r = head;
    int i = head-> inf;
    head = head-> next;
    if (!head) {
        tail = NULL;
    }
    delete r;
    return i;
}

void sdvig(queue *&head, queue *&tail) {
    if (!head) {
        std::cout << "Queue is empty";
        return;
    }
    int min = head->inf;
    queue *minNode = head;
    queue *nowHere = head;
    queue *prev = NULL;
    queue *minPrev = NULL;

    while (nowHere) {
        if (nowHere->inf < min) {
            min = nowHere->inf;
            minNode = nowHere;
            minPrev = prev; // Запоминаем предыдущий элемент
        }
        prev = nowHere;
        nowHere = nowHere->next;
    }  
    if (minNode == head) return;
    // Удаляем minNode из текущей позиции
    if (minPrev) {
        minPrev->next = minNode->next; 
    }
    if (minNode == tail) {
        tail = minPrev;
    }

    //minNode в начало
    minNode->next = head;
    head = minNode;
}


int main() {
    queue *head = NULL;     
    queue *tail = NULL;

    int n;
    std::cout << "count elements: ";
    std::cin >> n;

    std::cout << "Input elements:";
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        push(head, tail, x);
    }
    queue* copyHead = head; 
    // переменная copyHead необходима из-за того, 
    // что иначе после первого прохождения очереди при
    //ее выводе head становится NULL и возникает ошибка.
    std::cout << "Queue: ";
    while (copyHead) {
        std::cout << copyHead->inf << " ";
        copyHead = copyHead->next;
    }
    std::cout << std::endl;
    sdvig(head, tail);
    copyHead = head;
    std::cout << "New queue: ";
    while (copyHead) {
        std::cout << copyHead->inf << " ";
        copyHead = copyHead->next;
    }
    std::cout << std::endl;
    while (head) {
        queue *temp = head;
        head = head->next;
        delete temp;
    }
    return 0;
}