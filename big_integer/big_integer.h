#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <iosfwd>
#include <vector>

const int ST = 30;
const int BASE = (1 << ST);

struct big_integer
{

private:
    // sometimes digits can be negative
    std::vector<int> digits;
    bool negative;

    // deleting leading zero from number
    void erase_zero();

    big_integer& add(big_integer const& b, size_t shift);
    big_integer& subtract(big_integer const& b, size_t shift);

    int big_integer_cmp(big_integer const& b, bool ignore_sign) const;

    big_integer& mul_on_short(int rhs);
    big_integer& divide_on_short(int rhs);

    big_integer& subtract_for_division(big_integer const& b, int multiplier, size_t shift);

    int module_of_short(int rhs);

public:
    // default constructor
    big_integer();
    // copy constructor
    big_integer(big_integer const& other);
    // move constructor
    big_integer(big_integer&& other);
    // default int constructor
    big_integer(int b);
    // default string constructor
    explicit big_integer(std::string const& str);
    // destructor
    ~big_integer();

    // assigment operator
    big_integer& operator=(big_integer const& other);
    // operator of addition big_integer
    big_integer& operator+=(big_integer const& rhs);
    // operator of subtraction big_integer
    big_integer& operator-=(big_integer const& rhs);
    // operator of multiplication big_integer
    big_integer& operator*=(big_integer const& rhs);
    // operator of division big_integer
    big_integer& operator/=(big_integer const& rhs);
    // operator of module of big_integer
    big_integer& operator%=(big_integer const& rhs);

    // unary plus
    big_integer operator+() const;
    // unary minus
    big_integer operator-() const;

    // big_integer to string
    // using for output to the stream
    friend std::string to_string(big_integer const& a);

    // operator of addition two big_integer
    friend big_integer operator+(big_integer a, big_integer const& b);
    // operator of subtraction two big_integer
    friend big_integer operator-(big_integer a, big_integer const& b);
    // operator of multiplication two big_integer
    friend big_integer operator*(big_integer a, big_integer const& b);
    // operator of division two big_integer
    friend big_integer operator/(big_integer a, big_integer const& b);
    // operator of module
    friend big_integer operator%(big_integer a, big_integer const& b);

    // output to the stream
    friend std::ostream& operator<<(std::ostream& os, big_integer const& a);
    // input from the stream
    friend std::istream & operator>>(std::istream & is, big_integer &a);
};

#endif // BIG_INTEGER_H
