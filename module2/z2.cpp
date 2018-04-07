#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>

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

struct Train {
    int arr_time; //время прибытия
    int dep_time; // время отправления
};

class MyHeap {
    public:
        MyHeap(size_t _bufferSize = 8);
        ~MyHeap();

        void add(Train element);
        Train extract_min();

        Train get_min() const;

        bool is_empty();
        int get_size();
        void  print_data();

        int get_result();
    private:

        Train* data;
        size_t buffer_size; // размер выделенного буфера
        int buffer_top;  //следующий элемент - незаполненый или первый заполненый
        int result;

        void realloc_data();
        void sift_down(int i);
        void sift_up(int i);
};

template<class T>
int get_count_deadlock(T *arr, int n) {
    MyHeap depot;
    for (int i = 0; i < n; i++) {
        if (!depot.is_empty()) {
        depot.print_data();
            // поезд, который будет отправляться из депо (с наименьшим временем отправки) - лежит на вершине кучи
            // пока  поезд на вершине может быть отправлен рашьше, чем прибывает текущий (можем освободить тупик для текущего поезда,
            // гарантируется тем, что входные данные упорядочены по  возрастанию прибытия),
            // то мы можем освободить данный тупик

            while (depot.get_min().dep_time < arr[i].arr_time )
                depot.extract_min();
        }
        depot.add(arr[i]);
    }
    return depot.get_result();
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

    std::cout << get_count_deadlock(&train_schedule[0], count_trains);

    return 0;
}


MyHeap::MyHeap(size_t bufferSize) : buffer_size(bufferSize), buffer_top(-1), result(0) {
    data = new Train[bufferSize];
}

MyHeap::~MyHeap() {
    delete[] data;
}

void MyHeap::realloc_data() {
    size_t newBufferSize = (buffer_size < 8) ? 8 : buffer_size * 2;
    Train *temp = new Train[newBufferSize];
    for (int i = 0; i < buffer_size; ++i) {
        temp[i] = data[i];
    }
    delete[] data;
    data = temp;
    buffer_size = newBufferSize;
}


void  MyHeap::print_data() {
    std::cout << "depo: " << std::endl;
    for (int i = 0; i < get_size(); ++i) {
        std::cout << "arr_time: " <<data[i].arr_time << "dep_time: " << data[i].dep_time <<std::endl;
    }
}


void MyHeap::sift_down(int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    // Ищем меньшего  сына, если такой есть. Так как на вершине(в корне) - самый маленький элемент
    int lesser = i;
    if( left < get_size() && data[left].dep_time < data[i].dep_time )
        lesser = left;
    if( right < get_size() && data[right].dep_time < data[lesser].dep_time )
        lesser = right;
    // Если меньший сын есть, то проталкиваем корень в него.
    if( lesser != i ) {
        std::swap(data[i], data[lesser]);
        sift_down(lesser);
    }
}

// проталкиваем наименьший элемент наверх
void MyHeap::sift_up(int i) {
    while(i > 0) {
        int parent = (i - 1)/ 2;
        if(data[i].dep_time >= data[parent].dep_time )
            return;
        std::swap(data[i], data[parent] );
        i = parent;
    }
}

void MyHeap::add(Train element) {
    if (get_size() >= buffer_size)
        realloc_data();
    //кладём новые данные в последний элемент
    data[++buffer_top] = element;
    sift_up(buffer_top); // проталкиваем элемент на нужное место

    if (get_size() > result)
        result = get_size();
}

Train MyHeap::extract_min() { // так как минимум - в корне
    assert(buffer_top >= 0);
    //запоминаем значение корня
    Train result = data[0];
    // Переносим последний элемент в корень.
    data[0] = data[buffer_top];
    --buffer_top;
    // Вызываем SiftDown для корня.
    sift_down(0);
    return result;
}

Train MyHeap::get_min() const {
    return data[0];
}


bool  MyHeap::is_empty() {
    return buffer_top < 0;
}

int MyHeap::get_size() {
    return buffer_top + 1;
}

int MyHeap::get_result() {
    return result;
}
