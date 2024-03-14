#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere: public hittable {
    public:
        sphere(point3 _center, double _radius) : center(_center), radius(_radius) {}

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            const double a = r.direction().length_squared();
            const double half_b = dot((r.origin() - center), r.direction());
            const double c = dot(r.origin() - center, r.origin() - center) - radius * radius;
            const double discriminant = half_b * half_b - a * c;

            if (discriminant < 0)
                return false;
            const double sqrtDiscri = sqrtl(discriminant);
            
            const double nearest_root = (-half_b - sqrtDiscri) / a;
            const double farest_root = (-half_b + sqrtDiscri) / a;

            // 6.4 Front Faces Versus Back Faces
            if (ray_t.contains(nearest_root)) {
                rec.t = nearest_root;
                rec.p = r.at(rec.t);
                // rec.normal = (rec.p - center) / radius; // Actually, this may be the same as the following code
                vec3 outer_normal = (rec.p - center) / radius;
                rec.set_face_normal(r, outer_normal);
            } else if (ray_t.contains(farest_root)) {
                rec.t = farest_root;
                rec.p = r.at(rec.t);
                // rec.normal = (center - rec.p) / radius; // always point against the ray. Actually, this may be the same as the following code
                vec3 outer_normal = (rec.p - center) / radius;
                rec.set_face_normal(r, outer_normal);
            } else 
                return false;
            return true;
        }
    private:
        point3 center;
        double radius;
};

#endif