#ifndef CAMERA_H
#define CAMERA_H

#include <headderMain.h>
#include <material.h>


class camera {
    public:

            /*public camera parameters*/
        //image
        //default image width
        int imageWidth = 1920;
        //change with user input
        //std::cout << "please input image width" << std::endl;
        //std::cin >> imageWidth;

        //default image ratio
        float aspectRatio = 1.78f;
        //change with user input
        //std::cout << "please input the aspect ratio" << std::endl;
        //std::cin >> aspectRatio;
        int samplesPerPixel = 5;
        int channelNum = 3;
        int maxDepth = 10;

        double focalLength = 50;
        double sensorSize = 36;

        camera() {
            initialise();
        }







        void render(const hittable& world) {

            initialise();

            pixelSamplesScale = 1.0 / samplesPerPixel;
            pixels = new uint8_t[imageWidth * imageHeight * channelNum];

            int index = 0;
            for (int j = imageHeight - 1; j >= 0; --j) {
                //std::clog << imageHeight << std::endl << std::flush;
                //std::clog << j << std::endl << std::flush;
                int percentRemaining = static_cast<int>((j/imageHeight)*100);
                std::clog << "scanlines remaning: " << j << std::endl << std::flush;
                //std::clog << imageHeight << std::endl;

                for (int i = 0; i < imageWidth; ++i) {

                    color pixelColor(0 ,0 ,0);

                    for (int sample = 0; sample < samplesPerPixel; sample++) {
                        ray r = get_ray(i, j);
                        pixelColor += ray_col(r, maxDepth, world);
                    }
                    //auto pixelCenter = pixel00Loc + (i * pixelUDelta) + (j * pixelVDelta);
                    //auto rayDir = pixelCenter - cameraCenter;
                    //ray r(cameraCenter, rayDir);

                    //color pixelColor = ray_col(r, world);
                    
                    pixels = convertNormalisedToBit(pixels, index, pixelSamplesScale * pixelColor);
                }
            }

            std::string focalLengthString = std::to_string(static_cast<int>(focalLength));
            std::string outputName = "output/output_" + focalLengthString + "mm" + ".jpg";
            int imageWriteSuccess = stbi_write_jpg(outputName.c_str(), imageWidth, imageHeight, 3, pixels, 100);
            if (imageWriteSuccess == 1){
                std::clog << "image write success!" << std::endl;
            }
            else{
                std::clog << "failed to write image!" << std::endl;
            }

            delete[] pixels;
        }
 

    private:
    /*private camera parameters*/
    int imageHeight;
    double pixelSamplesScale;
    point3 center;
    point3 pixel00Loc;
    vec3 viewportUpperLeft;
    vec3 pixelUDelta;
    vec3 pixelVDelta;
    uint8_t* pixels;






        void initialise() {

            imageHeight = static_cast<int>(imageWidth / aspectRatio);
            imageHeight = std::max(1, imageHeight);
            int channelNum = 3;

            

            std::cout << "image width is " << imageWidth << std::endl;
            std::cout << "image height is " << imageHeight << std::endl;
            
            pixels = new uint8_t[imageWidth * imageHeight * channelNum];

 
            //auto theta = 2 * atan(sensorSize / (2 * focalLength));
            //auto theta = degrees_to_radians(wfov);
            //auto w = std::tan(theta/2);

            //float viewportWidth = 2 * w * 1.0;

            //float viewportHeight = viewportWidth * (double(imageHeight)/imageWidth);

            double focusDist = 1.0;

            double viewportWidth = (sensorSize / focalLength) * focusDist;
            double viewportHeight = viewportWidth * ( double(imageHeight) / double(imageWidth));

            center = point3(0,0,0);

            vec3 viewportU = vec3(viewportWidth, 0, 0);
            vec3 viewportV = vec3(0, viewportHeight, 0);

            pixelUDelta = viewportU / imageWidth;
            pixelVDelta = viewportV / imageHeight;

            viewportUpperLeft = center - vec3(0, 0, focusDist) - viewportU/2 - viewportV/2;
            pixel00Loc = viewportUpperLeft + 0.5 * (pixelUDelta + pixelVDelta);
            

        }

        ray get_ray(int i, int j) const {
            auto offset = sampleSquare();
            auto pixelSample = pixel00Loc + ((i + offset.x()) * pixelUDelta) + ((j + offset.y()) * pixelVDelta);
            auto rayOrigin = center;
            auto rayDir = pixelSample - rayOrigin;
            return ray(rayOrigin, rayDir);
        }

        vec3 sampleSquare() const {
            return vec3(randomDouble() - 0.5, randomDouble() - 0.5, 0);
        }
        
        color ray_col(const ray& r, int depth, const hittable& world) {
            if (depth <= 0)
                return color(0, 0, 0);

            hitRecord rec;

            if (world.hit(r, interval(0.001, infinity), rec)) {
                ray scattered;
                color attenuation;

                if (rec.mat->scatter(r, rec, attenuation, scattered))
                    return attenuation * ray_col(scattered, depth -1, world);
                return color (0, 0, 0);
            }

            vec3 unitDir = unit_vector(r.direction());
            auto a = 0.5*(unitDir.y()+1.0);

            return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7 ,1.0); 
        } 


};





#endif