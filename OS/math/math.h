#pragma once


template <typename integerTypes> 
concept Integer = __is_integral(integerTypes);

namespace Math
 {

        /** Absolute value of x*/
        template <Integer ints> ints abs(ints x);

        /** Multiply x and y */
        template <Integer ints> ints multiply(ints x, ints y);

        /** Divide x by y */
        template <Integer ints> ints divide(ints x, ints y);

        /** Return smallest value between x and y */
        template <Integer ints> ints min(ints x, ints y);

        /** Return greatest value between x and y */
        template <Integer ints> ints max(ints x, ints y);

        /** Return square root of x */
        template <Integer ints> ints sqrt(ints x);

        /** Round value up to the next multiple of alignment (alignment must be a power of 2) */
        template <Integer ints> ints alignUp(const ints value, const ints alignment);

        template <Integer ints> constexpr ints minOf();
        template <Integer ints> constexpr ints maxOf();

};

#include "math.tpp"
