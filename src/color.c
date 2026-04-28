#include "../headers/color.h"

void WriteColorToPPMFile(FILE * restrict fp, const Color * restrict c, uint32_t maxval)
{
    QRTC_ALWAYS_ASSERT(fp != NULL);
    QRTC_ALWAYS_ASSERT(c != NULL);
    QRTC_ALWAYS_ASSERT(maxval != 0);

    Interval i = (Interval){0.0f, 1.0f};

    float r_temp = ClampInterval(i, c->r);
    float g_temp = ClampInterval(i, c->g);
    float b_temp = ClampInterval(i, c->b);

    uint32_t r = (uint32_t)(maxval * r_temp + 0.5f);
    uint32_t g = (uint32_t)(maxval * g_temp + 0.5f);
    uint32_t b = (uint32_t)(maxval * b_temp + 0.5f);

    fprintf(fp, "%" PRIu32 " %" PRIu32 " %" PRIu32 "\n", r, g, b);
}