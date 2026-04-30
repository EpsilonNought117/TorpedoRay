#include "../include/qrtc.h"
#include "../headers/qrtc_internal.h"

int main(void)
{
    HittableList world;
    InitHittableList(&world, 2);

    Sphere s1 = InitSphere((Point3){0.0f, 0.0f, -1.0f}, 0.5f);
    Sphere s2 = InitSphere((Point3){0.0f, -100.5f, -1.0f}, 100.0f);

    Hittable obj_h1 = InitHittableObject(SPHERE, &s1);
    Hittable obj_h2 = InitHittableObject(SPHERE, &s2);

    AddToHittableList(&world, obj_h1);
    AddToHittableList(&world, obj_h2);

    Camera cam;
    InitCamera(
        &cam, 
        2560U, 
        (Point3){0.0f, 0.0f, 0.0f}, 
        16.0f / 10.0f, 
        1.0f, 
        2.0f,
        128U
    );

    RenderCameraWorld(&cam, &world, 0xFFFFU);
    return EXIT_SUCCESS;
}