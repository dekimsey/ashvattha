#ifndef __ASHNOISE_H__
#define __ASHNOISE_H__

#include <climits>

class ASHNoise {
    public:
        ASHNoise();
        ASHNoise(int seedX, int seedY, int seedZ, int seedW);
        int getSeedX();
        int getSeedY();
        int getSeedZ();
        int getSeedW();

        float octave(int n, float x, float p, float scale, float low, float high);
        float octave(int n, float x, float y, float p, float scale, float low, float high);
        float octave(int n, float x, float y, float z, float p, float scale, float low, float high);
        float octave(int n, float x, float y, float z, float w, float p, float scale, float low, float high);


    private:
        static const int MAX_SEED = USHRT_MAX;
        int _seedX;
        int _seedY;
        int _seedZ;
        int _seedW;

        int generateSeed();
        int clampSeed(int seed);
};
#endif

