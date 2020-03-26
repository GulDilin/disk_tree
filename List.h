#include <iostream>
#include <stdexcept>
#include <limits>

using namespace std;


template<typename T>
class List {
public:
    struct Node {
        Node *prev;
        T item;
        Node *next;
    };
private:
    Node *first;
    Node *last;
    int length;

public:

    List() {
        first = new Node;
        first->prev = 0;
        first->next = 0;
        last = first;
        length = 0;
    }

    List(T *array, int n) {
        first = new Node;
        first->prev = 0;
        first->next = 0;
        last = first;
        length = 0;
        for (int i = 0; i < n; ++i) {
            add(array[i]);
        }
    }

    ~List() {
        Node *node = first;
        Node *temp;
        while (node) {
            temp = node->next;
            delete node;
            node = temp;
        }
        // delete first, last;
    }

    void swap(int i, int k) {
        if (i >= length || i < 0 || k >= length || k < 0 || i == k) return;
        if (i > k) {
            int t = i;
            i = k;
            k = t;
        }
        Node * node = first;
        Node * node_i;
        Node * node_k;
        T *temp_item;
        for (int j = 0; j < i; ++j) {
            node = node->next;
        }
        node_i = node;
        temp_item = node_i->item;
        for (int l = i; l < k; ++l) {
            node = node->next;
        }
        node_k = node;
        node_i->item = node_k->item;
        node_k->item = temp_item;
    }

    void swap(Node * n1, Node * n2){
        if (n1 == n2) return;
        T temp_item;
        temp_item = n1->item;
        n1->item = n2->item;
        n2->item = temp_item;
    }

    void sort(){
        int min = 0;
        Node * min_node;
        Node * node_i = first;
        Node * node_j;
        for (int i = 0; i < length; ++i) {
            min_node = node_i;
            node_j = node_i;
            for (int j = i; j < length; ++j){
                if (node_j->item < min_node->item) min_node = node_j;
                node_j = node_j->next;
            }
            swap(node_i, min_node);
            node_i = node_i->next;
        }
    }

    void show() {
        Node *temp = first;
        while (temp) {
            cout << temp->item;
            if (temp->next)
                cout << ", ";
            temp = temp->next;
        }
        cout << endl;
    }

    int size() {
        return length;
    }

    Node *get_first() {
        return first;
    }

    Node *get_last() {
        return last;
    }

    T *get(int index) {
        Node *node = first;
        if (index >= size()) {
            throw invalid_argument("Index too high.");
        }
        if (index < 0) {
            throw invalid_argument("Index too low.");
        }

        for (int i = 0; i < index; ++i) {
            node = node->next;
        }
        return &(node->item);
    }

    T get_item(int index) {
        Node *node = first;
        if (index >= size()) {
            throw invalid_argument("Index too high.");
        }
        if (index < 0) {
            throw invalid_argument("Index too low.");
        }

        for (int i = 0; i < index; ++i) {
            node = node->next;
        }
        return (node->item);
    }

    T *to_array() {
        int length = size();
        T *array = new T[length];
        Node *node = first;
        for (int i = 0; i < length; ++i) {
            array[i] = node->item;
            node = node->next;
        }
        return array;
    }

    void add(T item) {
        if (length == 0) {
            last->item = item;
            length = 1;
            // return true;
        } else {
            Node *temp = new Node;
            temp->item = item;
            last->next = temp;
            temp->prev = last;
            temp->next = 0;
            last = temp;
            length++;
            // return true;
        }
    }

    void add(T *&item) {
        add(*item);
    }

//    int add(T item, int index);

    bool delete_item(T item) {
        bool flag = false;
        Node *temp = first;
        for (int i = 0; i < size(); ++i) {
            if (temp->item == item) {
                if (temp == first) {
                    if (first->next == 0) {
                        first = new Node;
                    } else {
                        (temp->next)->prev = 0;
                        first = (temp->next);
                    }
                } else if (temp->next == 0) {
                    (temp->prev)->next = 0;
                    last = temp->prev;
                } else {
                    (temp->prev)->next = temp->next;
                    (temp->next)->prev = temp->prev;
                }
                delete temp;
                length--;
                flag = true;
            }
            temp = first->next;
        }
        return flag;
    }

    bool delete_item_by_index(int index) {
        if (index < 0 || index >= size()) {
            return false;
        }
        Node *temp = first;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        if (index == 0) {
            if (first->next == 0) {
                first = new Node;
            } else {
                (temp->next)->prev = 0;
                first = (temp->next);
            }
        } else if (temp->next == 0) {
            (temp->prev)->next = 0;
            last = temp->prev;
        } else {
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
        }
        delete temp;
        length--;
        return true;
    }

    void clear() {
        // first = new Node;
        first->prev = 0;
        first->next = 0;
        last = first;
        length = 0;
    }
};

