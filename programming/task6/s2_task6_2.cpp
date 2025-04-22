//Создать двусвязный список, содержащий целые числа. 
//Перенести в начало списка числа, меньшие Х. 

#include <iostream>
struct list {
    int inf;
    list* next;
    list* prev;
};

void push(list*& head, list*& tail, int x) {
    list* r = new list; //новый элемент
    r->inf = x;
    r->next = NULL;
    if (!head && !tail) {
        r->prev = NULL;
        head = r; //это голова       
    }
    else {
        tail->next = r; //r - следующий для хвоста
        r->prev = tail;  //хвост - предыдущий для r      
    }
    tail = r;
}

void print(list* head, list* tail) {
    list* p = head;
    while (p) {
        std::cout << p->inf << " ";
        p = p->next;
    }
}

list* find(list* head, list* tail, int x) {
    list* p = head;//укзатель на голову
    while (p) {
        if (p->inf == x) {
            break;
        }
        p = p->next;
    }
    return p;//возвращаем указатель
}

void insert_after(list*& head, list*& tail, list* r, int x) { //вставка элемента после r
    list* p = new list;
    p->inf = x;
    if (r == tail) { //вставка после хвоста
        p->next = NULL;
        p->prev = r;
        r->next = p;
        tail = p;
    }
    else { //вставляем в середину списка
        r->next->prev = p;//для следующего за r эл-та предыдущий - p
        p->next = r->next;//следующий за p - следующий за r
        p->prev = r;//p вставляем после r
        r->next = p;
    }
}


void del_node(list*& head, list*& tail, list* r) {//удаляем после r
    if (r == head && r == tail) {//единственный элемент списка
        head = tail = NULL;
    }
    else if (r == head) {//удаляем голову списка
        head = head->next;//сдвигаем голову
        head->prev = NULL;
    }
    else if (r == tail) {//удаляем хвост списка
        tail = tail->prev;
        tail->next = NULL;
    }
    else {
        r->next->prev = r->prev; //для следующего от r предыдущим становится r->prev
        r->prev->next = r->next; //для предыдущего от r следующим становится r->next
    }
    delete r; //удаляем r
}

void del_list(list*& head, list*& tail) {
    while (head) {
        list* p = head;
        head = head->next;
        head->prev = NULL;
        delete p;
    }
}

void function(list*& head, list*& tail, int x) {   
    list* newHead = NULL;
    list* newTail = NULL;
    list* oldHead = NULL;
    list* oldTail = NULL;

    list* vremHead = head;
    while (vremHead) {
        list* next = vremHead->next; //сохраняем след

        if (vremHead->inf < x) { //элементы списка, которые меньше x
            push(newHead, newTail, vremHead->inf);
        }
        else {
            // Оставляем элемент в старом списке (для элементов >= X)
            push(oldHead, oldTail, vremHead->inf);
        }
        vremHead = next;
    }

    // Соединяем два списка
    if (newHead) {
        head = newHead;
        if (oldHead) {
            newTail->next = oldHead;
            oldHead->prev = newTail;
            tail = oldTail;
        }
        else {
            tail = newTail;
        }
    }
    else {
        head = oldHead;
        tail = oldTail;
    }
    print(head, tail);
}

int main() {
    list* headList = NULL;
    list* tailList = NULL;
    int n;
    std::cout << "count elements: ";
    std::cin >> n;

    std::cout << "Input elements:";
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        push(headList, tailList, x);
    }
    std::cout << "List: ";
    print(headList, tailList);

    int x;
    std::cout << "\nInput X: ";
    std::cin >> x;

    std::cout << std::endl;

    std::cout << "New list: ";
    function(headList, tailList,x);
    std::cout << std::endl;
   
    return 0;
}