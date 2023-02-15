#include "hittable.hpp"

class sphere : public hittable {
public:
  sphere(point3 cen, double r) : center(cen), radius(r){};

  virtual bool hit(const Ray &r, double t_min, double t_max,
           hit_record &rec) const override {

    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
      return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
      root = (-half_b + sqrtd) / a;
      if (root < t_min || t_max < root)
        return false; 
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    rec.set_face_normal(r,(rec.p - center) / radius);
    return true;

  }

public:
  point3 center;
  double radius;
};
