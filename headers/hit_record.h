#ifndef QRTC_HIT_RECORD_H
#define QRTC_HIT_RECORD_H

#include "../include/qrtc.h"
#include "vec3.h"
#include "ray.h"

typedef struct HitRecord
{   
    Point3 p;
    Vec3 normal;
    float t;
    bool front_face;

} HitRecord;

void SetHitRecordFaceNormal(
    HitRecord* h_rec, 
    const Ray* r, 
    const Vec3* outward_normal
);

#endif