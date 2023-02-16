#pragma once

#include "Ray.hpp"
#include "hittable.hpp"

struct hit_record;

class material {
public:
  virtual bool scatter(const Ray &r_in, const hit_record &rec,
                       color &attenuation, Ray &scattered) const = 0;
};

class lambertian : public material {
public:
  lambertian(const color &a) : albedo(a) {}

  virtual bool scatter(const Ray &r_in, const hit_record &rec,
                       color &attenuation, Ray &scattered) const override {
    auto scatter_direction = rec.normal + random_unit_vector();
     if (scatter_direction.near_zero())
                scatter_direction = rec.normal;
    scattered = Ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
  }

public:
  color albedo;
};

class metal : public material {
    public:
        metal(const color& a) : albedo(a) {}

        virtual bool scatter(
            const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered
        ) const override {
            vec3 reflected = reflect(normalize(r_in.direction()), rec.normal);
            scattered = Ray(rec.p, reflected);
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }

    public:
        color albedo;
};