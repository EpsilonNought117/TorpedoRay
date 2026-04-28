#include "camera.h"

static Color RayColor(const Ray* r, const HittableList* world)
{
    QRTC_ASSERT(r != NULL);
    QRTC_ASSERT(world != NULL);
    QRTC_ASSERT(world->data != NULL);
    QRTC_ASSERT(world->capacity != 0);
    QRTC_ASSERT(world->size != 0 && world->size < world->capacity);

    HitRecord rec;

    if (HitObjectsInHittableList(world, r, (Interval){0.0f, QRTC_INFINITY}, &rec))
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

void InitCamera(
    Camera* cam,
    size_t image_width,
    Point3 cam_center,
    float aspect_ratio,
    float focal_length,
    float viewport_height
)
{
    QRTC_ASSERT(cam != NULL);
    QRTC_ASSERT(image_width != 0);
    QRTC_ASSERT(aspect_ratio > 0.0f);
    QRTC_ASSERT(focal_length > 0.0f);
    QRTC_ASSERT(viewport_height > 0.0f);

    cam->aspect_ratio = aspect_ratio;
    cam->image_width = image_width;

    size_t image_height = (size_t)(image_width / aspect_ratio);
    cam->image_height = (image_height == 0) ? (size_t)1 : image_height;

    cam->focal_length = focal_length;
    cam->viewport_height = viewport_height;

    cam->viewport_width = cam->viewport_height * ((float)cam->image_width / (float)cam->image_height);

    cam->center = cam_center;

    /* Viewport edge vectors */
    Vec3 viewport_u = (Vec3){ cam->viewport_width, 0.0f, 0.0f };
    Vec3 viewport_v = (Vec3){ 0.0f, -cam->viewport_height, 0.0f };

    /* Pixel-to-pixel delta vectors */
    cam->pixel_delta_u = DivVec3Scalar(&viewport_u, (float)cam->image_width);
    cam->pixel_delta_v = DivVec3Scalar(&viewport_v, (float)cam->image_height);

    /* Calculate upper-left corner of viewport */
    Vec3 focal_offset = (Vec3){ 0.0f, 0.0f, cam->focal_length };

    Point3 viewport_center = AddVec3(&cam->center, &focal_offset);

    Vec3 half_viewport_u = DivVec3Scalar(&viewport_u, 2.0f);
    Vec3 half_viewport_v = DivVec3Scalar(&viewport_v, 2.0f);

    Point3 viewport_upper_left = SubVec3(&viewport_center, &half_viewport_u);
    viewport_upper_left = SubVec3(&viewport_upper_left, &half_viewport_v);

    /* Calculate location of pixel (0, 0) center */
    Vec3 pixel_delta_sum = AddVec3(&cam->pixel_delta_u, &cam->pixel_delta_v);
    Vec3 pixel_offset = MulVec3Scalar(&pixel_delta_sum, 0.5f);

    cam->pixel00_loc = AddVec3(&viewport_upper_left, &pixel_offset);
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
    QRTC_ASSERT(world->size != 0 && world->size < world->capacity);
    QRTC_ASSERT(cam->image_width != 0);
    QRTC_ASSERT(cam->image_height != 0);
    QRTC_ASSERT(maxval < 65535);

    fprintf(stdout, "P3\n%zu %zu\n%" PRIu32 "\n", cam->image_width, cam->image_height, maxval);

    for (size_t j = 0; j < cam->image_height; ++j)
    {
        fprintf(stderr, "Current Scanline: %zu ... ", j + 1);

        for (size_t i = 0; i < cam->image_width; ++i)
        {
            Vec3 pixel_offset_u = MulVec3Scalar(&cam->pixel_delta_u, (float)i);
            Vec3 pixel_offset_v = MulVec3Scalar(&cam->pixel_delta_v, (float)j);

            Vec3 pixel_offset = AddVec3(&pixel_offset_u, &pixel_offset_v);
            Point3 pixel_center = AddVec3(&cam->pixel00_loc, &pixel_offset);

            Vec3 ray_direction = SubVec3(&pixel_center, &cam->center);
            Ray r = (Ray){cam->center, ray_direction};

            Color pixel_color = RayColor(&r, world);
            WriteColorToPPMFile(stdout, &pixel_color, maxval);
        }

        fprintf(stderr, "Done\n");
    }

    fprintf(stderr, "Image Done!\n");
}