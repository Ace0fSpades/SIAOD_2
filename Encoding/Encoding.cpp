#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

void RLE(string s) {
    int length = s.length();
    int* arr_c = new int [length];
    char* arr_s = new char[length];

    int count = 0;
    int iterator = 0;
    for (int i = 0; i < length; i++) {
        count++;
        if (s[i] != s[i + 1]) {
            arr_c[iterator] = count;
            arr_s[iterator] = s[i];
            count = 0;
            iterator++;
        }
    }
    cout << "Строка: " << s << endl;
    cout << "RLE: ";
    for (int i = 0; i < iterator; i++) {
        cout << arr_c[i] << "|" << arr_s[i] << " ";
    }
    double koef = length / (2.0 * iterator);
    cout << endl << "Коэффициент сжатия: " << koef << endl;

}

void RLE_text_divide(string s, int new_length) {
    int length = s.length();
    int divider = length / new_length;    
    
    int* arr_c = new int[divider];
    string* arr_s = new string[divider];
    for (int i = 0; i < divider; i++) arr_c[i] = -1;
    
    int count = 0;
    int iterator = 0;
    int j = 0;
    for (int i = 0; i < divider; i++) {
        count++;
        if (i != 0) {
            int key = 0;
            for (int l = 0; l < new_length; l++) {
                if (arr_s[i - 1][l] == s[j]) {
                    key++; j++;
                }
                else
                {                    
                    j -= key;
                    int t = 0;
                    while (t < new_length) {
                        arr_s[i] += s[j];
                        t++;
                        j++;
                    }
                    arr_c[i] = count;
                    count = 0;
                    break;
                }
            }
            if (key == new_length) {
                arr_c[i - 1] += count;
                key = 0;
                count = 0;
            };
        }
        else {
            int t = 0;
            while (t < new_length) {
                arr_s[i] += s[j];
                t++;
                j++;
            }
            arr_c[i] = count;
            count = 0;
        }
        
    }
    cout << "Строка: " << s << endl;
    cout << "RLE для разбиения на " << divider << " групп(ы): ";
    for (int i = 0; i < divider; i++) {
        cout << (arr_c[i] == -1 ? 0 : arr_c[i]) << "|" << (arr_s[i].size() == NULL ? "-" : arr_s[i]) << " ";
    }
    double koef = length / (2.0 * divider);
    cout << endl << "Коэффициент сжатия: " << koef << endl;

}

void print_result(int a, int l, char k) {
    cout << "<" << a << ", " << l << ", " << k << "> ";
}

void LZ77(string text) {
    
    
    char alphabet[21] = "";
    for (int i = 0; i < 21; i++) {        
        alphabet[i] = '-';
    }
    int current_pos = 4;   

    char buffer[4] = "";
    for (int i = 0; i < 4; i++) {
        buffer[i] = text[i];       
    }
    
    int length = 0;
    int address = 0;

    int a_pos = 0;
    int a_filled = 0;

    while (buffer[0] != '\0') {

            int* tmp = new int[a_filled];
            while (alphabet[a_pos] != buffer[0]) {
                if (alphabet[a_pos] == '-') break;
                a_pos++;
            }
            if (alphabet[a_pos] == '-') {
                alphabet[a_pos] = buffer[0];
                for (int j = 0; j < 3; j++) {
                    buffer[j] = buffer[j + 1];
                }
                buffer[3] = text[current_pos];
                current_pos++;
                a_filled++;
                print_result(0, 0, buffer[0]);
                a_pos = 0;                
            }
            else {
                for (int count = a_pos; count < a_filled; count++) {
                    for (int i = 0; i < 4; i++) {
                        if (alphabet[count + i] == buffer[i]) {
                            length++;
                            if (length == 4) {
                                tmp[count] = length;
                                length = 0;
                                break;
                            }                            
                        }
                        else {
                            tmp[count] = length;
                            length = 0;
                            break;                           
                        }
                    }

                }

                int max = tmp[a_pos];
                address = a_pos;
                for (int count = a_pos + 1; count < a_filled; count++) {
                    if (tmp[count] > max) {
                        max = tmp[count];
                        address = count;
                    }
                }
                int is_char = 0;
                for (int l = 0; l < 4; l++) if (buffer[is_char] != '\0') is_char++;
                address = current_pos - is_char - address;
                length = max;

                print_result(address, length, text[current_pos-is_char+length]);
                
                if (length < 4) {
                    length++;

                    for (int j = 0; j < length; j++) {
                        if (buffer[j] == '\0') break;
                        alphabet[a_filled + j] = buffer[j];
                    }
                    a_filled += length;

                    // alphabet[a_filled] = text[current_pos-4+length];
                    // a_filled++;
                    refresh:
                    int k = 4 - length;
                    if (k != 0)
                        for (int j = 0; j < (4 - length); j++) {
                            buffer[j] = buffer[4 - k + j];
                        }
                    while (length) {
                        buffer[k] = text[current_pos];
                        if (current_pos == 21 || buffer[0] == '\0') {
                            for (int j = 0; j < (4 - k); j++) buffer[k+j] = '\0';
                            break;
                        }
                        current_pos++;
                        k++;
                        length--;
                    }

                    length = 0;
                    address = 0;
                    a_pos = 0;
                }
                else if (length == 4) {
                    for (int j = 0; j < length; j++) {
                        alphabet[a_filled + j] = buffer[j];
                    }
                    a_filled += length;
                    alphabet[a_filled] = text[current_pos-4+length];
                    a_filled++;
                    current_pos++;
                    goto refresh;
                }
            }

        }

}




struct Node {
    int index;
    string data;
    Node* next;
};

void st_Node(Node* head, int index, string data) {
    head->index = index;
    head->data = data;
    head->next = NULL;
}

void insert_Node(Node* head, int index, string data) {
    Node* new_Node = new Node;
    new_Node->index = index;
    new_Node->data = data;
    new_Node->next = NULL;

    Node* curr = head;
    while (curr != NULL)
    {
        if (curr->next == NULL)
        {
            curr->next = new_Node;
            return;
        }
        curr = curr->next;
    }
}

Node* search_Node(Node* head, string data)
{
    Node* curr = head;
    while (curr != NULL)
    {
        if (data.compare(curr->data) == 0)
            return curr;
        else
            curr = curr->next;
    }
    return NULL;
}

Node* search_Node(Node* head, int index)
{
    Node* curr = head;
    while (curr != NULL)
    {
        if (index == curr->index)
            return curr;
        else
            curr = curr->next;
    }
    return NULL;
}




void LZ78(string input)
{   
        Node* dictionary = new Node;
        string word, result;
        int length, last_seen, index = 1;

        length = (int)input.length();
        word = input[0];
        st_Node(dictionary, 1, word);
        result += "0," + word;

        for (int i = 1; i < length; i++)
        {
            string data;
            data = input[i];

        re_check:
            Node* search = search_Node(dictionary, data);

            if (search)
            {
                i++;
                data += input[i];
                last_seen = search->index;
                goto re_check;
            }
            else
            {
                char zero;
                if (input[i] == ' ')
                    zero = '0';
                else
                    zero = input[i];

                if ((int)data.length() < 2)
                    result += " " + to_string(0) + "," + zero;
                else
                    result += " " + to_string(last_seen) + "," + zero;

                index++;
                if (i != length)
                    insert_Node(dictionary, index, data);
            }
        }

        cout << result;
    
    
}

// Тише, мыши, кот на крыше, 
// А котята ещё выше.Кот пошёл за молоком,
// А котята кувырком.
// тише, мыши, кот на крыше, а котята еще выше. кот пошел за молоком, а котята кувырком.

char c_arr[22] = " октеаш,мылиряв.знпщу";
int p_arr[21] = { 1765,1059,941,824,706,706,588,471,471,471,235,235,235,235,235,235,118,118,118,118,118};
vector<string> fano_result;


void Fano(char branch, string s, int start_pos, int end_pos) {
    double dS;
    int S, i, m;
    string c_branch;
    if (c_arr != " ") c_branch = s + branch;
    else c_branch = ' ';

    if (start_pos == end_pos) {
        fano_result.push_back(c_branch);
        return;
    }

    dS = 0;
    for (int j = start_pos; j < end_pos; j++) {
        dS += p_arr[j];
    }
    dS /= 2;

    S = 0;
    i = start_pos;
    m = i;
    while (S + p_arr[i] < dS && i < end_pos) {
        S += p_arr[i];
        i++;
        m++;
    }
    Fano('0', c_branch, start_pos, m);
    Fano('1', c_branch, m + 1, end_pos);
}

void Fano_compression(string s) {
    for (int i = 0; i < s.length(); i++) {
        for (int j = 0; j < 21; j++) {
            if (s[i] == c_arr[j]) cout << fano_result[j] << ' ';
        }
    }
}

// Хаффман
struct Node_haff
{
    char ch;
    int freq;
    Node_haff* left, * right;
};

// Добавление нового узла
Node_haff* getNode_haff(char ch, int freq, Node_haff* left, Node_haff* right)
{
    Node_haff* node = new Node_haff();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

// Сравнение
struct comp
{
    bool operator()(Node_haff* l, Node_haff* r)
    {
        // Больший приоритет реже встречаемому симв
        return l->freq > r->freq;
    }
};

// кодировка с помощью дерева и таблицы кодов, представленной в виде карты
void encode(Node_haff* root, string str,
    unordered_map<char, string>& huffmanCode)
{
    if (root == nullptr)
        return;

    // находим листок (крайний симв)
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

// traverse the Huffman Tree and decode the encoded string
//void decode(Node_haff* root, int& index, string str)
//{
//    if (root == nullptr) {
//        return;
//    }
//
//    // found a leaf node
//    if (!root->left && !root->right)
//    {
//        cout << root->ch;
//        return;
//    }
//
//    index++;
//
//    if (str[index] == '0')
//        decode(root->left, index, str);
//    else
//        decode(root->right, index, str);
//}

// Вывод результата 
void buildHuffmanTree(string text)
{

    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    priority_queue<Node_haff*, vector<Node_haff*>, comp> pq;

    for (auto pair : freq) {
        pq.push(getNode_haff(pair.first, pair.second, nullptr, nullptr));
    }

    while (pq.size() != 1)
    {
        Node_haff* left = pq.top(); pq.pop();
        Node_haff* right = pq.top();	pq.pop();

        int sum = left->freq + right->freq;
        pq.push(getNode_haff('\0', sum, left, right));
    }
    Node_haff* root = pq.top();

    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    cout << "Huffman Codes are :\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << " " << pair.second << '\n';
    }
    cout << "\nВходная строка:\n" << text << '\n';

    string str = "";
    for (char ch : text) {
        str += huffmanCode[ch]+' ';
    }

    cout << "\nЗакодированное сообщение:\n" << str << '\n';

}



int main()
{
    setlocale(LC_ALL, "rus");

    int key;
    do {
        cout << "[1]RLE\n[2]RLE блоками\n[3]LZ77\n[4]LZ78\n[5]Fano\n[6]Haffman\n[0]Выход\n>>> ";
        cin >> key;
        switch (key) {
        case 1:
        {
            system("cls");
            cout << "Введите строку для RLE: ";
            string sl;
            cin >> sl;
            RLE(sl);
            break;
        }
        case 2:
        {
            system("cls");
            cout << "Введите строку для RLE: ";
            string sl;
            cin >> sl;
            int by;
            cout << "Введите делитель: ";
            cin >> by;
            RLE_text_divide(sl, by);
            break;
        }
        case 3:
        {
            system("cls");
            cout << "Строка для LZ77: 110101011001100001001\n";
            LZ77("110101011001100001001");
            cout << endl;
            break;
        }
        case 4:
        {
            system("cls");
            cout << "Строка для LZ78: долделдолдилделдил\n";
            LZ78("долделдолдилделдил");
            cout << endl;
            break;
        }
        case 5:
        {
            system("cls");
            cout << "Строка для Фано: тише, мыши, кот на крыше, а котята еще выше. кот пошел за молоком, а котята кувырком.\nТаблица кодировки\n";
            Fano('\0', "", 0, 20);
                for (int i = 0; i < fano_result.size(); i++) {
                    cout << c_arr[i] << " = " << fano_result[i] << endl;
                }
            Fano_compression("тише, мыши, кот на крыше, а котята еще выше. кот пошел за молоком, а котята кувырком.");
            cout << endl;
            break;
        }
        case 6:
        {
            system("cls");
            cout << "Строка для Хаффмана: Дергачев Андрей Сергеевич\n";

            string text = "Дергачев Андрей Сергеевич";
            buildHuffmanTree(text);
            break;
        }
        }


    } while (key);   

    return 0;
}
	

