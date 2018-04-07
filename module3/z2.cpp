#include <iostream>
#include <queue>

/*
Дано число N < 10^6 и последовательность целых чисел из [-2^31..2^31] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то
узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Рекурсия запрещена.

2_4. Выведите элементы в порядке level-order (по слоям, “в ширину”).
in[1]
3
2 1 3
out[1]
2 1 3

in[2]
3
1 2 3
out[2]
1 2 3

in[3]
3
3 1 2
out[3]
3 1 2

in[4]
4
3 1 4 2

out[4]
3 1 4 2

*/


template <class T>
struct tree_node {
    T data;
    tree_node<T> *left;
    tree_node<T> *right;
    tree_node (const T& data):data(data),
                              left(nullptr),
                              right(nullptr){}
};


template <class T>
class binary_tree {
public:
    binary_tree();
    ~binary_tree();

    void show_level_order ();
    void add(const T &data);

private:
    tree_node<T> *root;
};


template<class T>
binary_tree<T>::binary_tree() : root(nullptr){}


template <class T>
binary_tree<T>::~binary_tree() {
    std::queue<tree_node<T> *> queue;

    for (queue.push(root);!queue.empty(); queue.pop()) {
        tree_node<T> *cur = queue.front();
        if(cur->left != NULL) {
            queue.push(cur->left);
        }
        if(cur->right != NULL) {
            queue.push(cur->right);
        }

        delete cur;
    }
}

template <class T>
void binary_tree<T>::show_level_order () {
    std::queue<tree_node<T>*> queue;
    if (!root) {
        return;
    }
    for (queue.push(root); !queue.empty(); queue.pop()) {
        tree_node<T>* buff = queue.front(); // голова очереди
        std::cout << buff->data << " ";
        if (buff->left) {
            queue.push(buff->left);
        }
        if (buff->right) {
            queue.push(buff->right);
        }
    }
}


template <class T>
void binary_tree<T>::add(const T &data) {
    tree_node<T>* node = new tree_node<T>(data);

    if (root == nullptr) {
        root = node;
        return;
    }

    tree_node<T>* next_node = root;
    while (true) {
        if (data >= next_node->data) { //если значение в рассматриваемом элементе - больше либо равно
                                      // - идем направо, пока не nullptr, иначе налево
            if (next_node->right == nullptr) { // если дошли до листового - вставляем
                next_node->right = node;
                return;
            }
            next_node = next_node->right;
        } else {
            if (next_node->left == nullptr) { // если дошли до листового - вставляем
                next_node->left = node;
                return;
            }
            next_node = next_node->left;
        }
    }
}


int main() {

    int n = 0;
    std::cin >> n;

    binary_tree<int> tree;

    int curr_elem;
    for(int i = 0; i < n; i++) {
        std::cin >> curr_elem;
        tree.add(curr_elem);
    }

    tree.show_level_order();

    return 0;
}
