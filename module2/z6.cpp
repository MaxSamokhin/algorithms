#include <iostream>
#include <vector>

/*
 *6_3. Binary MSD для long long.
Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше ...
Отсортировать массив методом MSD по битам (бинарный QuickSort).

In 
3
4 1000000 7
Out
4 7 1000000

*/

//Проверка наличия единицы в раряде под номером индекс
long long digit( long long number, int index ) {
    return (number >> index) & 1;
}

template <class T>
void BinaryQuickSort( T* a, int left, int right, int w) {
    if( right <= left || w < 0 )
        return;

    int i = left;
    int j = right;

    while( i != j ) {
        while( digit( a[i], w ) == 0 && i < j )
            ++i;
        while( digit( a[j], w ) == 1 && i < j )
            --j;
        std::swap( a[i], a[j] );
    }

    if(  digit( a[right], w ) == 0 )
        ++j;
    BinaryQuickSort( a, left, j - 1, w - 1 );
    BinaryQuickSort( a, j, right, w - 1 );
}

int main() {
    std::vector<int> arr;
    int curr_elem = 0;
    while (std::cin >> curr_elem) {
        arr.push_back(curr_elem);
    }

    BinaryQuickSort( &arr[0] , 0, arr.size() - 1, 127);

    for (int i = 9; i < arr.size(); i+=10) {
        std::cout << arr[i] << " ";
    }
    return 0;
}
