#pragma once

#include <iostream>

class Fraction {
public:
    Fraction();
    Fraction(long long integer);
    Fraction(long long numerator, long long denominator);
    Fraction(Fraction&& other);
    Fraction(const Fraction& other);

    Fraction& operator=(const Fraction& other);
    Fraction& operator=(const long long& other);
    Fraction& operator=(Fraction&& other);

    Fraction operator-() const;

    Fraction& operator+=(const Fraction& other);
    Fraction& operator-=(const Fraction& other);
    Fraction& operator*=(const Fraction& other);
    Fraction& operator/=(const Fraction& other);

    Fraction& operator+=(const long long& other);
    Fraction& operator-=(const long long& other);
    Fraction& operator*=(const long long& other);
    Fraction& operator/=(const long long& other);

    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;

    Fraction operator+(const long long& other) const;
    Fraction operator-(const long long& other) const;
    Fraction operator*(const long long& other) const;
    Fraction operator/(const long long& other) const;

    friend Fraction operator+(const long long& integer, const Fraction& fraction);
    friend Fraction operator-(const long long& integer, const Fraction& fraction);
    friend Fraction operator*(const long long& integer, const Fraction& fraction);
    friend Fraction operator/(const long long& integer, const Fraction& fraction);

    bool operator==(const Fraction& other) const;
    bool operator==(const int& other) const;
    bool operator!=(const Fraction& other) const;
    bool operator!=(const int& other) const;

    bool operator<=(const Fraction& other) const;
    bool operator>=(const Fraction& other) const;
    bool operator<(const Fraction& other) const;
    bool operator>(const Fraction& other) const;

    operator double() const;

    friend std::ostream& operator<<(std::ostream& out, const Fraction& Fraction);
    friend std::istream& operator>>(std::istream& in, Fraction& Fraction);

    size_t StringLength() const;
    void Simplify();

    friend Fraction GreatestSq(const Fraction& fraction);

private:
    long long numerator_;
    long long denominator_;
};
