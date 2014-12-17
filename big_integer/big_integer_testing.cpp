#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <utility>
#include <gtest/gtest.h>

#include "big_integer.h"

TEST(correctness, two_plus_two)
{
    EXPECT_EQ(big_integer(2) + big_integer(2), big_integer(4));
    EXPECT_EQ(big_integer(2) + 2             , 4); // implicit converion from int must work
    EXPECT_EQ(2              + big_integer(2), 4);
}

TEST(correctness, default_ctor)
{
    big_integer a;
    big_integer b = 0;
    EXPECT_EQ(a, 0);
    EXPECT_EQ(a, b);
}

TEST(correctness, copy_ctor)
{
    big_integer a = 3;
    big_integer b = a;

    EXPECT_EQ(a, b);
    EXPECT_EQ(b, 3);
}

TEST(correctness, copy_ctor_real_copy)
{
    big_integer a = 3;
    big_integer b = a;
    a = 5;

    EXPECT_EQ(b, 3);
}

TEST(correctness, copy_ctor_real_copy2)
{
    big_integer a = 3;
    big_integer b = a;
    b = 5;

    EXPECT_EQ(a, 3);
}

TEST(correctness, assignment_operator)
{
    big_integer a = 4;
    big_integer b = 7;
    b = a;

    EXPECT_EQ(a, b);
}

TEST(correctness, self_assignment)
{
    big_integer a = 5;
    a = a;

    EXPECT_EQ(a, 5);
}

TEST(correctness, assignment_return_value)
{
    big_integer a = 4;
    big_integer b = 7;
    (a = b) = a;

    EXPECT_EQ(a, 7);
    EXPECT_EQ(b, 7);
}

TEST(correctness, compare_zero_and_minus_zero)
{
    big_integer a;
    big_integer b = -a;

    EXPECT_EQ(a, b);
}

TEST(correctness, add)
{
    big_integer a = 5;
    big_integer b = 20;

    EXPECT_EQ(a + b, 25);

    a += b;
    EXPECT_EQ(a, 25);
}

TEST(correctness, add_signed)
{
    big_integer a = 5;
    big_integer b = -20;

    EXPECT_EQ(a + b, -15);

    a += b;
    EXPECT_EQ(a, -15);
}

TEST(correctness, add_return_value)
{
    big_integer a = 5;
    big_integer b = 1;

    (a += b) += b;
    EXPECT_EQ(a, 7);
}

TEST(correctness, sub)
{
    big_integer a = 20;
    big_integer b = 5;

    EXPECT_EQ(a - b, 15);

    a -= b;
    EXPECT_EQ(a, 15);
}

TEST(correctness, sub_signed)
{
    big_integer a = 5;
    big_integer b = 20;

    EXPECT_EQ(a - b, -15);

    a -= b;
    EXPECT_EQ(a, -15);

    a -= -100;
    EXPECT_EQ(a, 85);
}

TEST(correctness, sub_return_value)
{
    big_integer a = 5;
    big_integer b = 1;

    (a -= b) -= b;
    EXPECT_EQ(a, 3);
}

TEST(correctness, mul)
{
    big_integer a = 5;
    big_integer b = 20;

    EXPECT_EQ(a * b, 100);

    a *= b;
    EXPECT_EQ(a, 100);
}

TEST(correctness, mul_signed)
{
    big_integer a = -5;
    big_integer b = 20;

    EXPECT_EQ(a * b, -100);

    a *= b;
    EXPECT_EQ(a, -100);
}

TEST(correctness, mul_return_value)
{
    big_integer a = 5;
    big_integer b = 2;

    (a *= b) *= b;
    EXPECT_EQ(a, 20);
}

TEST(correctness, div_)
{
    big_integer a = 20;
    big_integer b = 5;
    big_integer c = 20;

    EXPECT_EQ(a / b, 4);
    EXPECT_EQ(a % b, 0);

    a /= b;
    EXPECT_EQ(a, 4);

    c %= b;
    EXPECT_EQ(c, 0);
}

TEST(correctness, div_signed)
{
    big_integer a = -20;
    big_integer b = 5;

    EXPECT_EQ(a / b, -4);
    EXPECT_EQ(a % b, 0);
}

TEST(correctness, div_rounding)
{
    big_integer a = 23;
    big_integer b = 5;

    EXPECT_EQ(a / b, 4);
    EXPECT_EQ(a % b, 3);
}

TEST(correctness, div_rounding_negative)
{
    big_integer a = 23;
    big_integer b = -5;
    big_integer c = -23;
    big_integer d = 5;

    EXPECT_EQ(a / b, -4);
    EXPECT_EQ(c / d, -4);
    EXPECT_EQ(a % b, 3);
    EXPECT_EQ(c % d, -3);
}

TEST(correctness, div_return_value)
{
    big_integer a = 100;
    big_integer b = 2;

    (a /= b) /= b;
    EXPECT_EQ(a, 25);
}

TEST(correctness, unary_plus)
{
    big_integer a = 123;
    big_integer b = +a;

    EXPECT_EQ(a, b);

}

TEST(correctness, negation)
{
    big_integer a = 666;
    big_integer b = -a;

    EXPECT_EQ(b, -666);
}

TEST(correctness, add_long)
{
    big_integer a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    big_integer b(                                                     "100000000000000000000000000000000000000");
    big_integer c("10000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000");

    EXPECT_EQ(a + b, c);
}

TEST(correctness, add_long_signed)
{
    big_integer a("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    big_integer b( "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

    EXPECT_EQ(a + b, 0);
}

TEST(correctness, add_long_signed2)
{
    big_integer a("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    big_integer b(                                                     "100000000000000000000000000000000000000");
    big_integer c( "-999999999999999999999999999999999999999999999999999900000000000000000000000000000000000000");

    EXPECT_EQ(a + b, c);
}

TEST(correctness, add_long_pow2)
{
    big_integer a( "18446744073709551616");
    big_integer b("-18446744073709551616");
    big_integer c( "36893488147419103232");

    EXPECT_EQ(a + a, c);
    EXPECT_EQ(b + c, a);
    EXPECT_EQ(c + b, a);
}

TEST(correctness, sub_long)
{
    big_integer a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    big_integer b(                                                     "100000000000000000000000000000000000000");
    big_integer c( "9999999999999999999999999999999999999999999999999999900000000000000000000000000000000000000");

    EXPECT_EQ(a - b, c);
}

TEST(correctness, mul_long)
{
    big_integer a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    big_integer b(                                                     "100000000000000000000000000000000000000");
    big_integer c("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
                                                                        "00000000000000000000000000000000000000");

    EXPECT_EQ(a * b, c);
}

TEST(correctness, mul_long_signed)
{
    big_integer a("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    big_integer b(                                                     "100000000000000000000000000000000000000");
    big_integer c("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
                                                                        "00000000000000000000000000000000000000");

    EXPECT_EQ(a * b, c);
}

TEST(correctness, mul_long_signed2)
{
    big_integer a("-100000000000000000000000000");
    big_integer c("100000000000000000000000000"
                   "00000000000000000000000000");

    EXPECT_EQ(a * a, c);
}

TEST(correctness, mul_long_pow2)
{
    big_integer a("18446744073709551616");
    big_integer b("340282366920938463463374607431768211456");
    big_integer c("115792089237316195423570985008687907853269984665640564039457584007913129639936");

    EXPECT_EQ(a * a, b);
    EXPECT_EQ(b * b, c);
}

TEST(correctness, div_long)
{
    big_integer a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    big_integer b(                                                     "100000000000000000000000000000000000000");
    big_integer c("100000000000000000000000000000000000000000000000000000");

    EXPECT_EQ(a / b, c);
}

TEST(correctness, div_long_signed)
{
    big_integer a("-10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    big_integer b(                                                      "100000000000000000000000000000000000000");
    big_integer c("-100000000000000000000000000000000000000000000000000000");

    EXPECT_EQ(a / b, c);
}

TEST(correctness, div_long_signed2)
{
    big_integer a("-10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    big_integer b(                                                     "-100000000000000000000000000000000000000");
    big_integer c( "100000000000000000000000000000000000000000000000000000");

    EXPECT_EQ(a / b, c);
}

TEST(correctness, negation_long)
{
    big_integer a( "10000000000000000000000000000000000000000000000000000");
    big_integer c("-10000000000000000000000000000000000000000000000000000");

    EXPECT_EQ(-a, c);
    EXPECT_EQ(a, -c);
}

TEST(correctness, string_conv)
{
    EXPECT_EQ(to_string(big_integer("100")), "100");
    EXPECT_EQ(to_string(big_integer("0100")), "100");
    EXPECT_EQ(to_string(big_integer("0")), "0");
    EXPECT_EQ(to_string(big_integer("-0")), "0");
    EXPECT_EQ(to_string(big_integer("-1000000000000000")), "-1000000000000000");
}


namespace
{
    unsigned const number_of_iterations = 10;
    size_t const number_of_multipliers = 1000;

    int myrand()
    {
        int val = rand() - RAND_MAX / 2;
        if (val != 0)
            return val;
        else
            return 1;
    }
}

TEST(correctness, mul_div_randomized)
{
    for (unsigned itn = 0; itn != number_of_iterations; ++itn)
    {
        std::vector<int> multipliers;

        for (size_t i = 0; i != number_of_multipliers; ++i)
            multipliers.push_back(myrand());

        big_integer accumulator = 1;

        for (size_t i = 0; i != number_of_multipliers; ++i)
            accumulator *= multipliers[i];

        std::random_shuffle(multipliers.begin(), multipliers.end());

        for (size_t i = 1; i != number_of_multipliers; ++i)
            accumulator /= multipliers[i];

        EXPECT_EQ(accumulator, multipliers[0]);
    }
}

namespace
{
    template <typename T>
    void erase_unordered(std::vector<T>& v, typename std::vector<T>::iterator pos)
    {
        std::swap(v.back(), *pos);
        v.pop_back();
    }

    template <typename T>
    T extract_random_element(std::vector<T>& v)
    {
        size_t index = rand() % v.size();
        T copy = v[index];
        erase_unordered(v, v.begin() + index);
        return copy;
    }

    template <typename T>
    void merge_two(std::vector<T>& v)
    {
        assert(v.size() >= 2);

        T a = extract_random_element(v);
        T b = extract_random_element(v);

        T ab = a * b;
        ASSERT_EQ(ab / a, b);
        ASSERT_EQ(ab / b, a);

        v.push_back(ab);
    }

    template <typename T>
    T merge_all(std::vector<T> v)
    {
        assert(!v.empty());

        while (v.size() >= 2)
            merge_two(v);

        return v[0];
    }
}

TEST(correctness, mul_merge_randomized)
{
    for (unsigned itn = 0; itn != number_of_iterations; ++itn)
    {
        std::vector<big_integer> x;
        for (size_t i = 0; i != number_of_multipliers; ++i)
            x.push_back(myrand());

        big_integer a = merge_all(x);
        big_integer b = merge_all(x);

        EXPECT_EQ(a, b);
    }
}
