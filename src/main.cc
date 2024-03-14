#include "math_const.h"

#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "interval.h"

#include <iostream>

// double hit_sphere(const point3& center, double radius, const ray& r) {
//     // r.origin(): P = A + tB
//     // dot(A + tB - center, A + tB - center) <= radius ^2 => return TRUE
//     // That is, discriminant >= 0
//     const double a = r.direction().length_squared();
//     const double half_b = dot((r.origin() - center), r.direction());
//     const double c = dot(r.origin() - center, r.origin() - center) - radius * radius;
//     const double discriminant = half_b * half_b - a * c;

//     if (discriminant < 0)
//         return -1.0;
//     else
//         return (-half_b - sqrt(discriminant)) / a;
// }

color ray_color(const ray &r, const hittable& world) {
    // double t = hit_sphere(point3(0, 0, -1), 0.5, r);
    hit_record rec;
    // if (t > 0.0) {
    //     vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
    //     return 0.5 * color(N.x()+1, N.y()+1, N.z()+1);
    // }
    if (world.hit(r, interval(0, INF), rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }
    // if (hit_sphere(point3(0, 0, -1), 0.5, r))
    //     return color(51.0/255, 204.0/255, 255.0/255);

    vec3 unit_direction = unit_vector(r.direction());
    double a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {

    // Image

    const double ideal_aspect_ratio = 16.0 / 9.0;
    const int image_width = 800;
    const int image_height = static_cast<int>(image_width / ideal_aspect_ratio);
    // Re-define the aspect_ratio
    const double aspect_ratio = 1.0 * image_width / image_height;

    // World

    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    // Camera

    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = std::max(1.0, viewport_height * aspect_ratio);
    point3 camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    vec3 viewport_upper_left = camera_center 
                             - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            vec3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            vec3 ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);
            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";

}