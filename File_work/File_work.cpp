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

        code = int(rand() % 899 + 100);        
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
    void search(char key[13]);
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

void manage_file::search(char key[9]) {
    
    char tmp[13] = "";
    bool flag = false;
    file.seekg(0);
    for (int i = 0; i < size; i++) {
        file.read(tmp, 13);
        for (int j = 4; j < 13; j++) {
            if (tmp[j] != key[j - 4]) { 
                flag = true;
                break;
            }            
        }
        if (flag == false) {
            cout << key << endl;
            break;

        }
        else flag = false;
    }

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
    void find_key(Node* root, int x);
    Node* find_key_upper(Node* root, int x);
    Node* delete_elem(Node* root, int x);
    Node* right_key(Node*);

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

Node* Binary_tree::find_key_upper(Node* root, int x) {
    if (root && (root->Left->Key == x || root->Right->Key == x)) {
        
        return root;
    }
    else if (root && x < root->Key) {
        find_key(root->Left, x);
    }
    else if (root) {
        find_key(root->Right, x);
    }
}

void Binary_tree::find_key(Node* root, int x) {
    if (root && root->Key == x) {
        cout << "Key: " << root->Key << endl;
        return;
    }
    else if (root && x < root->Key) {
        find_key(root->Left, x);
    }
    else if (root) {
        find_key(root->Right, x);
    }
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







int main()
{   
    generate_file(30);
    manage_file Test;
    Binary_tree Hel;
   
    Hel.build_tree(Hel.get_root());
    int choice;
    cout << "Pick task:\n[1] Print tree\n[2] Find key\n[3] Add elem\n[4] Delete elem\n>> ";
    cin >> choice;
    while (choice) {
        switch (choice) {
        case 1: {
            Hel.print_tree(Hel.get_root(), 0);
            break;
        }
        case 2: {
            int x;
            cout << "Enter key: ";
            cin >> x;
            Hel.find_key(Hel.get_root(), x);
            break;
        }
        case 3: {
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
        cin >> choice;
    }
    
    

    return 0;
}
