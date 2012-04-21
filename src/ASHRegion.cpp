#include <ASHRegion.h>

ASHRegion::RegionCube ASHRegion::initRegionCube(int xspan, int yspan, int zspan) {
    RegionCube cube(xspan);

    for(int x = 0; x < xspan; ++x) {
        rptr.push_back(ASHRegion::initRegionSquare(yspan, zspan));
    }

    return rptr; 
}

ASHRegion::region_square_t ASHRegion::initRegionSquare(int xspan, int yspan) {
    region_square_t square(xspan);

    for(int x = 0; x < yspan; ++x) {
        RegionStrip strip(yspan);
        rptr.push_back(stripPtr);

        for(int y = 0; y < yspan; ++y) {
            rptr[x].push_back(0);
        }
    }
    return rptr;
}

