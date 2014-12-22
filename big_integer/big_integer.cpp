#include "big_integer.h"

#include <cstring>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <algorithm>

// default constructor
big_integer::big_integer()
{
    negative = false;
    digits.push_back(0);
}

// copy constructor
big_integer::big_integer(big_integer const& other)
{
    digits.assign(other.digits.begin(), other.digits.end());
    negative = other.negative;
    erase_zero();
}

// move constructor
big_integer::big_integer(big_integer&& other) {
    negative = other.negative;
    digits = std::move(other.digits);
}

// default int constructor
big_integer::big_integer(int b)
{
    if (b < 0)
    {
        negative = true;
        b = -b;
    }
    else
    {
        negative = false;
    }
    while (b >= BASE)
    {
        digits.push_back(b % BASE);
        b /= BASE;
    }
    digits.push_back(b);
}

// default string constructor
big_integer::big_integer(std::string const& str)
{
    try {
        digits.push_back(0);
        for (size_t i = 0 + (str[0] == '-'); i < str.size(); i++)
            if (str[i] >= '0' && str[i] <= '9' ) {
		mul_on_short(10);
                int value = (int)(str[i] - '0');
		add(value, 0);
	    }
            else
                throw i;

        if (str[0] == '-')
            negative = true;

	erase_zero();

     } catch (int e) {
            std::cerr << std::endl << "symbol " << e + 1 << " is invalid ";
            throw std::invalid_argument("");
     }
}

// destructor
big_integer::~big_integer()
{
    digits.clear();
}

void big_integer::erase_zero()
{
    while (digits.size() > 1 && digits.back() == 0)
    {
        digits.pop_back();
    }
    if (digits.back() == 0)
    {
        negative = false;
    }
}

// assigment operator
big_integer& big_integer::operator=(big_integer const& other)
{
    digits.assign(other.digits.begin(), other.digits.end());
    negative = other.negative;
    erase_zero();
    return *this;
}

// void using for big_integer_cmp
int depend_on_sign(int res, bool sign, bool ignore_sign)
{
    if (ignore_sign)
    {
        return res;
    }
    if (!sign)
    {
        return res;
    }
    else
    {
        return 0 - res;
    }
}

// comparation this number with another big_number
// if ignore_sign than function compare two non-negative numbers
int big_integer::big_integer_cmp(big_integer const& b, bool ignore_sign = false) const
{
    if (digits.back() == 0 && b.digits.back() == 0)
    {
        return 0;
    }
    if (!ignore_sign)
    {
        if (negative && !b.negative)
        {
            return -1;
        }
        else if (!negative && b.negative)
        {
            return 1;
        }
    }
    if (digits.size() > b.digits.size())
    {
        return depend_on_sign(1, negative, ignore_sign);
    }
    else if (digits.size() < b.digits.size())
    {
        return depend_on_sign(-1, negative, ignore_sign);
    }
    else
    {
        // size of numbers are equals
        // that's why we compare digits
        auto brit = b.digits.rbegin();
        for (auto rit = digits.rbegin(); rit != digits.rend(); rit++)
        {
            if (*rit > *brit)
            {
                return depend_on_sign(1, negative, ignore_sign);
            }
            else if (*rit < *brit)
            {
                return depend_on_sign(-1, negative, ignore_sign);
            }
            brit++;
        }
        return 0;
    }
}

// add not paying attention on sign of numbers
// shift means that b = b * BASE^shift
big_integer& big_integer::add(big_integer const& b, size_t shift = 0)
{
    int carry = 0;
    for (size_t i = 0; i < b.digits.size() || carry; i++)
    {
        while (i + shift >= digits.size())
        {
            digits.push_back(0);
        }
        digits[i + shift] = digits[i + shift] + (i >= b.digits.size() ? 0 : b.digits[i]) + carry;
        if (digits[i + shift] >= BASE)
        {
            carry = 1;
            digits[i + shift] -= BASE;
        }
        else
        {
            carry = 0;
        }
    }
    erase_zero();
    return *this;
}

// subtract not paying attention on sign of numbers
// shift means that b = b * BASE^shift
big_integer& big_integer::subtract(big_integer const& b, size_t shift = 0)
{
    int carry = 0;
    for (size_t i = 0; i < b.digits.size(); i++)
    {
        while (i + shift >= digits.size())
        {
            digits.push_back(0);
        }
        digits[i + shift] -= b.digits[i] + carry;
        if (digits[i + shift] < 0)
        {
            carry = 1;
            digits[i + shift] += BASE;
        }
        else
        {
            carry = 0;
        }
    }
    // if b is bigger than this we need to do this = BASE^digits.size() - this
    if (carry == 1 && b.digits.size() + shift == digits.size())
    {
        carry = 0;
        for (auto it = digits.begin(); it != digits.end(); it++)
        {
            *it = 0 - (*it) - carry;
            if (*it < 0)
            {
                *it += BASE;
                carry = 1;
            }
            else
            {
                carry = 0;
            }
        }
        negative ^= 1;
    }
    else
    {
        size_t j = b.digits.size() + shift;
        while (carry > 0)
        {
            digits[j] -= carry;
            if (digits[j] < 0)
            {
                digits[j] += BASE;
            }
            else
            {
                carry = 0;
            }
            j++;
        }
    }
    erase_zero();
    return *this;
}

// operator of addition big_integer
big_integer& big_integer::operator+=(big_integer const& rhs)
{
    if (negative != rhs.negative)
    {
        subtract(rhs);
    }
    else
    {
        add(rhs);
    }
    return *this;
}

// operator of subtraction big_integer
big_integer& big_integer::operator-=(big_integer const& rhs)
{
    if (negative != rhs.negative)
    {
        add(rhs);
    }
    else
    {
        subtract(rhs);
    }
    return *this;
}

// multiply this on digit
big_integer& big_integer::mul_on_short(int rhs)
{
    long long cur = 0;
    for (size_t i = 0; i < digits.size() || cur; i++)
    {
        if (i == digits.size())
        {
            digits.push_back(0);
        }
        cur += 1ll * rhs*digits[i];
        digits[i] = (cur % BASE);
        cur >>= ST;
    }
    erase_zero();
    return *this;
}

// operator of multiplication big_integer
big_integer& big_integer::operator*=(big_integer const& rhs)
{
    negative ^= rhs.negative;
    if (rhs.digits.size() == 1)
    {
        return mul_on_short(rhs.digits.back());
    }
    std::vector<int> a(digits.begin(), digits.end());
    digits.assign(a.size() + rhs.digits.size(), 0);
    for (size_t i = 0; i < a.size(); i++)
    {
        int carry = 0;
        for (size_t j = 0; j < rhs.digits.size(); j++)
        {
            long long now = digits[i + j] + 1ll * a[i] * rhs.digits[j] + carry;
            digits[i + j] = now % BASE;
            carry = now / BASE;
        }
        if (carry)
        {
            digits[i + rhs.digits.size()] += carry;
        }
    }
    erase_zero();
    return *this;
}

// divide this on digit
big_integer& big_integer::divide_on_short(int rhs)
{
    long long cur = 0;
    for (auto rit = digits.rbegin(); rit != digits.rend(); rit++)
    {
        cur = (cur * BASE) + *rit;
        *rit = (cur / rhs);
        cur %= rhs;
    }
    erase_zero();
    return *this;
}

int big_integer::module_of_short(int rhs)
{
    int carry = 0;
    for (auto rit = digits.rbegin(); rit != digits.rend(); rit++)
    {
        carry = (int)((*rit * 1ll + carry * 1ll * BASE) % rhs);
    }
    return carry;
}

// result = this - b*multiplier*BASE^shift
// last digit can be negative
big_integer& big_integer::subtract_for_division(const big_integer &b, int multiplier, size_t shift)
{
    if (multiplier == 0)
    {
        return *this;
    }
    int carry_mul = 0;
    int carry_sub = 0;
    long long tmpRes = 0;
    for (size_t i = 0; i < b.digits.size() || carry_sub || carry_mul; i++)
    {
        tmpRes = 1ll * multiplier*(i < b.digits.size() ? b.digits[i] : 0) + carry_mul;
        if (i + shift == digits.size())
        {
            digits.push_back(0);
        }
        digits[i + shift] -= carry_sub + (int)(tmpRes % BASE);
        carry_mul = (int)(tmpRes / BASE);
        if (digits[i + shift] < 0)
        {
            if (carry_mul > 0
                || i + 1 < b.digits.size()
                || i + shift + 1 < digits.size()
                )
            {
                carry_sub = 1;
                digits[i + shift] += BASE;
            }
            else
            {
                carry_sub = 0;
            }
        }
        else
        {
            carry_sub = 0;
        }
    }
    erase_zero();
    return *this;
}

// operator of division big_integer
big_integer& big_integer::operator/=(big_integer const& rhs)
{
    negative ^= rhs.negative;
    // optimize for short numbers
    if (rhs.digits.size() == 1)
    {
        return divide_on_short(rhs.digits.back());
    }
    int n = rhs.digits.size();
    int m = digits.size() - n;
    if (big_integer_cmp(rhs, true) < 0)
    {
        *this = 0;
        return *this;
    }
    big_integer divider(rhs);
    big_integer dividend(*this);
    divider.negative = false;
    dividend.negative = false;
    // normalization of numbers
    if (divider.digits.back() < BASE / 2)
    {
        int tmp_mul = BASE / (divider.digits.back() + 1);
        divider.mul_on_short(tmp_mul);
        dividend.mul_on_short(tmp_mul);
        n = divider.digits.size();
        m = dividend.digits.size() - n;
    }
    digits.resize(m + 1);
    if (dividend.subtract_for_division(divider, 1, m).digits.back() >= 0)
    {
        digits[m] = 1;
    }
    else
    {
        digits[m] = 0;
        dividend.add(divider, m);
    }
    size_t j = m - 1;
    for (auto rit = ++digits.rbegin(); rit != digits.rend(); rit++)
    {
        *rit = (std::min(1ll * BASE - 1,
            (1ll * (n + j < dividend.digits.size() ? dividend.digits[n + j] : 0) * BASE
            + (n + j - 1 < dividend.digits.size() ? dividend.digits[n + j - 1] : 0))
            / divider.digits.back()));
        dividend.subtract_for_division(divider, *rit, j);
        while (dividend.digits.back() < 0)
        {
            (*rit)--;
            dividend.add(divider, j);
        }
        j--;
    }
    erase_zero();
    return *this;
}

// operator of module of big_integer
big_integer& big_integer::operator%=(big_integer const& rhs)
{
    int n = rhs.digits.size();
    int m = digits.size() - n;
    if (big_integer_cmp(rhs, true) < 0)
    {
        return *this;
    }
    big_integer divider = rhs;
    bool was_negative = negative;
    divider.negative = false;
    negative = false;
    int tmp_mul = BASE / (divider.digits.back() + 1);
    // normalization
    if (divider.digits.back() < BASE / 2)
    {
        divider.mul_on_short(tmp_mul);
        mul_on_short(tmp_mul);
        n = divider.digits.size();
        m = digits.size() - n;
    }
    if (subtract_for_division(divider, 1, m).digits.back() < 0)
    {
        add(divider, m);
    }
    for (size_t j = m; j-- > 0;)
    {
        subtract_for_division(divider,
            std::min(1ll * BASE - 1,
            (1ll * (n + j < digits.size() ? digits[n + j] : 0) * BASE
            + (n + j - 1 < digits.size() ? digits[n + j - 1] : 0))
            / divider.digits.back())
            , j);
        while (digits.back() < 0)
        {
            add(divider, j);
        }
    }
    negative = was_negative;
    erase_zero();
    if (tmp_mul > 1)
    {
        divide_on_short(tmp_mul);
    }
    return *this;
}

// unary plus
big_integer big_integer::operator+() const
{
    return *this;
}

// unary minus
big_integer big_integer::operator-() const
{
    big_integer r = *this;
    r.negative ^= 1;
    return r;
}

// operator of addition two big_integer
big_integer operator+(big_integer a, big_integer const& b)
{
    return a += b;
}

// operator of subtraction two big_integer
big_integer operator-(big_integer a, big_integer const& b)
{
    return a -= b;
}

// operator of multiplication two big_integer
big_integer operator*(big_integer a, big_integer const& b)
{
    return a *= b;
}

// operator of division two big_integer
big_integer operator/(big_integer a, big_integer const& b)
{
    return a /= b;
}

// operator of module
big_integer operator%(big_integer a, big_integer const& b)
{
    return a %= b;
}

// big_integer to string
// using for output to the stream
std::string to_string(big_integer const& b)
{
    std::string res = "";
    big_integer a = b;

    if (a.big_integer_cmp(0, true) == 0)
    {
        return "0";
    }

    while (a.digits.back() >= 10 || a.digits.size() > 1)
    {
        res.append(std::to_string(a.module_of_short(10)));
        a.divide_on_short(10);
    }
    res.append(std::to_string(a.digits.back()));
    if (a.negative)
    {
        res.append("-");
    }
    std::reverse(res.begin(), res.end());
    return res;
}

// output to the stream
std::ostream& operator<<(std::ostream& os, big_integer const& a)
{
    return os << to_string(a);
}

// input from the stream
std::istream& operator>>(std::istream & is, big_integer& a)
{
    std::string str;
    is >> str;
    a = big_integer(str);
    return is;
}
