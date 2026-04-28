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
    Point3 center, pixel00_loc;
    Vec3 pixel_delta_u, pixel_delta_v;
    size_t image_height, image_width;
    float aspect_ratio, focal_length;
    float viewport_width;

} Camera;

void InitCamera(
    Camera* cam, 
    size_t image_width, 
    Point3 cam_center,
    float aspect_ratio, 
    float focal_length,
    float viewport_width
);

void RenderCameraWorld(
    const Camera* cam, 
    const HittableList* world
);

#endif