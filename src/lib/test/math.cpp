// in math.cpp
#include "math.h"
#include <iostream>

namespace engine::math {
    int add(int a, int b) {
        std::cout << "Hello from library\n";
        return a + b;
    }
}