#ifndef QRTC_INTERNAL_H
#define QRTC_INTERNAL_H

#include "../include/qrtc.h"

// ---------------- Constants ----------------

#define QRTC_INFINITY   INFINITY
#define QRTC_PI         3.1415926535897932385f

// ---------------- Utility Functions ----------------

static inline float DegreesToRadians(float degrees)
{
    return degrees * QRTC_PI / 180.0f;
}

/* Per-thread PRNG state */
static THREAD_LOCAL uint64_t prng_state[4] = { 0 };

/* Internal 64-bit SFC generator */
static inline uint64_t RandomSFC64U64(void)
{
    uint64_t out = prng_state[1] + prng_state[2] + prng_state[0];

    prng_state[0]++;
    prng_state[1] = prng_state[2] ^ (prng_state[2] >> 11);
    prng_state[2] = prng_state[3] + (prng_state[3] << 3);
    prng_state[3] = ((prng_state[3] << 24) | (prng_state[3] >> 40)) + out;

    return out;
}

/* Seed current thread's generator */
static inline void RandomSFC64Seed(uint64_t seed)
{
    prng_state[0] = 1;
    prng_state[1] = seed;
    prng_state[2] = seed;
    prng_state[3] = seed;

    /* Warm-up rounds */
    for (int i = 0; i < 16; ++i)
        RandomSFC64U64();
}

/* Return float in [0.0f, 1.0f) */
static inline float RandomSFC64F32(void)
{
    /* Use top 24 bits for full float mantissa precision */
    uint32_t x = (uint32_t)(RandomSFC64U64() >> 40);

    return (float)x * (1.0f / (float)(1 << 24)); /* divide by 2^24 */
}

// Header files

#include "camera.h"
#include "color.h"
#include "hit_record.h"
#include "hittable_list.h"
#include "hittable.h"
#include "interval.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"

#endif