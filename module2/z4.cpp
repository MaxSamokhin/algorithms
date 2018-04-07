#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
/*
Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n. Требуется
найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом
k (0..n-1) в отсортированном массиве. Напишите нерекурсивный алгоритм.
Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n).
Функцию Partition следует реализовывать методом прохода двумя итераторами в одном
направлении. Описание для случая прохода от начала массива к концу:
● Выбирается опорный элемент. Опорный элемент меняется с последним элементом
массива.
● Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.
Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат
нерассмотренные элементы. Последним элементом лежит опорный.
● Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
● Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
● Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше
        опорного, то сдвигаем j.
Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
● В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.
*/

/*4_4.​ Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition
реализуйте методом прохода двумя итераторами от конца массива к началу.

In 
10 4
1 2 3 4 5 6 7 8 9 10
Out
5

In
10 0
3 6 5 7 2 9 8 10 4 1
Out
1

In
10 9
0 0 0 0 0 0 0 0 0 1
Out
1

*/


int get_random_pos (int left, int right) {
    return left + rand() % (right - left);
}

// Возвращает индекс, на который встанет пивот после разделения.
template <class T>
int partition( T* a, int left, int right, bool (*isLess)(const T &, const T &) ) {
    int rand_pos = get_random_pos(left,right);
    std::swap(a[left], a[rand_pos]);
    int i = right - 1;
    int j = right - 1;

    while ( j!= left) {
        if (isLess(a[j],a[left])) {
            std::swap(a[j],a[i]);
            i--;
        }
        j--;
    }
    std::swap(a[left], a[i]);
    return i;
}

template <class T>
int findKStatistics(T* arr, int l, int r, int k, bool (*isLess)(const T &, const T &)) {
    while (true) {
        int pivotPos = partition(arr, l, r, isLess);
        if (pivotPos > k)
            r = pivotPos;
        if (pivotPos < k)
            l = pivotPos + 1;
        if(pivotPos == k)
            return arr[pivotPos];
    }
}

bool int_cmp(const int& a, const int & b) {
    return a > b;
}

int main() {
    srand(time(0));

    int n = 0, k = 0;
    std::cin >> n >> k;

    std::vector<int> array;
    int value = 0;

    for( int i = 0; i < n; i++ ) {
        std::cin >> value;
        array.push_back(value);
    }

    std:: cout << findKStatistics(&array[0], 0, array.size(), k,  int_cmp);

    return 0;
}
