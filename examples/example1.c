#include "../include/qrtc.h"
#include "../headers/color.h"
#include "../headers/ray.h"
#include "../headers/vec3.h"
#include "../headers/hittable_list.h"
#include "../headers/sphere.h"
#include "../headers/hittable.h"
#include "../headers/qrtc_internal.h"
#include "../headers/interval.h"

#include <stdio.h>
#include <inttypes.h>
#include <math.h>

// ------------------------------------------------------------

Color RayColor(const Ray* r, const HittableList* world)
{
    HitRecord rec;

    if (HitInHittableList(world, r, 0.0f, QRTC_INFINITY, &rec))
    {
        Color c = {rec.normal.x + 1.0f, rec.normal.y + 1.0f, rec.normal.z + 1.0f};
        MulColorScalarInplace(&c, 0.5f);
        return c;
    }

    Vec3 unit_direction = UnitVectorVec3(&(r->dir));
    float a = 0.5f * (unit_direction.y + 1.0f);

    Color white = {1.0f, 1.0f, 1.0f};
    Color blue  = {0.5f, 0.7f, 1.0f};

    Color c1 = MulColorScalar(&white, (1.0f - a));
    Color c2 = MulColorScalar(&blue, a);

    return AddColor(&c1, &c2);
}

// ------------------------------------------------------------

int main(void)
{
    float aspect_ratio = 16.0f / 9.0f;
    uint32_t maxval = 65535;

    size_t image_width = 1920;
    size_t image_height = (size_t)(image_width / aspect_ratio);
    image_height = (image_height == 0) ? 1 : image_height;

    // ---------------- World ----------------

    HittableList world;
    InitHittableList(&world, 2);

    Hittable s1;
    s1.type = SPHERE;
    s1.obj.sphere = InitSphere((Point3){0.0f, 0.0f, -1.0f}, 0.5f);
    AddToHittableList(&world, s1);

    Hittable s2;
    s2.type = SPHERE;
    s2.obj.sphere = InitSphere((Point3){0.0f, -100.5f, -1.0f}, 100.0f);
    AddToHittableList(&world, s2);

    // ---------------- Camera ----------------

    float focal_length = 1.0f;
    float vp_height = 2.0f;
    float vp_width = vp_height * ((float)image_width / (float)image_height);

    Point3 camera_center = {0.0f, 0.0f, 0.0f};

    Vec3 viewport_u = {vp_width, 0.0f, 0.0f};
    Vec3 viewport_v = {0.0f, -vp_height, 0.0f};

    Vec3 pixel_delta_u = DivVec3Scalar(&viewport_u, (float)image_width);
    Vec3 pixel_delta_v = DivVec3Scalar(&viewport_v, (float)image_height);

    Vec3 focal_vec = {0.0f, 0.0f, focal_length};

    Point3 tmp = SubVec3(&camera_center, &focal_vec);
    Vec3 half_u = DivVec3Scalar(&viewport_u, 2.0f);
    Vec3 half_v = DivVec3Scalar(&viewport_v, 2.0f);

    tmp = SubVec3(&tmp, &half_u);
    Point3 viewport_upper_left = SubVec3(&tmp, &half_v);

    Vec3 delta_sum = AddVec3(&pixel_delta_u, &pixel_delta_v);
    Vec3 half_delta = MulVec3Scalar(&delta_sum, 0.5f);
    Point3 pixel00_loc = AddVec3(&viewport_upper_left, &half_delta);

    // ---------------- Render ----------------

    printf("P3\n%zu %zu\n%" PRIu32 "\n", image_width, image_height, maxval);

    for (size_t j = 0; j < image_height; j++)
    {
        fprintf(stderr, "Scanlines remaining: %zu\n", image_height - j);

        for (size_t i = 0; i < image_width; i++)
        {
            Vec3 offset_u = MulVec3Scalar(&pixel_delta_u, (float)i);
            Vec3 offset_v = MulVec3Scalar(&pixel_delta_v, (float)j);

            Point3 pixel_center = AddVec3(&pixel00_loc, &offset_u);
            pixel_center = AddVec3(&pixel_center, &offset_v);

            Vec3 ray_direction = SubVec3(&pixel_center, &camera_center);

            Ray r;
            r.orig = camera_center;
            r.dir  = ray_direction;

            Color pixel_color = RayColor(&r, &world);
            ClampColor(&pixel_color);

            WriteColorToPPMFile(stdout, &pixel_color, maxval);
            fputc('\n', stdout);
        }
    }

    fprintf(stderr, "Done.\n");

    FreeHittableList(&world);

    return EXIT_SUCCESS;
}