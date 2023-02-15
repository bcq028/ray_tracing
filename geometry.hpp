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

  double length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
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

    // Divide the color by the number of samples.
    auto scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * Mathf::Clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Mathf::Clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Mathf::Clamp(b, 0.0, 0.999)) << '\n';
}





const double pi=3.14159265;

inline double d2r(double degree){
    return degree*pi/180;
}

inline double random_double(){
    return rand()/(RAND_MAX+1.0);
}

inline double random_double(double min,double max) {
    return min+(max-min)* random_double();
}

