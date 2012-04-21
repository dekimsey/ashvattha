#ifndef __ASHTERRAIN_H__
#define __ASHTERRAIN_H__

#include "ASHNoise.h"
#include "ASHRegion.h"
#include <vector>
#include <memory>

class ASHTerrain {
    private:
        //density noise
        ASHNoise _dNoise;
        //height noise
        ASHNoise _hNoise;
        
        int _depth, _height;

        void init();
        void fillZTerrain(int x, int y, int zmin, unsigned int zspan);

    public:
        static const int MIN_DENSITY;
        static const int MAX_DENSITY;

        ASHTerrain(unsigned int depth, unsigned int height);

        ASHRegion::RegionCube getRegionCube(int xmin, 
                unsigned int xspan, int ymin, unsigned int yspan, 
                int zmin, unsigned int zspan);
};

#endif
