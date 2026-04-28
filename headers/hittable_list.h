#ifndef QRTC_HITTABLE_LIST_H
#define QRTC_HITTABLE_LIST_H

#include "hittable.h"
#include "interval.h"
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

bool HitObjectsInHittableList(
    const HittableList* list,
    const Ray* r,
    Interval ray_t,
    HitRecord* rec
);

#endif