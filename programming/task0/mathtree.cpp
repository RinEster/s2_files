//Дано математическое выражение. 
//Построить на его основе дерево по примеру, приведенному в лекциях. 
//Вывести данное выражение в префиксной и постфиксной формах, используя соответствующие обходы. 

#include <iostream>
#include <string>
#include <stack>
#include <iomanip>
#include <windows.h>

HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;

struct tree {
    char inf;
    tree* right;
    tree* left;
    tree* parent;
};

tree* node(int x) {
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = NULL;
    n->parent = NULL;
    return n;
}

//приоритет операторов
int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

tree* createTree(std::string str) {
    std::stack<tree*> nodes;//для операндов
    std::stack<char> ops;//для операторов

    for (unsigned int i = 0; i < str.length(); i++) {
        if (str[i] == ' ') continue; //пропуск пробелов
        //число
        if (isdigit(str[i])) {
            tree* n = node(str[i]);
            nodes.push(n);
        }
        else if (str[i] == '(') {
            ops.push(str[i]);
        }
        else if (str[i] == ')') {
            //для формирования поддерева извлекаем до открывающей скобки
            while (!ops.empty() && ops.top() != '(') {
                tree* v = node(ops.top());
                ops.pop();
                //верхний узел - правый ребенок
                v->right = nodes.top();
                nodes.top()->parent = v;
                nodes.pop();
                //следующий после верхнего узел - левый ребенок
                v->left = nodes.top();
                nodes.top()->parent = v;
                nodes.pop();
                //поддерево в стек
                nodes.push(v);
            }
            ops.pop();
        }
        else {            
            //для других операторов
            while (!ops.empty() && priority(ops.top()) >= priority(str[i])) {
                tree* v = node(ops.top());
                ops.pop();

                v->right = nodes.top();
                nodes.top()->parent = v;
                nodes.pop();

                v->left = nodes.top();
                nodes.top()->parent = v;
                nodes.pop();

                nodes.push(v);
            }
            ops.push(str[i]);
        }
    }
    //дособираем дерево
    while (!ops.empty()) {
        tree* v = node(ops.top());
        ops.pop();

        v->right = nodes.top();
        nodes.top()->parent = v;
        nodes.pop();

        v->left = nodes.top();
        nodes.top()->parent = v;
        nodes.pop();

        nodes.push(v);
    }
    if (nodes.empty()) {
        return NULL;
    }
    else {
        return nodes.top();
    }
}

void max_height(tree* x, short& max, short deepness = 1) {
    if (!x) return;
    if (deepness > max) max = deepness;
    if (x->left) max_height(x->left, max, deepness + 1);
    if (x->right) max_height(x->right, max, deepness + 1);
}

void print_helper(tree* x, const COORD pos, const short offset) {
    SetConsoleTextAttribute(outp, 7); // Default color (white)
    SetConsoleCursorPosition(outp, pos);
    std::cout << std::setw(offset + 1) << x->inf;
    if (x->left) print_helper(x->left, { pos.X, short(pos.Y + 1) }, offset >> 1);
    if (x->right) print_helper(x->right, { short(pos.X + offset), short(pos.Y + 1) }, offset >> 1);
}

void print_tree(tree* root) {
    if (root) {
        short max = 1;
        max_height(root, max);
        short width = 1 << max + 1, max_w = 128;
        if (width > max_w) width = max_w;
        for (short i = 0; i < max; ++i) std::cout << '\n';
        GetConsoleScreenBufferInfo(outp, &csbInfo);
        COORD endPos = csbInfo.dwCursorPosition;
        print_helper(root, { 0, short(endPos.Y - max) }, width >> 1);
        SetConsoleCursorPosition(outp, endPos);
        SetConsoleTextAttribute(outp, 7);
    }
}

//прямой обход (К-Л-П)
void prefix(tree* tr) {
    if (tr) {
        std::cout << tr->inf << " ";
        prefix(tr->left);
        prefix(tr->right);
    }
}

//обратный обход (Л-П-К)
void postfix(tree* tr) {
    if (tr) {
        postfix(tr->left);
        postfix(tr->right);
        std::cout << tr->inf << " ";
    }
}

int main() {
    std::string str;
    std::cout << "Enter expression: ";
    getline(std::cin, str);

    //корректность символов
    std::string znak = "+-/*0123456789() ";
    bool flag = true;
    for (unsigned int i = 0; i < str.length(); i++) {
        if (znak.find(str[i]) == std::string::npos) {
            flag = false;
            break;
        }
    }

    if (!flag) {
        std::cout << "Error\n";
    }
    else {
        tree* tr = createTree(str);
        if (!tr) {
            std::cout << "Error\n";
            return 1;
        }
        //структура дерева
        std::cout << "\nTree structure:\n";
        print_tree(tr);
        //префиксная запись
        std::cout << "\n\nPrefix: ";
        prefix(tr);
        //постфиксная запись
        std::cout << "\nPostfix: ";
        postfix(tr);        
    }

    return 0;
}