#include <iostream>
#include <cmath>
#include <functional>

using namespace std;

double func_1(double x) {
	return sqrt(1 + 2 * (x*x) - (x*x*x));
}

double func_2(double x) {
	return cos(x) / (x + 2);
}

double func_3(double x) {
	return 4 / x - 5 * pow(x, 4) + 2 * sqrt(x);
}

function<double(double)> f_1 = func_1; // преобразуем функции, как аргументы
function<double(double)> f_2 = func_2; 
function<double(double)> f_3 = func_3; 

double trapezoidalIntegral(double a, double b, int n, const function<double(double)>& f) {
    const double width = (b - a) / n;
    double x1, x2;
    double* arr_f = new double[n+1];
    double* arr_x = new double[n+1];

    for (int i = 0; i <= n; i++) {
        arr_f[i] = INT_MAX;
        arr_x[i] = 0;
    }

    double trapezoidal_integral = 0;
    for (int step = 0; step < n; step++) {
        if (arr_f[step] == INT_MAX) {
            x1 = a + step * width;
            x2 = a + (step + 1) * width;
            arr_x[step + 1] = x2;
            arr_f[step + 1] = f(x2);
            trapezoidal_integral += 0.5 * (x2 - x1) * (f(x1) + arr_f[step+1]);
        }
        else {
            x2 = a + (step + 1) * width;
            arr_x[step + 1] = x2;
            arr_f[step + 1] = f(x2);
            trapezoidal_integral += 0.5 * (x2 - arr_x[step]) * (arr_f[step] + arr_f[step+1]);
        }
        
    }
    delete[]arr_x;
    delete[]arr_f;

    return trapezoidal_integral;
}

double rounded(double x, int scope) {
    int t = pow(10, scope);
    return round(x * t) / t;
}

double trapezoidalIntegral(double a, double b, int n, const function<double(double)>& f, int scope) {
    const double width = (b - a) / n;
    double x1, x2;
    double* arr_f = new double[n+1];
    double* arr_x = new double[n+1];

    for (int i = 0; i <= n; i++) {
        arr_f[i] = INT_MAX;
        arr_x[i] = 0;
    }

    double trapezoidal_integral = 0;
    for (int step = 0; step < n; step++) {
        if (arr_f[step] == INT_MAX) {
            x1 = a + step * width;
            x2 = a + (step + 1) * width;
            arr_x[step + 1] = x2;
            arr_f[step + 1] = rounded(f(x2),scope);
            trapezoidal_integral += 0.5 * (x2 - x1) * (rounded(f(x1),scope) + arr_f[step+1]);
        }
        else {
            x2 = a + (step + 1) * width;
            arr_x[step + 1] = x2;
            arr_f[step + 1] = rounded(f(x2),scope);
            trapezoidal_integral += 0.5 * (x2 - arr_x[step]) * (arr_f[step] + arr_f[step+1]);
        }
        
    }
    delete[]arr_x;
    delete[]arr_f;

    return rounded(trapezoidal_integral,scope);
}

int main() {

    setlocale(LC_ALL, "rus");

    int key;
    do {
        cout << "[1] Интеграл sqrt(1 + 2 * (x*x) - (x*x*x))\n[2] Интеграл cos(x) / (x + 2)\n[3] Интеграл 4 / x - 5 * pow(x, 4) + 2 * sqrt(x)\n[0] Выход\n>> ";
        cin >> key;
        switch (key) {
        case 1: {
            system("cls");
            cout << "[1] Посчитать подынтегральную функцию в точке x\n[2] Вычислить интеграл на отрезке при n разбиениях\n>> ";
            int pick;
            cin >> pick;
            switch (pick) {
            case 1: {
                system("cls");
                cout << "sqrt(1 + 2 * (x*x) - (x*x*x))\nВведите х: ";
                double x;
                cin >> x;
                cout << "Результат: " << func_1(x) << endl;
                system("pause");
                break;
            }
            case 2: {
                system("cls");
                cout << "sqrt(1 + 2 * (x*x) - (x*x*x))\nВведите отрезок: ";
                double a, b;
                cin >> a >> b;
                cout << "Введите кол-во разбиений: ";
                int n;
                cin >> n;
                cout << "Округлить результат? Y/N\n>> ";
                char k;
                cin >> k;
                if (k == 'Y') {
                    cout << "Введите кол-во цифр после запятой: ";
                    int r;
                    cin >> r;
                    cout << "Результат: " << trapezoidalIntegral(a, b, n, func_1,r) << endl;
                } else cout << "Результат: " << trapezoidalIntegral(a, b, n, func_1) << endl;
                system("pause");
                break;
            }
            }
            break;

        }

        case 2: {
            system("cls");
            cout << "[1] Посчитать подынтегральную функцию в точке x\n[2] Вычислить интеграл на отрезке при n разбиениях\n>> ";
            int pick;
            cin >> pick;
            switch (pick) {
            case 1: {
                system("cls");
                cout << "cos(x) / (x + 2)\nВведите х: ";
                double x;
                cin >> x;
                cout << "Результат: " << func_2(x) << endl;
                system("pause");
                break;
            }
            case 2: {
                system("cls");
                cout << "cos(x) / (x + 2)\nВведите отрезок: ";
                double a, b;
                cin >> a >> b;
                cout << "Введите кол-во разбиений: ";
                int n;
                cin >> n;
                cout << "Округлить результат? Y/N\n>> ";
                char k;
                cin >> k;
                if (k == 'Y') {
                    cout << "Введите кол-во цифр после запятой: ";
                    int r;
                    cin >> r;
                    cout << "Результат: " << trapezoidalIntegral(a, b, n, func_2, r) << endl;
                }
                else cout << "Результат: " << trapezoidalIntegral(a, b, n, func_2) << endl;
                system("pause");
                break;
            }
            }
            break;

        }

        case 3: {
            system("cls");
            cout << "[1] Посчитать подынтегральную функцию в точке x\n[2] Вычислить интеграл на отрезке при n разбиениях\n>> ";
            int pick;
            cin >> pick;
            switch (pick) {
            case 1: {
                system("cls");
                cout << "4 / x - 5 * pow(x, 4) + 2 * sqrt(x)\nВведите х: ";
                double x;
                cin >> x;
                cout << "Результат: " << func_3(x) << endl;
                system("pause");
                break;
            }
            case 2: {
                system("cls");
                cout << "4 / x - 5 * pow(x, 4) + 2 * sqrt(x)\nВведите отрезок: ";
                double a, b;
                cin >> a >> b;
                cout << "Введите кол-во разбиений: ";
                int n;
                cin >> n;
                cout << "Округлить результат? Y/N\n>> ";
                char k;
                cin >> k;
                if (k == 'Y') {
                    cout << "Введите кол-во цифр после запятой: ";
                    int r;
                    cin >> r;
                    cout << "Результат: " << trapezoidalIntegral(a, b, n, func_3, r) << endl;
                }
                else cout << "Результат: " << trapezoidalIntegral(a, b, n, func_3) << endl;
                system("pause");
                break;
            }
            }
            break;
        }
        default: key = 0;
        }        
        
        system("cls");

    } while (key);

	return 0;
}