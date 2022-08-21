#pragma once

#include <atomic>

class lf_list {
    struct node {
        node* next = nullptr;
    };
public:
    lf_list() : head(&root) {}

    void add() {
        auto* new_node = new node;
        auto current_head = head.exchange(&(*head)->next);
        *current_head = new_node; // TODO add memory barrier
    }

    ~lf_list() {
        auto it = root;
        while (it != nullptr) {
            auto tmp = it;
            it = it->next;
            delete tmp;
        }
    }

private:

    node* root = nullptr;
    std::atomic<node**> head;
};
