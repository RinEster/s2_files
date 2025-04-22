//Дан список целых чисел. Построить дерево бинарного поиска. Найти сумму внутренних узлов дерева.

#include <iostream>
#include <cmath>
#include <queue>
#include <vector>

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


bool internalNode(tree* tr) {
    return tr && (tr->left || tr->right);// && tr->parent;
}
int sumInternal(tree* tr) {
    if (!tr) return 0;

    int sum = 0;
    if (internalNode(tr)) {
        sum += tr->inf;
    }

    sum += sumInternal(tr->left);
    sum += sumInternal(tr->right);

    return sum;
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
    int k = int(log((float)n) / log((float)2.0));
    print(tr, k);
    int sum = 0;
    std::cout << "\nSum: " << sumInternal(tr);
}