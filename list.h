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
            if (empty()) {
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

        iterator end() const {
            return iterator(tail);
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

            curent_node = nullptr;

            --node_size;

        }
    };
}

#endif //LIST_H