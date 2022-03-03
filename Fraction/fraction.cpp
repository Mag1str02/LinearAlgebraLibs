#include "fraction.h"

#include <numeric>
#include <sstream>
#include <tuple>

Fraction::Fraction() : numerator_(0), denominator_(1){};
Fraction::Fraction(long long integer) : numerator_(integer), denominator_(1){};
Fraction::Fraction(long long numerator, long long denominator) : numerator_(numerator), denominator_(denominator) {
    Simplify();
};
Fraction::Fraction(Fraction&& other) : numerator_(other.numerator_), denominator_(other.denominator_) {
    other.numerator_ = 0;
    other.denominator_ = 0;
}
Fraction::Fraction(const Fraction& other) : numerator_(other.numerator_), denominator_(other.denominator_) {
}

Fraction& Fraction::operator=(const Fraction& other) {
    numerator_ = other.numerator_;
    denominator_ = other.denominator_;
    return *this;
}
Fraction& Fraction::operator=(const long long& other) {
    numerator_ = other;
    denominator_ = 1;
    return *this;
}
Fraction& Fraction::operator=(Fraction&& other) {
    numerator_ = other.numerator_;
    denominator_ = other.denominator_;
    other.numerator_ = 0;
    other.denominator_ = 0;
    return *this;
}

Fraction Fraction::operator-() const {
    Fraction result = *this;
    result.numerator_ = -numerator_;
    return result;
}

Fraction& Fraction::operator+=(const Fraction& other) {
    numerator_ = numerator_ * other.denominator_ + denominator_ * other.numerator_;
    denominator_ = denominator_ * other.denominator_;
    Simplify();
    return *this;
}
Fraction& Fraction::operator-=(const Fraction& other) {
    *this += -other;
    return *this;
}
Fraction& Fraction::operator*=(const Fraction& other) {
    numerator_ *= other.numerator_;
    denominator_ *= other.denominator_;
    Simplify();
    return *this;
}
Fraction& Fraction::operator/=(const Fraction& other) {
    numerator_ *= other.denominator_;
    denominator_ *= other.numerator_;
    Simplify();
    return *this;
}

Fraction& Fraction::operator+=(const long long& other) {
    numerator_ += denominator_ * other;
    Simplify();
    return *this;
}
Fraction& Fraction::operator-=(const long long& other) {
    numerator_ -= denominator_ * other;
    Simplify();
    return *this;
}
Fraction& Fraction::operator*=(const long long& other) {
    numerator_ *= other;
    Simplify();
    return *this;
}
Fraction& Fraction::operator/=(const long long& other) {
    denominator_ *= other;
    Simplify();
    return *this;
}

Fraction Fraction::operator+(const Fraction& other) const {
    Fraction result = *this;
    result += other;
    return result;
}
Fraction Fraction::operator-(const Fraction& other) const {
    Fraction result = *this;
    result -= other;
    return result;
}
Fraction Fraction::operator*(const Fraction& other) const {
    Fraction result = *this;
    result *= other;
    return result;
}
Fraction Fraction::operator/(const Fraction& other) const {
    Fraction result = *this;
    result /= other;
    return result;
}

Fraction Fraction::operator+(const long long& other) const {
    Fraction result = *this;
    result += other;
    return result;
}
Fraction Fraction::operator-(const long long& other) const {
    Fraction result = *this;
    result -= other;
    return result;
}
Fraction Fraction::operator*(const long long& other) const {
    Fraction result = *this;
    result *= other;
    return result;
}
Fraction Fraction::operator/(const long long& other) const {
    Fraction result = *this;
    result /= other;
    return result;
}

Fraction operator+(const long long& integer, const Fraction& fraction) {
    return fraction + integer;
}
Fraction operator-(const long long& integer, const Fraction& fraction) {
    return -(fraction - integer);
}
Fraction operator*(const long long& integer, const Fraction& fraction) {
    return fraction * integer;
}
Fraction operator/(const long long& integer, const Fraction& fraction) {
    Fraction result = integer;
    result /= fraction;
    return result;
}

bool Fraction::operator==(const Fraction& other) const {
    return numerator_ == other.numerator_ && denominator_ == other.denominator_;
}
bool Fraction::operator==(const int& other) const {
    return double(numerator_) / denominator_ == other;
}
bool Fraction::operator!=(const Fraction& other) const {
    return numerator_ != other.numerator_ || denominator_ != other.denominator_;
}
bool Fraction::operator!=(const int& other) const {
    return double(numerator_) / denominator_ != other;
}

bool Fraction::operator<=(const Fraction& other) const {
    return std::tie(numerator_, denominator_) <= std::tie(other.numerator_, other.denominator_);
}
bool Fraction::operator>=(const Fraction& other) const {
    return std::tie(numerator_, denominator_) >= std::tie(other.numerator_, other.denominator_);
}
bool Fraction::operator<(const Fraction& other) const {
    return std::tie(numerator_, denominator_) < std::tie(other.numerator_, other.denominator_);
}
bool Fraction::operator>(const Fraction& other) const {
    return std::tie(numerator_, denominator_) > std::tie(other.numerator_, other.denominator_);
}

Fraction::operator double() const {
    return static_cast<double>(numerator_) / denominator_;
}

std::ostream& operator<<(std::ostream& out, const Fraction& Fraction) {
    if (Fraction.denominator_ == 1) {
        out << Fraction.numerator_;
    } else {
        out << Fraction.numerator_ << '/' << Fraction.denominator_;
    }

    return out;
}
std::istream& operator>>(std::istream& in, Fraction& Fraction) {
    std::string s;
    in >> s;
    size_t id_of_slash = s.find('/');
    if (id_of_slash != std::string::npos) {
        Fraction.numerator_ = stoll(s.substr(0, id_of_slash));
        Fraction.denominator_ = stoll(s.substr(id_of_slash + 1, s.size() - id_of_slash - 1));
        return in;
    }
    Fraction.numerator_ = std::stoll(s);
    Fraction.denominator_ = 1;
    return in;
}

size_t Fraction::StringLength() const {
    std::stringstream stream;
    stream << *this;
    return stream.str().size();
}
void Fraction::Simplify() {
    long long nod = std::gcd(numerator_, denominator_);
    numerator_ /= nod;
    denominator_ /= nod;
    if (denominator_ < 0) {
        denominator_ *= -1;
        numerator_ *= -1;
    }
    if (numerator_ == 0) {
        denominator_ = 1;
    }
}
Fraction GreatestSq(const Fraction& fraction) {
    Fraction result = 1;
    for (size_t i = std::abs(fraction.numerator_); i > 0; --i) {
        if ((std::abs(fraction.numerator_) % (i * i)) == 0) {
            result.denominator_ = i;
            break;
        }
    }
    for (size_t i = fraction.denominator_; i > 0; --i) {
        if (fraction.denominator_ % (i * i) == 0) {
            result.numerator_ = i;
            break;
        }
    }
    result.Simplify();
    return result;
}