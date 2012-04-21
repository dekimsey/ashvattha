#ifndef __ASHREGION_H__
#define __ASHREGION_H__

#include <vector>
#include <memory>

namespace ASHRegion {
    typedef std::vector< int > RegionStrip;
    typedef std::vector< RegionStrip > RegionSquare;
    typedef std::vector< RegionSquare > RegionCube;

    static region_cube_ptr initRegionCube(int xspan, int yspan, 
            int zspan);
    static region_square_ptr initRegionSquare(int xspan, int yspan);
    
    struct RegionBounds {
        int xmin;
        unsigned int xspan;

        int ymin;
        unsigned int yspan;

        int zmin;
        unsigned int zspan;
    };
};

#endif
