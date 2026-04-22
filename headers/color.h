#ifndef QRTC_RGB_H
#define QRTC_RGB_H

#include "../include/qrtc.h"

typedef struct Color
{
    float r, g, b;

} Color;

/**
 * result = c1 + c2
 */
static inline Color AddColor(const Color* c1, const Color* c2)
{
    Color c;
    c.r = c1->r + c2->r;
    c.g = c1->g + c2->g;
    c.b = c1->b + c2->b;
    return c;
}

/**
 * result = c1 - c2
 */
static inline Color SubColor(const Color* c1, const Color* c2)
{
    Color c;
    c.r = c1->r - c2->r;
    c.g = c1->g - c2->g;
    c.b = c1->b - c2->b;
    return c;
}

/**
 * result = c1 * c2 (component-wise)
 */
static inline Color MulColor(const Color* c1, const Color* c2)
{
    Color c;
    c.r = c1->r * c2->r;
    c.g = c1->g * c2->g;
    c.b = c1->b * c2->b;
    return c;
}

/**
 * result = c1 / c2 (component-wise)
 */
static inline Color DivColor(const Color* c1, const Color* c2)
{
    Color c;
    c.r = c1->r / c2->r;
    c.g = c1->g / c2->g;
    c.b = c1->b / c2->b;
    return c;
}

/**
 * result = c * scalar
 */
static inline Color MulColorScalar(const Color* c1, float f)
{
    Color c;
    c.r = c1->r * f;
    c.g = c1->g * f;
    c.b = c1->b * f;
    return c;
}

/**
 * result = c / scalar
 */
static inline Color DivColorScalar(const Color* c1, float f)
{
    float inv = 1.0f / f;
    Color c;
    c.r = c1->r * inv;
    c.g = c1->g * inv;
    c.b = c1->b * inv;
    return c;
}

/**
 * in-place operations
 */
static inline void AddColorInplace(Color* c1, const Color* c2)
{
    c1->r += c2->r;
    c1->g += c2->g;
    c1->b += c2->b;
}

static inline void SubColorInplace(Color* c1, const Color* c2)
{
    c1->r -= c2->r;
    c1->g -= c2->g;
    c1->b -= c2->b;
}

static inline void MulColorInplace(Color* c1, const Color* c2)
{
    c1->r *= c2->r;
    c1->g *= c2->g;
    c1->b *= c2->b;
}

static inline void DivColorInplace(Color* c1, const Color* c2)
{
    c1->r /= c2->r;
    c1->g /= c2->g;
    c1->b /= c2->b;
}

static inline void MulColorScalarInplace(Color* c1, float f)
{
    c1->r *= f;
    c1->g *= f;
    c1->b *= f;
}

static inline void DivColorScalarInplace(Color* c1, float f)
{
    float inv = 1.0f / f;
    c1->r *= inv;
    c1->g *= inv;
    c1->b *= inv;
}

/**
 * clamp to [0, 1]
 */
static inline void ClampColor(Color* c)
{
    c->r = (c->r < 0.0f) ? 0.0f : (c->r > 1.0f ? 1.0f : c->r);
    c->g = (c->g < 0.0f) ? 0.0f : (c->g > 1.0f ? 1.0f : c->g);
    c->b = (c->b < 0.0f) ? 0.0f : (c->b > 1.0f ? 1.0f : c->b);
}

/**
 * print color, assumes values are in [0, 1] range for floats
 */
void PrintColor(FILE * restrict fp, const Color * restrict c, uint32_t maxval)
{
    QRTC_ALWAYS_ASSERT(fp != NULL);
    QRTC_ALWAYS_ASSERT(c != NULL);
    QRTC_ALWAYS_ASSERT(maxval != 0);

    uint32_t r = (uint32_t)(maxval * c->r + 0.5f);
    uint32_t g = (uint32_t)(maxval * c->g + 0.5f);
    uint32_t b = (uint32_t)(maxval * c->b + 0.5f);

    fprintf(fp, "%" PRIu32 " %" PRIu32 " %" PRIu32, r, g, b);
}

#endif // QRTC_RGB_H