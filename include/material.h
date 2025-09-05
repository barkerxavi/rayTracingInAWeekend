#ifndef MATERIAL_H
#define MATERIAL_H

#include <hittable.h>
#include <ray.h>

class material{

    public:

        virtual ~material() = default;

        virtual bool scatter(
            const ray& r_in, const hitRecord& rec, color& attenuation, ray& scattered) const {
                return false;
            } 
};

class lambertian : public material{
    public:
        lambertian(const color& albedo) : albedo(albedo) {}

        bool scatter (const ray& r_in, const hitRecord& rec, color& attenuation, ray& scattered)
        const override {

            auto scatterDir = rec.normal + randomUnitVector();

            if (scatterDir.nearZero())
                scatterDir = rec.normal;

            scattered = ray(rec.p, scatterDir);
            attenuation = albedo;

            return true;
        }

    private:
        color albedo;
};

class metal : public material  {
    public:

        metal(const color& albedo) : albedo(albedo) {}

        bool scatter (const ray& r_in, const hitRecord& rec, color& attenuation, ray& scattered)
        const override {

            vec3 reflected = reflect(r_in.direction(), rec.normal);

            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return true;
        }

    private:
        
        color albedo;
};

#endif