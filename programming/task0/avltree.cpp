//Выполнить любую из задач задания, используя AVL дерево
//Дано дерево. Подсчитать сумму листьев.
//Дано дерево. Удалить элементы, кратные 𝑋.
#include <iostream>
#include <stack>
#include <vector>
#include <iomanip>
#include <windows.h>

HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;

// структура для представления узлов дерева
struct tree {
    int key;
    unsigned char height;
    tree* left;
    tree* right;
    tree(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

unsigned char height(tree* p) {
    return p ? p->height : 0;
}

//вычисление баланс фактора узла
int bfactor(tree* p) {
    return height(p->right) - height(p->left);
}

//восстановление корректного значения высоты узла
void fixheight(tree* p) {
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

// правый поворот вокруг p
tree* rotateright(tree* p) {
    tree* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}


// левый поворот вокруг q
tree* rotateleft(tree* q) {
    tree* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

//балансировка
tree* balance(tree* p) {
    fixheight(p);
    if (bfactor(p) == 2) {
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2) {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;
}


tree* insert(tree* p, int k) {
    if (!p) return new tree(k);
    if (k < p->key)
        p->left = insert(p->left, k);
    else if (k > p->key)
        p->right = insert(p->right, k);
    return balance(p);
}

// поиск узла с минимальным значением в дереве p 
tree* findmin(tree* p) {
    return p->left ? findmin(p->left) : p;
}

// удаление узла с минимальным знач из дерева p
tree* removemin(tree* p) {
    if (!p->left) return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

//удаление
tree* remove(tree* p, int k) {
    if (!p) return nullptr;
    if (k < p->key)
        p->left = remove(p->left, k);
    else if (k > p->key)
        p->right = remove(p->right, k);
    else {
        tree* q = p->left;
        tree* r = p->right;
        delete p;
        if (!r) return q;
        tree* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
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
    std::cout << std::setw(offset + 1) << x->key;
    if (x->left) print_helper(x->left, { pos.X, short(pos.Y + 1) }, offset >> 1);
    if (x->right) print_helper(x->right, { short(pos.X + offset), short(pos.Y + 1) }, offset >> 1);
}

void print_tree(tree* root) {
    if (root) {
        short max = 1;
        max_height(root, max);
        short width = 1 << (max + 1), max_w = 128;
        if (width > max_w) width = max_w;
        for (short i = 0; i < max; ++i) std::cout << '\n';
        GetConsoleScreenBufferInfo(outp, &csbInfo);
        COORD endPos = csbInfo.dwCursorPosition;
        print_helper(root, { 0, short(endPos.Y - max) }, width >> 1);
        SetConsoleCursorPosition(outp, endPos);
        SetConsoleTextAttribute(outp, 7);
    }
}

//сумма листьев
int sumOfLeaves(tree* tr) {
    if (!tr) return 0;
    if (!tr->left && !tr->right)
        return tr->key;
    return sumOfLeaves(tr->left) + sumOfLeaves(tr->right);
}


void deleteTree(tree* p) {
    if (p) {
        deleteTree(p->left);
        deleteTree(p->right);
        delete p;
    }
}

//удаление элменетов, кратных Х
void removeMultiples(tree*& tr, int X) {
    if (!tr || X == 0) return;
    std::vector<int> toRemove;//для элементов, которые надо удалить
    std::stack<tree*> s; //для обхода
    tree* v = tr;

    //обход дерева
    while (v || !s.empty()) {
        while (v) {
            s.push(v);
            v = v->left;
        }
        v = s.top();
        s.pop();
        if (v->key % X == 0) { //кратен X
            toRemove.push_back(v->key);
        }
        v = v->right;
    }
    //удаление
    for (int v : toRemove) {
        tr = remove(tr, v);
    }        
}

int main() {
    tree* tr = NULL;
    int n;
    std::cout << "n = ";
    std::cin >> n;

    std::cout << "Enter numbers: ";
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        tr = insert(tr, x);
    }
   
    std::cout << "\ntree:\n";
    print_tree(tr);
    std::cout << std::endl;

    std::cout << "\nSum of leaves: " << sumOfLeaves(tr) << std::endl;

    int X;
    std::cout << "\nRemove multiples of X = ";
    std::cin >> X;
    removeMultiples(tr, X);

    std::cout << "\ntree:\n";
    print_tree(tr);
    std::cout << std::endl;

    deleteTree(tr);
    return 0;
}