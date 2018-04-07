#include <iostream>
#include <vector>
#include <assert.h>

/*Во всех задачах данного раздела необходимо реализовать и использовать локальную
пирамидальную сортировку ​(без использования дополнительной памяти). Общее время работы
алгоритма O(n log n).
 3_3. Закраска прямой 1.
На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого
отрезка (Li и Ri). Найти длину окрашенной части числовой прямой.

In:
3
1 4
7 8
2 5

Out:
5

*/

template<class T>
void SiftDown(T *arr, int i, int count_elem, bool (*isLess)(const T &, const T &)) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;
    if (left < count_elem && isLess(arr[left], arr[i]))
        largest = left;
    if (right < count_elem && isLess(arr[right], arr[largest]))
        largest = right;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        SiftDown(arr, largest, count_elem, isLess);
    }
}

template<class T>
void BuildHeap(T *arr, int count_elem, bool (*isLess)(const T &, const T &)) {
    for (int index = count_elem / 2 - 1; index >= 0; --index) {
        SiftDown(arr, index, count_elem, isLess);
    }
}

template<class T>
void HeapSort(T *a, int left, int right, bool (*isLess)(const T &, const T &)) {
    int heapSize = right - left;
    BuildHeap(a, heapSize, isLess);
    while (heapSize > 1) {
        std::swap(a[0], a[heapSize - 1]);
        heapSize--;
        SiftDown(a, 0, heapSize, isLess);
    }
}

struct line {
    int left,right;
    line(int l=0, int r=0):left(l), right(r) {}
};

bool line_cmp(const line& l, const line& r) {
    return l.left > r.left;
}

int max_length(const std::vector<line>& range) {
    int len = range[0].right - range[0].left;
    int r = range[0].right;

     for (int i = 1; i < range.size(); ++i) {
         if (range[i].left > r) { //если отрезки не пересекаются
             r = range[i].right ;
             len += r - range[i].left;
         }
         if (range[i].left <= r && range[i].right  > r) { // если есть пересечение,
                                                          // но правая часть выходин за пересечение
             len += range[i].right  - r;
             r = range[i].right ;
         }
    }

    return len;
}

int main() {
    int n = 0;
    std::cin >> n;

    std::vector<line> lines;
    line curr_line;

    for (int i = 0; i < n; ++i) {
        std::cin >> curr_line.left >> curr_line.right;
        lines.push_back(curr_line);
    }

    HeapSort(&lines[0], 0, lines.size(), line_cmp);
    std::cout << max_length(lines);

    return 0;
}
