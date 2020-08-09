#include "noise.h"
#include <iostream>
#include <vector>

#include <math.h>
#include <string>

int length = 10;
using namespace custom_noise_algorithm;
using namespace std;

int main() {
    vector<vec3> coordinates;
    coordinates.reserve(length*length);

    perlin_noise_func perlinNoise(length,.1f,1);
    coordinates = perlinNoise.GenerateNoise();

    // printing the y coordinates
    int mappingindex = 0;
    
    for (int x = 0; x < sqrt(coordinates.size()); x++) {
        string mapping = "";
        for (int z = 0; z < sqrt(coordinates.size()); z++) {
            mapping += to_string(coordinates.at(mappingindex).y) + " ";
            mappingindex++;
        }

        cout << mapping << endl;
    }
}
