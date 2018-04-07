#include <iostream>
#include <assert.h>

/*1_6. ​Дан массив целых чисел A[0..n). Не используя других
  массивов переставить элементы массива A в обратном порядке за O(n).*/

void get_reversal(int* arr, int size) {
    int buff = 0;
    for (int i = 0; i < size / 2; i++) {
        buff = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = buff;
    }
}

void print_arr(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
}

int main() {
    int size_arr = 0;
    std::cin >> size_arr;

    assert(size_arr > 0);

    int* arr = new int[size_arr];

    for (int i = 0; i < size_arr; ++i) {
        std::cin >> arr[i];
    }

    get_reversal(arr, size_arr);
    print_arr(arr, size_arr);
    
    delete [] arr;
    return 0;
}
