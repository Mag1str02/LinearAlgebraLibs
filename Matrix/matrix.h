#pragma once

#include <iostream>
#include <vector>

#include "../Fraction/fraction.h"
#include "../Permutation/permutation.h"


class MatrixWrongSize : public std::exception {};

class Matrix {
private:
    using matrix = std::vector<std::vector<Fraction>>;
    using ColumnWidth = std::vector<size_t>;

public:
    Matrix();
    Matrix(const size_t& height, const size_t& width);
    Matrix(const std::vector<std::vector<long long>>& other);

    Matrix& operator=(const Matrix& other);

    void Op1(const size_t& from, const size_t& to, const Fraction& k);
    void Op2(const size_t& from, const size_t& to);
    void Op3(const size_t& from, const Fraction& k);

    void Op1_s(const size_t& from, const size_t& to, const Fraction& k);
    void Op2_s(const size_t& from, const size_t& to);
    void Op3_s(const size_t& from, const Fraction& k);

    Fraction Determinator() const;

    void SetSplit(const size_t& split_);
    void InputMatrix(std::istream& in = std::cin, std::ostream& out = std::cout);
    Matrix operator-() const;

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    Matrix& operator*=(const long long& other);
    Matrix& operator*=(const Fraction& other);
    Matrix& operator/=(const long long& other);
    Matrix& operator/=(const Fraction& other);

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(const long long& other) const;
    Matrix operator*(const Fraction& other) const;
    Matrix operator/(const long long& other) const;
    Matrix operator/(const Fraction& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    friend std::istream& operator>>(std::istream& in, Matrix& matrix);

    friend Matrix E(const Matrix& matrix);
    void SimetrickGauss();

private:
    matrix mat_;

    size_t height_;
    size_t width_;

    size_t split_ = 0;

    void CheckSameSize(const Matrix& other) const;
    void CheckMultiplicationSize(const Matrix& other) const;

    ColumnWidth CalculateColumnWidth() const;
};

void PrintSpaces(std::ostream& out, const size_t& spaces_amount);