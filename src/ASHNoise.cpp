#include "ASHNoise.h"
#include "SimplexNoise.h"
#include <random>

//generate a new noise with random seeds
ASHNoise::ASHNoise() {
    _seedX = generateSeed();
    _seedY = generateSeed();
    _seedZ = generateSeed();
    _seedW = generateSeed();
}

//generate new noise with clamped given seeds
ASHNoise::ASHNoise(int seedX, int seedY, int seedZ, int seedW) : _seedX(clampSeed(seedX)), _seedY(clampSeed(seedY)), _seedZ(clampSeed(seedZ)), _seedW(clampSeed(seedW)) {}

//generate a signed seed within bounds
int ASHNoise::generateSeed() {
    std::random_device rd;
    return rd() % USHRT_MAX * ((rd() % 2 >= 1) ? 1 : -1);
}

//clamp a seed to be within [-ASHNoise::MAX_SEED, ASHNoise::MAX_SEED]
int ASHNoise::clampSeed(int seed) {
    if(seed > ASHNoise::MAX_SEED) {
        seed = ASHNoise::MAX_SEED;
    }
    else if(seed < -ASHNoise::MAX_SEED) {
        seed = -ASHNoise::MAX_SEED;
    }

    return seed;
}

int ASHNoise::getSeedX() {
    return _seedX;
}

int ASHNoise::getSeedY() {
    return _seedY;
}

int ASHNoise::getSeedZ() {
    return _seedZ;
}

int ASHNoise::getSeedW() {
    return _seedW;
}

float ASHNoise::octave(int n, float x, float p, float scale, float low, float high) {
    return SimplexNoise::octave(n, x + _seedX, p, scale, low, high);
}

float ASHNoise::octave(int n, float x, float y, float p, float scale, float low, float high) {
    return SimplexNoise::octave(n, x + _seedX, y + _seedY, p, scale, low, high);
}

float ASHNoise::octave(int n, float x, float y, float z, float p, float scale, float low, float high) {
    return SimplexNoise::octave(n, x + _seedX, y + _seedY, z + _seedZ, p, scale, low, high);
}

float ASHNoise::octave(int n, float x, float y, float z, float w, float p, float scale, float low, float high) {
    return SimplexNoise::octave(n, x + _seedX, y + _seedY, z + _seedZ, w + _seedW, p, scale, low, high);
}

