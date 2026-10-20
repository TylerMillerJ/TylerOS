#pragma once

#include "panic/panic.h"

//Tempate integer ensures the floats are not used in the kernel math functions

namespace Math {

template <Integer ints> 
ints abs(const ints x) {
    if (x < 0) 
    {
        if (x == ints(ints(1) << (sizeof(ints) * 8 - 1))) //min negative value of given int type
         {
            panic("lowest Valued Int Does Not Have Posotive Correspondant");
        }   
    return ~x + 1;
    }
return x;
}


template <Integer ints> 
ints multiply(const ints x, const ints y) {
    
    if (x == 0 || y == 0) {
        return 0;
    }
    
    ints mask = 1;
    ints result = 0;
    ints bitShifted = x;
    ints bitCount = sizeof(ints) * 8;

    for (int i = 0; i < bitCount; i++) {
        if ((y & mask) != 0) {
            result += bitShifted;
        }
        bitShifted <<= 1;
        mask <<= 1;
    }

    return result;
}

template <Integer ints>
ints divide(const ints numerator, const ints denominator){

    if (denominator == 0) {
        panic("Cannot Divide by 0");
    }
    
    bool negative = false;
    ints startingDenominator = denominator;

    if (startingDenominator < 0) {
        negative = true;
        startingDenominator = abs(startingDenominator);
    }

    ints startingNumerator = numerator;
    ints timesDoubled = 1;
    ints chunkValue = denominator;

    ints quotient = 0;

    while (chunkValue < startingDenominator) {
        timesDoubled <<= 1;
        chunkValue <<= 1;
    }

    while (startingDenominator > 0) {
        if (chunkValue <= startingNumerator){
            startingNumerator -= chunkValue;
            quotient += timesDoubled;
        }
        chunkValue >>= 1;
        timesDoubled >>= 1;
    }

    if (negative) {
        quotient = abs(quotient);
    }
    return quotient;

}

template <Integer ints>
ints min(const ints& x, const ints& y){
    if (x <= y) {
        return x;
    }
    else {
        return y;
    }
}

template <Integer ints>
ints max(const ints& x, const ints& y){
    if (x >= y) {
        return x;
    }
    else {
        return y;
    }
}

template <Integer ints>
ints sqrt(ints x){
    return x;
}

template <Integer ints>
ints gcd(ints x){

    return x;
}

template <Integer ints>
ints lcm(ints x){
    return x;
}


/** Round value up to the next multiple of alignment (alignment must be a power of 2) */
template <Integer ints>
ints alignUp(const ints value, const ints multipleOf) {
    if (multipleOf == 0 || (multipleOf & (multipleOf - 1)) != 0) {
        panic("alignUp: alignment must be a power of 2");
    }
    return (value + multipleOf - 1) & ~(multipleOf - 1);
}


/** Smallest value the type can hold (e.g. -2147483648 for int, 0 for unsigned) */
template <Integer ints>
constexpr ints minOf() {
    if constexpr (__is_signed(ints)) {
        return ints(ints(1) << (sizeof(ints) * 8 - 1));   // only the top bit set: 1000...0
    } else {
        return 0;                                          // unsigned types start at 0
    }
}

/** Largest value the type can hold (e.g. 2147483647 for int, 4294967295 for uint32_t) */
template <Integer ints>
constexpr ints maxOf() {
    if constexpr (__is_signed(ints)) {
        return ints(~minOf<ints>());                       // flip every bit: 0111...1
    } else {
        return ints(~ints(0));                             // all bits set: 1111...1
    }
}

}