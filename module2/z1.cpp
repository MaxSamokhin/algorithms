#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <time.h>

/*
Во всех вариантах данной задачи необходимо реализовать и использовать сортировку
вставками​. Функция сравнения или оператор сравнения или функтор должен быть явно
определен и передаваться в функцию сортировки.

1_4. Строки.
Напишите программу, печатающую набор строк в лексикографическом порядке.
Строки разделяются символом перевода строки '\n'. Если последний символ в потоке ввода '\n',
считать, что после него нет пустой строки. Максимальная длина строки 255 символов. Написать
свою функцию сравнения строк.

in:
4
caba
abba
ab
aba

out:
ab
aba
abba
caba

*/

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


bool strcmp(const std::string &s1, const std::string &s2) {
     std::string::const_iterator it1 = s1.begin();
     std::string::const_iterator it2 = s2.begin();

    std::string::const_iterator it1_end = s1.end();
    std::string::const_iterator it2_end = s2.end();

    while (it1 != it1_end && it2 != it2_end) {
        if (*it1 < *it2) {
            return true;
        } else if (*it1 > *it2) {
            return false;
        }
        it1++;
        it2++;
    }

    return s1.size() < s2.size();
}

int main() {
    int n = 0;
    std::cin >> n;

    std::vector<std::string> lines;

    std::string curr_world;
    for (int i = 0; i < n; ++i) {
        std::cin >> curr_world;
        lines.push_back(curr_world);
    }

    insertion_sort(&lines[0], 0, lines.size(), strcmp);

    for (int i = 0; i < n; ++i) {
        std::cout << lines[i] << std::endl;
    }
    return 0;
}
