#include <iostream>
#include <assert.h>


/*
3_3. ​Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию. A[0..n-1] и B[0..m-1].
n >> m. Найдите их пересечение. Требуемое время работы: O(m * log k), где k - позиция элементта B[m-1] в
массиве A.. В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска
элемента B[i-1].
n, k ≤ 10000.

in:
5
3
1 2 3 4 5
1 3 5

out:
1 3 5

 */

void searchBorders(int *a, int n, int element, int &first, int &last) {
    int index = 1;

    if (index < first)
        index = first;

    for (; index < n && a[index] < element; index *= 2);

    if ((first < index/2))
        first = index / 2;

    last = index > n ? n : index;
}

bool BinarySearch(int *arr, int count, int element,int &pos) {
    int first = pos;
    int last = 0;
    searchBorders(arr, count, element, first, last);
    pos = first;
    int mid = 0;
    while (first < last) {
        mid = (first + last) / 2;
        if (element <= arr[mid])
            last = mid;
        else
            first = mid + 1;
    }
    // Все элементы слева от first строго больше искомого.
    return (first == count || arr[first] != element) ? false : true;
}

int find_intersection(int* Result, int* A, int* B, int n, int m) {
    assert(n >= 0);
    assert(m >= 0);
    assert(n > m);
    int pos_first = 0; // так как массивы упорядочены, начало последующего отрезка поиска для отрезка будем запоминать с предыдущей итерации поиска
    //поиск пересечения
    int count_element_inter = 0;
    for (int i = 0; i < m; ++i) {
        if (BinarySearch(A, n, B[i], pos_first)) {
            Result[count_element_inter] = B[i];
            count_element_inter++;
        }
    }
    return count_element_inter;
}

int main() {
    int n = 0;
    std::cin >> n;
    int m = 0;
    std::cin >> m;

    int *A = new int[n];
    int *B = new int[m];

    for (int i = 0; i < n; ++i)
        std::cin >> A[i];
    for (int i = 0; i < m; ++i)
        std::cin >> B[i];

    int *Result = new int[m];
    int count_element_intersection = find_intersection(Result, A, B, n, m);
    for (int i = 0; i < count_element_intersection; i++)
        std::cout << Result[i] << " ";

    delete[] A;
    delete[] B;
    delete[] Result;
    return 0;
}
