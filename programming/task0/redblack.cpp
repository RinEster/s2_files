//Выполнить любое задание для красно-черного дерева. 
//Написать функции для создания дерева, удаления элемента, вставки нового элемента, симметричного обхода.
//15. Дано дерево. Вывести все листья.
//7
//10 5 15 3 7 12 17

#include <iostream>
#include <cmath>
#include <queue>
#include <vector>
#include <windows.h>
#include <iomanip>
#define RED 'r'
#define BLACK 'b'

HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;

struct tree {
    int inf;
    tree* right;
    tree* left;
    tree* parent;
    char color;
};

//левый поворот
void left_rotate(tree*& tr, tree* x) {
    tree* y = x->right;
    x->right = y->left;
    if (y->left) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent->left == x) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    if (!y->parent) {
        tr = y;
        y->color = 'b';
    }
}

//правый поворот
void right_rotate(tree*& tr, tree* x) {
    tree* y = x->left;
    x->left = y->right;
    if (y->right) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent->left == x) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
    if (!y->parent) {
        tr = y;
        y->color = 'b';
    }
}

//функция, создающая узел
tree* node(tree* prev, int X) {
    tree* n = new tree;
    n->inf = X;
    n->left = n->right = nullptr;
    n->parent = prev;
    n->color = 'r';
    return n;
}

//функция, создающая корень
tree* root(int X) {
    tree* n = new tree;
    n->inf = X;
    n->left = n->right = nullptr;
    n->parent = nullptr;
    n->color = 'b';
    return n;
}


tree* grandfather(tree* X) {
    if (X && X->parent) {
        return X->parent->parent;
    }
    else {
        return nullptr;
    }
}

tree* uncle(tree* X) {
    tree* g = grandfather(X);
    if (!g) {
        return nullptr;
    }
    if (X->parent == g->left) {
        return g->right;
    }
    else {
        return g->left;
    }
}

tree* brother(tree* X) {
    if (X && X->parent) {
        if (X == X->parent->left) {
            return X->parent->right;
        }
        else {
            return X->parent->left;
        }
    }
    else {
        return nullptr;
    }
}

//вставка нового элемента в дерево
void insert_case_1(tree*& tr, tree* X);
void insert_case_2(tree*& tr, tree* X);
void insert_case_3(tree*& tr, tree* X);
void insert_case_4(tree*& tr, tree* X);
void insert_case_5(tree*& tr, tree* X);

void insert_case_1(tree*& tr, tree* X) {
    if (!X->parent) {
        X->color = 'b';
    }
    else {
        insert_case_2(tr, X);
    }
}

void insert_case_2(tree*& tr, tree* X) {
    if (X->parent->color == 'r') {
        insert_case_3(tr, X);
    }
}

void insert_case_3(tree*& tr, tree* X) {
    tree* g = grandfather(X);
    tree* u = uncle(X);
    if (u && u->color == 'r' && X->parent->color == 'r') {
        X->parent->color = 'b';
        u->color = 'b';
        g->color = 'r';
        insert_case_1(tr, g);
    }
    else {
        insert_case_4(tr, X);
    }
}

void insert_case_4(tree*& tr, tree* X) { 
    tree* g = grandfather(X);
    tree* p = X->parent;
    if (p->right == X && g->left == p) {
        left_rotate(tr, X);
        X = X->left;
    }
    else if (p->left == X && g->right == p) {
        right_rotate(tr, X);
        X = X->right;
    }
    insert_case_5(tr, X);
}

void insert_case_5(tree*& tr, tree* X) {
    tree* g = grandfather(X);
    tree* p = X->parent;
    p->color = 'b';
    g->color = 'r';
    if (X == p->right) {
        left_rotate(tr, g);
    }
    else {
        right_rotate(tr, g);
    }
}

void insert(tree*& tr, tree* prev, int X) {
    if (!tr) {
        tree* n = root(X);
        tr = n;
    }
    else {
        if (X < prev->inf && !prev->left) {
            prev->left = node(prev, X);
            insert_case_1(tr, prev->left);
        }
        else if (X < prev->inf && prev->left) {
            insert(tr, prev->left, X);
        }
        else if (X > prev->inf && !prev->right) {
            prev->right = node(prev, X);
            insert_case_1(tr, prev->right);
        }
        else if (X > prev->inf && prev->right) {
            insert(tr, prev->right, X);
        }
    }
}

//удаление элемента из красно-черного дерева
void delete_case_1(tree*& tr, tree* X);
void delete_case_2(tree*& tr, tree* X);
void delete_case_3(tree*& tr, tree* X);
void delete_case_4(tree*& tr, tree* X);
void delete_case_5(tree*& tr, tree* X);
void delete_case_6(tree*& tr, tree* X);

void delete_case_1(tree*& tr, tree* X) {
    if (!X->parent) {
        if (X->left) {
            tr = X->left;
        }
        else {
            tr = X->right;
        }
    }
    else {
        delete_case_2(tr, X);
    }
}

void delete_case_2(tree*& tr, tree* X) {
    tree* b = brother(X);
    tree* p = X->parent;
    if (b->color == 'r') {
        p->color = 'r';
        b->color = 'b';
        if (p->left == X) {
            left_rotate(tr, p);
        }
        else {
            right_rotate(tr, p);
        }
    }
    delete_case_3(tr, X);
}

void delete_case_3(tree*& tr, tree* X) {
    tree* b = brother(X);
    if (X->parent->color == 'b' && b->color == 'b' && (!b->left || b->left->color == 'b')
        && (!b->right || b->right->color == 'b')) {
        b->color = 'r';
        delete_case_1(tr, X);
    }
    else {
        delete_case_4(tr, X);
    }
}

void delete_case_4(tree*& tr, tree* X) {
    tree* p = X->parent;
    tree* b = brother(X);
    if (X->parent->color == 'r' && b->color == 'b' && (!b->left || b->left->color == 'b')
        && (!b->right || b->right->color == 'b')) {
        b->color = 'r';
        p->color = 'b';
    }
    else {
        delete_case_5(tr, X);
    }
}

void delete_case_5(tree*& tr, tree* X) {
    tree* b = brother(X);
    tree* p = X->parent;
    if (b->color == 'b') {
        if (p->left == X && (b->left && b->left->color == 'r') &&
            (!b->right || b->right->color == 'b')) {
            b->color = 'r';
            b->left->color = 'b';
            right_rotate(tr, b);
        }
        else if (p->right == X && (b->right && b->right->color == 'r')
            && (!b->left || b->left->color == 'b')) {
            b->color = 'r';
            b->right->color = 'b';
            left_rotate(tr, b);
        }
    }
    delete_case_6(tr, X);
}

void delete_case_6(tree*& tr, tree* X) {
    tree* b = brother(X);
    tree* p = X->parent;
    b->color = p->color;
    p->color = 'b';
    if (X == p->left) {
        b->right->color = 'b';
        left_rotate(tr, p);
    }
    else {
        b->left->color = 'b';
        right_rotate(tr, p);
    }
}

void replace(tree*& tr, tree* X) {
    if (X->left) {
        tree* ch = X->left;
        ch->parent = X->parent;
        if (X->parent) {
            if (X == X->parent->left) {
                X->parent->left = ch;
            }
            else {
                X->parent->right = ch;
            }
        }
    }
    else {
        tree* ch = X->right;
        ch->parent = X->parent;
        if (X->parent) {
            if (X == X->parent->left) {
                X->parent->left = ch;
            }
            else {
                X->parent->right = ch;
            }
        }
    }
}

void erase(tree*& tr, tree* X) {
    if (X->left && X->right) {
        tree* buf = nullptr;
        if (X->inf <= tr->inf) {
            buf = X->left;
            while (buf->right) {
                buf = buf->right;
            }
        }
        else {
            buf = X->right;
            while (buf->left) {
                buf = buf->left;
            }
        }
        X->inf = buf->inf;
        X = buf;
    }
    else if (X->left || X->right) {
        tree* ch = nullptr;
        if (X->left) {
            ch = X->left;
        }
        else {
            ch = X->right;
        }
        replace(tr, X);
        if (X->color == 'b') {
            if (ch->color == 'r') {
                ch->color = 'b';
            }
            else {
                delete_case_1(tr, X);
            }
        }
    }
    else {
        if (X->color == 'b') {
            delete_case_1(tr, X);
        }
        else {
            if (X->parent->left == X) {
                X->parent->left = nullptr;
            }
            else {
                X->parent->right = nullptr;
            }
        }
    }
    delete X;
}

void max_height(tree* x, short& max, short deepness = 1) {
    if (deepness > max) max = deepness;
    if (x->left) max_height(x->left, max, deepness + 1);
    if (x->right) max_height(x->right, max, deepness + 1);
}

void print_helper(tree* x, const COORD pos, const short offset) {
    SetConsoleTextAttribute(outp, x->color == RED ? 12 : 8);
    SetConsoleCursorPosition(outp, pos);
    std::cout << std::setw(offset + 1) << x->inf;
    if (x->left) print_helper(x->left, { pos.X, short(pos.Y + 1) }, offset >> 1);
    if (x->right) print_helper(x->right, { short(pos.X + offset), short(pos.Y + 1) }, offset >> 1);
}

void print(tree* root = NULL) {
    if (root) {
        short max = 1;
        max_height(root, max);
        short width = 1 << max + 1, max_w = 128; //вычисляем ширину вывода
        if (width > max_w) width = max_w;
        for (short i = 0; i < max; ++i) std::cout << '\n'; //резервируем место для вывода
        GetConsoleScreenBufferInfo(outp, &csbInfo); //получаем данные
        COORD endPos = csbInfo.dwCursorPosition;
        print_helper(root, { 0, short(endPos.Y - max) }, width >> 1);
        SetConsoleCursorPosition(outp, endPos);
        SetConsoleTextAttribute(outp, 7);
    }
}

void printLeaves(tree* tr) {
    if (!tr) return;

    if (!tr->left && !tr->right) {
        std::cout << tr->inf << " ";
        return;
    }

    printLeaves(tr->left);
    printLeaves(tr->right);
}

//симметричный обход (Л-П-К)
void inorder(tree* tr) {
    if (tr) {
        inorder(tr->left);
        SetConsoleTextAttribute(outp, tr->color == RED ? 12 : 8);
        std::cout << tr->inf << " ";
        inorder(tr->right); 
    }
    SetConsoleTextAttribute(outp, 7);
}

int main() {    
    int n;
    std::cout << "Count: ";
    std::cin >> n;
    tree* tr = nullptr;
    int x;
    for (int i = 0; i < n; i++) {        
        std::cin >> x;
        insert(tr, tr, x);
    }
    print(tr);
    inorder(tr);
    std::cout << std::endl;   
    printLeaves(tr);
}