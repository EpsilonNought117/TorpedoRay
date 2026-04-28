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

// Header files

#include "color.h"
#include "hit_record.h"
#include "hittable_list.h"
#include "hittable.h"
#include "interval.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"

#endif