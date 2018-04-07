#include <iostream>
#include <cstring>

/*
Решение всех задач данного раздела предполагает использование стека. Способ реализации стека может
быть любым (список/динамический массив).
5_1. Скобочная последовательность.
Дан фрагмент последовательности скобок, состоящей из символов (){}[].
Требуется определить, возможно ли продолжить фрагмент в обе стороны, получив корректную
последовательность.
Длина исходной последовательности ≤ 200000.
Формат входных данных. Строка, содержащая символы (){}[] и, возможно, перевод строки.
Формат выходных данных. Если возможно - вывести минимальную корректную последовательность, иначе -
напечатать "IMPOSSIBLE​".

in[1]: {}[[[[{}[] out[1]: {}[[[[{}[]]]]]
in[2]: {][[[[{}[] out[2]: IMPOSSIBLE
in[3]: ]()}[](({} out[3]: {[]()}[](({}))

*/

class Stack {
public:
    Stack(int _capacity = 10);
    ~Stack();
    void push(char a);
    char pop();
    bool is_empty() const { return top == -1; }
    int get_size();
private:
    char *buff;
    int capacity;
    int top;

    void resize_stack();
};

Stack::Stack(int _capacity) :
        capacity(_capacity),
        top(-1) { // топ - первый заполненный элемент
    buff = new char[_capacity];
}

Stack::~Stack() {
    delete[] buff;
}

void Stack::push(char elem) {
    if (top + 1 == capacity) {
        resize_stack();
    }
    buff[++top] = elem;
}

char Stack::pop() {
    return !is_empty() ? buff[top--] : 'y';
}

void Stack::resize_stack() {
    capacity *= 2;
    char *new_buff = new char[capacity];
    memcpy(new_buff, buff, capacity/2 * sizeof(buff[0]));
    delete[] buff;
    buff = new_buff;
}

int Stack::get_size() {
    return top + 1;
}

void read_data(Stack* res) {
    char c;
    while( (c=getchar()) != '\n' ) {
        res->push(c);
    }
    return;
}

void print_data(Stack* bracket_data) {
    Stack* res = new(Stack);
    while( !bracket_data->is_empty())
        res->push(bracket_data->pop());
    while( !res->is_empty() )
        std::cout << res->pop();
    delete res;
}


char get_bracket(char ch) {
    switch (ch) {
        case '(':
            return ')';
        case '{':
            return '}';
        case '[':
            return ']';
        case ')':
            return '(';
        case '}':
            return '{';
        case ']':
            return '[';
    }
    return 0;
}

bool get_supplement_brackets(Stack* bracket_data, Stack* res) {
    Stack *reverse = new(Stack);
    //создаим копию, так так будем делать pop()  и мы потеряем данные
    Stack *copy_bracket_data = new(Stack);
    // "перевернем" стек ,чтобы получать элементы в порядке их ввода
    while (!bracket_data->is_empty()) {
        char buff = bracket_data->pop();
        reverse->push(buff);
        copy_bracket_data->push(buff);
    }

    Stack open_bracket(reverse->get_size()/2+1);
    Stack close_bracket(reverse->get_size()/2+1);
    char buff;

    for (int i = 0; !reverse->is_empty(); i++) {
         buff = reverse->pop();
         switch (buff) {
             case '(':
             case '{':
             case '[':
                 //если открывающая скобка - пишим в стек открывающих скобок
                 open_bracket.push(buff);
                 break;
             case ')':
             case '}':
             case ']':
                 // если закрывающая скобка: если в стеке открывающих - лежит скобка -
                 // - сверяем тип последней скобки стека с текущей скобкой
                 if (open_bracket.get_size() == 0) {
                     close_bracket.push(buff);
                 } else {
                     char myChar = get_bracket(open_bracket.pop());
                     if (buff != myChar) {
                         return false;
                     }
                 }
                 break;
         }
     }
    while( !close_bracket.is_empty()) // присоединяем недостоющие скобки (открывающие) - слева
        res->push(get_bracket(close_bracket.pop()));
    while (!copy_bracket_data->is_empty()) // присоединяем копию  bracket_data
        res->push(copy_bracket_data->pop());
    while(!open_bracket.is_empty())  // присоединяем недостоющие скобки (закрывающие) - справа
        res->push(get_bracket(open_bracket.pop()));

    delete reverse;
    delete copy_bracket_data;
    return true;
}

int main() {
    Stack *bracket_data = new (Stack);
    read_data( bracket_data);
    Stack *result = new (Stack);

    if (get_supplement_brackets(bracket_data, result)){
        print_data(result);
    } else {
        std::cout << "IMPOSSIBLE";
    }

    delete result;
    delete bracket_data;
    return 0;
}



