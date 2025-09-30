#ifndef HEADDERMAIN_H
#define HEADDERMAIN_H


#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
//#include <glad/glad.h>
#include <cstdlib>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>



using std::make_shared;
using std::shared_ptr;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees*pi / 180.0;

}

inline double randomDouble() {
    return std::rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max) {
    return min + (max-min) * randomDouble();
}

#include <ray.h>
#include <color.h>
#include <vec3.h>
#include <hittable.h>
#include <hittableList.h>
#include <interval.h>
#include <sphere.h>
#include <camera.h>
#include <material.h>

#endif