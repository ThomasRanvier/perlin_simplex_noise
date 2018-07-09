#ifndef PERLIN_NOISE_SIMPLEX_H
#define PERLIN_NOISE_SIMPLEX_H

#include <cmath>

class Simplex {
private:
    static unsigned char perm[512];
    int fastfloor(float x);
    float grad(int hash, float x, float y);
    float grad(int hash, float x, float y, float z);

public:
    Simplex();

    float noise(float x, float y);
    float noise(float x, float y, float z);
};


#endif
