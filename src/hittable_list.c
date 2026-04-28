#include "../headers/hittable_list.h"

// ---------------- Internal ----------------

static bool ResizeHittableList(HittableList* list)
{
    QRTC_ASSERT(list->size == list->capacity);

    size_t new_capacity = (3 * list->capacity) / 2 + 8;

    Hittable* new_data = (Hittable*)realloc(list->data, new_capacity * sizeof(Hittable));
    if (!new_data)
        return false;

    list->data = new_data;
    list->capacity = new_capacity;
    return true;
}

// ---------------- Public ----------------

bool InitHittableList(
    HittableList* list, 
    size_t initial_capacity
)
{
    list->size = 0;
    list->capacity = (initial_capacity > 0) ? initial_capacity : 1;

    list->data = (Hittable*)malloc(list->capacity * sizeof(Hittable));
    if (!list->data)
        return false;

    return true;
}

bool AddToHittableList(
    HittableList* list, 
    Hittable obj
)
{
    QRTC_ASSERT(list != NULL);

    if (list->size == list->capacity)
    {
        if (!ResizeHittableList(list))
            return false;
    }

    list->data[list->size++] = obj;
    return true;
}

void FreeHittableList(HittableList* list)
{
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

bool HitObjectsInHittableList(
    const HittableList* list,
    const Ray* r,
    Interval ray_t,
    HitRecord* rec
)
{
    HitRecord temp_rec;
    bool hit_anything = false;
    float closest_so_far = ray_t.max;
    size_t lsize = list->size;

    for (size_t i = 0; i < lsize; i++)
    {
        Interval temp_intvl = {ray_t.min, closest_so_far};

        if (Hit(&(list->data[i]), r, temp_intvl, &temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            *rec = temp_rec;
        }
    }

    return hit_anything;
}