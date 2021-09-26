#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

string generate_item()
{
    int length = rand() % 4 + 4; // определяем длину кода специализации
    string line = "";
    for (int i = 0; i < length; i++)        
        line = line + char(rand() % 9 + 48);
    line = line + " ";    
    length = rand() % 10 + 5; // определяем длину названия вуза
    for (int i = 0; i < length; i++)        
        line = line + char(rand() % 25 + 65);            
    return(line);
}

void generate_file() {
    ofstream fout("text.bit");
    string line;
    for (int i = 0; i < 100; i++) {
        line = generate_item();
        fout << (i == 99 ? line : line + '\n');
    }
    fout.close();
}

struct Stack {
    string code;
    string name;
    Stack* Next;
    Stack* Head;
    

    Stack() {
        code = "";
        name = "";
        Next = nullptr;  
        Head = this;
        
        
    }
    Stack(string code, string name) {
        this->code = code;
        this->name = name;
        Next = nullptr;
        Head = this;
        
        
    }

    bool empty() {
        return Head == nullptr;
    }

    void add_next(string code, string name) {        
        Stack* a = new Stack(code, name);
        if (empty()) {
            Head = a;
            Next = a->Next;
            
            return;
        }
        Stack* tmp;
        tmp = this;
        while(tmp->Next != NULL)
        tmp = tmp->Next;        
        tmp->Next = a;
        
        a->Head = this;
    }

    };

class Hash_table {
private:
    Stack* table[100];   

public:

    Hash_table() {
        for (int i = 0; i < 100; i++) {            
            table[i] = new Stack();
        }
    }
    ~Hash_table() {
        for (int i = 0; i < 100; i++) {
            delete table[i];
        }
    }

    int hash(string code);
    void read_paste();    
    void delete_target(string code);
    void find(string code);
    void table_out();

};



int Hash_table::hash(string code)
{
    int result = 0;
    int i = 0;
    while (code[i]) {
        result += int(code[i]);
        i++;
    }    
    return (result % 100);
}

void Hash_table::read_paste()
{
    ifstream fin("text.bit");
    int count_lines = 0;
    string line;
    while (!fin.eof()) {
        getline(fin, line);
        count_lines++;
    }
    fin.clear(); // установка поинтера в начало файла
    fin.seekg(0);
    for (int i = 0; i < count_lines; i++) {
        getline(fin, line); // формат код_название
        int j = 0;
        string tmp_code = "";
        string tmp_name = "";
        while (line[j]!=' ') {
            tmp_code = tmp_code + line[j];
            j++;
        }
        j++;
        while (line[j]) {
            tmp_name += line[j];
            j++;
        }
        if (table[hash(tmp_code)]->code == "") {  // привязка +1 ячейки в случае одинаковых хеш значений
            table[hash(tmp_code)]->code = tmp_code;
            table[hash(tmp_code)]->name = tmp_name;            
        }
        else {            
            table[hash(tmp_code)]->add_next(tmp_code, tmp_name);            
        }   
    }
    fin.close();
}

void Hash_table::delete_target(string code) {
    int index = hash(code);
    Stack* tmp_1 = table[index];
    Stack* tmp_2 = table[index]->Next;
    if (tmp_1->Head->code == code) {
        tmp_1 = tmp_2;
        while (tmp_2) {
            
            tmp_2->Head = tmp_1;            
            tmp_2 = tmp_2->Next;
        }        
        delete table[index];
        table[index] = tmp_1;
        return;
    }
    while (tmp_2->code != code) {
        tmp_2 = tmp_2->Next;
        tmp_1 = tmp_1->Next;
    } 
    tmp_1->Next = tmp_2->Next;

    delete tmp_2;
    
}

void Hash_table::find(string code)
{
    int index = hash(code);
    Stack* tmp = table[index];
    while (tmp->code != code) {
        tmp = tmp->Next;
    }
    cout << "Hash: " << index << " | " << tmp->code << " | " << tmp->name << '\n';

}

void Hash_table::table_out()
{
    for (int i = 0; i < 100; i++) {
        
            Stack* tmp = table[i];
            while (tmp) {
                cout << "Hash " << i << " | " << tmp->code << " | " << tmp->name << '\n';
                tmp = tmp->Next;
            }
        
    }
}


int main()
{
    generate_file();
    Hash_table test;
    test.read_paste();
    int key;
    do {
        cout << "Choose operation:\n[1] Show table\n[2] Search subject by code\n[3] Delete subject by code\n[0] Exit\n>>> ";
        cin >> key;        
        switch (key) {
        case 1: test.table_out(); break;
        case 2: {
            string code;
            cout << "Insert code: ";
            cin >> code;
            system("cls");
            test.find(code);
            system("pause");
            system("cls");
            break;
        }
        case 3: {
            string code;
            cout << "Insert code: ";
            cin >> code;
            system("cls");
            test.delete_target(code);            
            system("cls");
            break;
        }
        }
    } while (key);
    
    return 0;
}


