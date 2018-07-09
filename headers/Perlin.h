#ifndef PERLIN_NOISE_PERLIN_H
#define PERLIN_NOISE_PERLIN_H

#include <iostream>

class Perlin {
private:
    unsigned static char perm[];

    int fastfloor(float);
    float grad(int hash, float x, float y);
    float grad(int hash, float x, float y, float z);
    float fade(float t);

    float lerp(float t, float a, float b);
public:
    Perlin();

    Perlin(int seed);
    float noise(float x, float y);
    float pnoise(float x, float y, int px, int py);
    float noise(float x, float y, float z);
};


#endif
