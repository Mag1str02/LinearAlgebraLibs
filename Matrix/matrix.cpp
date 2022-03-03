#include "matrix.h"

#include <algorithm>

Matrix::Matrix() {
}
Matrix::Matrix(const std::vector<std::vector<long long>>& other) : height_(other.size()), width_(other[0].size()) {
    mat_.resize(height_);
    for (size_t y = 0; y < height_; ++y) {
        mat_[y].resize(width_);
        for (size_t x = 0; x < width_; ++x) {
            mat_[y][x] = Fraction(other[y][x]);
        }
    }
}
Matrix::Matrix(const size_t& height, const size_t& width) : height_(height), width_(width) {
    mat_.resize(height_);
    for (size_t y = 0; y < height_; ++y) {
        mat_[y].resize(width_);
    }
}

Matrix& Matrix::operator=(const Matrix& other) {
    mat_ = other.mat_;
    height_ = other.height_;
    width_ = other.width_;
    return *this;
}

void Matrix::Op1(const size_t& from, const size_t& to, const Fraction& k) {
    for (size_t i = 0; i < width_; ++i) {
        mat_[to][i] += mat_[from][i] * k;
    }
}
void Matrix::Op2(const size_t& from, const size_t& to) {
    for (size_t i = 0; i < width_; ++i) {
        Fraction buff = mat_[to][i];
        mat_[to][i] = mat_[from][i];
        mat_[from][i] = buff;
    }
}
void Matrix::Op3(const size_t& from, const Fraction& k) {
    for (size_t i = 0; i < width_; ++i) {
        mat_[from][i] *= k;
    }
}

void Matrix::Op1_s(const size_t& from, const size_t& to, const Fraction& k) {
    for (size_t i = 0; i < width_; ++i) {
        mat_[to][i] += mat_[from][i] * k;
    }
    for (size_t i = 0; i < height_; ++i) {
        mat_[i][to] += mat_[i][from] * k;
    }
}
void Matrix::Op2_s(const size_t& from, const size_t& to) {
    for (size_t i = 0; i < width_; ++i) {
        Fraction buff = mat_[to][i];
        mat_[to][i] = mat_[from][i];
        mat_[from][i] = buff;
    }
    for (size_t i = 0; i < height_; ++i) {
        Fraction buff = mat_[i][to];
        mat_[i][to] = mat_[i][from];
        mat_[i][from] = buff;
    }
}
void Matrix::Op3_s(const size_t& from, const Fraction& k) {
    for (size_t i = 0; i < width_; ++i) {
        mat_[from][i] *= k;
    }
    for (size_t i = 0; i < height_; ++i) {
        mat_[i][from] *= k;
    }
}

void Matrix::SetSplit(const size_t& split) {
    split_ = split;
}
void Matrix::InputMatrix(std::istream& in, std::ostream& out) {
    out << "Input matrix height and width: ";
    in >> height_ >> width_;
    out << "Input matrix elements:" << std::endl;
    mat_.resize(height_);
    for (size_t y = 0; y < height_; ++y) {
        mat_[y].resize(width_);
        for (size_t x = 0; x < width_; ++x) {
            in >> mat_[y][x];
            mat_[y][x].Simplify();
        }
    }
    out << "Input Split Pos: ";
    size_t pos_of_split;
    in >> pos_of_split;
    if (pos_of_split > 0 && pos_of_split < width_) {
        SetSplit(pos_of_split);
    }
}

Fraction Matrix::Determinator() const {
    Permutation permutation;
    Fraction result;
    Fraction poly;
    if (height_ != width_) {
        throw MatrixWrongSize();
    }
    std::vector<size_t> order(height_);
    for (size_t i = 0; i < height_; ++i) {
        order[i] = i;
    }
    do {
        poly = 0;
        for (size_t i = 0; i < order.size(); ++i) {
            poly += mat_[i][order[i]];
        }
        permutation = order;
        poly *= permutation.Sign();
        result += poly;
    } while (std::next_permutation(order.begin(), order.end()));
    return result;
}

Matrix Matrix::operator-() const {
    Matrix res = *this;
    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            res.mat_[y][x] *= -1;
        }
    }
    return res;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    CheckSameSize(other);
    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            mat_[y][x] += other.mat_[y][x];
        }
    }
    return *this;
}
Matrix& Matrix::operator-=(const Matrix& other) {
    CheckSameSize(other);
    *this += -other;
    return *this;
}
Matrix& Matrix::operator*=(const Matrix& other) {
    CheckMultiplicationSize(other);
    Matrix res(height_, other.width_);
    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < other.width_; ++j) {
            for (size_t k = 0; k < width_; ++k) {
                res.mat_[i][j] += mat_[i][k] * other.mat_[k][j];
            }
        }
    }
    *this = res;
    return *this;
}
Matrix& Matrix::operator*=(const long long& other) {
    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            mat_[y][x] *= other;
        }
    }
    return *this;
}
Matrix& Matrix::operator*=(const Fraction& other) {
    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            mat_[y][x] *= other;
        }
    }
    return *this;
}
Matrix& Matrix::operator/=(const long long& other) {
    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            mat_[y][x] /= other;
        }
    }
    return *this;
}
Matrix& Matrix::operator/=(const Fraction& other) {
    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            mat_[y][x] /= other;
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const {
    Matrix result = *this;
    result += other;
    return result;
}
Matrix Matrix::operator-(const Matrix& other) const {
    Matrix result = *this;
    result -= other;
    return result;
}
Matrix Matrix::operator*(const Matrix& other) const {
    Matrix result = *this;
    result *= other;
    return result;
}
Matrix Matrix::operator*(const long long& other) const {
    Matrix result = *this;
    result *= other;
    return result;
}
Matrix Matrix::operator*(const Fraction& other) const {
    Matrix result = *this;
    result *= other;
    return result;
}
Matrix Matrix::operator/(const long long& other) const {
    Matrix result = *this;
    result /= other;
    return result;
}
Matrix Matrix::operator/(const Fraction& other) const {
    Matrix result = *this;
    result /= other;
    return result;
}

void Matrix::CheckSameSize(const Matrix& other) const {
    if (other.height_ != height_ && other.width_ != width_) {
        throw MatrixWrongSize();
    }
}
void Matrix::CheckMultiplicationSize(const Matrix& other) const {
    if (other.height_ != width_) {
        throw MatrixWrongSize();
    }
}

Matrix::ColumnWidth Matrix::CalculateColumnWidth() const {
    ColumnWidth result(width_);
    for (size_t x = 0; x < width_; ++x) {
        result[x] = 0;
        for (size_t y = 0; y < height_; ++y) {
            result[x] = std::max(result[x], mat_[y][x].StringLength());
        }
    }
    return result;
}
void PrintSpaces(std::ostream& out, const size_t& spaces_amount) {
    for (size_t i = 0; i < spaces_amount; ++i) {
        out << ' ';
    }
}

std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
    Matrix::ColumnWidth column_width = matrix.CalculateColumnWidth();
    for (size_t y = 0; y < matrix.height_; ++y) {
        for (size_t x = 0; x < matrix.width_; ++x) {
            if (x == matrix.split_ && x != 0) {
                out << " | ";
            }
            size_t spaces_amount = column_width[x] - matrix.mat_[y][x].StringLength() + 1;
            if (static_cast<double>(matrix.mat_[y][x]) >= 0) {
                out << " ";
                --spaces_amount;
            }
            out << matrix.mat_[y][x];
            PrintSpaces(out, spaces_amount);
        }
        out << std::endl;
    }
    return out;
}
std::istream& operator>>(std::istream& in, Matrix& matrix) {
    for (size_t y = 0; y < matrix.height_; ++y) {
        for (size_t x = 0; x < matrix.width_; ++x) {
            in >> matrix.mat_[y][x];
        }
    }
    return in;
}

Matrix E(const Matrix& matrix) {
    Matrix res(matrix.height_, matrix.height_);
    for (size_t i = 0; i < matrix.height_; ++i) {
        res.mat_[i][i] = 1;
    }
    return res;
}
void Matrix::SimetrickGauss() {
    for (int i = 0; i < height_; ++i) {
        if (mat_[i][i] == 0) {
            int first = i;
            for (int k = i + 1; k < height_; ++k) {
                if (mat_[i][k] != 0) {
                    first = k;
                    break;
                }
            }
            if (first != i) {
                Op1_s(first, i, 1);
                std::cout << "1_ " << first + 1 << " " << i + 1 << " 1" << std::endl << *this << std::endl;
            } else {
                continue;
            }
        }
        for (int k = i + 1; k < height_; ++k) {
            if (mat_[i][k] != 0) {
                std::cout << "1_ " << i + 1 << " " << k + 1 << " " << (-mat_[i][k] / mat_[i][i]) << std::endl;
                Op1_s(i, k, -mat_[i][k] / mat_[i][i]);
                std::cout << *this << std::endl;
            }
        }
    }
    for (int i = 0; i < height_; ++i) {
        if (mat_[i][i] != 0) {
            Fraction multiplier = GreatestSq(mat_[i][i]);
            std::cout << "3_ " << i + 1 << " " << multiplier << std::endl;
            Op3_s(i, multiplier);
            std::cout << *this << std::endl;
        }
    }
};