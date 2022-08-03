/**
 * @file util.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-07-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <cstdlib>

namespace DR {
    /**
     * @brief Dice roll where p is a probability 0-1
     *
     * @param p
     * @return true
     * @return false
     */
    static inline bool prob(double p) {
        if (p == 0) {
            return false;
        }

        if (p >= 1) {
            return true;
        }

        int upperbound = 1;
        while (p < 1) {
            p *= 10;
            upperbound *= 10;
        }

        int rval = std::rand() % upperbound;
        return rval < p;
    }

    static inline void bit_flip(char* v, int i) {
        *(v + (i / 8)) |= (1 << (i % 8));
    }

    static inline int is_bit_flipped(const char* v, int i) {
        return *(v + (i / 8)) & (1 << (i % 8));
    }
}