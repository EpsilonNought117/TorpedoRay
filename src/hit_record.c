#include "../headers/hit_record.h"

void SetHitRecordFaceNormal(
    HitRecord* h_rec, 
    const Ray* r, 
    const Vec3* outward_normal
)
{
    h_rec->front_face = DotProductVec3(&(r->dir), outward_normal) < 0.0f;
    h_rec->normal = h_rec->front_face ? *outward_normal : NegateVec3(outward_normal);
    return;
}