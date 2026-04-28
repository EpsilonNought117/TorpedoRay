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
    float viewport_width
)
{
    QRTC_ASSERT(cam != NULL);
    QRTC_ASSERT(image_width != 0);
    QRTC_ASSERT(aspect_ratio > 0.0f);
    QRTC_ASSERT(focal_length > 0.0f);
    QRTC_ASSERT(viewport_width > 0.0f);

    cam->aspect_ratio = aspect_ratio;
    cam->image_width = image_width;
    size_t image_height = (size_t)(image_width / aspect_ratio);
    cam->image_height = image_height == 0 ? 1U : image_height;
    
    cam->focal_length = focal_length;
    float 
}