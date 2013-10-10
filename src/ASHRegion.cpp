#include <ASHRegion.h>

ASHRegion::RegionCube ASHRegion::initRegionCube(
        int xspan, int yspan, int zspan) {
    RegionCube cube(xspan);

    for(int x = 0; x < xspan; ++x) {
        cube.push_back(ASHRegion::initRegionSquare(yspan, zspan));
    }

    return cube; 
}

ASHRegion::RegionSquare ASHRegion::initRegionSquare(
        int xspan, int yspan) {
    RegionSquare square(xspan);

    for(int x = 0; x < yspan; ++x) {
        square.push_back(ASHRegion::initRegionStrip(yspan));
    }

    return square;
}


ASHRegion::RegionStrip ASHRegion::initRegionStrip(int xspan) {
    RegionStrip strip(xspan);

    for(int x = 0; x < xspan; ++x) {
        strip.push_back(0);
    }

    return strip;
}
