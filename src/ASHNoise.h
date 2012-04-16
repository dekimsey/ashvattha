#ifndef __ASHNOISE_H__
#define __ASHNOISE_H__

#include <climits>

class ASHNoise {
    public:
        ASHNoise();
        ASHNoise(int seedX, int seedY, int seedZ, int seedW);


        //octave with default values
        float octave(float x);
        float octave(float x, float y);
        float octave(float x, float y, float z);
        float octave(float x, float y, float z, float w);

        //octave with custom values
        float octave(int n, float x, float p, float scale, float low, float high);
        float octave(int n, float x, float y, float p, float scale, float low, float high);
        float octave(int n, float x, float y, float z, float p, float scale, float low, float high);
        float octave(int n, float x, float y, float z, float w, float p, float scale, float low, float high);

        int getSeedX();
        int getSeedY();
        int getSeedZ();
        int getSeedW();
        int getOctaves();
        void setOctaves(int octaves);
        float getPersistence();
        void setPersistence(float persistence);
        float getScale();
        void setScale(float scale);
        float getLow();
        void setLow(float low);
        float getHigh();
        void setHigh(float high);


    private:
        static const int MAX_SEED = USHRT_MAX;
        int _seedX;
        int _seedY;
        int _seedZ;
        int _seedW;

        //noise variables with default values
        int _octaves = 16;
        float _persistence = .5;
        float _scale = .007;
        float _low = 0;
        float _high = 255;


        int generateSeed();
        int clampSeed(int seed);
};
#endif

