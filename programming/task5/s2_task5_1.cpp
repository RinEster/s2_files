//Создать очередь, содержащую целые числа. 
//После всех чисел, равных последнему числу, вставить максимальный элемент. 
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

void insertLastAfterMax(queue *&head, queue *&tail) {
    if (!head) {
        std::cout << "Queue is empty";
        return;
    }
    int last = tail->inf;
    //нахождение максимального элемента
    int max = head->inf;
    queue *hereNow = head->next;
    while (hereNow) {
        if (hereNow->inf > max) {
            max = hereNow->inf;
        }
        hereNow = hereNow->next;
    }
    //создание временной очереди, чтобы добавить новый элемент, равный максимальному,
    //после элемента равного последнему
    queue *vremHead = NULL;
    queue *vremTail = NULL;
    while (head) {
        int newElem = pop(head, tail);
        push(vremHead, vremTail, newElem);

        if (newElem == last) {
            push(vremHead, vremTail, max);
        }
    }

    while (vremHead) {
        int el = pop(vremHead, vremTail);
        push(head, tail, el);
    }
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

    insertLastAfterMax(head, tail);
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