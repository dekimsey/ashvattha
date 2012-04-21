#ifndef __ASHTERRAIN_H__
#define __ASHTERRAIN_H__

#include "ASHNoise.h"
#include "ASHRegion.h"
#include <vector>
#include <memory>

class ASHTerrain {
    private:
        //density noise
        std::shared_ptr< ASHNoise > _dNoise;

        //height noise
        std::shared_ptr< ASHNoise > _hNoise;
        int _depth, _height;

        void init();
        void fillZTerrain(int x, int y, int zmin, unsigned int zspan, 
                const ASHRegion::region_square_ptr& heightmap,
                const ASHRegion::region_cube_ptr& rcubePtr);

    public:
        static const int MIN_DENSITY;
        static const int MAX_DENSITY;

        ASHTerrain(unsigned int depth, unsigned int height);

        ASHRegion::region_cube_ptr getRegionCube(int xmin, 
                unsigned int xspan, int ymin, unsigned int yspan, 
                int zmin, unsigned int zspan);
};

#endif
