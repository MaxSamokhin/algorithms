#include <iostream>
#include <math.h>
#include <assert.h>
/*
2_2. ​Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин. Вначале вводится
количество вершин, затем последовательно целочисленные координаты всех вершин в порядке обхода
против часовой стрелки. n < 1000, координаты < 10000.
Указание. Для вычисления площади n-угольника можно посчитать сумму ориентированных площадей
трапеций под каждой стороной многоугольника.
 */

double get_square(const int& num, const int* x, const int* y){
    double curr_square = 0;
    for (int i = 0; i < num; i++) {
        if (i == 0) {
            curr_square += x[i]*(y[num-1] - y[i+1]); //первый элемент, от которого мы считаем - зависит от последнего
        } else if (i == num-1) {
            curr_square += x[i]*(y[i-1] - y[0]); // расчет площади последней трапеции - зависит от координат 1-й точки
        } else {
            curr_square += x[i]*(y[i-1] - y[i+1]); // формула расчёта площади
        }
    }
    curr_square /= 2;
    return fabs(curr_square);
}

int main() {
    int number_vertices = 0;
    std::cin >> number_vertices;

    assert(number_vertices > 2);

    int* x_coord = new int[number_vertices];
    int* y_coord = new int[number_vertices];

    for (int i = 0; i < number_vertices; ++i) {
        std::cin >> x_coord[i];
        std::cin >> y_coord[i];
    }

    double square = get_square(number_vertices, x_coord,y_coord);
    std::cout << square;

    delete[] x_coord;
    delete[] y_coord;

    return 0;
}