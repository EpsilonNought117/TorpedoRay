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

/* Default interval is empty: [ +inf, -inf ] */
static inline Interval EmptyInterval(void)
{
    return (Interval){ INFINITY, -INFINITY };
}

/* Universe interval: [ -inf, +inf ] */
static inline Interval UniverseInterval(void)
{
    return (Interval){ -INFINITY, INFINITY };
}

/* Constructor equivalent */
static inline Interval MakeInterval(float min, float max)
{
    return (Interval){ min, max };
}

/* size() */
static inline float SizeInterval(const Interval* i)
{
    return i->max - i->min;
}

/* contains(x) */
static inline bool ContainsInterval(const Interval* i, float x)
{
    return i->min <= x && x <= i->max;
}

/* surrounds(x) */
static inline bool SurroundsInterval(const Interval* i, float x)
{
    return i->min < x && x < i->max;
}

/* clamp(x) */
static inline float ClampInterval(Interval itvl, float x)
{
    float out = (x < itvl.max) ? ((x > itvl.min) ? x : itvl.min) : itvl.max;
    return out;
}

#endif