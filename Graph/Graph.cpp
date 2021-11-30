#include <iostream>
#include <queue>


using namespace std;

struct Edge {
	bool** arr_edges;
	int count = 0;

	Edge() {
		arr_edges = new bool*[1];
		arr_edges[0] = new bool;
		arr_edges[0][0] = false;
		count = 1; }
	Edge(int n) {
		arr_edges = new bool* [n];
		for (int i = 0; i < n; i++) {
			arr_edges[i] = new bool[n];			
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) arr_edges[i][j] = false;
		count = n;
	}
	~Edge() {
		delete[] arr_edges;
	}

	void add_node(int beg, int end);
	void print();
	bool connected_graph();
	void short_distance(int beg, int end);
	
};

void Edge::add_node(int beg, int end) {
	
	if (beg > count && (end <= count || beg == end)) {  // добавление нового узла
		bool** tmp = new bool* [beg];
		for (int i = 0; i < beg; i++) {
			tmp[i] = new bool[beg];
			
		}
		for (int i = 0; i < beg; i++)
			for (int j = 0; j < beg; j++) tmp[i][j] = 0;
		for (int i = 0; i < count; i++)
			for (int j = 0; j < count; j++) tmp[i][j] = arr_edges[i][j];
		
		if (end != 0 && tmp[end - 1][end - 1] == 1) {
			cout << "Ошибка: Невозможно привязать к бессвязному узлу.\n";
			
		}
		else if (beg == end) tmp[beg-1][beg-1] = 1; // если узел бессвязный
		else {
			tmp[beg-1][end-1] = 1;
			tmp[end-1][beg-1] = 1;
		}

		count = beg;
		arr_edges = tmp;

		
	}
	else if (beg <= count && end <= count) { // добавление пути к существующему узлу
		{
			if (arr_edges[end - 1][end - 1] == 1) {
				cout << "Ошибка: Невозможно привязать к бессвязному узлу.\n";

			}
			else {
				if (arr_edges[beg - 1][beg - 1] == 1)
				{
					arr_edges[beg - 1][beg - 1] = 0;
					arr_edges[beg - 1][end - 1] = 1;
					arr_edges[end - 1][beg - 1] = 1;
				}
				else 
				{					
					arr_edges[beg - 1][end - 1] = 1;
					arr_edges[end - 1][beg - 1] = 1;
				}
			}
		}

	}
	else cout << "Ошибка: " << end << " данного узла не существует.\n";
	
}

bool Edge::connected_graph() {	
	for (int i = 0; i < count; i++)
		if (arr_edges[i][i] == 1) return false;
	return true;
}

void Edge::print() {
	
	queue<int> Q;
	int* marks = new int[count];
	for (int i = 0; i < count; i++)marks[i] = 0;
	Q.push(0);
	while (!Q.empty()) {
		int tmp = Q.front();
		Q.pop();
		marks[tmp] = 2;
		for (int i = 0; i < count; i++) {
			if (marks[i] == 0 && arr_edges[tmp][i] == 1) {				
				Q.push(i);
				marks[i] = 1;			
			}
		}
		cout << tmp + 1 << " \n";
	}

	cout << "Список бессвязных узлов:\n";
	for (int i = 0; i < count; i++)
		if (marks[i] == 0 && arr_edges[i][i] == 1) cout << i + 1 << endl;

	cout << "Таблица узлов:\n";
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++)
			if (arr_edges[i][j] == false) cout << 0 << ' ';
			else cout << 1 << ' ';
		cout << endl;
	}


}

void Edge::short_distance(int beg, int end) {
	if (beg > count || end > count || beg <= 0 || end <= 0) {
		cout << "Ошибка\n";
		return ;
	}
	else {
		bool* visited = new bool[count];
		int* distance = new int [count];
		int* arr = new int[count];
		int mn, u;		
		
		for (int i = 0; i < count; i++) {
			distance[i] = INT_MAX;
			visited[i] = false;
			arr[i] = -1;
			
		}
		distance[beg - 1] = 0;
		for (int i = 0; i < count; i++) {
			mn = INT_MAX, u = -1;
			for (int j = 0; j < count; j++)
				if (!visited[j] && distance[j] < mn) {
					mn = distance[j], u = j;
				}
			if (u == -1) break;
			visited[u] = true;
			for (int j = 0; j < count; j++)
				if (distance[j] > distance[u] + arr_edges[u][j] && arr_edges[u][j] > 0)
					distance[j] = distance[u] + arr_edges[u][j], arr[j] = u;
		}

		
			
		cout << "Кратчайший путь: " << distance[end - 1] << endl;		
		
		vector<int> path;
		
		if (arr[end - 1] == -1) cout << "Нет пути\n";
		else {
			for (int u = end - 1; u != -1; u = arr[u]) path.push_back(u);
			reverse(path.begin(), path.end());
			for (int i = 0; i < path.size(); i++) {
				if (i > 0) cout << " -> ";
				cout << path[i]+1;
			}
			cout << endl;
		}		
		
	}
	
}

int main() {
	setlocale(LC_ALL, "rus");

	Edge test;
	
	int key;
	do {
		cout << "Выберите опцию:\n[1] Вывести граф\n[2] Добавить узел/связь\n[3] Определить связный ли граф\n[4] Вывести кратчайший путь от одной вершины к другой\n[0] Выход\n>> ";
		cin >> key;
		switch (key) {
		case 1: {
			system("cls");
			test.print();
			break;
		}
		case 2: {
			system("cls");
			int a, b;
			cout << "Введите новый узел: ";
			cin >> a;
			cout << "С каким существующим узлом соединить? (Введите 0 для бессвязного узла): ";
			cin >> b;
			if (b == 0) test.add_node(a, a);
			else test.add_node(a, b);
			break;
		}
		case 3: {
			system("cls");
			cout << (test.connected_graph() == 1 ? "Граф связный\n" : "Граф несвязный\n");
			break;
		}
		case 4: {
			system("cls");
			cout << "Введите два существующих узла: ";
			int a, b;
			cin >> a >> b;
			test.short_distance(a, b);
			break;
		}
		}

	} while (key);



	return 0;
}
