#include "bit-array.h"

#ifdef USE_INLINE
inline unsigned long BA_size(BitArray_t array) {
    return array[0];
}

inline void BA_set_bit(BitArray_t array, unsigned long long index, int value) {
    if(value)
        array[(index+ULONG_BITS)/(ULONG_BITS)] |= (1UL<<((index+ULONG_BITS)%(ULONG_BITS)));
    else
        array[(index+ULONG_BITS)/(ULONG_BITS)] &= (~(1UL<<((index+ULONG_BITS)%(ULONG_BITS))));
}

inline char BA_get_bit(BitArray_t array, unsigned long long index) {
    return (array[(index+ULONG_BITS)/(ULONG_BITS)]>>((index+ULONG_BITS)%(ULONG_BITS)))&1;
}
#endif
