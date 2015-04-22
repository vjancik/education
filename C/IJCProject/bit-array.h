#ifndef BIT_ARRAY_H_
#define BIT_ARRAY_H_

typedef unsigned long* BitArray_t;

#define ULONG_BITS sizeof(unsigned long)*8
#define TYPE_BITS(name) sizeof((name))*8

#define BA_create(name, size) unsigned long (name)[((size) + ULONG_BITS - 1)/(ULONG_BITS) + 1] = {(size)};

#ifndef USE_INLINE

#define BA_size(name) (name)[0]
#define BA_set_bit(name, index, value) \
    if((value)) \
        (name)[((index)+ULONG_BITS)/(ULONG_BITS)] |= (1UL<<((((index)+ULONG_BITS)%(ULONG_BITS)))); \
    else \
        (name)[((index)+ULONG_BITS)/(ULONG_BITS)] &= (~(1UL<<((((index)+ULONG_BITS)%(ULONG_BITS)))));
#define BA_get_bit(name, index) (((name)[((index)+ULONG_BITS)/(ULONG_BITS)]>>((((index)+ULONG_BITS)%(ULONG_BITS))))&1)

#else

inline unsigned long BA_size(BitArray_t array);

inline void BA_set_bit(BitArray_t array, unsigned long long index, int value);

inline char BA_get_bit(BitArray_t array, unsigned long long index);

#endif

#endif
