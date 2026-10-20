#pragma once


#define WORD_SIZE (__SIZEOF_POINTER__)
#define WORD_BITS (__SIZEOF_POINTER__ * 8)


#if (WORD_BITS == 32)
    using word_t = uint32_t;

#elif (WORD_BITS == 64)
    using word_t = uint64_t;

#else 
    #error "Please Add OS Support For Requested CPU Word Size"

#endif

static_assert(sizeof(word_t) == sizeof(void*), "Word Size Must Match Pointer Size");