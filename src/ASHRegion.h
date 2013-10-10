#ifndef __ASHREGION_H__
#define __ASHREGION_H__

#include <vector>
#include <memory>

namespace ASHRegion {
    typedef std::vector< int > RegionStrip;
    typedef std::vector< RegionStrip > RegionSquare;
    typedef std::vector< RegionSquare > RegionCube;

    RegionCube initRegionCube(int xspan, int yspan, int zspan);
    RegionSquare initRegionSquare(int xspan, int yspan);
    RegionStrip initRegionStrip(int xspan);
    
    struct Bounds {
        int xmin;
        unsigned int xspan;

        int ymin;
        unsigned int yspan;

        int zmin;
        unsigned int zspan;
    };
};

#endif
