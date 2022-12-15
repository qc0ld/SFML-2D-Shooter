#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <iterator>
#include <list>


namespace my {
    template<class T>
    class list {
    public:
        struct node {
            T data;
            node *next;

            node(T const &_data, node *_next) {
                data = _data;
                next = _next;
            }

            node(T &&_data, node *_next) {
                data = _data;
                next = _next;
            }
        };

        struct Iterator {
        private:
            T *ptr;
        public:
            Iterator() {
                ptr = nullptr;
            }

            Iterator(T *_ptr) {
                ptr = _ptr;
            }

            T &operator*() {
                return *ptr;
            }

            T *operator->() {
                return ptr;
            }

            Iterator &operator++() {
                ptr++;
                return *this;
            }

            Iterator operator++(int) {
                return *this++;
            }

            bool operator==(const Iterator &i) const {
                return this->ptr == i.ptr;
            }

            bool operator!=(const Iterator &i) const {
                return this->ptr != i.ptr;
            }
        };

        int size;
        node *head;
        node *tail;
        Iterator iterator();
    public:
        list() {
            size = 0;
            head = nullptr;
            head->next = nullptr;
        }

        void push_back(T new_data) {
            node *new_node(new_data, nullptr);
            if (head) {
                node *temp = head;
                while (temp->next) {
                    temp = temp->next;
                }
                temp->next = new_node;
            } else {
                head = new_node;
            }
        }

        Iterator end() {
            node *temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            return iterator(temp);
        }


        Iterator begin() {
            iterator = head->data;
            return iterator;
        }


    };
}

#endif //LIST_H