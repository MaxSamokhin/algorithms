/*

Задача 1. Хеш-таблица (7 баллов)

Реализуйте структуру данных типа “множество строк” на основе динамической
хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных
латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения
многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте
при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает
3/4.
Структура данных должна поддерживать операции добавления строки в множество,
удаления строки из множества и проверки принадлежности данной строки множеству.

1_2.​ Для разрешения коллизий используйте двойное хеширование.

stdin 
+ hello
+ bye
? bye
+ bye
- bye
? bye
? hello

stdout
OK
OK
OK
FAIL
OK
FAIL
OK

*/
#include <iostream>
#include <string>
#include <vector>

const int DefaultHashTableSize = 8;

int hash1(const std::string &key, int size) {
    int hash = 0;
    for (int i = 0; i < key.size(); i++) {
        hash += (47 * hash + key[i]) % size;
    }
    return hash % size;
}


int hash2(const std::string &key, int size) {
    int hash = 0;
    for (int i = 0; i < key.size(); i++) {
        hash += (73 * hash + key[i]) % size;
    }
    return ((hash << 1) + 1) % size;
}


template<class T>
class HashTable {
public:
    HashTable();

    ~HashTable(){};

    bool add(const std::string &key);

    bool del(const std::string &key);

    bool has(const std::string &key) const;

private:
    std::vector<T> table;
    unsigned int table_size;
    int keysCount;

    void resize();
};

template<class T>
HashTable<T>::HashTable():keysCount(0), table_size(DefaultHashTableSize), table(DefaultHashTableSize, "EMPTY") {}

//template<class T>
//HashTable<T>::~HashTable() {}

template<class T>
bool HashTable<T>::add(const std::string &key) {
    if (((double) keysCount / (double) table_size) >= 0.75) {
        resize();
    }

    int h1 = hash1(key, table_size);
    int h2 = hash2(key, table_size);
    int i = 0;
    int first_del_elem = -1;  // первый удалёный

    while (table[h1] != "EMPTY" && i < table_size) { //ищем позицию для вставки
        if (table[h1] == key) { 
            return false;
        }
        if (table[h1] == "DEL" && first_del_elem < 0) {
            first_del_elem = h1;
        }
        h1 = (h1 + h2) % table_size;
        i++;
    }

    if (first_del_elem >= 0) {   // если встретилась удалёная ячейка, вставляем в неё
        table[first_del_elem] = key;
    } else {
        table[h1] = key;
    }
    keysCount++;
    return true;
}

template<class T>
bool HashTable<T>::del(const std::string &key) {
    int h1 = hash1(key, table_size);
    int h2 = hash2(key, table_size);
    int i = 0;

    while (table[h1] != "EMPTY" && i < table_size) {
        if (table[h1] == key) {
            table[h1] = "DEL";
            keysCount--;
            return true;
        }
        h1 = (h1 + h2) % table_size;
        i++;
    }

    return false;
}

template<class T>
bool HashTable<T>::has(const std::string &key) const {
    int h1 = hash1(key, table_size);
    int h2 = hash2(key, table_size);
    int i = 0;
    while (table[h1] != "EMPTY" && i < table_size) {
        if (table[h1] == key) {
            return true;
        }
        h1 = (h1 + h2) % table_size;
        i++;
    }

    return false;
}

template<class T>
void HashTable<T>::resize() {
    unsigned int new_table_size = table_size * 2;
    std::vector<T> new_table(new_table_size, "EMPTY");

    for (int i = 0; i < table_size; i++) {
        if (table[i] != "EMPTY" && table[i] != "DEL") {

            T data = table[i];
            int h1 = hash1(data, new_table_size);
            int h2 = hash2(data, new_table_size);

            int j = 0;
            while (new_table[h1] != "EMPTY" && j < new_table_size) {
                h1 = (h1 + h2) % new_table_size;
                j++;
            }
            new_table[h1] = table[i];

        }
    }
    table = new_table;
    table_size = new_table_size;
}


int main() {
    HashTable<std::string> table;
    char operation;
    std::string word;
    while (std::cin >> operation >> word) {
        if (operation == '+')
            std::cout << (table.add(word) ? "OK" : "FAIL") << "\n";
        if (operation == '-')
            std::cout << (table.del(word) ? "OK" : "FAIL") << "\n";
        if (operation == '?')
            std::cout << (table.has(word) ? "OK" : "FAIL") << "\n";
    }
    return 0;
}
