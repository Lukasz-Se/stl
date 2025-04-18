#include "ArithmeticAverage.h"

double ArithmeticAverage(const std::vector<int>& first, const std::vector<int>& second) {
    double SumOfFirstVec = std::accumulate(begin(first), end(first), 0);
    double SumOfSecondVec = std::accumulate(begin(second), end(second), 0);
    double SumOfElements = first.size() + second.size();

    return (SumOfFirstVec + SumOfSecondVec) / SumOfElements;
}

double Distance(const std::vector<int>& first, const std::vector<int>& second) {
    if (first.size() == second.size()) {
        std::vector<int> temp(first.size());
        std::transform(begin(first), end(first), begin(second), begin(temp), std::minus<int>());
        std::transform(begin(temp), end(temp), begin(temp), [](int& number) { return pow(number, 2); });

        return sqrt(std::accumulate(begin(temp), end(temp), 0));
    }
    return -1.0;
}
