/* camera.c */

#include "camera.h"

static inline Vec3 SampleSquare(void)
{
    /* Random point in [-0.5, +0.5] × [-0.5, +0.5] */
    return (Vec3)
    {
        GetRandomFloat32() - 0.5f,
        GetRandomFloat32() - 0.5f,
        0.0f
    };
}

static Ray GetRay(
    const Camera* cam,
    size_t i,
    size_t j
)
{
    QRTC_ASSERT(cam != NULL);

    Vec3 offset = SampleSquare();

    Vec3 offset_u = MulVec3Scalar(
        &cam->pixel_delta_u,
        ((float)i + offset.x)
    );

    Vec3 offset_v = MulVec3Scalar(
        &cam->pixel_delta_v,
        ((float)j + offset.y)
    );

    Point3 pixel_sample = AddVec3(&cam->pixel00_loc, &offset_u);
    pixel_sample = AddVec3(&pixel_sample, &offset_v);

    Point3 ray_origin = cam->center;
    Vec3 ray_direction = SubVec3(&pixel_sample, &ray_origin);

    Ray r = { ray_origin, ray_direction };
    return r;
}

static Color RayColor(
    const Ray* r,
    const HittableList* world
)
{
    QRTC_ASSERT(r != NULL);
    QRTC_ASSERT(world != NULL);
    QRTC_ASSERT(world->data != NULL);
    QRTC_ASSERT(world->capacity != 0);
    QRTC_ASSERT(world->size != 0 && world->size <= world->capacity);

    HitRecord rec;

    if (HitObjectsInHittableList(
        world,
        r,
        (Interval){ 0.0f, QRTC_INFINITY },
        &rec))
    {
        Color c =
        {
            rec.normal.x + 1.0f,
            rec.normal.y + 1.0f,
            rec.normal.z + 1.0f
        };

        MulColorScalarInplace(&c, 0.5f);
        return c;
    }

    Vec3 unit_direction = UnitVectorVec3(&r->dir);
    float a = 0.5f * (unit_direction.y + 1.0f);

    Color white = { 1.0f, 1.0f, 1.0f };
    Color blue  = { 0.5f, 0.7f, 1.0f };

    Color c1 = MulColorScalar(&white, 1.0f - a);
    Color c2 = MulColorScalar(&blue, a);

    return AddColor(&c1, &c2);
}

void InitCamera(
    Camera* cam,
    size_t image_width,
    Point3 cam_center,
    float aspect_ratio,
    float focal_length,
    float viewport_height,
    uint32_t samples_per_pixel
)
{
    QRTC_ASSERT(cam != NULL);
    QRTC_ASSERT(image_width != 0);
    QRTC_ASSERT(aspect_ratio > 0.0f);
    QRTC_ASSERT(focal_length > 0.0f);
    QRTC_ASSERT(viewport_height > 0.0f);
    QRTC_ASSERT(samples_per_pixel != 0);

    cam->aspect_ratio = aspect_ratio;
    cam->image_width = image_width;
    cam->samples_per_pixel = samples_per_pixel;

    size_t image_height = (size_t)((float)image_width / aspect_ratio);
    cam->image_height = (image_height < 1) ? 1 : image_height;

    cam->pixel_samples_scale =
        1.0f / (float)cam->samples_per_pixel;

    cam->focal_length = focal_length;
    cam->viewport_height = viewport_height;

    cam->viewport_width =
        cam->viewport_height *
        ((float)cam->image_width / (float)cam->image_height);

    cam->center = cam_center;

    Vec3 viewport_u =
    {
        cam->viewport_width,
        0.0f,
        0.0f
    };

    Vec3 viewport_v =
    {
        0.0f,
        -cam->viewport_height,
        0.0f
    };

    cam->pixel_delta_u =
        DivVec3Scalar(&viewport_u, (float)cam->image_width);

    cam->pixel_delta_v =
        DivVec3Scalar(&viewport_v, (float)cam->image_height);

    Vec3 focal_offset =
    {
        0.0f,
        0.0f,
        cam->focal_length
    };

    Point3 viewport_center =
        SubVec3(&cam->center, &focal_offset);

    Vec3 half_viewport_u =
        DivVec3Scalar(&viewport_u, 2.0f);

    Vec3 half_viewport_v =
        DivVec3Scalar(&viewport_v, 2.0f);

    Point3 viewport_upper_left =
        SubVec3(&viewport_center, &half_viewport_u);

    viewport_upper_left =
        SubVec3(&viewport_upper_left, &half_viewport_v);

    Vec3 pixel_delta_sum =
        AddVec3(&cam->pixel_delta_u, &cam->pixel_delta_v);

    Vec3 pixel_offset =
        MulVec3Scalar(&pixel_delta_sum, 0.5f);

    cam->pixel00_loc =
        AddVec3(&viewport_upper_left, &pixel_offset);
}

void RenderCameraWorld(
    const Camera* cam,
    const HittableList* world,
    uint32_t maxval
)
{
    QRTC_ASSERT(cam != NULL);
    QRTC_ASSERT(world != NULL);
    QRTC_ASSERT(world->data != NULL);
    QRTC_ASSERT(world->capacity != 0);
    QRTC_ASSERT(world->size != 0 && world->size <= world->capacity);
    QRTC_ASSERT(cam->image_width != 0);
    QRTC_ASSERT(cam->image_height != 0);
    QRTC_ASSERT(cam->samples_per_pixel > 0);
    QRTC_ASSERT(maxval < 65535);

    fprintf(
        stdout,
        "P3\n%zu %zu\n%" PRIu32 "\n",
        cam->image_width,
        cam->image_height,
        maxval
    );

    for (size_t j = 0; j < cam->image_height; ++j)
    {
        fprintf(
            stderr,
            "\rScanlines remaining: %zu ",
            cam->image_height - j
        );

        for (size_t i = 0; i < cam->image_width; ++i)
        {
            Color pixel_color = (Color){0.0f, 0.0f, 0.0f};

            for (uint32_t sample = 0; sample < cam->samples_per_pixel; ++sample)
            {
                Ray r = GetRay(cam, i, j);
                Color sample_color = RayColor(&r, world);

                pixel_color =
                    AddColor(&pixel_color, &sample_color);
            }

            MulColorScalarInplace(
                &pixel_color,
                cam->pixel_samples_scale
            );

            Interval i = {0.0f, 1.0f};

            pixel_color.r = ClampInterval(i, pixel_color.r);
            pixel_color.g = ClampInterval(i, pixel_color.g);
            pixel_color.b = ClampInterval(i, pixel_color.b);

            WriteColorToPPMFile(
                stdout,
                &pixel_color,
                maxval
            );
        }
    }

    fprintf(stderr, "\rDone.                 \n");
}