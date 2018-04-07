#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <cstring>

/*
  7_1.​ Атлеты.
В город N приехал цирк с командой атлетов. Они хотят удивить горожан города N — выстроить из своих тел
башню максимальной высоты. Башня — это цепочка атлетов, первый стоит на земле, второй стоит у него на
плечах, третий стоит на плечах у второго и т.д.Каждый атлет характеризуется силой si (kg) и массой mi
(kg). Сила — это максимальная масса, которую атлет способен держать у себя на плечах.
К сожалению ни один из атлетов не умеет программировать, так как всю жизнь они занимались физической
 подготовкой, и у них не было времени на изучение языков программирования. Помогите им, напишите программу,
 которая определит максимальную высоту башни, которую они могут составить. Известно, что если атлет тяжелее, то он и сильнее:
если mi>mj, то si > sj
Атлеты равной массы могут иметь различную силу.
Формат входных данных:
Вход содержит только пары целых чисел — массу и силу атлетов. Число атлетов 1 ≤ n ≤ 100000. Масса и
сила являются положительными целыми числами меньше, чем 2000000.
Формат выходных данных:
Выход должен содержать натуральное число — максимальную высоту башни.

in:
3 4
2 2
7 6
4 5 

out:
3
 */
struct athlete {
    int weight;
    int force;
};

template<class Type>
class my_vector {
public:
    typedef Type* Iterator;
    Iterator begin();
    Iterator end();
    my_vector();
    my_vector(const my_vector<Type> &obj);
    my_vector& operator=(const my_vector<Type> &obj);
    void push_back(Type val);
    size_t size();
    bool empty();
    Type pop_back();
    Type operator[](size_t index);
    ~my_vector();

private:
    size_t Size; // следующий незаполненный элемент!
    size_t Capacity;
    Type *Data;

    void realloc_data();
};

template<class Type>
typename my_vector<Type>::Iterator my_vector<Type>::begin() {
    return Data;
}

template<class Type>
typename my_vector<Type>::Iterator my_vector<Type>::end() {
    return Data + size();
}

template<class Type>
my_vector<Type>::my_vector() {
    Size = 0;
    Capacity = 8;
    Data = new Type[Capacity];
}

template<class Type>
my_vector<Type>::my_vector(const my_vector<Type> &copy):Size(copy.Size), Capacity(copy.Capacity), Data(new Type[Capacity]) {
    std::copy(copy.Data, copy.Data + copy.Size, Data);
    //memmove( Data, copy.Data, Size * sizeof(Data[0]) );
}

template<class Type>
my_vector<Type> &my_vector<Type>::operator=(const my_vector<Type> &obj) {
    delete Data;
    Size = obj.Size;
    Capacity = obj.Capacity;
    Data = new Type[Capacity];
    std::copy(obj.Data, obj.Data + obj.Size, Data);
    //memmove( Data, obj.Data, Size * sizeof(Data[0]) );
    return *this;
}

template<class Type>
void my_vector<Type>::push_back(Type val) {
    if(Size == Capacity){ realloc_data(); }
    Data[Size] = val;
    ++Size;
}

template<class Type>
size_t my_vector<Type>::size() {
    return Size;
}

template<class Type>
bool my_vector<Type>::empty() {
    return Size == 0;
}

template<class Type>
Type my_vector<Type>::pop_back() {
    assert(Size > 0);
    --Size;
    Type val = Data[Size];
    return val;
}

template<class Type>
Type my_vector<Type>::operator[](size_t index) {
    assert( index >= 0 );
    assert( index < Size);
    return Data[index];
}

template<class Type>
my_vector<Type>::~my_vector() {
    delete Data;
}

template<class Type>
void my_vector<Type>::realloc_data() {
    size_t new_capacity = 2 * Capacity;
    Type *new_data = new Type[new_capacity];

    std::copy(Data, Data + Capacity, new_data);
    //memmove( Data, new_data, Size * sizeof(Data[0]) );
    delete[] Data;

    Data = new_data;
    Capacity = new_capacity;
}

/*
void sort_weight(std::vector<athlete> &ath) {
    int i, j, flag = 1;
    athlete buff_ath;
    size_t len = ath.size();
    for (i = 1; (i <= len) && flag; i++) {
        flag = 0;
        for (j = 0; j < len - 1; j++) {
            if (ath[j + 1].weight < ath[j].weight) {
                buff_ath = ath[j];
                ath[j] = ath[j + 1];
                ath[j + 1] = buff_ath;
                flag = 1;
            }
        }
    }
    return;
}*/

bool cmp_athlete(athlete a, athlete b) {
    return (a.weight < b.weight) || (a.force < b.force);
}



int main() {
    /*
    std::vector<athlete> athlets;
    int curr_weight = 0;
    int curr_force = 0;

    while (std::cin >> curr_weight >> curr_force) {
        athlete curr_athlete = {curr_weight, curr_force};
        athlets.push_back(curr_athlete);
    }
    //выделили самых сильных и легких - по убыванию веса - сверху самые легкие
    //sort_weight(athlets);

    std::sort(athlets.begin(), athlets.end(), cmp_athlete);

    int height = 0;
    int weight_tower = 0;
    // атлет должен поднимать массу стоящих на нем athlets[i].power > weight_tower
    //  будем ставить легких атлетов, пока сильные смогут их поднимать

    for (athlete ath: athlets) {
        if (weight_tower <= ath.force) {
            weight_tower += ath.weight;
            height++;
        }
    }

    std::cout << height;
     */

    my_vector<athlete> athlets;
    int curr_weight = 0;
    int curr_force = 0;

    while (std::cin >> curr_weight >> curr_force) {
        assert(curr_weight > 0);
        assert(curr_force > 0);
        athlete curr_athlete = {curr_weight, curr_force};
        athlets.push_back(curr_athlete);
    }

    std::sort(athlets.begin(), athlets.end(), cmp_athlete);

    /*int i = 0;
    while (!athlets.empty()) {
        std::cout << athlets[i].weight <<" " <<athlets[i].force <<std::endl;
        i++;
    }*/

    int height = 0;
    int weight_tower = 0;

    // атлет должен поднимать массу стоящих на нем athlets[i].force > weight_tower
    //  будем ставить легких атлетов, пока сильные смогут их поднимать
    // если массы равны, берем атлетов с малой силой

    for(int i = 0; i < athlets.size(); i++) {
        if (weight_tower <= athlets[i].force) {
            weight_tower += athlets[i].weight;
            height++;
        }
    }

    std::cout << height;

    return 0;
}
