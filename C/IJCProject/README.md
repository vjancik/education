#IJC Project 1

**DISCLAIMER**: Code files inside this project are uncommented, therefore they may have limited readability.

*Note: The following assignment description is translated from Czech and shortened, so some details are left out.*

###Assignment

####Part 1

Implement bit array functionality inside `bit-array.h`.

Specifically implement macros `BA_Create`, `BA_size`, `BA_set_bit`, `BA_get_bit`.

If the symbol `USE_INLINE` is defined compile the project with an inline function implementation of the forementioned macros.

As a test example, implement a function, which uses the algorithm known as Eratosthenes sieve and use it to computer the last 10 prime numbers of all prime numbers from 2 to 201 million.

**Algorithm: Eratosthenes sieve**

1. Set bit field `p` of size `N` to 0, set index `i` to 2.
2. Choose the smallest index `i`, such that `p[i]==0`. Then `i` is a prime number.
3. For all multiples of `i`, set bit `p[n\*i]` to 1.
4. `i++`; until we get beyond `sqrt(N)`, repeat points 2 to 4.
5. Result: in the field `p`, the prime numbers are the indexes at which the `p[i]` value is 0.

####Part 2

Write the module `error.c` with the header `error.h` which defines the function Warning and the function Fatal Error which extend the functionality of `printf`.

Write the module `ppm.c` with the header `ppm.h` which implements the functionality of reading and writing `.ppm` files.

Write a test program `steg-decode.c` and inside the main function: load from a file a `.ppm` test image and find the encoded message inside it. Print out the message.

The message is a string of characters, encoded inside the message as the least significant bits of each byte for which the index is a prime number.
