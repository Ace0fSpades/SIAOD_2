#include <iostream>
#include <queue>

using namespace std;

struct node{
    char Key;    
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
    node** get_leftroot(){return &(root)->Left;}
    void build_tree(int, node**);
    void print_tree(node**, int);
    void search(char, node**, int);
    int count_numbers(node**);    
    void print_vertical(node**);
};

int Tree::count_numbers(node** p) {
    node* tmp = *p;
    if (tmp == NULL) return 0;
    if (tmp->Key < '0' || tmp->Key > '9') return 0 + count_numbers(&(tmp)->Left) + count_numbers(&(tmp)->Right);
    if (tmp->Key >= '0' && tmp->Key <= '9') {
        return 1 + count_numbers(&(tmp)->Left) + count_numbers(&(tmp)->Right);
    }    
}

void Tree::search(char a, node** p, int level = 0) {    
    node* tmp = *p;    
    if (tmp->Key == a) {
        cout << "Уровень элемента: " << level << endl;
        return;
    }    
    if (tmp->Left) {
        search(a, &tmp->Left, ++level);
        --level;
    }
    if (tmp->Right) {
        search(a, &tmp->Right, ++level);
    }    
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

void Tree::print_tree(node** w, int l = 0){
    if (*w != NULL)
    {
        print_tree(&((**w).Right), l + 1);
        for (int i = 1; i <= l; i++) cout << "   ";
        cout << (**w).Key << endl;
        print_tree(&((**w).Left), l + 1);
    }
}

void Tree::print_vertical(node** p) {
    node* cur = *p;
    int rowelems = 1, currentelems = 0, level = 0;
    queue<node*> q;
    q.push(cur);    
    while (!q.empty()) {
        node* top = q.front();
        if (top) cout << top->Key;
        else cout << " ";
        currentelems++;
        if (currentelems == rowelems) {
            cout << endl;
            rowelems *= 2;
            currentelems = 0;
            level++;
        }
        else cout << " ";           
        
        if (top) {
            if (top->Left) q.push(top->Left);
            else q.push(NULL);
        }
        if (top) {
            if (top->Right) q.push(top->Right);
            else q.push(NULL);
        }
        q.pop();
    }

}

int main()
{
    setlocale(LC_ALL, "rus");
    Tree A;
    int n;
    int key;
    char b;
    
    do {
        cout << "Выберите команду[0-5]:\n[1] Построить дерево\n[2] Вывести дерево, повернув на 90*\n[3] Определить уровень элемента\n[4] Определить кол-во цифр в левом поддереве\n[5] Вывести элементы вертикально\n[0] Выход\n>>> ";
        cin >> key;
        switch (key) {
        case 1: {
            system("cls");
            cout << "Введите кол-во элементов: ";
            cin >> n;
            A.build_tree(n, A.get_root());
            break;
        }
        case 2: {
            system("cls");
            A.print_tree(A.get_root());
            break;

        }
        case 3: {
            system("cls");
            A.print_tree(A.get_root());
            cout << "Введите элемент: ";
            cin >> b;
            A.search(b, A.get_root());
            break;

        }
        case 4: {
            system("cls");
            A.print_tree(A.get_root());
            cout <<"Цифр в л.поддереве: " << A.count_numbers(A.get_leftroot()) << endl;
            break;
        }
        case 5: {
            system("cls");
            A.print_tree(A.get_root());
            cout << endl;
            A.print_vertical(A.get_root());
            cout << endl;
            break;
        }
        }
    } while (key);


    return 0;
}