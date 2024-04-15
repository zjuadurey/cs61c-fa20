#include <stdio.h>
#include "bit_ops.h"

// Return the nth bit of x.
// Assume 0 <= n <= 31
unsigned get_bit(unsigned x,
                 unsigned n) {
    // YOUR CODE HERE
    // Returning -1 is a placeholder (it makes
    // no sense, because get_bit only returns 
    // 0 or 1)
    return (x >> n) & 0b1;
}
// Set the nth bit of the value of x to v.
// Assume 0 <= n <= 31, and v is 0 or 1
void set_bit(unsigned * x,
             unsigned n,
             unsigned v) {
    // YOUR CODE HERE
    unsigned mask = ~(0b1 << n);
    (*x) = ((*x) & mask) + (v << n);

    /*
    unsigned high_part = ((*x) >> (n + 1) ) << (n + 1);
    unsigned low_part = ((*x) << (32 - n) ) >>  (32 - n);
    printf("high_part: %08x low_part: %08x\n", high_part, low_part);
    unsigned set_part = v << n;
    (*x) = high_part + low_part + set_part;
    */
}
// Flip the nth bit of the value of x.
// Assume 0 <= n <= 31
void flip_bit(unsigned * x,
              unsigned n) {
    // YOUR CODE HERE
    unsigned bit = get_bit(*x, n);
    printf("bit: %u\n", bit);
    set_bit(x, n, (~bit) & 0b1);
}

