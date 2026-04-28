#include "../headers/hittable.h"

bool Hit(
    const Hittable* hit_obj, 
    const Ray* r,
    Interval ray_t,
    HitRecord* h_rec
)
{
    switch (hit_obj->type)
    {
        case SPHERE:
            return HitSphere(&(hit_obj->obj.sphere), r, ray_t, h_rec);

        default:
            return false;
    }
}