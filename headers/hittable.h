#ifndef HITTABLE_H
#define HITTABLE_H

#include "../include/qrtc.h"
#include "ray.h"
#include "hit_record.h"
#include "sphere.h"
#include "interval.h"

typedef enum HittableObjType
{
    SPHERE

} HittableObjType;

typedef struct Hittable
{
    HittableObjType type;

    union
    {
        Sphere sphere;

    } obj;

} Hittable;

bool Hit(
    const Hittable* hit_obj, 
    const Ray* r,
    Interval ray_t,
    HitRecord* h_rec
);

#endif