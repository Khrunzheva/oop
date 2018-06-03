#pragma once


template<class T>
class Container {

    class Node {
    public:
        T data;
        Node *prev;
        Node *next;

        Node(T data, Node *prev, Node *next) : data(data), prev(prev), next(next) {}
    };

    size_t size;
    Node *head;
    Node *tail;

public:

    class container_is_empty : public std::logic_error {
    public:
        container_is_empty() : logic_error("Container is isEmpty") {}
    };


    Container() {
        this->size = 0;
        this->head = nullptr;
        this->tail = nullptr;
    }

    Container(const Container &other) {
        head = new Node(other.head->data, nullptr, nullptr);

        auto prev = head;
        for (auto i = ++other.cbegin(); i != other.cend(); ++i) {
            auto current = new Node(*i, prev, nullptr);
            prev->next = current;
            prev = current;
        }

        tail = prev;
        size = other.size;
    }

    Container &operator=(const Container &other) {
        if (this != &other) {
            clear();

            head = new Node(other.head->data, nullptr, nullptr);

            auto prev = head;
            for (auto i = ++other.cbegin(); i != other.cend(); ++i) {
                auto current = new Node(*i, prev, nullptr);
                prev->next = current;
                prev = current;
            }

            tail = prev;
            size = other.size;
        }

        return *this;
    }

    ~Container() {
        this->clear();
    }

    class iterator {
        Node *node;

    public:
        iterator(Node *node) : node(node) {}

        iterator(const iterator &it) {
            node = it.node;
        }

        bool operator!=(iterator const &other) {
            return node != other.node;
        }

        T &operator*() {
            return node->data;
        }

        iterator &operator++() {
            node = node->next;
            return *this;
        }
    };

    iterator begin() {
        return iterator(head);
    }

    iterator end() {
        return iterator(nullptr);
    }

    class const_iterator {
        const Node *node;

    public:
        const_iterator(const Node *node) : node(node) {}

        const_iterator(const const_iterator &it) {
            node = it.node;
        }

        bool operator!=(const const_iterator &other) {
            return node != other.node;
        }

        const T &operator*() {
            return node->data;
        }

        const_iterator &operator++() {
            node = node->next;
            return *this;
        }
    };

    const_iterator cbegin() const {
        return const_iterator(head);
    }

    const_iterator cend() const {
        return const_iterator(nullptr);
    }

    void addBegin(const T &element) {
        if (size == 0) {
            head = new Node(element, nullptr, nullptr);
            tail = head;
        } else {
            auto node = new Node(element, nullptr, head);
            head->prev = node;
            head = node;
        }
        size++;
    }

    void addEnd(const T &element) {
        if (size == 0) {
            tail = new Node(element, nullptr, nullptr);
            head = tail;
        } else {
            auto node = new Node(element, tail, nullptr);
            tail->next = node;
            tail = node;
        }
        size++;
    }

    void removeBegin() {
        if (size == 0) {
            throw container_is_empty();
        }
        if (size == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            auto deleteLater = head;
            head->next->prev = nullptr;
            head = head->next;
            delete deleteLater;
        }
        size--;
    }

    void removeEnd() {
        if (size == 0) {
            throw container_is_empty();
        }
        if (size == 1) {
            delete tail;
            head = nullptr;
            tail = nullptr;
        } else {
            auto deleteLater = tail;
            tail->prev->next = nullptr;
            tail = tail->prev;
            delete deleteLater;
        }
        size--;
    }

    const T &first() const {
        return head->data;
    }

    const T &last() const {
        return tail->data;
    }

    size_t getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void clear() {
        if (size != 0) {
            Node *i = head;
            while (i->next != nullptr) {
                i = i->next;
                delete i->prev;
            }
            delete i;
            size = 0;
            head = nullptr;
            tail = nullptr;
        }
    }
};
