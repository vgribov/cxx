#include "lib.hpp"

#include <cassert>
#include <cstdio>
#include <vector>

void say_hello(const char* name) {
    assert(name);

    std::printf("Hello, %s!\n", name);
}

void do_something_bad(int n) {
    std::vector<int> vec(n, int{});
    for (int i = 0; i < n; ++i) {
        vec[i] = vec[i+1];
    }
}
