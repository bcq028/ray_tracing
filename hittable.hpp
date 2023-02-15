#pragma once
#include "Ray.hpp"


struct hit_record {
    point3 p;
    vec3 normal;
    double t;
    bool front_face;
    inline void set_face_normal(const Ray&r,const vec3&outward_normal){
        front_face=dot(r.direction(),outward_normal)<0;
        normal=front_face?outward_normal:-outward_normal;
    }
};

class hittable {
    public:
    virtual bool hit(const Ray&r,double t_min,double t_max,hit_record&rec) const =0;
};


class hittable_list:public hittable {
    public:
    hittable_list(){}
    hittable_list(std::shared_ptr<hittable> object) {add(object);}
    
    virtual bool hit(const Ray&r,double t_min,double t_max,hit_record & rec) const {
        hit_record temp_rec;
        bool hit_anything=false;
        auto closest_so_far=t_max;
        for(const auto&object:objects){
            if(object->hit(r,t_min,closest_so_far,temp_rec)) {
                hit_anything=true;
                closest_so_far=temp_rec.t;
                rec=temp_rec;
            }
        }
        return hit_anything;
    }
    
    void add(std::shared_ptr<hittable> object) {
        objects.push_back(object);
    }
    std::vector<std::shared_ptr<hittable>> objects;

};