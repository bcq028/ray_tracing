
#include "Sphere.hpp"


color ray_color(const Ray &r){
    hit_record rec{};
    sphere s(point3(0,0,-1),0.5);
    if(s.hit(r, -11, 100,rec)){
        return 0.5*(rec.normal+color(1,1,1));
    }
    vec3 unit_direction = normalize(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return Mathf::Lerp(color(1,1,1),color(0.5,0.7,1),t);
}

int main(){
    const auto aspect_radio=16.0/9;
    const int image_width=400;
    const int image_height=static_cast<int>(image_width/aspect_radio);

    auto viewport_height=2.0;
    auto viewport_width=viewport_height*aspect_radio;
    auto focal_length=1.0;
    // set camera at (0,0,-1) 
    auto origin=point3(0,0,0);
    auto horizontal=vec3(viewport_width,0,0);
    auto vertical=vec3(0,viewport_height,0);
    auto lower_left_corner=origin-horizontal/2-vertical/2-vec3(0,0,focal_length);

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            Ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}