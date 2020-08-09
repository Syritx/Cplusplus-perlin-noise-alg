#ifndef NOISE_ALG
#define NOISE_ALG

#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>

using namespace std;

namespace custom_noise_algorithm {

    class vec3 {
    public:
        int x,z;
        float y;

        vec3(int x, float y, int z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        ~vec3() {}
    };

    class perlin_noise_func {
    
        int length;
        float frequency,amplitude;

        vector<vec3> coords;

    public:
        perlin_noise_func(int length, float freq, float ampl) {

            coords.reserve(length*length);

            frequency = freq;
            amplitude = ampl;
            this->length = length;

            int index = 0;

            // creating the coordinates and giving them a default y of 0
            for (int x = 0; x < length; x++) {
                for (int z = 0; z < length; z++) {
                    auto len = coords.begin()+index;
                    coords.insert(len,vec3(x,0,z));
                    index++;
                }
            }

            cout << coords.size() << " SIZE" << endl;
        }

        vector<vec3> GenerateNoise() {

            // setting a seed for the rand() function
            time_t t;
            std::srand((unsigned)time(&t));

            for (int i = 0; i < length*length; i++) {
                for (int layer = 0; layer < 10; layer++) {

                vec3 coord = coords.at(i);
                vec3 focus(0,0,0);

                int x = coord.x;
                int z = coord.z;

                // adding an offset to the origin coords
                int scale = 2;
                int xOffset = (rand()%(scale*2))+1-scale;
                int zOffset = (rand()%(scale*2))+1-scale;

                int newX = x+xOffset;
                int newZ = z+zOffset;

                // checking to see if they're valid
                for (int j = 0; j < coords.size(); j++) {
                    if ((newX == coords.at(j).x) && (newZ == coords.at(j).z)) {
                        focus = coords.at(j);
                        break;
                    }
                }

                // adding a y offset to the focus var
                int min = 3, max = 7;
                // min will always represent a negative number

                float yOffset = ((rand()%(min+max))+1-min)*frequency*amplitude;
                focus = vec3(focus.x,coord.x+yOffset,focus.z);

                // 're-assigning' the focus vec3 into the coords array
                for (int j = 0; j < coords.size(); j++) {
                
                    if ((focus.x == coords.at(j).x) && (focus.z == coords.at(j).z)) {
                        coords.at(j) = vec3(coords.at(j).x, focus.y+coords.at(j).y,coords.at(j).z);
                        break;
                    }
                }
            }
            }
            return coords;
        }

        ~perlin_noise_func() {}
    };
}

#endif
