#include "../headers/hittable.h"

bool Hit(
    const Hittable* hit_obj, 
    const Ray* r, 
    float ray_tmin, 
    float ray_tmax, 
    HitRecord* h_rec
)
{
    switch (hit_obj->type)
    {
        case SPHERE:
            return HitSphere(&(hit_obj->obj.sphere), r, ray_tmin, ray_tmax, h_rec);

        default:
            return false;
    }
}