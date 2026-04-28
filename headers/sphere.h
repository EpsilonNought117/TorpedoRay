#ifndef QRTC_SPHERE_H
#define QRTC_SPHERE_H

#include "../include/qrtc.h"
#include "hit_record.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "interval.h"
#include <math.h>

typedef struct Sphere
{
    Point3 center;
    float radius;
    
} Sphere;

Sphere InitSphere(
    Point3 c, 
    float r
);

bool HitSphere(
    const Sphere* s, 
    const Ray* r,
    Interval ray_t, 
    HitRecord* h_rec
);

#endif