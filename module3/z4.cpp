#include <iostream>
#include <queue>
#include <assert.h>


/*
4_2. Порядковые статистики.​ Дано число N и N строк. Каждая строка содержит команду
добавления или удаления натуральных чисел, а также запрос на получение k-ой
порядковой статистики. Команда добавления числа A задается положительным числом A,
команда удаления числа A задается отрицательным числом “-A”. Запрос на получение
k-ой порядковой статистики задается числом k. Требуемая скорость выполнения запроса -
O(log n).

in 
5
40 0
10 1
4 1
-10 0
50 2

out
40
40
10
4
50
*/


struct node { // структура для представления узлов дерева
    int key;
    unsigned char height;
    node *left;
    node *right;

    node(int k) {
        key = k;
        left = right = nullptr;
        height = 1;
    }
};

unsigned char height(node *p) {
    return p ? p->height : 0;
}

int bfactor(node *p) {
    return height(p->right) - height(p->left);
}

void fixheight(node *p) { // восстанавливаем высоты
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

node *rotateright(node *p) { // правый поворот вокруг p
    node *q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q; // новый корень дерева
}

node *rotateleft(node *q) { // левый поворот вокруг q
    node *p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node *balance(node *p) { // балансировка узла p
    fixheight(p);
    if (bfactor(p) == 2) {  // если высота правого дерева больше, поворачиваем влево
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2) {   // если высота левого дерева больше, поворачиваем вправо
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}

node *insert(node *p, int k) { // вставка ключа k в дерево с корнем p
    if (!p) return new node(k);
    if (k < p->key) // как и в обычное дерево
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p); // после вставки производим балансировку
}

node* find_not_null_child(node* node) {
    return node->left ? node->left : node->right;
}

node* my_removemin(node* p, node*& root) {
    if(p->left) {
        p->left = my_removemin(p->left,root);
    } else {
        root->key = p->key;
        delete p;
        return p->right;
    }
    return balance(p);
    /*
    int res=0;
    node* next =  find_not_null_child(p);
    while (true) {
  //      if (p->left == nullptr || p->right == nullptr) {
        if (next == nullptr) {
            res = p->key;
            delete p;
            p = nullptr;
            return res;
        } else {
            res = next->key;
            p->left = nullptr;
            return res;
        }

        }

        p = p->left;
        next =  find_not_null_child(p);
    }
*/
}

node *remove(node *p, int k) // удаление ключа k из дерева p
{
    if (!p)
        return nullptr;
    if (k < p->key)
        p->left = remove(p->left, k);
    else if (k > p->key)
        p->right = remove(p->right, k);
    else //  k == p->key
    {
//        int buff = my_removemin(p->right);
//        p->key = buff;
        node* q = p->left;
        node* r = p->right;
        if( !r ) return q;
        p->right = my_removemin(r,p);//за один проход получаем новое правое поддерево с удалёным минимумом уже вствили минимум на место
        p->left = q;
    }
    return balance(p);
    //в статье на хабре на удаление тратится два прохода - поиск и само удаление
}

void show_level_order (node* root) {
    std::queue<node*> queue;
    if (!root) {
        return;
    }
    for (queue.push(root); !queue.empty(); queue.pop()) {
        node* buff = queue.front(); // голова очереди
        std::cout << buff->key << " ";
        if (buff->left) {
            queue.push(buff->left);
        }
        if (buff->right) {
            queue.push(buff->right);
        }
    }
}

int get_count_element(node *p) { // количество элементов в дереве
    if (!p) {
        return 0;
    }
    std::queue<node *> queue;
    int count = 0;
    for (queue.push(p); !queue.empty(); queue.pop()) {
        node *cur = queue.front();
        ++count;
        if (cur->left != nullptr) {
            queue.push(cur->left);
        }
        if (cur->right != nullptr) {
            queue.push(cur->right);
        }
    }
    return count;
}

int find_k_statistic(node *root, int k) {
    while (root) {
        int left_height = get_count_element(root->left);

        if (left_height == k) { // если количество элементов у левого сына  == нужной статистики, то статистика - отец этого сына.
            return root->key;
        }

        if (left_height < k) { // если нужная статистика больше колличества элементов в левом сыне,
                               // идём вправо и ищем в правом поддереве (k - количество в левом поддереве - 1) статистику
            root = root -> right;
            k -= left_height+1;
        } else {
            root = root ->left;
        }

    }
    return -1;
}

void destr(node *root) {
    std::queue<node *> queue_node;

    for (queue_node.push(root); !queue_node.empty(); queue_node.pop()) {
        node *cur = queue_node.front();
        if (cur->left != nullptr) {
            queue_node.push(cur->left);
        }
        if (cur->right != nullptr) {
            queue_node.push(cur->right);
        }
        delete cur;
    }
}


int main() {
    int cout_elem = 0;
    int k_stat = -1;
    std::cin >> cout_elem;


    struct node *root = nullptr;
    for (size_t i = 0; i < cout_elem; i++) {
        int value;
        int statistics;
        std::cin >> value >> statistics;
        if (value >= 0)
            root = insert(root, value);
        else {
            root = remove(root, std::abs(value));
        }
        //std::cout << get_count_element(root) << std::endl;
        //show_level_order(root);
        //std::cout << " "<<std::endl;
        k_stat = find_k_statistic(root,statistics);
        if (k_stat == -1)
            assert(false);
        std::cout <<  k_stat << std::endl;
    }

    destr(root);
    return 0;
}
