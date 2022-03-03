//#include "../Matrix/matrix.h"
#include <iostream>
#include <math.h>
#include <numeric>
#include <sstream>

long double fact(int k) {
    long double res = 1;
    for (size_t i = 2; i <= k; ++i) {
        res *= i;
    }
    return res;
}

int main() {
    long double a = 1.0 / 2;
    std::cout << "a = " << a << std::endl;
    for (int i = 1; i < 100; ++i) {
        a -= (long double)(i + 1) / (fact(i + 2));
        std::cout << a << " " << (abs(a - (long double)(1.0) / fact(i + 2)) < 0.00001 ? '+' : '-') << std::endl;
    }
    return 0;
}