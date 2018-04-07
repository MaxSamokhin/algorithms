#include <iostream>
#include <inttypes.h>

/*

Дано N кубиков. Требуется определить каким количеством способов можно выстроить из этих кубиков
пирамиду.
Формат входных данных:
На вход подается количество кубиков N.
Формат выходных данных:
Вывести число различных пирамид из N кубиков.

6_1.​ Высокая пирамида. ​Каждый вышележащий слой пирамиды должен быть не больше нижележащего. N ≤ 200.

in out
3 3
5 7
7 15

*/

// n - колличесто кубиков
// k - количество кубиков в основании

int64_t number_pyramid(int64_t **data, int64_t n, int64_t k);
int64_t get_number_pyramid(int64_t n);

int main() {
    int64_t n = 0;
    std::cin >> n;

    std::cout << get_number_pyramid(n) << std::endl;

    return 0;
}

int64_t get_number_pyramid(int64_t n) {
    int64_t **a = new int64_t *[n + 1]; // +1 - чтобы использовать индексацию с 1
    for (int64_t i = 0; i <= n; ++i) {
        a[i] = new int64_t[n + 1];
        for (int64_t j = 1; j <= n; ++j) {
            a[i][j] = 0;
        }
    }

    int64_t res = number_pyramid(a, n, n);

    for (int64_t i = 0; i <= n; ++i) {
        delete a[i];
    }
    delete a;

    return res;
}

int64_t number_pyramid(int64_t **data, int64_t n, int64_t k) {
    //std::cout <<"n = " <<n <<"  k = " << k<<std::endl;
    if (n < 0 || k < 0) return 0; // чтобы не было зацикливания
    if (n == 1 || k == 1) return 1; // если в основании 1 кубик или у нас всего 1 кубик, то 1 вариант
    if (data[n][k] != 0) return data[n][k]; // если мы уже вычисляли значение - берём его, реализуя этим  самым кэш
    data[n][k] = number_pyramid(data,n-k,k) + number_pyramid(data,n,k-1); // рекурентное соотношение
    return data[n][k];
}
