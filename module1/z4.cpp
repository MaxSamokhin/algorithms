#include <iostream>
#include <cstring>
#include <assert.h>

/*
Во всех задачах из следующего списка следует написать структуру данных,
обрабатывающую команды push* и pop*.
Формат входных данных.
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана
 для пустой структуры данных, то ожидается “-1”.
Формат выходных данных.
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя
 бы одно ожидание не оправдалось, то напечатать NO.

 4_3. ​Реализовать очередь с помощью двух стеков. Использовать стек,
 реализованный с помощью динамического буфера.
 */

class Stack {
public:
    Stack(int _capacity = 10);
    ~Stack();
    void push(int a);
    int pop();
    bool is_empty() const { return top == -1; }

private:
    int *buff;
    int capacity;
    int top;

    void resize_stack();
};

Stack::Stack(int _capacity) :
        capacity(_capacity),
        top(-1) { // топ - первый заполненный элемент
    buff = new int[_capacity];
}

Stack::~Stack() {
    delete[] buff;
}

void Stack::push(int elem) {
    if (top + 1 == capacity) {
        resize_stack();
    }
    buff[++top] = elem;
}

int Stack::pop() {
    return !is_empty() ? buff[top--] : -1;
}

void Stack::resize_stack() {
    capacity *= 2;
    int *new_buff = new int[capacity];
    memcpy(new_buff, buff, capacity/2 * sizeof(int));
    delete[] buff;
    buff = new_buff;
}


class Queue {
private:
    Stack input;
    Stack output;
    void transportBuff();
public: // реализуем только основной, необходимый интерфейс
    Queue(){};
    void push(int);
    int pop();
};

void Queue::push(int value) {
    input.push(value);
}

int Queue::pop() {
    if (!output.is_empty()) {
        return output.pop();
    } else if (!input.is_empty()) {
        transportBuff();
        return output.pop();
    }
    return -1;
}

void Queue::transportBuff() {
    for (int i = 0; !input.is_empty(); i++) {
        output.push(input.pop());
    }
}

int main() {
    Queue queue;
    int count_command = 0;
    std :: cin >> count_command;
    int a = 0;
    int b = 0;

    for (int i = 0; i < count_command; ++i) {
        std::cin >> a >> b;
        switch (a) {
            case 2:
                if ( queue.pop() != b) {
                    std::cout << "NO";
                    return 0;
                }
                break;
            case 3:
                queue.push(b);
                break;
            default:
                assert(false);
        }
    }
    std::cout << "YES";

    return 0;
}
