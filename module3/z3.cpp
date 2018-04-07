#include <iostream>
#include <queue>
#include <stack>


/*
Дано число N < 10^6 и последовательность пар целых чисел из [-2^31..2^31] длиной N.
Построить декартово дерево из N узлов, характеризующихся парами чисел {Xi, Yi}.
Каждая пара чисел {Xi, Yi} определяет ключ Xi и приоритет Yi в декартовом дереве.
Добавление узла в декартово дерево выполняйте второй версией алгоритма,
рассказанного на лекции:
● При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим
приоритетом. Затем разбейте найденное поддерево по ключу x так, чтобы в
первом поддереве все ключи меньше x, а во втором больше или равны x.
Получившиеся два дерева сделайте дочерними для нового узла (x, y). Новый узел
вставьте на место узла P.
Построить также наивное дерево поиска по ключам Xi методом из задачи 2.

3_1. ​Вычислить разницу глубин наивного дерева поиска и декартового дерева. Разница
может быть отрицательна.

in[1]
10
5 11
18 8
25 7
50 12
30 30
15 15
20 10
22 5
40 20
45 9
out[1]
2

in[2]
10
38 19
37 5
47 15
35 0
12 3
0 42
31 37
21 45
30 26
41 6
out[2]
2
*/

template<class T>
struct tree_node {
    T data;
    int priority;
    tree_node<T> *left;
    tree_node<T> *right;

    tree_node(const T &data, int priority = 0) : data(data),
                                                 left(nullptr),
                                                 right(nullptr),
                                                 priority(priority) {}
};


template<class T>
class binary_tree {
public:
    binary_tree();

    ~binary_tree();

    int max_depth();

    int max_depth1() { return max_depth1(root); }

    void add(const T &data);

private:
    int max_depth1(const tree_node<T> *root);

    tree_node<T> *root;
};


template<class T>
binary_tree<T>::binary_tree() : root(nullptr) {}


template<class T>
binary_tree<T>::~binary_tree() {
    std::queue<tree_node<T> *> queue_node;

for (queue_node.push(root); !queue_node.empty(); queue_node.pop()) {
        tree_node<T> *cur = queue_node.front();
        if (cur->left != nullptr) {
            queue_node.push(cur->left);
        }
        if (cur->right != nullptr) {
            queue_node.push(cur->right);
        }
        delete cur;
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


template<class T>
int binary_tree<T>::max_depth1(const tree_node<T> *root) {
    if (root) {
        return std::max(max_depth1(root->left), max_depth1(root->right)) + 1;
    }
    return 0;
}

template<class T>
int binary_tree<T>::max_depth() {//PreOrder
    // обрабатываем текущий узел, при наличии правого поддерева
    // добавляем его в стек для последующей обработки. Переходим
    // к узлу левого поддерева. Если левого узла нет, переходим
    // к верхнему узлу из стека.
    if (root == nullptr)
        return 0;
    tree_node<T> *top = root;
    std::stack<tree_node<T> *> stack;

    int max_depth = 0;
    int current_depth = 0;
    std::stack<int> depths; // для хранения глубин, тех вершин у которых есть правый сын...

    while (top != nullptr || !stack.empty()) {
        if (!stack.empty()) {
            top = stack.top();
            stack.pop();

            current_depth = depths.top();
            depths.pop();
        }
        while (top != nullptr) {
            if (top->right != nullptr) {
                stack.push(top->right);
                ++current_depth;
                depths.push(current_depth);
                --current_depth;
            }
            if (top->left != nullptr) {
                current_depth++;
            } else if (current_depth > max_depth)
                max_depth = current_depth;
            top = top->left;
        }
    }
    return max_depth;
}


template<class T>
class treap_tree {
public:
    treap_tree();

    ~treap_tree();

    void split(tree_node<T> *node, const T &data, tree_node<T> *&left, tree_node<T> *&right);

    tree_node<T> *merge(tree_node<T> *left, tree_node<T> *right);

    void add(const T &data, int priority);

    int max_depth();

private:
    tree_node<T> *root;
};

template<class T>
treap_tree<T>::treap_tree():root(nullptr) {}

template<class T>
tree_node<T> *treap_tree<T>::merge(tree_node<T> *left, tree_node<T> *right) {
    if (left == NULL || right == NULL) {
        return (left == NULL) ? right : left;
    }

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}

template<class T>
void treap_tree<T>::split(tree_node<T> *node, const T &data, tree_node<T> *&left, tree_node<T> *&right) {
    if (node == NULL) {
        left = NULL;
        right = NULL;
    } else if (node->data <= data) {
        split(node->right, data, node->right, right);
        left = node;
    } else {
        split(node->left, data, left, node->left);
        right = node;
    }
}

template<class T>
treap_tree<T>::~treap_tree() {
    std::queue<tree_node<T> *> queue_node;

    for (queue_node.push(root); !queue_node.empty(); queue_node.pop()) {
        tree_node<T> *cur = queue_node.front();
        if (cur->left != nullptr) {
            queue_node.push(cur->left);
        }
        if (cur->right != nullptr) {
            queue_node.push(cur->right);
        }
        delete cur;
    }
}

/*
template<class T>
void treap_tree<T>::add(const T &data, int priority) {
    tree_node<T> *node = new tree_node<T>(data, priority);
    tree_node<T> *left = nullptr;
    tree_node<T> *right = nullptr;

    split(root,  node->data, left, right);
    root = merge(merge(left, node), right);
}*/

template<class T>
void treap_tree<T>::add(const T &data, int priority) {
    tree_node<T> *insert_node = new tree_node<T>(data, priority);

    if (root == nullptr) {
        root = insert_node;
        return;
    }
    tree_node<T> *curr_tree = root;
    tree_node<T> *prev_tree = root;

    //ищем элемент с меньшим приоритетом, чем вставляемый
    while (curr_tree != nullptr && priority <= curr_tree->priority) {
        prev_tree = curr_tree;
        if (data > curr_tree->data) {
            curr_tree = curr_tree->right;
        } else {
            curr_tree = curr_tree->left;
        }
    }

    split(curr_tree, data, insert_node->left, insert_node->right);//записываем в сыновья добавленного узла

    if (curr_tree == root) { // если вставляемый узел приоритетнее корня
        root = insert_node;
        return;
    }

    if (curr_tree != root && data > prev_tree->data) {
        prev_tree->right = insert_node;
    } else {
        prev_tree->left = insert_node;
    }
    return;
}

/*
template <class T>
int treap_tree<T>::max_depth(const tree_node<T> *root) {
    if (root) {
        return std::max(max_depth(root->left), max_depth(root->right)) + 1;
    }
    return 0;
}*/

template<class T>
int treap_tree<T>::max_depth() { //PreOrder
    // обрабатываем текущий узел, при наличии правого поддерева
    // добавляем его в стек для последующей обработки. Переходим
    // к узлу левого поддерева. Если левого узла нет, переходим
    // к верхнему узлу из стека.
    if (root == nullptr)
        return 0;
    tree_node<T> *top = root;
    std::stack<tree_node<T> *> stack;

    int max_depth = 0;
    int current_depth = 0;
    std::stack<int> depths; // для хранения глубин, тех вершин у которых есть правый сын...

    while (top != nullptr || !stack.empty()) {
        if (!stack.empty()) {
            top = stack.top();
            stack.pop();

            current_depth = depths.top();
            depths.pop();
        }
        while (top != nullptr) {
            if (top->right != nullptr) {
                stack.push(top->right);
                ++current_depth;
                depths.push(current_depth);
                --current_depth;
            }
            if (top->left != nullptr) {
                current_depth++;
            } else if (current_depth > max_depth)
                max_depth = current_depth;
            top = top->left;
        }
    }
    return max_depth;
}

int main() {
    binary_tree<int> binary;
    treap_tree<int> treap;

    int count_node = 0;
    std::cin >> count_node;

    int curr_value = 0;
    int curr_priority = 0;

    for (int i = 0; i < count_node; ++i) {
        std::cin >> curr_value >> curr_priority;
        binary.add(curr_value);
        treap.add(curr_value, curr_priority);
    }

    std::cout << binary.max_depth() - treap.max_depth() << std::endl;

    return 0;
}
