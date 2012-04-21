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
        ASHRegion::RegionStrip fillZTerrain(
                const ASHRegion::Bounds& bounds);
        ASHRegion::RegionSquare getHeightMap(
                const ASHRegion::Bounds& bounds);

    public:
        static const int MIN_DENSITY;
        static const int MAX_DENSITY;

        ASHTerrain(unsigned int depth, unsigned int height);

        ASHRegion::RegionCube getRegionCube(ASHRegion::Bounds bounds);
};

#endif
