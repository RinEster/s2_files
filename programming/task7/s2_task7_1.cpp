//Дан список целых чисел. Построить дерево бинарного поиска. Вывести путь от корня до узла Х. 
//10 0 12 11 6 -1 -9 20
//8
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

void preorder(tree* tr) { // прямой обход (К-Л-П)
    if (tr) {
        std::cout << tr->inf << " "; //корень
        preorder(tr->left); //левое
        preorder(tr->right); //правое
    }
}

void postorder(tree* tr) { // обратный обход (Л-П-К)
    if (tr) {
        postorder(tr->left); //левое
        postorder(tr->right); //правое
        std::cout << tr->inf << " "; //корень
    }
}

void inorder(tree* tr) { // симметричный обход (Л-К-П)
    if (tr) {
        inorder(tr->left); //левое
        std::cout << tr->inf << " "; //корень
        inorder(tr->right); //правое
    }
}

void insert(tree*& tr, int x) {
    tree* n = node(x);
    if (!tr) {
        tr = n; //если дерево пустое - корень
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

//поиск значения
bool findPath(tree* tr, int x, std::vector<int>& path) {
    if (!tr) return false;

    //добавление в путь
    path.push_back(tr->inf);

    //значение достигнуто
    if (tr->inf == x) return true;

    //продолжение поиска
    if (x < tr->inf) {
        return findPath(tr->left, x, path);
    }
    else {
        return findPath(tr->right, x, path);
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
    std::cout << "\nX: ";
    std::cin >> x;

    std::vector<int> path; //путь

    if (findPath(tr, x, path)) {
        std::cout << "\nThe path from the root to the node " << x << ": ";
        for (int val : path) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "\nNode " << x << " not found." << std::endl;
    }

    return 0;
}