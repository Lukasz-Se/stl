#include "ArithmeticAverage.h"

int main() {
    std::vector<int> first{-5, 4, 2, -5, 2, 4, 6, 7};
    std::vector<int> second{3, 5, -2, 6, 7, -3, 6, 9};

    std::vector<int> v1{7, 4, 3};
    std::vector<int> v2{17, 6, 2};

    std::cout << ArithmeticAverage(first, second) << std::endl;
    std::cout << Distance(v1, v2) << std::endl;
}
