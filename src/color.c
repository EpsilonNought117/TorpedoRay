#include "../headers/color.h"

void WriteColorToPPMFile(FILE * restrict fp, const Color * restrict c, uint32_t maxval)
{
    QRTC_ASSERT(fp != NULL);
    QRTC_ASSERT(c != NULL);
    QRTC_ASSERT(maxval != 0);

    uint32_t r = (uint32_t)(maxval * c->r + 0.5f);
    uint32_t g = (uint32_t)(maxval * c->g + 0.5f);
    uint32_t b = (uint32_t)(maxval * c->b + 0.5f);

    fprintf(fp, "%" PRIu32 " %" PRIu32 " %" PRIu32 "\n", r, g, b);
}