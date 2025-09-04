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

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -10000.5, -1), 10000));


    camera cam;

    cam.samplesPerPixel = 1;

    cam.render(world); 

}