#include "permutation.h"

Permutation::Permutation() {
}
Permutation::Permutation(const size_t& length) {
    permutation_.resize(length);
    for (size_t i = 0; i < permutation_.size(); ++i) {
        permutation_[i] = i;
    }
}
Permutation::Permutation(const Order& permutation) : permutation_(permutation) {
    for (auto& perm : permutation_) {
        --perm;
    }
}
Permutation::Permutation(const Permutation& other) : permutation_(other.permutation_) {
}

Permutation& Permutation::operator=(const Permutation& other) {
    permutation_ = other.permutation_;
    return *this;
}
Permutation& Permutation::operator=(const Order& other) {
    permutation_ = other;
    return *this;
}

size_t Permutation::size() const {
    return permutation_.size();
}
size_t Permutation::InversionsAmount() const {
    size_t result = 0;
    for (size_t i = 1; i < permutation_.size(); ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (permutation_[j] > permutation_[i]) {
                ++result;
            }
        }
    }   
    return result;
}
int Permutation::Sign() const {
    return (InversionsAmount() % 2) == 0 ? 1 : -1;
}

Permutation::Cylces Permutation::BuildCycles() const {
    Cylces result;
    Order cycle;
    std::vector<bool> used_nums(size(), false);
    for (size_t i = 0; i < size(); ++i) {
        if (used_nums[i]) {
            continue;
        }
        used_nums[i] = true;
        cycle.clear();
        cycle.push_back(i);
        while (permutation_[cycle.back()] != cycle.front()) {
            used_nums[permutation_[cycle.back()]] = true;
            cycle.push_back(permutation_[cycle.back()]);
        }
        result.push_back(cycle);
    }
    return result;
}

Permutation Permutation::operator*(const Permutation& permutation) const {
    Permutation result(permutation.size());
    for (size_t i = 0; i < permutation.size(); ++i) {
        result.permutation_[i] = permutation_[permutation.permutation_[i]];
    }
    return result;
}
Permutation Permutation::operator-() const {
    Permutation result(permutation_.size());
    for (size_t i = 0; i < permutation_.size(); ++i) {
        result.permutation_[permutation_[i]] = i;
    }
    return result;
}
Permutation Permutation::operator^(const int& power) const {
    if (power == -1) {
        return -*this;
    }
    Permutation result(size());
    Cylces cycles = BuildCycles();
    for (const auto& cycle : cycles) {
        for (size_t i = 0; i < cycle.size(); ++i) {
            result.permutation_[cycle[i]] = cycle[CycledId(i + power, cycle.size())];
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& out, const Permutation& permutation) {
    for (size_t i = 0; i < permutation.size(); ++i) {
        out << i + 1 << " -> " << permutation.permutation_[i] + 1 << std::endl;
    }
    return out;
}
std::istream& operator>>(std::istream& in, Permutation& permutation) {
    for (size_t i = 0; i < permutation.size(); ++i) {
        in >> permutation.permutation_[i];
        --permutation.permutation_[i];
    }
    return in;
}

size_t Permutation::CycledId(const size_t& id, const size_t& cycle_len) const {
    if (id >= cycle_len) {
        return id % cycle_len;
    }
    return id;
}