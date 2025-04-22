#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

struct stack {
    double inf;
    stack* next;
};

void push(stack*& h, double x) {
    stack* r = new stack; // создаем новый элемент
    r->inf = x; 
    r->next = h; 
    h = r; // теперь r является головой
}

double pop(stack*& h) {
    double i = h->inf; // значение первого элемента
    stack* r = h; // указатель на голову стека
    h = h->next; // переносим указатель на следующий элемент
    delete r;
    return i; 
}

//проверка является ли оператором
bool isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

//вычисление математического выражения, записанного в префиксной форме
double prefix(const std::string& expr, const int& l) {
    stack* st = NULL; 
    std::istringstream iss(expr);
    std::string mathv;

    // Считываем выражение и обрабатываем его
    std::string* mathvs = new std::string[l];
    int count = 0;

    while (iss >> mathv) {
        mathvs[count++] = mathv;
    }

    for (int i = count - 1; i >= 0; --i) {
        mathv = mathvs[i];

        if (isOperator(mathv)) {
            // извлекаем два верхних элемента
            double a = pop(st);
            double b = pop(st);
            if (mathv == "+") {
                push(st, a + b);
            }
            else if (mathv == "-") {
                push(st, a - b);
            }
            else if (mathv == "*") {
                push(st, a * b);
            }
            else if (mathv == "/") {
                push(st, a / b);
            }
        }
        else {
            push(st, std::stod(mathv)); // преобразуем строку в число и помещаем в стек
        }
    }

    return pop(st);
}

int main() {
    std::string inputStr;
    std::cout << "pref: ";
    std::getline(std::cin, inputStr);
    int count = inputStr.length();

    double result = prefix(inputStr, count);
    std::cout << "res: " << result << std::endl;

    return 0;
}