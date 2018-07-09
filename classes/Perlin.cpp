#include "../headers/Perlin.h"

unsigned char Perlin::perm[] = {151,160,137,91,90,15,
                        131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
                        190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
                        88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
                        77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
                        102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
                        135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
                        5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
                        223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
                        129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
                        251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
                        49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
                        138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
                        151,160,137,91,90,15,
                        131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
                        190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
                        88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
                        77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
                        102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
                        135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
                        5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
                        223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
                        129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
                        251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
                        49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
                        138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};

int Perlin::fastfloor(float x) {
    return x > 0 ? int(x) : int(x) - 1;
}

float Perlin::grad( int hash, float x, float y ) {
    int h = hash & 7;
    float u = h<4 ? x : y;
    float v = h<4 ? y : x;
    return ((h&1)? -u : u) + (h&2 ? -2.0 * v : 2.0 * v);
}

float Perlin::fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float Perlin::lerp(float t, float a, float b) {
    return a + t * (b - a);
}

float Perlin::noise(float x, float y)
{
    int ix0, iy0, ix1, iy1;
    float fx0, fy0, fx1, fy1;
    float s, t, nx0, nx1, n0, n1;

    ix0 = fastfloor(x);
    iy0 = fastfloor(y);
    fx0 = x - ix0;
    fy0 = y - iy0;
    fx1 = fx0 - 1.0f;
    fy1 = fy0 - 1.0f;
    ix1 = (ix0 + 1) & 0xff;
    iy1 = (iy0 + 1) & 0xff;
    ix0 = ix0 & 0xff;
    iy0 = iy0 & 0xff;

    t = fade(fy0);
    s = fade(fx0);

    nx0 = grad(perm[ix0 + perm[iy0]], fx0, fy0);
    nx1 = grad(perm[ix0 + perm[iy1]], fx0, fy1);
    n0 = lerp(t, nx0, nx1);

    nx0 = grad(perm[ix1 + perm[iy0]], fx1, fy0);
    nx1 = grad(perm[ix1 + perm[iy1]], fx1, fy1);
    n1 = lerp(t, nx0, nx1);

    return 0.507f * (lerp(s, n0, n1));
}

float Perlin::pnoise(float x, float y, int px, int py)
{
    int ix0, iy0, ix1, iy1;
    float fx0, fy0, fx1, fy1;
    float s, t, nx0, nx1, n0, n1;

    ix0 = fastfloor(x);
    iy0 = fastfloor(y);
    fx0 = x - ix0;
    fy0 = y - iy0;
    fx1 = fx0 - 1.0f;
    fy1 = fy0 - 1.0f;
    ix1 = ((ix0 + 1) & px) & 0xff;
    iy1 = ((iy0 + 1) & py) & 0xff;
    ix0 = (ix0 & px) & 0xff;
    iy0 = (iy0 & py) & 0xff;

    t = fade(fy0);
    s = fade(fx0);

    nx0 = grad(perm[ix0 + perm[iy0]], fx0, fy0);
    nx1 = grad(perm[ix0 + perm[iy1]], fx0, fy1);
    n0 = lerp( t, nx0, nx1 );

    nx0 = grad(perm[ix1 + perm[iy0]], fx1, fy0);
    nx1 = grad(perm[ix1 + perm[iy1]], fx1, fy1);
    n1 = lerp(t, nx0, nx1);

    return 0.507f * (lerp(s, n0, n1));
}

float  Perlin::grad(int hash, float x, float y , float z) {
    int h = hash & 15;
    float u = h<8 ? x : y;
    float v = h<4 ? y : h==12||h==14 ? x : z;
    return ((h&1)? -u : u) + ((h&2)? -v : v);
}

float Perlin::noise(float x, float y, float z)
{
    int ix0, iy0, ix1, iy1, iz0, iz1;
    float fx0, fy0, fz0, fx1, fy1, fz1;
    float s, t, r;
    float nxy0, nxy1, nx0, nx1, n0, n1;

    ix0 = fastfloor(x);
    iy0 = fastfloor(y);
    iz0 = fastfloor(z);
    fx0 = x - ix0;
    fy0 = y - iy0;
    fz0 = z - iz0;
    fx1 = fx0 - 1.0f;
    fy1 = fy0 - 1.0f;
    fz1 = fz0 - 1.0f;
    ix1 = (ix0 + 1) & 0xff;
    iy1 = (iy0 + 1) & 0xff;
    iz1 = (iz0 + 1) & 0xff;
    ix0 = ix0 & 0xff;
    iy0 = iy0 & 0xff;
    iz0 = iz0 & 0xff;

    r = fade(fz0);
    t = fade(fy0);
    s = fade(fx0);

    nxy0 = grad(perm[ix0 + perm[iy0 + perm[iz0]]], fx0, fy0, fz0);
    nxy1 = grad(perm[ix0 + perm[iy0 + perm[iz1]]], fx0, fy0, fz1);
    nx0 = lerp(r, nxy0, nxy1);

    nxy0 = grad(perm[ix0 + perm[iy1 + perm[iz0]]], fx0, fy1, fz0);
    nxy1 = grad(perm[ix0 + perm[iy1 + perm[iz1]]], fx0, fy1, fz1);
    nx1 = lerp(r, nxy0, nxy1);

    n0 = lerp(t, nx0, nx1);

    nxy0 = grad(perm[ix1 + perm[iy0 + perm[iz0]]], fx1, fy0, fz0);
    nxy1 = grad(perm[ix1 + perm[iy0 + perm[iz1]]], fx1, fy0, fz1);
    nx0 = lerp(r, nxy0, nxy1);

    nxy0 = grad(perm[ix1 + perm[iy1 + perm[iz0]]], fx1, fy1, fz0);
    nxy1 = grad(perm[ix1 + perm[iy1 + perm[iz1]]], fx1, fy1, fz1);
    nx1 = lerp(r, nxy0, nxy1);

    n1 = lerp(t, nx0, nx1);

    return 0.936f * (lerp(s, n0, n1));
}

Perlin::Perlin() {}

Perlin::Perlin(int seed) {
    srand(seed);
    for (int i(0); i < 512; i++) {
        this->perm[i] = rand() % 0xff;
    }
}
