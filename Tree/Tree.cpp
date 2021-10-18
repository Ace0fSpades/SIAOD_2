﻿#include <iostream>
#include <queue>
#include <map>
#include <vector>

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
    void getVerticalOrder(node**, int, map<int,vector<char>>&m);
    void printVerticalOrder(node**);
    
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
        cout << level << endl;
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

void Tree::getVerticalOrder(node** p, int hd, map<int, vector<char>>& m) {
    node* tmp = *p;
    if (tmp == NULL) return;
    m[hd].push_back(tmp->Key);
    getVerticalOrder(&(tmp)->Left, hd - 1, m);
    getVerticalOrder(&(tmp)->Right, hd + 1, m);
}

void Tree::printVerticalOrder(node** p) {
    map<int, vector<char>>m;
    int hd = 0;
    getVerticalOrder(&(*p), hd, m);
    map<int, vector<char>> ::iterator it;
    for (it = m.begin(); it != m.end(); it++) {
        for (int i = 0; i < it->second.size(); i++) {
            cout << it->second[i] << " ";

        }
        cout << endl;
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
        cout << "Выберите команду[0-5]:\n[1] Построить дерево\n[2] Вывести дерево, повернув на 90*\n[3] Определить уровень элемента\n[4] Определить кол-во цифр в левом поддереве\n[5] Вывести элементы вертикально\n[0] Выход\n";
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
            A.printVerticalOrder(A.get_root());
            break;
        }
        }
    } while (key);


    return 0;
}