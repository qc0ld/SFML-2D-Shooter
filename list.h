#ifndef LIST_H
#define LIST_H

namespace my {
    template<typename T>
    class list {
    private:
        struct Node {
            Node *prev;
            Node *next;
            T value;
        };

        Node *head;
        Node *tail;

        size_t node_size;
    public:
        class const_iterator {
        private:
            Node *node_ptr;
        public:
            const_iterator(Node *node) {
                node_ptr = node;
            }

            Node *node() const {
                return node_ptr;
            }

            T &value() const {
                return node_ptr->value;
            }

            const_iterator &operator++() {
                if (node_ptr->next) {
                    node_ptr = node_ptr->next;
                }
                return *this;
            }

            const_iterator &operator--() {
                if (node_ptr->prev != nullptr) {
                    node_ptr = node_ptr->prev;
                }
                return *this;
            }

            bool operator==(const const_iterator &const_iterator) const {
                return const_iterator.node_ptr == this->node_ptr;
            }

            const T *operator->() {
                return &node_ptr->value;
            }

            const T &operator*() {
                return node_ptr->value;
            }

            bool operator!=(const const_iterator &const_iterator) const {
                return const_iterator.node_ptr != this->node_ptr;
            }
        };

        class iterator {
        private:
            Node *node_ptr;
        public:
            iterator(Node *node) {
                node_ptr = node;
            }

            Node *node() const {
                return node_ptr;
            }

            T &value() const {
                return node_ptr->value;
            }

            iterator &operator++() {
                if (node_ptr->next) {
                    node_ptr = node_ptr->next;
                }
                return *this;
            }

            iterator &operator--() {
                if (node_ptr->prev != nullptr) {
                    node_ptr = node_ptr->prev;
                }
                return *this;
            }

            bool operator==(const iterator &iterator) const {
                return iterator.node_ptr == this->node_ptr;
            }

            T *operator->() {
                return &node_ptr->value;
            }

            Node operator*() {
                return *node_ptr;
            }

            bool operator!=(const iterator &iterator) const {
                return iterator.node_ptr != this->node_ptr;
            }
        };

        list() {
            head = new Node;
            tail = new Node;

            head->next = tail;
            head->prev = nullptr;

            tail->next = nullptr;
            tail->prev = head;

            node_size = 0;

            std::cout << "Default constructor was called" << std::endl;
        }

        list(const list &_list) {
            head = new Node;
            tail = new Node;

            head->next = tail;
            head->prev = nullptr;

            tail->next = nullptr;
            tail->prev = head;

            node_size = 0;

            for (iterator it = _list.begin(); it != _list.end(); ++it) {
                push_back(it.value());
            }
            std::cout << "Copy constructor was called" << std::endl;
        }

        list(list &&_list) {
            head = new Node;
            tail = new Node;

            head = _list.head;
            tail = _list.tail;

            node_size = _list.node_size;

            _list.head = nullptr;
            _list.tail = nullptr;

            std::cout << "Move constructor was called" << std::endl;
        }

        list<T> &operator=(const list<T> &list) {
            if (this != &list) {
                for (int i = 0; i < this->size(); i++) {
                    this->pop_back();
                }
                for (iterator it = list.begin(); it != list.end(); ++it) {
                    this->push_back(it.value());
                }
                std::cout << "Overloaded operator = (copy assigment) was called " << std::endl;
            }
            return *this;
        }

        list<T> &operator=(list <T> &&list) {
            if (this != &list) {
                for (int i = 0; i < this->size(); i++) {
                    this->pop_back();
                }

                head = list.head;
                tail = list.tail;

                node_size = list.node_size;

                list.head = nullptr;
                list.tail = nullptr;
                list.node_size = 0;

                std::cout << "Overloaded operator = (move assigment) was called " << std::endl;
            }
            return *this;
        }

        ~list() {
            Node *trash = nullptr;
            Node *curent_node = head;

            while (curent_node) {
                trash = curent_node;
                curent_node = curent_node->next;

                delete trash;

                trash = nullptr;
            }

            node_size = 0;

            std::cout << "Dustructor was called" << std::endl;
        }

        bool empty() {
            if (node_size == 0) {
                return true;
            }
            return false;
        }

        size_t size() {
            return node_size;
        }

        void clear() {
            if (node_size == 0) {
                return;
            }
            for (iterator it = this->begin(); it != this->end(); ++it) {
                Node *curent_node = it.node();

                delete curent_node;

                curent_node = nullptr;
            }

            head->next = tail;
            tail->prev = head;

            node_size = 0;

        }

        void push_back(const T &value) {
            iterator iterator(tail);
            insert_node(value, iterator);
        }

        void push_front(const T &value) {
            iterator iterator(head->next);
            insert_node(value, iterator);
        }

        void pop_back() {
            iterator iterator(tail->prev);
            remove_node(iterator);
        }

        void pop_front() {
            iterator iterator(head->next);
            remove_node(iterator);
        }

        void erase(const iterator &iterator) {
            remove_node(iterator);
        }

        void print_list() {
            for (iterator it = this->begin(); it != this->end(); ++it) {
                std::cout << it.value() << std::endl;
            }
        }

        iterator begin() const {
            return iterator(head->next);
        }

        const_iterator cbegin() const {
            return const_iterator(head->next);
        }

        iterator end() const {
            return iterator(tail);
        }

        const_iterator cend() const {
            return const_iterator(tail);
        }

        iterator find(const T &value) const {
            iterator it = this->begin();
            for (; it != this->end(); ++it) {
                if (value == it.value()) {
                    return it;
                }
            }
            return it;
        }


    private:

        void insert_node(const T &value, const iterator &iterator) {
            Node *new_node = new Node;
            Node *curent_node = iterator.node();

            new_node->next = curent_node;
            new_node->prev = curent_node->prev;
            curent_node->prev = new_node;
            new_node->prev->next = new_node;

            new_node->value = value;

            ++node_size;
        }

        void remove_node(const iterator &iterator) {
            Node *curent_node = iterator.node();

            curent_node->next->prev = curent_node->prev;
            curent_node->prev->next = curent_node->next;

            delete iterator.node();

            curent_node = nullptr;

            --node_size;

        }
    };
}

#endif //LIST_H