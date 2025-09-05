#include <headderMain.h>

#include <hittable.h>
#include <hittableList.h>
#include <sphere.h>

#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <cmath>





int main(){

    
    //World
    hittableList world;
    
    for (int a = -11; a < 11;  a++) {
        for (int b = -11; b < 11; b++) {
            auto chooseMat = randomDouble();
            point3 center(a +0.9*randomDouble(), 0.2, b + randomDouble());

            if ((center  - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphereMat;

                if (chooseMat < 0.8) {
                    // diffuse mat
                    auto albedo = color::random() * color::random();
                    sphereMat = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphereMat));
                } else if (chooseMat < 0.95) {
                    //metal mat
                    auto albedo = color::random(0.5, 1);
                    sphereMat = make_shared<metal>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphereMat));
                } else {
                    //glass mat
                    auto randIOR = randomDouble(1.33, 2.5);
                    sphereMat = make_shared<dielectric>(randIOR);
                    world.add(make_shared<sphere>(center, 0.2, sphereMat));
                }
            }
        }
    }

    auto material_ground = make_shared<lambertian>(color(0.2, 0.8, 0.1));
    auto material_lambert_orange = make_shared<lambertian>(color(0.9, 0.4, 0.05));
    auto material_metal_white = make_shared<metal>(color(0.9, 0.7, 0.4));
    auto material_glass_white = make_shared<dielectric>(1.45);
    auto material_bubble = make_shared<dielectric>(1.00/1.45);




    world.add(make_shared<sphere>(point3(0.5, 0, -1), 0.5, material_lambert_orange));
    world.add(make_shared<sphere>(point3(-1.3, 0.1, -2), 0.6, material_metal_white));
    world.add(make_shared<sphere>(point3(-0.3, -0.299, -0.7), 0.2, material_glass_white));
    world.add(make_shared<sphere>(point3(-0.3, -0.299, -0.7), 0.15, material_bubble));





    world.add(make_shared<sphere>(point3(0, -10000.5, -1), 10000, material_ground));


    camera cam;
    std::cout << "how many samples for ya then?" << std::endl;
    std::cin >> cam.samplesPerPixel;
    std::cout << "and the depth?" << std::endl;
    std::cin >> cam.maxDepth;
    std::cout << "focal fength?" << std::endl;
    std::cin >> cam.focalLength;

    

    cam.render(world); 

}