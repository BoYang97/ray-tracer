#ifndef HITABLEH
#define HITABLEH
#include "ray.h"
class material;
struct hit_record{
    float t;
    float u;
    float v;
    vec3 p;
    vec3 normal;
    material *mat_ptr;
};
class hitable{
    public:
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const=0;
};

class flip_normals : public hitable {
public:
    flip_normals(hitable *p) : ptr(p) {}
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
        if (ptr->hit(r, t_min, t_max, rec)) {
            rec.normal = -rec.normal;
            return true;
        }
        else
            return false;
    }
   hitable *ptr;
};
#endif