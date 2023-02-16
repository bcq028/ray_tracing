#pragma once

#include <cmath>

#include <iostream>

using std::sqrt;

#include <memory>
#include <vector>

class Mathf{
    public:
    template <typename T>
    static T Lerp(T start,T end,float t){
        return start+t*(end-start);
    }
    template <typename T>
    static T Clamp(T value,T start, T end){
        if(value<start) return start;
        if(value>end) return end;
        return value;
    }

    static double random_double(){
    return rand()/(RAND_MAX+1.0);
}

    static double random_double(double min,double max) {
    return min+(max-min)* random_double();
}


};

class vec3 {
public:
  vec3(){}
  vec3(double e1, double e2, double e3) : e{e1, e2, e3} {}
  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }
  vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
  vec3 &operator+=(const vec3 &v) {
    e[0] += v.x();
    e[1] += v.y();
    e[2] += v.z();
    return *this;
  }
  vec3 &operator*=(double f) {
    e[0] *= f;
    e[1] *= f;
    e[2] *= f;
    return *this;
  }
   double operator*=(const vec3 &v) {
    return e[0]*v.e[0]+e[1]*v.e[1]+e[2]*v.e[2];
  }
  vec3 &operator/=(const double t) { return *this *= 1 / t; }

  double length() const { return sqrt(length_squared()); }

    bool near_zero() const {
        // Return true if the vector is close to zero in all dimensions.
        const auto s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }

  double length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

  static vec3 random() {
    return vec3(Mathf::random_double(),Mathf::random_double(),Mathf::random_double());
  }
   static vec3 random(double min, double max) {
        return vec3(Mathf::random_double(min,max), Mathf::random_double(min,max), Mathf::random_double(min,max));
    }
  double e[3];
};

using point3=vec3;
using color=vec3;
using Vector3=vec3;

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 normalize(vec3 v)  {
    return v / v.length();
}

inline void write_color(std::ostream &out, color pixel_color,int samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples and gamma-correct for gamma=2.0.
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * Mathf::Clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Mathf::Clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Mathf::Clamp(b, 0.0, 0.999)) << '\n';
}





const double pi=3.14159265;

inline double d2r(double degree){
    return degree*pi/180;
}


// get a random point in a sphere
inline vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

inline vec3 random_unit_vector() {
    return normalize(random_in_unit_sphere());
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n)*n;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}