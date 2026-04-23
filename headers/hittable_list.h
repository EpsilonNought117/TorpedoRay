#ifndef QRTC_HITTABLE_LIST_H
#define QRTC_HITTABLE_LIST_H

#include "hittable.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct HittableList
{
    Hittable* data;
    size_t size;
    size_t capacity;
    
} HittableList;

bool InitHittableList(
    HittableList* list, 
    size_t initial_capacity
);

bool AddToHittableList(
    HittableList* list, 
    Hittable obj
);

void FreeHittableList(HittableList* list);

bool HitInHittableList(
    const HittableList* list,
    const Ray* r,
    float ray_tmin,
    float ray_tmax,
    HitRecord* rec
);

#endif