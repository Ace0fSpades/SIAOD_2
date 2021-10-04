#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

void generate_file(int count = 100)
{
    int length = 7; // определяем длину кода специализации
    char line[16];
    FILE* fout = fopen("text.bin", "wb"); // создаем файл для записи в бинарном виде

    for (int j = 0; j < count; j++) {
        for (int i = 0; i < length; i++)
            line[i] = char(rand() % 9 + 48);
        line[7] = ' ';
        length = 15; // определяем длину названия вуза
        for (int i = 8; i < length; i++)
            line[i] = char(rand() % 25 + 65);
        if (j == count-1) line[15] = '\0';
        else line[15] = '\n';
        fwrite(line, 16, 1, fout);        
    }
    fclose(fout);
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
    void insert_target(string code, string name);
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
    return ((result * 123 )%100);
}

void Hash_table::read_paste()
{
    ifstream fin("text.bin", ios::binary);
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
    if (tmp_1 && tmp_1->Head->code == code) {
        tmp_1 = tmp_2;
        while (tmp_2) {
            
            tmp_2->Head = tmp_1;            
            tmp_2 = tmp_2->Next;
        }        
        delete table[index];
        table[index] = tmp_1;
        return;
    }
    while (tmp_2 && tmp_2->code != code) {
        tmp_2 = tmp_2->Next;
        tmp_1 = tmp_1->Next;
    }
    if (tmp_1 == NULL || tmp_2 == NULL) {
        cout << "Hash not found.\n";
        return;
    }
    tmp_1->Next = tmp_2->Next;

    delete tmp_2;
    
}

void Hash_table::insert_target(string code, string name) {
    int index = hash(code);
    Stack* tmp = table[index];
    tmp->add_next(code, name);

}

void Hash_table::find(string code)
{
    auto begin = std::chrono::steady_clock::now();

    int index = hash(code);    
    Stack* tmp = table[index];    
   while (tmp != NULL && tmp->code != code) {
            tmp = tmp->Next;
   }
   auto end = std::chrono::steady_clock::now();
   auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
   if (tmp)
       cout << "Hash: " << index << " | " << tmp->code << " | " << tmp->name << '\n' << "Elapsed time: "<< elapsed_ms.count() << "ns\n";
   
   else cout << "Hash not found.\n" << "Elapsed time: " << elapsed_ms.count() << "ns\n";
}

void Hash_table::table_out()
{
    for (int i = 0; i < 100; i++) {
        
            Stack* tmp = table[i];
            while (tmp) {
                if(tmp->code != "")
                cout << "Hash " << i << " | " << tmp->code << " | " << tmp->name << '\n';                
                tmp = tmp->Next;
            }
        
    }
}


int main()
{
    generate_file(1000);
    
    Hash_table test;
    test.read_paste();
    int key;
    do {
        cout << "Choose operation:\n[1] Show table\n[2] Search subject by code\n[3] Delete subject by code\n[4] Insert subject by code&name\n[0] Exit\n>>> ";
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
            test.delete_target(code);
            system("pause");
            system("cls");
            break;
        }
        case 4: {
            string code, name;
            cout << "Insert code: ";
            cin >> code;            
            cout << "Insert name: ";
            cin >> name;            
            test.insert_target(code, name); 
            system("cls");
            break;
        }
        }
    } while (key);
        
    
    return 0;
    
}


