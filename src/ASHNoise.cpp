#include "ASHNoise.h"
#include "SimplexNoise.h"
#include <random>

const int ASHNoise::MAX_SEED = USHRT_MAX;
const int ASHNoise::DEFAULT_OCTAVES = 16;
const float ASHNoise::DEFAULT_PERSISTENCE = .5;
const float ASHNoise::DEFAULT_SCALE = .007;
const float ASHNoise::DEFAULT_LOW = 0;
const float ASHNoise::DEFAULT_HIGH = 255;


//generate a new noise with random seeds
ASHNoise::ASHNoise() {
    _seedX = generateSeed();
    _seedY = generateSeed();
    _seedZ = generateSeed();
    _seedW = generateSeed();
    init();
}

//generate new noise with clamped given seeds
ASHNoise::ASHNoise(int seedX, int seedY, int seedZ, int seedW) : _seedX(clampSeed(seedX)), _seedY(clampSeed(seedY)), _seedZ(clampSeed(seedZ)), _seedW(clampSeed(seedW)) {
    init();
}

void ASHNoise::init() {
    _octaves = ASHNoise::DEFAULT_OCTAVES;
    _persistence = ASHNoise::DEFAULT_PERSISTENCE;
    _scale = ASHNoise::DEFAULT_SCALE;
    _low = ASHNoise::DEFAULT_LOW;
    _high = ASHNoise::DEFAULT_HIGH;
}


//generate a signed seed within bounds
int ASHNoise::generateSeed() {
    std::random_device rd;
    return rd() % MAX_SEED * ((rd() % 2 >= 1) ? 1 : -1);
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

float ASHNoise::octave(float x) {
    return octave(_octaves, x, _persistence, _scale, _low, _high);
}

float ASHNoise::octave(float x, float y) {
    return octave(_octaves, x, y, _persistence, _scale, _low, _high);
}

float ASHNoise::octave(float x, float y, float z) {
    return octave(_octaves, x, y, z, _persistence, _scale, _low, _high);
}

float ASHNoise::octave(float x, float y, float z, float w) {
    return octave(_octaves, x, y, z, w, _persistence, _scale, _low, _high);
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

int ASHNoise::getOctaves() {
    return _octaves;
}

void ASHNoise::setOctaves(int octaves) {
    _octaves = octaves;
}

float ASHNoise::getPersistence() {
    return _persistence;
}

void ASHNoise::setPersistence(float persistence) {
    _persistence = persistence;
}

float ASHNoise::getScale() {
    return _scale;
}

void ASHNoise::setScale(float scale) {
    _scale = scale;
}

float ASHNoise::getLow() {
    return _low;
}

void ASHNoise::setLow(float low) {
    _low = low;
}

float ASHNoise::getHigh() {
    return _high;
}

void ASHNoise::setHigh(float high) {
    _high = high;
}

