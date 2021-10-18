#include <iostream>

using namespace std;

struct node{
    char Key;
    int Count;
    node* Left;
    node* Right;
};

class Tree
{
private:
    node* root; 
public:
    Tree() { root = NULL; }
    node** get_root() { return &root; }
    void build_tree(int, node**);
    void print_tree(node**, int);
    int level_elem(int, node**);
    node* search(char);
};

node* Tree::search(char a) {
    node* tmp = this->root;

    if (tmp == NULL) return NULL;
    if (tmp->Key == a) return tmp;


}

int Tree::level_elem(int n, node** p) {
    return 0;
}

void Tree::build_tree(int n, node** p)
{
    node* now;
    char x;
    int nl, nr;

    now = *p;
    if (n == 0) *p = NULL;
    else
    {
        nl = n / 2; // кол-во левых ветвей
        nr = n - nl - 1; // кол-во правых ветвей
        cin >> x;
        now = new(node);
        (*now).Key = x;
        build_tree(nl, &((*now).Left));
        build_tree(nr, &((*now).Right));
        *p = now;
    }
}

void Tree::print_tree(node** w, int l){
    if (*w != NULL)
    {
        print_tree(&((**w).Right), l + 1);
        for (int i = 1; i <= l; i++) cout << "   ";
        cout << (**w).Key << endl;
        print_tree(&((**w).Left), l + 1);
    }
}
int main()
{
    setlocale(LC_ALL, "rus");
    Tree A;
    int n;

    cout << "Введите количество вершин -...\n"; cin >> n;
    cout << "Вводите ключи...\n";
    A.build_tree(n, A.get_root()); A.print_tree(A.get_root(), 0);

    return 0;
}