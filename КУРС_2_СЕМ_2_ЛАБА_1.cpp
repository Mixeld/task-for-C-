// КУРС_2_СЕМ_2_ЛАБА_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <stdexcept>
#include <locale.h>


using namespace std;


class two_dimensional_array{                //класс реализующий матрицу при помощи двумерного массива
private:
    int** data;
    int rows;
    int cols;

    int determinant_for_cube() const {
        return data[0][0] * data[1][1] * data[2][2] +
            data[0][1] * data[1][2] * data[2][0] +
            data[0][2] * data[1][0] * data[2][1] -
            data[0][2] * data[1][1] * data[2][0] -
            data[0][0] * data[1][2] * data[2][1] -
            data[0][1] * data[1][0] * data[2][2];
    }

public:
    two_dimensional_array (int r, int c) : rows(r), cols(c) {
        data = new int* [rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = 0;
            }
        }
    }

    ~two_dimensional_array() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    void input() {
        cout << "Введите элементы матрицы (" << rows << "x" << cols << "):\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << "Введите значение элемента [" << i + 1 << "][" << j + 1 << "]" << endl;
                cin >> data[i][j];
            }
        }
    }

    void display() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    int get(int i, int j) const {
        return data[i][j];
    }

    void set(int i, int j, int value) {
        data[i][j] = value;
    }

    two_dimensional_array multiply(const two_dimensional_array& other) const {
        if (cols != other.rows) {
            throw invalid_argument("Невозможно перемножить матрицы: количество столбцов первой матрицы не равно количеству строк второй.");
        }

        two_dimensional_array result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                for (int k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    
    two_dimensional_array transpon() const {
        two_dimensional_array result(cols, rows); // Меняем местами строки и столбцы
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[j][i] = data[i][j]; // Переворачиваем
            }
        }
        return result;
    }

    two_dimensional_array minus(const two_dimensional_array& other) {
        if ((cols != other.cols) && (rows != other.rows)) {
            throw invalid_argument("Невозможно перемножить матрицы: количество столбцов первой матрицы не равно количеству строк второй.");
        }

        two_dimensional_array result(rows, cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    two_dimensional_array sum (const two_dimensional_array& other) {

        if ((cols != other.cols) && (rows != other.rows)) {
            throw invalid_argument("Невозможно перемножить матрицы: количество столбцов первой матрицы не равно количеству строк второй.");
        }

        two_dimensional_array result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    

    two_dimensional_array minor_finder(int exclude_row, int exclude_col) const {
        two_dimensional_array minor(rows - 1, cols - 1);

        int mi = 0;
        for (int i = 0; i < rows; ++i) {
            if (i == exclude_row) continue;

            int mj = 0;
            for (int j = 0; j < cols; ++j) {
                if (j == exclude_col) continue;

                minor.data[mi][mj] = data[i][j]; // прямой доступ, если внутри класса
                ++mj;
            }
            ++mi;
        }

        return minor;
    }


    int determinant() const {
        if (rows != cols) {
            throw invalid_argument("Определитель можно вычислить только для квадратной матрицы.");
        }

        if (rows == 1) {
            return data[0][0];
        }

        if (rows == 2) {
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        }
        if (rows == 3) {
            determinant_for_cube();
        }
        int det = 0;
        for (int j = 0; j < cols; ++j) {
            two_dimensional_array minor = minor_finder(0, j); // исключаем строку 0 и столбец j
            int sign = (j % 2 == 0) ? 1 : -1;
            det += sign * data[0][j] * minor.determinant(); // рекурсивный вызов
        }

        return det;
    }
    
};

class one_demensional_array {               //класс реализующий матрицу при помощи одномерного массива
private:
    int* massive;
    int row;
    int column;

public:
    // Конструктор
    one_demensional_array(int row, int col) : row(row), column(col) {
        massive = new int[row * col](); // Инициализация нулями
    }

    // Деструктор
    ~one_demensional_array() {
        delete[] massive;
    }

    // Копирующий конструктор
    one_demensional_array(const one_demensional_array& other): row(other.row), column(other.column) {
        massive = new int[row * column];
        for (int i = 0; i < row * column; ++i) {
            massive[i] = other.massive[i];
        }
    }

    // Оператор присваивания
    one_demensional_array& operator=(const one_demensional_array& other) {
        if (this == &other) return *this; // Защита от самоприсваивания

        delete[] massive;

        row = other.row;
        column = other.column;
        massive = new int[row * column];
        for (int i = 0; i < row * column; ++i) {
            massive[i] = other.massive[i];
        }

        return *this;
    }

    // Ввод элементов
    void input() {
        cout << "Введите элементы матрицы (" << row << " x " << column << "):\n";
        for (int i = 0; i < row * column; ++i) {
            cin >> massive[i];
        }
    }

    // Вывод матрицы
    void display() const {
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                cout << massive[i * column + j] << " ";
            }
            cout << endl;
        }
    }

    // Умножение матриц
    one_demensional_array multiply(const one_demensional_array& other) const {
        if (column != other.row) {
            throw invalid_argument("Невозможно перемножить матрицы: количество столбцов первой матрицы не равно количеству строк второй.");
        }

        one_demensional_array result(row, other.column);

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < other.column; ++j) {
                for (int k = 0; k < column; ++k) {
                    result.massive[i * other.column + j] +=
                        massive[i * column + k] * other.massive[k * other.column + j];
                }
            }
        }

        return result;
    }
};

void multiply_menu() {
    int r1, c1, r2, c2;
    cout << "Введите количество строк и столбцов первой матрицы: ";
    cin >> r1 >> c1;
    two_dimensional_array matrix1(r1, c1);
    matrix1.input();

    cout << "Введите количество строк и столбцов второй матрицы: ";
    cin >> r2 >> c2;
    two_dimensional_array matrix2(r2, c2);
    matrix2.input();

    try {
        two_dimensional_array result = matrix1.multiply(matrix2);
        cout << "Результат перемножения матриц:" << endl;
        result.display();
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
    }
}

void determinant_fun() {
    while (true){
        
        int n1, n2, c1, c2;
        c1 = 0;
        cout << "Введите размеры матрицы" << endl;
        if (c1 == 0) {
            cout << "Notification: Помните, для нохождения определителся матрица должна быть квадратной" << endl;
        }
        c1 = c1 + 1;
        cin >> n1 >> n2;
        if (n1 != n2) {
            cout << "Матрица должна быть квадратной! Попробуйте ввести размеры снова" << endl;
        }
        else {
            two_dimensional_array matrix(n1, n2);
            matrix.input();
            matrix.display();

            int det = matrix.determinant();
            cout << "Определитель: " << det << endl;
            cout << "Хотите расчитать определитель ещё раз?" << endl << "1 - продолжить, 0 - вернуться в меню ";
            cin >> c2;
            if (c2 == 0) {
                break;
            }
            else if (c2 == 1) {
                continue;
            }
        }
    }
    
    
}

void transpon_menu() {
    int r, c;
    cout << "Введите количество строк и столбцов матрицы: ";
    cin >> r >> c;

    two_dimensional_array A(r, c);
    A.input();

    cout << "Исходная матрица:\n";
    A.display();

    two_dimensional_array At = A.transpon();
    cout << "Транспонированная матрица:\n";
    At.display();
}

void sum_menu() {
    int r1, c1, r2, c2;
    cout << "Введите количество строк и столбцов первой матрицы: ";
    cin >> r1 >> c1;
    two_dimensional_array matrix1(r1, c1);
    matrix1.input();

    cout << "Введите количество строк и столбцов второй матрицы: ";
    cin >> r2 >> c2;
    two_dimensional_array matrix2(r2, c2);
    matrix2.input();

    try {
        two_dimensional_array result = matrix1.sum(matrix2);
        cout << "Результат перемножения матриц:" << endl;
        result.display();
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
    }
}

void minus_menu() {
    int r1, c1, r2, c2;
    cout << "Введите количество строк и столбцов первой матрицы: ";
    cin >> r1 >> c1;
    two_dimensional_array matrix1(r1, c1);
    matrix1.input();

    cout << "Введите количество строк и столбцов второй матрицы: ";
    cin >> r2 >> c2;
    two_dimensional_array matrix2(r2, c2);
    matrix2.input();

    try {
        two_dimensional_array result = matrix1.minus(matrix2);
        cout << "Результат перемножения матриц:" << endl;
        result.display();
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
    }
}

void two_dimensional_massive() {
    int choise;
    while (true) {
        cout << "1. Умножение матрицы" << endl << "2. Транспонирование матрицы" << endl << "3. Суммирование" << endl << "4.Вычетание " << endl << "5. Нахождение определителя матрицы" << endl << "0. Выход" <<endl;
        cin >> choise;

        if (choise == 1) {
            multiply_menu();
        }

        else if (choise == 2) {
            transpon_menu();
        }

        else if (choise == 3) {
            sum_menu();
        }
        else if (choise == 4) {
            minus_menu();
        }
        else if (choise == 5) {
            determinant_fun();
        }

        else if (choise == 0) {
            cout << "Выход из раздела!" << endl;
            break;
        }
    }    
}   

void one_dimensional_massive() {
    int r1, c1, r2, c2;

    cout << "Введите количество строк и столбцов первой матрицы: ";
    cin >> r1 >> c1;
    one_demensional_array A(r1, c1);
    A.input();

    cout << "Введите количество строк и столбцов второй матрицы: ";
    cin >> r2 >> c2;
    one_demensional_array B(r2, c2);
    B.input();

    try {
        one_demensional_array C = A.multiply(B);
        cout << "Результат перемножения:\n";
        C.display();
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
    }

}

int main() {
    setlocale(LC_ALL, "Rus");

    while (true){
        cout << "Выберите вариант работы с памятью" << endl << "1. Двумерный массив" << endl << "2. Одноменрный массив" << endl << "0. Выход из программы" << endl;
        int choise;
        cin >> choise;
        if (choise == 1) {
            two_dimensional_massive();
        }
        else if (choise == 2) {
            one_dimensional_massive();

        }
        else if (choise == 0) {

            cout << endl << " ВЫХОД ИЗ ПРОГРАММЫ";
            break;

        } else {

            cout << "Выбирайте существующий вариант";

        }
    }

    return 0;

}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
