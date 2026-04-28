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

Hittable InitHittableObject(
    HittableObjType obj_type,
    const void* obj_ptr
)
{
    Hittable temp;

    switch(obj_type)
    {
        case SPHERE:
        {
            temp.type = obj_type;
            temp.obj.sphere = *(const Sphere*)obj_ptr;
            break;
        }
    }

    return temp;
}