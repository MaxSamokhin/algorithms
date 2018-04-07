#include <iostream>
#include <vector>
#include <stdint.h>

/*
5_3. Количество инверсий.
Дана последовательность целых чисел из диапазона (-10^9 .. 10^9). Длина последовательности не
больше 10^6. Числа записаны по одному в строке. Количество чисел не указано.
Пусть количество элементов n, и числа записаны в массиве a = a[i]: i из [0..n-1].
Требуется напечатать количество таких пар индексов (i,j) из [0..n-1], что (i < j и a[i] > a[j]).
Указание: количество инверсий может быть больше 4*10^9 - используйте int64_t.

*/


template <class T>
void merge(T* mas, int left, int right, bool (*isLess)(const T &, const T &) ,int64_t& res, T* temp){

    //std::vector<int64_t > temp(right - left + 1);
    int ind_first_arr = left;
    int mid = (left + right) / 2; // индекс середины можно принимать и из merge_sort
    int ind_second_arr = mid + 1;
    int ind_res_arr = 0;

//Слияние 2х чаcтей вектора mas [left, mid], [mid+1, right]

    while (ind_first_arr <= mid && ind_second_arr <= right) {
        if (isLess(mas[ind_first_arr], mas[ind_second_arr])) {
            temp[ind_res_arr++] = mas[ind_first_arr++];
        }
        else {
            res += mid - ind_first_arr + 1;
            temp[ind_res_arr++] = mas[ind_second_arr++];
        }
    }

    while (ind_first_arr <= mid)
        temp[ind_res_arr++] = mas[ind_first_arr++];

    while (ind_second_arr <= right)
        temp[ind_res_arr++] = mas[ind_second_arr++];

   // std::copy(temp.begin(), temp.end(), mas + left);
}

template <class T>
void merge_sort(T* mas, int left, int right, bool (*isLess)(const T &, const T &), int64_t & res) {
    if (left == right)
        return;

    int mid = (left + right) / 2;
    int len_mas = right - left+1;
    merge_sort(mas, left, mid, isLess, res);         // вызовем для левой половины
    merge_sort(mas, mid + 1, right,isLess, res);    // для правой
    //std::vector<int> c(len_mas);
    T* c = new T[len_mas];
    merge(mas, left, right, isLess, res,c);           //слияние
    std::copy(c, c+len_mas, mas + left);
    delete[] c;
}

bool int_cmp(const int & a, const int & b) {
    return a <= b;
}

int main() {
    std::vector<int> arr;

    int value;
    while( true ) {
        std::cin >> value;
        if( std::cin.fail() ) {
            break;
        }
        arr.push_back(value);
    }

    int64_t result = 0;
    merge_sort(&arr[0], 0, arr.size()-1,int_cmp, result);

    std::cout << result;

    return 0;
}
