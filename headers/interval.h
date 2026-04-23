#ifndef QRTC_INTERVAL_H
#define QRTC_INTERVAL_H

#include "../include/qrtc.h"
#include <math.h>
#include <stdbool.h>

// ---------------- C INTERVAL TYPE ----------------

typedef struct Interval
{
    float min, max;

} Interval;

// Default interval is empty: [ +inf, -inf ]
static inline Interval interval_empty(void)
{
    return (Interval){ INFINITY, -INFINITY };
}

// Universe interval: [-inf, +inf]
static inline Interval interval_universe(void)
{
    return (Interval){ -INFINITY, INFINITY };
}

// Constructor equivalent
static inline Interval interval_make(float min, float max)
{
    return (Interval){ min, max };
}

// size()
static inline float interval_size(const Interval* i)
{
    return i->max - i->min;
}

// contains(x)
static inline bool interval_contains(const Interval* i, float x)
{
    return i->min <= x && x <= i->max;
}

// surrounds(x)
static inline bool interval_surrounds(const Interval* i, float x)
{
    return i->min < x && x < i->max;
}

#endif