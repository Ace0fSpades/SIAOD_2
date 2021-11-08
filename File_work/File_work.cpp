#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <chrono>


using namespace std;

void generate_file(int count = 100)
{
   // srand(time(0));
    
    char line[9];
    int code;
    FILE* fout = fopen("text.bin", "wb"); // создаем файл для записи в бинарном виде

    for (int j = 0; j < count; j++) {    

        code = int(rand() % 100000 + 1);        
        for (int i = 0; i < 8; i++)
            line[i] = char(rand() % 25 + 65);
        line[8] = '\0';
        fwrite(&code, 4, 1, fout);
        fwrite(line, 9, 1, fout);
    }
    fclose(fout);
}

class manage_file {
    
    fstream file;

public:
    int size = 0;
    
    manage_file();
    void search(int key);
    void add(int,char*);
    void get(unsigned long long key);
    void print_file();
};



manage_file::manage_file() {

    file.open("text.bin", ios::in | ios::binary); 
    if (file) {
        file.seekg(0, file.end);
        size = file.tellg();
        file.seekg(0, file.beg);
    }
    size /= 13;
    file.close();
}

void manage_file::print_file() {
    FILE* fin = fopen("text.bin", "rb");
    char line[9];
    int code;
    for (int i = 0; i < size; i++) {
        fread(&code, 4, 1, fin);
        fread(line, 9, 1, fin);
        cout << "Index[" << i << "]: " << code << " | " << line << endl;

    }
    fclose(fin);
}

void manage_file::add(int key_code, char key_line[8]) {

    FILE* fin = fopen("text.bin", "ab");
    fwrite(&key_code, 4, 1, fin); //запись ключа и названия в файл
    fwrite(key_line, 9, 1, fin);
    size++;
    fclose(fin);

}

void manage_file::get(unsigned long long key) {
    if (key < 0) cout << "Invalid data.\n";
    FILE* fin = fopen("text.bin", "rb");
    int code = 0;
    char line[9];    
    fseek(fin, 13 * key, SEEK_SET);
    fread(&code, 4, 1, fin);
    fread(line, 9, 1, fin);
    cout << code << " | " << line << endl;

}

void manage_file::search(int key) {   

    int tmp = 0;
    char tmp_2[9] = "";
    bool flag = false;
    FILE* fin = fopen("text.bin", "rb"); 
    auto begin = std::chrono::steady_clock::now();   
    for (int i = 0; i < size; i++) {
        
        fread(&tmp, 4, 1, fin);
        fread(tmp_2, 9, 1, fin);
        
        if (tmp == key) {
            auto end = std::chrono::steady_clock::now();
            auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            cout << "Index [" << i << "] " << key  << " " << tmp_2 << endl;
            cout << "Elapsed time: " << elapsed_ms.count() << "ns\n";
            return;
        }
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "Index not found.\nElapsed time: " << elapsed_ms.count() << "ns\n";    

}


struct Node {
    int Key;

    Node* Left;
    Node* Right;

    Node(int Key) {
            this->Key = Key;
            Left = NULL;
            Right = NULL;
    }    
};

class Binary_tree {
private:
    Node* root;
public:    

    Binary_tree() { root = NULL; }

    Node* get_root() { return this->root; }

    void build_tree(Node* root);
    Node* add_elem(Node* root, int x);
    void print_tree(Node* root, int l);
    int find_key(Node* root, int x);    
    Node* delete_elem(Node* root, int x);
    Node* right_key(Node*);

    void calculate_time(Node* root, int x);

};

void Binary_tree::build_tree(Node* root) {
    int lines = 0;
    ifstream in("text.bin", ios::binary);
    if (in) { // получаем длину бинарного файла
        in.seekg(0, in.end);
        lines = in.tellg();
        in.seekg(0, in.beg);
    }
    in.close();
    lines /= 13;
    
    FILE* fin = fopen("text.bin", "rb");
    int tmp_code;
    char tmp_line[9];
    for (int i = 0; i < lines; i++) {
        fread(&tmp_code, 4, 1, fin);
        fread(tmp_line, 9, 1, fin);
        root = add_elem(root, tmp_code);
    }
    fclose(fin);
    this->root = root;
   
}

Node* Binary_tree::add_elem(Node* root, int x) {
    if (root == NULL) {
        root = new Node(x);        
    }
    else if (x < root->Key)
        root->Left = add_elem(root->Left, x);
    else
        root->Right = add_elem(root->Right, x);
    return (root);
}


int Binary_tree::find_key(Node* root, int x) {
    if (root && root->Key == x) {        
        return x;
    }
    else if (root && x < root->Key) {
        find_key(root->Left, x);
    }
    else if (root) {
        find_key(root->Right, x);
    }
    else return 0;
}

void Binary_tree::calculate_time(Node* root, int x) {
    auto begin = std::chrono::steady_clock::now();    
    find_key(root, x);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    int ans = find_key(root, x)!=0?find_key(root,x):0;
    if (ans == 0) cout << "Key not found.\nElapsed time: " << elapsed_ms.count() << "ns\n";
    else cout << "Key: " << ans << "\nElapsed time: " << elapsed_ms.count() << "ns\n";

}

Node* Binary_tree::right_key(Node* root) {
    Node* tmp = root;
    while (tmp && tmp->Left != NULL)
        tmp = tmp->Left;
    return tmp;
};

Node* Binary_tree::delete_elem(Node* root, int x) {
    
    if (root == NULL) return root;
    if (x < root->Key) root->Left = delete_elem(root->Left, x);
    else if (x > root->Key) root->Right = delete_elem(root->Right, x);
    else {
        if (root->Left == NULL && root->Right == NULL) {
            return NULL;
        }
        else if (root->Left == NULL) {
            Node* tmp = root->Right;
            free(root);
            return tmp;
        }
        else if (root->Right == NULL) {
            Node* tmp = root->Left;
            free(root);
            return tmp;
        }
        Node* tmp = right_key(root->Right);
        root->Key = tmp->Key;
        root->Right = delete_elem(root->Right, x);
    }
    return root;

}

void Binary_tree::print_tree(Node* root, int l) {
    if (root) {
        print_tree(root->Right, l + 1);
        for (int i = 0; i < l; i++) cout << "   ";
        cout << root->Key << endl;
        print_tree(root->Left, l + 1);
    }
}


struct avl_node {
    int key;
    unsigned int height;
    avl_node* left;
    avl_node* right;

    avl_node(int k) { key = k, left = right = 0; height = 1; }
};

class AVL_tree {
private:
    avl_node* root;
public:
    avl_node* getroot() { return root; }
    AVL_tree() { root = NULL; }

    unsigned int height(avl_node* p);
    int bfactor(avl_node* p);
    void fixheight(avl_node* p);
    avl_node* rotateright(avl_node* p); // повороты
    avl_node* rotateleft(avl_node* p);
    avl_node* balance(avl_node* p); // балансировка

    avl_node* findmin(avl_node* p);
    avl_node* removemin(avl_node* p);

    avl_node* remove(avl_node* p, int k); // удаление
    avl_node* insert(avl_node* p, int k); // вставка
    avl_node* search(avl_node* p, int k); // поиск

    void buildtree(); // построить дерево
    void printtree(avl_node* p, int l); // вывести дерево

    void calculate_time(avl_node* p, int k);

    float rotations = 0.0;

};

unsigned AVL_tree::height(avl_node* p) {
    return p ? p->height : 0;
}

int AVL_tree::bfactor(avl_node* p) {
    return height(p->right) - height(p->left);
}

void AVL_tree::fixheight(avl_node* p) {
    unsigned int hl = height(p->left);
    unsigned int hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

avl_node* AVL_tree::rotateleft(avl_node* p) {
    avl_node* tmp = p->right;
    p->right = tmp->left;
    tmp->left = p;
    fixheight(p);
    fixheight(tmp);
    rotations++;
    return tmp;
}

avl_node* AVL_tree::rotateright(avl_node* p) {
    avl_node* tmp = p->left;
    p->left = tmp->right;
    tmp->right = p;
    fixheight(p);
    fixheight(tmp);
    rotations++;
    return tmp;
}

avl_node* AVL_tree::balance(avl_node* p) {
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

avl_node* AVL_tree::insert(avl_node* p, int k) {
    if (!p) return new avl_node(k);
    if (k < p->key)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);
}

avl_node* AVL_tree::findmin(avl_node* p) {
    return p->left ? findmin(p->left) : p;
}

avl_node* AVL_tree::removemin(avl_node* p) {
    if (p->left == 0)
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

avl_node* AVL_tree::remove(avl_node* p, int k) {
    if (!p) return 0;
    if (k < p->key)
        p->left = remove(p->left, k);
    else if (k > p->key)
        p->right = remove(p->right, k);
    else {
        avl_node* q = p->left;
        avl_node* r = p->right;
        delete p;
        if (!r) return q;
        avl_node* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

avl_node* AVL_tree::search(avl_node* p, int k) {
    if (p == NULL || k == p->key)
        return p;
    if (k < p->key)
        return search(p->left, k);
    else
        return search(p->right, k);
}

void AVL_tree::calculate_time(avl_node* p, int k) {
    auto begin = std::chrono::steady_clock::now();
    search(p, k);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    avl_node* ans = search(p, k) != NULL ? search(p, k) : NULL;
    if (ans == NULL) cout << "Key not found.\nElapsed time: " << elapsed_ms.count() << "ns\n";
    else cout << "Key: " << ans->key << "\nElapsed time: " << elapsed_ms.count() << "ns\n";
}

void AVL_tree::buildtree() {
    int lines = 0;
    ifstream in("text.bin", ios::binary);
    if (in) { // получаем длину бинарного файла
        in.seekg(0, in.end);
        lines = in.tellg();
        in.seekg(0, in.beg);
    }
    in.close();
    lines /= 13;

    FILE* fin = fopen("text.bin", "rb");
    int tmp_code;
    char tmp_line[9];
    for (int i = 0; i < lines; i++) {
        fread(&tmp_code, 4, 1, fin);
        fread(tmp_line, 9, 1, fin);
        root = insert(root, tmp_code);
    }
    fclose(fin);
    this->root = root;
}

void AVL_tree::printtree(avl_node* root, int l) {
    if (root) {
        printtree(root->right, l + 1);
        for (int i = 0; i < l; i++) cout << "   ";
        cout << root->key << endl;
        printtree(root->left, l + 1);
    }
}

int main()
{   
    int t = 10000;
    generate_file(t);
    manage_file Test;
    Binary_tree Hel;
    AVL_tree Ofg;
   
    Hel.build_tree(Hel.get_root());
    Ofg.buildtree();
    int choice;
    
    do {
        cout << "[1]File\n[2]Binary tree\n[3]AVL tree\n[4]Elasped time\n>>> ";
    cin >> choice;
        switch (choice) {
        case 1: {
            system("cls");
            cout << "Pick task:\n[1] Print file\n[2] Add\n[3] Search by key\n[4] Search by index\n>> ";
            cin >> choice;
            switch(choice) {

            case 1:{
                system("cls");
                    Test.print_file();
                    break;
                }
            case 2:{
                system("cls");
                int key;
                char line[9];
                cout << "Enter key & line: ";
                cin >> key;
                cin >> line;
                Test.add(key, line);
                Test.print_file();
                    break;
                }
            case 3:{
                system("cls");
                int line;
                cout << "Enter key: ";
                cin >> line;
                Test.search(line);
                    break;
                }
            case 4:{
                system("cls");
                Test.print_file();
                int key;
                cout << "Enter index: ";
                cin >> key;
                Test.get(key);
                    break;
                }
            }
            break;
        }
        case 2: {
            system("cls");
            cout << "Pick task:\n[1] Print tree\n[2] Find key\n[3] Add elem\n[4] Delete elem\n>> ";
                cin >> choice;
            switch (choice) {
                
                case 1: {
                    system("cls");
                    Hel.print_tree(Hel.get_root(), 0);
                    break;
                }
                case 2: {
                    system("cls");
                    int x;
                    cout << "Enter key: ";
                    cin >> x;
                   // Hel.find_key(Hel.get_root(), x);
                    Hel.calculate_time(Hel.get_root(), x);
                    break;
                }
                case 3: {
                    system("cls");
                    int x;
                    cout << "Enter key: ";
                    cin >> x;
                    Hel.add_elem(Hel.get_root(), x);
                    break;
                }
                case 4: {
                    
                    int x;
                    cout << "Enter key: ";
                    cin >> x;
                    Hel.delete_elem(Hel.get_root(), x);
                    break;
                }
            }
            break;
        }
        case 3: {
            system("cls");
            cout << "Pick task:\n[1] Print tree\n[2] Find key\n[3] Add elem\n[4] Delete elem\n>> ";
            cin >> choice;
            switch (choice) {

            case 1: {
                system("cls");
                Ofg.printtree(Ofg.getroot(), 0);
                cout << "Rotations for "<< t << ": " << Ofg.rotations / (t * 1.0) << endl;
                break;
            }
            case 2: {
                system("cls");
                int x;
                cout << "Enter key: ";
                cin >> x;
                //Ofg.search(Ofg.getroot(), x);
                Ofg.calculate_time(Ofg.getroot(), x);
                break;
            }
            case 3: {
                system("cls");
                int x;
                cout << "Enter key: ";
                cin >> x;
                Ofg.insert(Ofg.getroot(), x);
                break;
            }
            case 4: {
                
                int x;
                cout << "Enter key: ";
                cin >> x;
                Ofg.remove(Ofg.getroot(), x);
                break;
            }
                  
            }
            break;
        }

        case 4: {
            system("cls");
            int x;
            cout << "Enter key: ";
            cin >> x;
            cout << "File: ";
            Test.search(x);
            cout << "\nBinary: ";
            Hel.calculate_time(Hel.get_root(), x);
            cout << "\nAVL: ";
            Ofg.calculate_time(Ofg.getroot(), x);
            break;
        }

        }
        
    } while (choice);
    
    

    return 0;
}
