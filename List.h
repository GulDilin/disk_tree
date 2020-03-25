#include <iostream>
#include <stdexcept>
#include <limits>

using namespace std;


template  <typename T> class List
{
private:
    struct Node
    {
        Node    *prev;
        T       item;
        Node    *next;
    };
    Node* first;
    Node* last;
    int length;

public:
    List()
    {
        first = new Node;
        first->prev = 0;
        first->next = 0;
        last = first;
        length = 0;
    }

    List(T * array,int  n)
    {
        first = new Node;
        first->prev = 0;
        first->next = 0;
        last = first;
        length = 0;
        for (int i = 0; i < n; ++i)
        {
            add(array[i]);
        }
    }

    ~List()
    {
        Node* node = first;
        Node* temp;
        while (node)
        {
            temp = node->next;
            delete node;
            node = temp;
        }
        // delete first, last;
    }


    void show()
    {
        Node* temp = first;
        while (temp)
        {
            cout << temp->item ;
            if(temp->next)
                cout << ", ";
            temp = temp->next;
        }
        cout << endl;
    }

    int size()
    {
        return length;
    }

    Node * get_first()
    {
        return first;
    }

    Node * get_last()
    {
        return last;
    }

    T* get(int index)
    {
        Node* node = first;
        if (index >= size()){
            throw invalid_argument("Index too high.");
        }
        if (index < 0){
            throw invalid_argument("Index too low.");
        }

        for (int i = 0; i < index; ++i)
        {
            node = node->next;
        }
        return &(node->item);
    }

    T get_item(int index)
    {
        Node* node = first;
        if (index >= size()){
            throw invalid_argument("Index too high.");
        }
        if (index < 0){
            throw invalid_argument("Index too low.");
        }

        for (int i = 0; i < index; ++i)
        {
            node = node->next;
        }
        return (node->item);
    }

    T* to_array()
    {
        int length = size();
        T* array = new T[length];
        Node * node = first;
        for (int i = 0; i < length; ++i)
        {
            array[i] = node->item;
            node = node->next;
        }
        return array;
    }

    void add(T item)
    {
        if (length == 0)
        {
            last->item = item;
            length = 1;
            // return true;
        } else {
            Node* temp = new Node;
            temp->item = item;
            last->next = temp;
            temp->prev = last;
            temp->next = 0;
            last = temp;
            length ++;
            // return true;
        }
    }

//    int add(T item, int index);

    bool delete_item(T item)
    {
        bool flag = false;
        Node* temp = first;
        for (int i = 0; i < size(); ++i)
        {
            if (temp->item == item)
            {
                if (temp == first){
                    if(first->next == 0)
                    {
                        first = new Node;
                    } else {
                        (temp->next)->prev = 0;
                        first = (temp->next);
                    }
                }else if (temp->next == 0){
                    (temp->prev)->next = 0;
                    last = temp->prev;
                }else{
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

    bool delete_item_by_index(int index){
        if (index < 0 || index >= size()){
            return false;
        }
        Node* temp = first;
        for (int i = 0; i < index; ++i)
        {
            temp = temp->next;
        }
        if (index == 0){
            if(first->next == 0)
            {
                first = new Node;
            } else {
                (temp->next)->prev = 0;
                first = (temp->next);
            }
        }else if (temp->next == 0) {
            (temp->prev)->next = 0;
            last = temp->prev;
        }else{
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
        }
        delete temp;
        length--;
        return true;
    }

    void clear(){
        // first = new Node;
        first->prev = 0;
        first->next = 0;
        last = first;
        length = 0;
    }

    class Iterator
    {
    public:
        Iterator(Node * f){
           tmp = new Node;
           tmp -> next = f;
       }
       ~Iterator(){
        delete tmp;
    }

    bool has_next(){
        return (tmp->next != 0);
    }

    T * next(){
        tmp = tmp-> next;
        return &(tmp->item);
    }

    bool has_prev(){
        return (tmp->prev != 0);
    }

    T * prev(){
        tmp = tmp-> prev;
        return &(tmp->item);
    }

    private:
        List::Node* tmp;
    };

    Iterator get_begin_iterator()
    {
        return Iterator(first);
    }

    Iterator get_end_iterator()
    {
        return Iterator(last);
    }

};

