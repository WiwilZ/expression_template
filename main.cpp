#include <iostream>

#include "tensor.h"

int main() {
    Tensor a(1, 4);
    Tensor b(2.f, 4);
    Tensor c{1, 2, 3, 4};
    Tensor v = 10.f * (a.cast<float>() - b.sqrt()) + c;
    std::cout << v;

    return 0;
}
