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

    auto material_ground = make_shared<lambertian>(color(0.2, 0.8, 0.1));
    auto material_sphere_lambert_orange = make_shared<lambertian>(color(0.8, 0.3, 0.1));
    auto material_sphere_metal_white = make_shared<metal>(color(0.9, 0.9, 0.9));



    world.add(make_shared<sphere>(point3(0.5, 0, -1), 0.5, material_sphere_lambert_orange));
    world.add(make_shared<sphere>(point3(-1.3, 0.1, -2), 0.6, material_sphere_metal_white));



    world.add(make_shared<sphere>(point3(0, -10000.5, -1), 10000, material_ground));


    camera cam;
    std::cout << "how many samples for ya then?" << std::endl;
    std::cin >> cam.samplesPerPixel;
    std::cout << "and the depth?" << std::endl;
    std::cin >> cam.maxDepth;
    
    cam.maxDepth = 5;
    

    cam.render(world); 

}