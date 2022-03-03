#pragma once

#include <iostream>
#include <vector>

class Permutation {
    using Order = std::vector<size_t>;
    using Cylces = std::vector<std::vector<size_t>>;

public:
    Permutation();
    Permutation(const size_t&);
    Permutation(const Order&);
    Permutation(const Permutation&);

    Permutation& operator=(const Permutation&);
    Permutation& operator=(const Order&);

    size_t size() const;
    size_t InversionsAmount() const;
    int Sign() const;

    Cylces BuildCycles() const;

    Permutation operator*(const Permutation&) const;
    Permutation operator-() const;
    Permutation operator^(const int&) const;

    friend std::ostream& operator<<(std::ostream&, const Permutation&);
    friend std::istream& operator>>(std::istream&, Permutation&);

private:
    Order permutation_;

    size_t CycledId(const size_t&, const size_t&) const;
};