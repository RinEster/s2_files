//Дан список целых чисел. Построить дерево бинарного поиска. Найти средний по значению лист и удалить его "деда".
#include <iostream>
#include <cmath>
#include <queue>
#include <vector>


// 5 3 8 1 4 7 9 2 6 10
//10 

//6 3  9 2 5 8 10 1 4 7

// 5 -3 3 -1 6 3 9 4 -2 -5

struct tree {
    int inf;
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

void insert(tree*& tr, int x) {
    tree* n = node(x);
    if (!tr) {
        tr = n;
    }
    else {
        tree* y = tr;
        while (y) {
            if (n->inf < y->inf) { //левая ветка
                if (y->left) {
                    y = y->left;
                }
                else {
                    y->left = n;
                    n->parent = y;
                    break;
                }
            }
            else if (n->inf > y->inf) { //правая ветка
                if (y->right) {
                    y = y->right;
                }
                else {
                    y->right = n;
                    n->parent = y;
                    break;
                }
            }
            else {
                break;
            }
        }
    }
}


void print(tree* tr, int k) {
    if (!tr) std::cout << "Empty tree\n";
    else {
        std::queue<tree*> cur, next; //cur - текущий уровень, next - следующий
        tree* r = tr; // корень
        cur.push(r);
        int j = 0;
        while (cur.size()) {
            if (j == 0) { //отступы
                for (int i = 0; i < (int)pow(2.0, k) - 1; i++)
                    std::cout << " ";
            }
            //вывод узлов текущего уровня
            tree* buf = cur.front();
            cur.pop();
            j++;
            if (buf) {
                std::cout << buf->inf;
                next.push(buf->left);
                next.push(buf->right);
                for (int i = 0; i < (int)pow(2.0, k + 1) - 1; i++)
                    std::cout << " ";
            }
            //пустые узлы
            if (!buf) {
                for (int i = 0; i < (int)pow(2.0, k + 1) - 1; i++)
                    std::cout << " ";
                std::cout << " ";
            }
            //след уровень
            if (cur.empty()) {
                std::cout << std::endl;
                swap(cur, next);
                j = 0;
                k--;
            }
        }
    }
}
tree* Min(tree* tr) { //поиск min
    if (!tr->left) return tr;
    else return Min(tr->left);
}

tree* Max(tree* tr) { //поиск max
    if (!tr->right) return tr; 
    else return Max(tr->right); 
}

tree* find(tree* tr, int x) { //поиск
    if (!tr || x == tr->inf) { 
        return tr; 
    }
    if (x < tr->inf) { 
        return find(tr->left, x); 
    }
    else { 
        return find(tr->right, x); 
    }
}

tree* Next(tree* tr, int x) { 
    tree* n = find(tr, x); 
    if (n->right) {
        return Min(n->right);
    }
    tree* y = n->parent; 
    while (y && n == y->right) { 
        n = y; 
        y = y->parent;
    }
    return y; 
}

tree* Prev(tree* tr, int x) { //поиск предыдущего
    tree* n = find(tr, x);
    if (n->left) { 
        return Max(n->left); 
    }
    tree* y = n->parent; 
    while (y && n == y->left) {
        n = y; 
        y = y->parent;
    }
    return y; 
}

void deleteNode(tree*& tr, tree* v) {
    tree* p = v->parent;
    if (!p) tr = NULL;
    else if (!v->left && !v->right) { //нет детей
        if (p->left == v) {
            p->left = NULL;
        }
        if (p->right == v) {
            p->right = NULL;
        }
        delete v;
    }
    else if (!v->left || !v->right) { //один ребенок
        if (!p) {
            if (!v->left) {
                tr = v->right;
                v->parent = NULL;
            }
            else {
                tr = v->left;
                v->parent = NULL;
            }
        }
        else {
            if (!v->left) {
                if (p->left == v) {
                    p->left = v->right;
                }
                else {
                    p->right = v->right;
                }
                v->right->parent = p;
            }
            else {
                if (p->left == v) {
                    p->left = v->right;
                }
                else {
                    p->right = v->right;
                }
                v->right->parent = p;
            }
            delete v;
        }
    }
    else {
        tree* succ = Next(tr, v->inf); 
        v->inf = succ->inf; 
        if (succ->parent->left == succ) { 
            succ->parent->left = succ->right;
            if (succ->right) succ->right->parent = succ->parent;
        }
        else { 
            succ->parent->right = succ->right;
            if (succ->right) succ->right->parent = succ->parent;
        }
        delete succ;
    }
}

//собираем листья
void collectLeaves(tree* tr, std::vector<tree*>& leaves) {
    if (!tr) return;
    if (!tr->left && !tr->right) {
        leaves.push_back(tr);
    }
    collectLeaves(tr->left, leaves);
    collectLeaves(tr->right, leaves);
}

tree* findSredLeaf(std::vector<tree*>& leaves) {
    if (leaves.empty()) return NULL;
    
    for (size_t i = 0; i < leaves.size(); ++i) {
        for (size_t j = 0; j < leaves.size() - i - 1; ++j) {
            if (leaves[j]->inf > leaves[j + 1]->inf) {
                tree* temp = leaves[j];       
                leaves[j] = leaves[j + 1];   
                leaves[j + 1] = temp;        
            }
        }
    }

    return leaves[leaves.size() / 2];
}

int main() {
    tree* tr = NULL;
    int n, x;
    std::cout << "n: ";
    std::cin >> n;

    std::cout << "\nInput: ";
    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        insert(tr, num);
    }
    std::cout << "\nTree before deletion:\n ";
    int k = int(log((float)n) / log((float)2.0));
    print(tr, k);

    std::vector<tree*> leaves;
    collectLeaves(tr, leaves);

    if (leaves.empty()) {
        std::cout << "No leaves in the tree!\n";
        return 0;
    }

    //средний лист
    tree* sredLeaf = findSredLeaf(leaves);
    std::cout << "Sred leaf: " << sredLeaf->inf << std::endl;

    //дед
     if (sredLeaf->parent && sredLeaf->parent->parent) {
        tree* grandparent = sredLeaf->parent->parent;
        std::cout << "Grandparent to delete: " << grandparent->inf << std::endl;

        //удаляем деда
        deleteNode(tr, grandparent);

        std::cout << "Tree after deletion:\n";
        print(tr, k);
    }
    else {
        std::cout << "No grandparent to delete!\n";
    }
    
}