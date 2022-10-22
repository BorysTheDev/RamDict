#pragma once

#include "lf_list.h"

#include <iostream>

void test_lf_list() {
    lf_list<int> ilist;
    for (int i = 0; i < 10; ++i) {
        ilist.wf_push_back(i);
    }

    auto it = ilist.begin();
    while (!it.is_end()) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;

}
