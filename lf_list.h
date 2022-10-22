#pragma once

#include <atomic>

template <class T> class lf_list {
    struct node {
        std::atomic<node*> next = nullptr;
        T val = {};
    };

public:
    class iterator {
        node *cur;
    public:
        iterator(node* node_ptr = nullptr) : cur(node_ptr) {}
        iterator operator++() {
            cur = cur->next.load(std::memory_order::acquire);
            return *this;
        }
        T &operator*() { return cur->val; }
        bool is_end() { return cur->next.load(std::memory_order::relaxed) == nullptr; }
    };

    iterator begin() { return iterator(_root); }

    lf_list() : _root(new node), _end(_root) {}

    void wf_push_back(const T& val) {
        auto* new_node = new node;
        auto prev_node = _end.exchange(new_node, std::memory_order::relaxed);
        prev_node->val = val;
        prev_node->next.store(new_node, std::memory_order::release);
    }

    ~lf_list() {
        while (_root != nullptr) {
            auto *tmp = _root;
            _root = _root->next;
            delete tmp;
        }
    }

private:
    lf_list(const lf_list&) = delete;
    lf_list operator=(const lf_list&) = delete;

private:
    node* _root;
    std::atomic<node*> _end;
};
