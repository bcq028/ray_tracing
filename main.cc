
#include "Sphere.hpp"

#include "Camera.hpp"

const double infinity=std::numeric_limits<double>::infinity();

color ray_color(const Ray &r,const hittable&world,int depth){
    hit_record rec{};

    if(depth<0){
        return color(0,0,0);
    }
    if(world.hit(r, 0.001,infinity,rec)){
        point3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5 * ray_color(Ray(rec.p, target - rec.p), world,depth-1);
    }
    vec3 unit_direction = normalize(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return Mathf::Lerp(color(1,1,1),color(0.5,0.7,1),t);
}

int main(){
    const auto aspect_radio=16.0/9;
    const int image_width=400;
    const int image_height=static_cast<int>(image_width/aspect_radio);
    const int samples_per_pixel = 100;
    const int max_depth=10;

   hittable_list world;
   world.add(std::make_shared<sphere>(point3(0,-100.5,-1),100));
   world.add(std::make_shared<sphere>(point3(0,0,-1),0.5));

    camera cam;

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + Mathf::random_double()) / (image_width-1);
                auto v = (j + Mathf::random_double()) / (image_height-1);
                Ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world,max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}