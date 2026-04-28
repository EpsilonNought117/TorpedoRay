#include "../headers/sphere.h"

Sphere InitSphere(Point3 c, float r)
{
    Sphere s;
    s.radius = fmaxf(0.0f, r);
    s.center = c;
    return s;
}

bool HitSphere(
    const Sphere* s, 
    const Ray* r,
    Interval ray_t,
    HitRecord* h_rec
)
{
    Vec3 oc = SubVec3(&(s->center), &(r->orig));
    float a = LengthSquaredVec3(&(r->dir));
    float h = DotProductVec3(&(r->dir), &oc);
    float c = LengthSquaredVec3(&oc) - (s->radius * s->radius);

    float discriminant = h * h - a * c;
    if (discriminant < 0.0f)
        return false;

    float sqrt_dmt = sqrtf(discriminant);
    float root = (h - sqrt_dmt) / a;

    if (root <= ray_t.min || root >= ray_t.max)
    {
        root = (h + sqrt_dmt) / a;

        if (root <= ray_t.min || root >= ray_t.max)
            return false;
    }

    h_rec->t = root;
    h_rec->p = EvalRayAt(r, h_rec->t);

    Vec3 outward_normal = SubVec3(&(h_rec->p), &(s->center));
    DivVec3ScalarInplace(&outward_normal, s->radius);
    SetHitRecordFaceNormal(h_rec, r, &outward_normal);
    
    return true;
}