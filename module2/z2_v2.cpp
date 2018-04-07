#include <iostream>

#include <assert.h>
#include <vector>

/*

Решение всех задач данного раздела предполагает использование кучи, реализованной в виде
класса.

2_3. Тупики.
На вокзале есть некоторое количество тупиков, куда прибывают электрички. Этот вокзал является
их конечной станцией. Дано расписание движения электричек, в котором для каждой электрички
указано время ее прибытия, а также время отправления в следующий рейс. Электрички в
расписании упорядочены по времени прибытия. Когда электричка прибывает, ее ставят в
свободный тупик с минимальным номером. При этом если электричка из какого-то тупика
отправилась в момент времени X, то электричку, которая прибывает в момент времени X, в этот
тупик ставить нельзя, а электричку, прибывающую в момент X+1 — можно.
В данный момент на вокзале достаточное количество тупиков для работы по расписанию.
Напишите программу, которая по данному расписанию определяет, какое минимальное
количество тупиков требуется для работы вокзала.
Формат входных данных. Вначале вводится n - количество электричек в расписании. Затем
вводится n строк для каждой электрички, в строке - время прибытия и время отправления. Время -
натуральное число от 0 до 10^9. Строки в расписании упорядочены по времени прибытия.
Формат выходных данных. Натуральное число - минимальное количеством тупиков.
Максимальное время: 50мс, память: 5Мб.


in[1]: 
1
10 20

out[1]: 1

in[2]:
2
10 20
20 25

out[2]:
2

in[3]
3
10 20
20 25
21 30

out[3]:
2

*/

template <class T>
class Heap {
public:
    Heap(int bufferSize, bool (*less_func)(const T &, const T &)) : buffer_size(bufferSize), size(0), less_func(less_func) {
        data = new T[bufferSize];
    }

    Heap(T *buffer, int size, bool (*less_func)(const T &, const T &)) : data(buffer), size(size), buffer_size(size), less_func(less_func) {
        for (int i = size/2 - 1; i >= 0; --i) {
            shift_down(i);
        }
    }

    ~Heap() {
        delete[] data;
    }

    int getSize() {
        return size;
    }

    T extract_max() {
        assert(size > 0);
        T result = data[0];
        size--;

        if(size > 0) {
            std::swap(data[0], data[size]);
            shift_down(0);
        }

        return result;
    }

    void add(const T &elem) {
        if(size >=buffer_size )
            realloc_data();

        data[size] = elem;
        shift_up(size);
        size++;

    }

    const T& get_max() {
        assert(size > 0);
        return data[0];
    }


    void print_data() {
        std::cout << "depo: " << std::endl;
        for (int i = 0; i < getSize(); ++i) {
            std::cout << "arr_time: " <<data[i].arr_time << "dep_time: " << data[i].dep_time <<std::endl;
        }
    }
private:
    T* data;
    int size; // количество элементов в куче
    int buffer_size;
    bool (*less_func)(const T &, const T &); // функция сравнения

    void realloc_data() {
        int newBufferSize = (buffer_size < 8) ? 8 : buffer_size * 2;
        T *temp = new T[newBufferSize];
        for(int i = 0; i < buffer_size; i++) {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
        buffer_size = newBufferSize;
    }


    void shift_up(int index) {
        int parent = (index - 1) / 2;
        while (index > 0 ) {
            if (!less_func(data[index], data[parent]))
                return;
            std::swap(data[index], data[parent]);
            index = parent;
        }
    }


    void shift_down(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;
        if( left < size  && less_func(data[left], data[i]) )
            largest = left;
        if( right < size  && less_func(data[right], data[largest]) )
            largest = right;
        if( largest != i ) {
            std::swap(data[i], data[largest]);
            shift_down(largest);
        }
    }

};

struct Train {
    int arr_time; //время прибытия
    int dep_time; // время отправления

    Train () {}
    Train (int arr_time, int dep_time) : arr_time(arr_time), dep_time(dep_time) {}
};


bool isPointLess(const Train &p1, const Train &p2) {
    return p1.dep_time < p2.dep_time;
}

bool isPointLess1(const Train &p1, const Train &p2) {
    return p1.dep_time < p2.arr_time;
}

template<class T>
int get_count_deadlock(T *arr,int l,int r, bool (*less_f)(const T &, const T &) ) {

    Heap<Train> depot(r-l, isPointLess);

    int result = 0;
    for (int i = 0; i < r-l ; i++) {
        if ((depot.getSize() > 0)) {

            // поезд, который будет отправляться из депо (с наименьшим временем отправки) - лежит на вершине кучи
            // пока  поезд на вершине может быть отправлен рашьше, чем прибывает текущий (можем освободить тупик для текущего поезда,
            // гарантируется тем, что входные данные упорядочены по  возрастанию прибытия),
            // то мы можем освободить данный тупик

            while (less_f(depot.get_max(),arr[i]))
                depot.extract_max();
        }
        depot.add(arr[i]);
        if (depot.getSize() > result)
            result = depot.getSize();
    }

    return result;
}

int main() {

    int count_trains;
    std::cin >> count_trains;

    std::vector<Train> train_schedule;
    Train curr_train;

    for (int i = 0; i < count_trains; i++) {
        std::cin >> curr_train.arr_time >> curr_train.dep_time;
        train_schedule.push_back(curr_train);
    }

    std::cout << get_count_deadlock(&train_schedule[0], 0, count_trains, isPointLess1);

    return 0;
}
