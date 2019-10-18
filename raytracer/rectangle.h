#ifndef RECTANGLEH
#define RECTANGLEH
#include "hitable.h"

class xy_rect: public hitable  {
public:
    xy_rect() {}
    xy_rect(float x0, float x1, float y0, float y1, float k, material *mat) : x0(x0), x1(x1), y0(y0), y1(y1), k(k), m(mat) {};
    virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const;
    material  *m;
    float x0, x1, y0, y1, k;
};

class xz_rect: public hitable  {
public:
    xz_rect() {}
    xz_rect(float x0, float x1, float y0, float y1, float k, material *mat) : x0(x0), x1(x1), y0(y0), y1(y1), k(k), m(mat) {};
    virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const;
    material  *m;
    float x0, x1, y0, y1, k;
};

class yz_rect: public hitable  {
public:
    yz_rect() {}
    yz_rect(float x0, float x1, float y0, float y1, float k, material *mat) : x0(x0), x1(x1), y0(y0), y1(y1), k(k), m(mat) {};
    virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const;
    material  *m;
    float x0, x1, y0, y1, k;
};

bool xy_rect::hit(const ray& r, float t0, float t1, hit_record& rec)const {
    float t=(k-r.origin().z())/r.direction().x();
    if(t<t0||t>t1){
        return false;
    }
    float x=r.origin().x()+t*r.direction().x();
    float y=r.origin().y()+t*r.direction().y();
    if(x<x0||x>x1||y<y0||y>y1){
        return false;
    }
    rec.u=(x-x0)/(x1-x0);
    rec.v=(y-y0)/(y1-y0);
    rec.t=t;
    rec.mat_ptr =m;
    rec.p=r.point_at_parameter(t);
    rec.normal=vec3(0,0,1);
    return true;
}
bool xz_rect::hit(const ray& r, float t0, float t1, hit_record& rec)const {
    float t=(k-r.origin().z())/r.direction().x();
    if(t<t0||t>t1){
        return false;
    }
    float x=r.origin().x()+t*r.direction().x();
    float y=r.origin().y()+t*r.direction().y();
    if(x<x0||x>x1||y<y0||y>y1){
        return false;
    }
    rec.u=(x-x0)/(x1-x0);
    rec.v=(y-y0)/(y1-y0);
    rec.t=t;
    rec.mat_ptr =m;
    rec.p=r.point_at_parameter(t);
    rec.normal=vec3(0,1,0);
    return true;
}
bool yz_rect::hit(const ray& r, float t0, float t1, hit_record& rec)const {
    float t=(k-r.origin().z())/r.direction().x();
    if(t<t0||t>t1){
        return false;
    }
    float x=r.origin().x()+t*r.direction().x();
    float y=r.origin().y()+t*r.direction().y();
    if(x<x0||x>x1||y<y0||y>y1){
        return false;
    }
    rec.u=(x-x0)/(x1-x0);
    rec.v=(y-y0)/(y1-y0);
    rec.t=t;
    rec.mat_ptr =m;
    rec.p=r.point_at_parameter(t);
    rec.normal=vec3(1,0,0);
    return true;
}
#endif