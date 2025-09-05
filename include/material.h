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

class dielectric : public material {
    public:
        dielectric(double refractionIndex) : refractionIndex(refractionIndex) {}

        bool scatter(const ray& r_in, const hitRecord& rec, color& attenuation, ray& scattered) const override{
            attenuation = color(1.0, 1.0, 1.0);
            double ri = rec.frontFace? (1.0/refractionIndex) : refractionIndex;

            vec3 unitDir = unit_vector(r_in.direction());

            double cos_theta = std::fmin(dot(-unitDir, rec.normal), 1.0);
            double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

            bool cannotRefract = ri * sin_theta > 1;
            vec3 direction;

            if (cannotRefract || reflectance(cos_theta, ri) > randomDouble())
                direction = reflect(unitDir, rec.normal);
            else    
                direction = refract(unitDir, rec.normal, ri);

            scattered = ray(rec.p, direction);
            return true;

        }

    private:
    double refractionIndex;

    static double reflectance (double cosine, double refractionIndex) {
        auto r0 = (1 - refractionIndex) / (1 + refractionIndex);
        r0 = r0*r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }
};

#endif