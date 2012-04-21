#include <ASHRegion.h>

ASHRegion::region_cube_ptr ASHRegion::initRegionCube(int xspan, int yspan, int zspan) {
    region_cube_ptr rptr(new region_cube_t(xspan));

    for(int x = 0; x < xspan; ++x) {
        rptr->push_back(ASHRegion::initRegionSquare(yspan, zspan));
    }

    return rptr; 
}

ASHRegion::region_square_ptr ASHRegion::initRegionSquare(int xspan, int yspan) {
    region_square_ptr rptr(new region_square_t(xspan));

    for(int x = 0; x < yspan; ++x) {
        region_strip_ptr stripPtr(new region_strip_t(yspan));
        rptr->push_back(stripPtr);

        for(int y = 0; y < yspan; ++y) {
            rptr->at(x)->push_back(0);
        }
    }
    return rptr;
}

