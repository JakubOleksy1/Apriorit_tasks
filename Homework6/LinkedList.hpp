#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <initializer_list>
#include <functional>
#include <memory>
#include <iostream>

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        Node(const T& value) : data(value), next(nullptr) {}
        Node(T&& value) : data(std::move(value)), next(nullptr) {}
    };

    std::unique_ptr<Node> head;
    size_t list_size;

public:
    LinkedList() : head(nullptr), list_size(0) {}

    LinkedList(std::initializer_list<T> init_list) : head(nullptr), list_size(0) {
        for (const auto& value : init_list) {
            insert_front(value);
        }
    }

    LinkedList(LinkedList&& other) noexcept : head(std::move(other.head)), list_size(other.list_size) {
        other.list_size = 0;
    }

    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            head = std::move(other.head);
            list_size = other.list_size;
            other.list_size = 0;
        }
        return *this;
    }

    void insert_front(const T& value) {
        auto new_node = std::make_unique<Node>(value);
        new_node->next = std::move(head);
        head = std::move(new_node);
        ++list_size;
    }

    void insert_front(T&& value) {
        auto new_node = std::make_unique<Node>(std::move(value));
        new_node->next = std::move(head);
        head = std::move(new_node);
        ++list_size;
    }

    void remove_front() {
        if (head) {
            head = std::move(head->next);
            --list_size;
        }
    }

    size_t size() const {
        return list_size;
    }

    LinkedList<T> split_when(std::function<bool(const T&)> condition) {
        LinkedList<T> new_list;
        Node* current = head.get();
        Node* prev = nullptr;

        while (current) {
            if (condition(current->data)) {
                if (prev) {
                    new_list.head = std::move(prev->next);
                    prev->next = nullptr;
                } else {
                    new_list.head = std::move(head);
                }
                new_list.list_size = list_size - (new_list.size());
                list_size -= new_list.size();
                break;
            }
            prev = current;
            current = current->next.get();
        }

        return new_list;
    }

    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node) : current(node) {}
        Iterator& operator++() {
            if (current) current = current->next.get();
            return *this;
        }
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
        T& operator*() const {
            return current->data;
        }
    };

    Iterator begin() const {
        return Iterator(head.get());
    }

    Iterator end() const {
        return Iterator(nullptr);
    }
};

#endif // LINKED_LIST_HPP