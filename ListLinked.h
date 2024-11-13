#include <ostream>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {

    private:
 
        Node<T>* first;
        int n;

    public:

    ListLinked(){
        first = nullptr;
        n = 0;
    }
    ~ListLinked(){
        Node<T>* act = first;
        while(act != nullptr){
            Node<T>* sig = act->next;
            delete act;
            act = next;
        }
    }

    T operator[](int pos) {
        if(pos < 0 || pos >= n){
            throw std::out_of_range("Index out of bounds");
        }
        Node<T>* act = first;
        for (int i = 0; i < pos; ++i) {
            act = act->next;
        }
        return act->data;
    }

    friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list){
        Node<T>* act = list.first;
        out << "[";
        while(act != nullptr){
            out << act->data;
            if(act->next != nullptr){
                out << ", ";
            }
            act = act->next;
        }
        out << "]";
        return out;
    }

    void insert(int pos, T element) override {
        if (pos < 0 || pos > n) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* new_node = new Node<T>(element);
        if (pos == 0) {
            new_node->next = first;
            first = new_node;
        } else {
            Node<T>* act = first;
            for (int i = 0; i < pos - 1; ++i) {
                act = act->next;
            }
            new_node->next = act->next;
            act->next = new_node;
        }
        ++n;
    }

    void append(T element) override {
        insert(n, element);
    }

    void prepend(T element) override {
        insert(0, element);
    }

    T remove(int pos) override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* removed;
        if (pos == 0) {
            removed = first;
            first = first->next;
        } else {
            Node<T>* act = first;
            for (int i = 0; i < pos - 1; ++i) {
                act = act->next;
            }
            removed = act->next;
            act->next = removed->next;
        }
        T element = removed->data;
        delete removed;
        --n;
        return element;
    }

    T get(int pos) override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* act = first;
        for (int i = 0; i < pos; ++i) {
            act = act->next;
        }
        return act->data;
    }
    
    int search(T element) override {
        Node<T>* act = first;
        for (int i = 0; i < n; ++i) {
            if (act->data == element) {
                return i;
            }
            act = act->next;
        }
        return -1;
    }
    
    bool empty() override {
        return n == 0;
    }

    int size() override {
        return n;
    }
};
