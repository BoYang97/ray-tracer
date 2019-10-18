#include <iostream>
#include <fstream>
#include "sphere.h"
#include "hitable_list.h"
#include <cfloat>
#include "camera.h"
#include "material.h"
#include "rectangle.h"
#include <random>
#define random(a,b) (rand()%(b-a+1)+a)
#define random1 (float((rand()%(100)))/100.0f)

using namespace std;


vec3 color(const ray& r,hitable *world, int depth)
{
    hit_record rec;
    if(world->hit(r,0.0,FLT_MAX,rec))
    {
        ray scattered;
        vec3 attenuation;

        if(depth<50 && rec.mat_ptr->scatter(r,rec,attenuation,scattered))
        {
            return attenuation * color(scattered, world, depth+1);
        } else
        {
            return vec3(0,0,0);
        }
    }
    else
    {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 *(unit_direction.x() + 1.0);
        return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
    }
}

int main()
{
    int nx = 1200;
    int ny = 900;
    int ns = 100;
    ofstream OutFile("Test.ppm"); 

    OutFile<<"P3\n"<<nx<<" "<<ny<<"\n255\n";

    camera cam(vec3(-2,2,1),vec3(0,0,-1),vec3(0,1,0),90,float(nx)/float(ny));

    hitable *list[6];
    list[0] = new sphere(vec3(0,0,-0.5),0.5,new lambertian(vec3(1.0,0.5,0.25)));
    list[1] = new sphere(vec3(0,-100.5,-1),100,new metal(vec3(1.0,1.0,1.0),0.0));
    list[2] = new sphere(vec3(1.5,0,-1),0.5,new metal(vec3(1.0,1.0,1.0),0.0));
    list[3] = new sphere(vec3(-1,0,-1),0.5,new dielectric(1.5));
    list[4] = new sphere(vec3(-1,0,-1),-0.45, new dielectric(1.5));
    list[5] = new xy_rect(2,4,2,4,0.5,new metal(vec3(0.25,0.5,0.5),0.0));
    hitable *world = new hitable_list(list,6);
    random_device rd;

    for(int j=ny-1;j>=0;j--)
    {
        for(int i=0;i<nx;i++)
        {
            vec3 col(0,0,0);

            for(int s = 0; s<ns; s++)
            {
                float u = (float(i)+float(random(0,100))/100.0f)/float(nx);
                float v = (float(j)+float(random(0,100))/100.0f)/float(ny);

                ray r = cam.get_ray(u,v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r,world,0);
            }
            col /= float(ns);
            col = vec3(sqrt(col[0]),sqrt(col[1]),sqrt(col[2]));

            int ir=int(255.99* col[0]);
            int ig=int(255.99* col[1]);
            int ib=int(255.99* col[2]);;
            OutFile<<ir<<" "<<ig<<" "<<ib<<"\n";
        }
    }

}