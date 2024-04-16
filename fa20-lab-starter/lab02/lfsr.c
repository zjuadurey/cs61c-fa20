#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

// Return the nth bit of x.
// Assume 0 <= n <= 15
unsigned get_bit_uint16_t(uint16_t x,
                 uint16_t n) {
    // YOUR CODE HERE
    // Returning -1 is a placeholder (it makes
    // no sense, because get_bit only returns 
    // 0 or 1)
    return (x >> n) & 0b1;
}

void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
    uint16_t msb = get_bit_uint16_t(*reg, 0) ^ get_bit_uint16_t(*reg, 2) ^ get_bit_uint16_t(*reg, 3) ^ get_bit_uint16_t(*reg, 5);
    (*reg) = ((*reg) >> 1) + (msb << 15);
}

