#ifndef QRTC_INTERNAL_H
#define QRTC_INTERNAL_H

#include "../include/qrtc.h"

// ---------------- Constants ----------------

// Use HUGE_VALF for true IEEE float infinity
static const float QRTC_INFINITY = HUGE_VALF;
static const float QRTC_PI = 3.1415926535897932385f;

// ---------------- Utility Functions ----------------

static inline float DegreesToRadians(float degrees)
{
    return degrees * QRTC_PI / 180.0f;
}

#endif