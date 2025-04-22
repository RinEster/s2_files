//Создать стек, содержащий буквы латинского алфавита. 
//В новый стек после первой гласной буквы (первой, введенной из файла или с клавиатуры) 
//вставить вопросительный знак. 
//Порядок следования букв в новом стеке должен совпадать с первоначальным. 
#include <iostream>
#include <string>
struct stack {
	char inf;
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
void vopros(stack*& head) {
	if (!head) {
		std::cout << "Stack is empty";
		return;
	}

	stack* newHead = NULL;
	bool foundG = false;
	std::string g = "aeiouyAEIOUY"; // Строка с гласными

	while (head) {
		char currentChar = pop(head);
		push(newHead, currentChar);

		//символ-гласная
		if (!foundG && g.find(currentChar) != std::string::npos) {
			foundG = true;
			push(newHead, '?'); // вставка ?
		}
	}
	
	reverse(newHead);
	head = newHead; 
}

int main() {
	stack* head = NULL;
	int n;
	std::cout << "Count elem: ";
	std::cin >> n;
	std::cout << "Input: ";
	for (int i = 0; i < n; i++) {
		char x;
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
	vopros(head);	
	
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

