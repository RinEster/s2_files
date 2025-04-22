//Создать стек, содержащий целые числа. 
//Перед  всеми минимальными числами вставить максимальное число. 
//Порядок следования в результате должен совпадать с порядком следования ввода. 
#include <iostream>

struct stack {
	int inf;
	stack* next;
};

void push(stack*& head, int x) {
	stack* r = new stack;
	r->inf = x;
	r->next = head; //следующий элемент head
	head = r; //r - голова
}

int pop(stack*& head) {
	int i = head->inf;
	stack* r = head;
	head = head->next;
	delete r;
	return i;
}
void reverse(stack*& head) {
	stack* head1 = NULL;
	while (head) {
		push(head1, pop(head));
	}
	head = head1;
}
void maxMin(stack*& head) {
	if (!head) {
		std::cout << "Stack is empty";
		return;
	}

	int min = head->inf;
	int max = head->inf;
	stack* hereNow = head; //временный стек
	while (hereNow) {
		if (hereNow->inf > max) {
			max = hereNow->inf;
		}
		if (hereNow->inf < min) {
			min = hereNow->inf;
		}
		hereNow = hereNow->next;
	}
	reverse(head);
	stack* vremHead = NULL;
	while (head) {
		int newElem = pop(head);
		push(vremHead, newElem);

		if (newElem == min) {
			push(vremHead, max);
		}

	}
	while (vremHead) {
		int el = pop(vremHead);
		push(head, el);
	}
}

int main() {
	stack* head = NULL;
	int n;
	std::cout << "Count elem: ";
	std::cin >> n;
	std::cout << "Input: ";
	for (int i = 0; i < n; i++) {
		int x;
		std::cin >> x;
		push(head, x);
	}
	reverse(head);
	stack* copyHead = head;
	//исходный стек
	std::cout << "Stack: ";
	while (copyHead) {
		std::cout << copyHead->inf << " ";
		copyHead = copyHead->next;
	}
	std::cout << std::endl;

	maxMin(head);
	reverse(head);
	copyHead = head;
	//новый стек
	std::cout << "New stack: ";
	while (copyHead) {
		std::cout << copyHead->inf << " ";
		copyHead = copyHead->next;
	}
	std::cout << std::endl;

	while (head) {
		stack* temp = head;
		head = head->next;
		delete temp;
	}
}

