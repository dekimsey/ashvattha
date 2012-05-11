#ifndef __ASHTERRAIN_H__
#define __ASHTERRAIN_H__

#include "ASHNoise.h"
#include "ASHRegion.h"
#include <vector>
#include <memory>

/*
 * ASHTerrain: A class that can be used to generate the terrain map for a given bounds
 *  it doesn't store the terrain, since the world can be consistently procedurally generated
 */

class ASHTerrain {
    private:
        //density noise
        ASHNoise m_dNoise;
        //height noise
        ASHNoise m_hNoise;
        
        int m_depth, m_height;

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
