#ifndef __ASHREGION_H__
#define __ASHREGION_H__

#include <vector>
#include <memory>

namespace ASHRegion {
    typedef std::vector< int > region_strip_t;
    typedef std::shared_ptr< region_strip_t > region_strip_ptr;
    typedef std::vector< region_strip_ptr > region_square_t;
    typedef std::shared_ptr< region_square_t > region_square_ptr;
    typedef std::vector< region_square_ptr > region_cube_t;
    typedef std::shared_ptr< region_cube_t > region_cube_ptr;

    static region_cube_ptr initRegionCube(int xspan, int yspan, int zspan);
    static region_square_ptr initRegionSquare(int xspan, int yspan);

};

#endif
