/* 7. Быстрейшая сортировка.
Отсортировать массив целых чисел.
Последовательность случайная, максимальный размер 25000000.
Вывести каждое десятое число в отсортированном массиве.
За основу должен быть взят алгоритм быстрой сортировки.
Набор оптимизаций, который необходимо реализовать:
1. Оптимизация выбора опорного элемента.
2. Оптимизация Partition.
3. Оптимизация концевой рекурсии – гибридная сортировка с использованием InsertionSort.
4. Написать без рекурсии.

In 
3 0 2 1 5 4 21 4 6 5
Out  21
*/

#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <assert.h>
#include <vector>

int get_pivot (int left, int right) {
    return left + rand() % (right - left+1);
}

template <class T>
int partition(T* a, int left, int right) {
    int pivotIndex = get_pivot(left, right);
    std::swap(a[left], a[pivotIndex]);

    int it = left + 1;
    int jt = right;

    while (true) {
        while (a[it] < a[left]) {
            ++it;
        }
        while (a[jt] > a[left]) {
            --jt;
        }
        if (it < jt) {
            std::swap(a[it], a[jt]);
            ++it;
            --jt;
        } else {
            --it;
            std::swap(a[left], a[it]);
            return it;
        }
    }
}


bool my_cmp(const int &s1, const int &s2) {
    return s1 < s2;
}


template<class T>
void insertion_sort (T *arr, int l, int r, bool (*isLess)(const T &, const T &)) {
    assert(arr);
    for(int i = l; i < r; i++) {
        T x = arr[i];
        int j = i;
        while (j > 0 && isLess(x, arr[j - 1])) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = x;
    }
}

template <class T>
void quick_sort(T* a, int left, int right, bool (*isLess)(const T &, const T &)) {
    std::stack<std::pair<int, int> > stack;
    stack.push(std::make_pair(left, right));
    while (!stack.empty()) {
        std::pair<int, int> top = stack.top();
        left = top.first;
        right = top.second;
        stack.pop();
        if (right - left <= 10) {
            insertion_sort(a + left, 0, right - left + 1, isLess);
            continue;
        }
        int pivot = partition(a,left,right);
        if (pivot - 1 > left) {
            stack.push(std::make_pair(left, pivot - 1));
        }
        if (pivot + 1 < right) {
            stack.push(std::make_pair(pivot + 1, right));
        }
    }
}

int main() {

//     clock_t start = clock();
//     improved_quick_sort(&arr[0], 0, arr.size(),my_cmp);
//     clock_t end = clock();
//     std::cout << (float)(end - start)/CLOCKS_PER_SEC << std::endl;

    std::vector<int> arr;
    int curr_elem = 0;
    while (std::cin >> curr_elem) {
        arr.push_back(curr_elem);
    }
    //clock_t start = clock();

    srand(time(NULL));
    quick_sort(&arr[0], 0, arr.size()-1, my_cmp);

    //clock_t end = clock();
    //std::cout << "time: " <<(float) (end - start) / CLOCKS_PER_SEC << std::endl;

    for (int i = 9; i < arr.size(); i+=10) {
        std::cout << arr[i] << " ";
    }

    return 0;
}
