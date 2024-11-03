#include <iostream>

#include "tensor.h"


int main() {
    Tensor a{1, 2, 3, 4};
    Tensor b{1, 4, 9, 16};
    Tensor c(-2, 4);
    Tensor v = ~(+a - b.sqrt()).cast<bool>() & (10 * abs(c));
    std::cout << v;

    return 0;
}
