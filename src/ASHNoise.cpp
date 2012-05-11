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
    m_seedX = generateSeed();
    m_seedY = generateSeed();
    m_seedZ = generateSeed();
    m_seedW = generateSeed();
    init();
}

//generate new noise with clamped given seeds
ASHNoise::ASHNoise(int seedX, int seedY, int seedZ, int seedW) :
    m_seedX(clampSeed(seedX)), m_seedY(clampSeed(seedY)), 
    m_seedZ(clampSeed(seedZ)), m_seedW(clampSeed(seedW)) {
    init();
}

void ASHNoise::init() {
    m_octaves = ASHNoise::DEFAULT_OCTAVES;
    m_persistence = ASHNoise::DEFAULT_PERSISTENCE;
    m_scale = ASHNoise::DEFAULT_SCALE;
    m_low = ASHNoise::DEFAULT_LOW;
    m_high = ASHNoise::DEFAULT_HIGH;
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
    return octave(m_octaves, x, m_persistence, m_scale, m_low, m_high);
}

float ASHNoise::octave(float x, float y) {
    return octave(m_octaves, x, y, m_persistence, m_scale, m_low, m_high);
}

float ASHNoise::octave(float x, float y, float z) {
    return octave(m_octaves, x, y, z, m_persistence, m_scale, m_low, m_high);
}

float ASHNoise::octave(float x, float y, float z, float w) {
    return octave(m_octaves, x, y, z, w, m_persistence, m_scale, 
            m_low, m_high);
}

float ASHNoise::octave(int n, float x, float p, float scale, 
        float low, float high) {
    return SimplexNoise::octave(n, x + m_seedX, p, scale, low, high);
}

float ASHNoise::octave(int n, float x, float y, float p, float scale, 
        float low, float high) {
    return SimplexNoise::octave(n, x + m_seedX, y + m_seedY, p, scale, 
            low, high);
}

float ASHNoise::octave(int n, float x, float y, float z, float p, 
        float scale, float low, float high) {
    return SimplexNoise::octave(n, x + m_seedX, y + m_seedY, z + m_seedZ, 
            p, scale, low, high);
}

float ASHNoise::octave(int n, float x, float y, float z, float w, 
        float p, float scale, float low, float high) {
    return SimplexNoise::octave(n, x + m_seedX, y + m_seedY, z + m_seedZ, 
            w + m_seedW, p, scale, low, high);
}

int ASHNoise::getSeedX() {
    return m_seedX;
}

int ASHNoise::getSeedY() {
    return m_seedY;
}

int ASHNoise::getSeedZ() {
    return m_seedZ;
}

int ASHNoise::getSeedW() {
    return m_seedW;
}

int ASHNoise::getOctaves() {
    return m_octaves;
}

void ASHNoise::setOctaves(int octaves) {
    m_octaves = octaves;
}

float ASHNoise::getPersistence() {
    return m_persistence;
}

void ASHNoise::setPersistence(float persistence) {
    m_persistence = persistence;
}

float ASHNoise::getScale() {
    return m_scale;
}

void ASHNoise::setScale(float scale) {
    m_scale = scale;
}

float ASHNoise::getLow() {
    return m_low;
}

void ASHNoise::setLow(float low) {
    m_low = low;
}

float ASHNoise::getHigh() {
    return m_high;
}

void ASHNoise::setHigh(float high) {
    m_high = high;
}

