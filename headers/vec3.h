#ifndef QRTC_VEC3_H
#define QRTC_VEC3_H

#include "../include/qrtc.h"

typedef struct Vec3
{
    float x, y, z;

} Vec3;

typedef Vec3 Point3;

// ---------------- Unary ----------------

static inline Vec3 NegateVec3(const Vec3* v)
{
    Vec3 res;
    res.x = -v->x;
    res.y = -v->y;
    res.z = -v->z;
    return res;
}

// ---------------- Length ----------------

static inline float LengthSquaredVec3(const Vec3* v)
{
    return (v->x * v->x + v->y * v->y + v->z * v->z);
}

static inline float LengthVec3(const Vec3* v)
{
    return sqrtf(LengthSquaredVec3(v));
}

// ---------------- In-place ops ----------------

static inline void AddVec3Inplace(Vec3* v1, const Vec3* v2)
{
    v1->x += v2->x;
    v1->y += v2->y;
    v1->z += v2->z; 
}

static inline void SubVec3Inplace(Vec3* v1, const Vec3* v2)
{
    v1->x -= v2->x;
    v1->y -= v2->y;
    v1->z -= v2->z;    
}

static inline void MulVec3Inplace(Vec3* v1, const Vec3* v2)
{
    v1->x *= v2->x;
    v1->y *= v2->y;
    v1->z *= v2->z;
}

static inline void DivVec3Inplace(Vec3* v1, const Vec3* v2)
{
    v1->x /= v2->x;
    v1->y /= v2->y;
    v1->z /= v2->z;
}

static inline void MulVec3ScalarInplace(Vec3* v, float s)
{
    v->x *= s;
    v->y *= s;
    v->z *= s;
}

static inline void DivVec3ScalarInplace(Vec3* v, float s)
{
    float inv = 1.0f / s;
    v->x *= inv;
    v->y *= inv;
    v->z *= inv;
}

// ---------------- Binary ops ----------------

static inline Vec3 AddVec3(const Vec3* v1, const Vec3* v2)
{
    Vec3 res;
    res.x = v1->x + v2->x;
    res.y = v1->y + v2->y;
    res.z = v1->z + v2->z;
    return res;
}

static inline Vec3 SubVec3(const Vec3* v1, const Vec3* v2)
{
    Vec3 res;
    res.x = v1->x - v2->x;
    res.y = v1->y - v2->y;
    res.z = v1->z - v2->z;
    return res;
}

static inline Vec3 MulVec3(const Vec3* v1, const Vec3* v2)
{
    Vec3 res;
    res.x = v1->x * v2->x;
    res.y = v1->y * v2->y;
    res.z = v1->z * v2->z;
    return res;
}

static inline Vec3 DivVec3(const Vec3* v1, const Vec3* v2)
{
    Vec3 res;
    res.x = v1->x / v2->x;
    res.y = v1->y / v2->y;
    res.z = v1->z / v2->z;
    return res;
}

static inline Vec3 MulVec3Scalar(const Vec3* v, float s)
{
    Vec3 res;
    res.x = v->x * s;
    res.y = v->y * s;
    res.z = v->z * s;
    return res;
}

static inline Vec3 DivVec3Scalar(const Vec3* v, float s)
{
    float inv = 1.0f / s;
    Vec3 res;
    res.x = v->x * inv;
    res.y = v->y * inv;
    res.z = v->z * inv;
    return res;
}

// ---------------- Vector ops ----------------

static inline float DotProductVec3(const Vec3* v1, const Vec3* v2)
{
    return (v1->x * v2->x +
            v1->y * v2->y +
            v1->z * v2->z);
}

static inline Vec3 CrossProductVec3(const Vec3* v1, const Vec3* v2)
{
    Vec3 res;
    res.x = v1->y * v2->z - v1->z * v2->y;
    res.y = v1->z * v2->x - v1->x * v2->z;
    res.z = v1->x * v2->y - v1->y * v2->x;
    return res;
}

static inline Vec3 UnitVectorVec3(const Vec3* v)
{
    float len = LengthVec3(v);
    float inv = 1.0f / len;

    Vec3 res;
    res.x = v->x * inv;
    res.y = v->y * inv;
    res.z = v->z * inv;
    return res;
}

#endif // QRTC_VEC3_H