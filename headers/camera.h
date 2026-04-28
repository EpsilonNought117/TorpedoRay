/* camera.h */

#ifndef QRTC_CAMERA_H
#define QRTC_CAMERA_H

#include "../include/qrtc.h"
#include "hittable.h"
#include "hittable_list.h"
#include "qrtc_internal.h"
#include "vec3.h"
#include "color.h"

typedef struct Camera
{
    size_t image_height;
    size_t image_width;

    uint32_t samples_per_pixel;
    float pixel_samples_scale;

    Point3 center;
    Point3 pixel00_loc;

    Vec3 pixel_delta_u;
    Vec3 pixel_delta_v;

    float aspect_ratio;
    float focal_length;

    float viewport_height;
    float viewport_width;

} Camera;

void InitCamera(
    Camera* cam,
    size_t image_width,
    Point3 cam_center,
    float aspect_ratio,
    float focal_length,
    float viewport_height,
    uint32_t samples_per_pixel
);

void RenderCameraWorld(
    const Camera* cam,
    const HittableList* world,
    uint32_t maxval
);

#endif