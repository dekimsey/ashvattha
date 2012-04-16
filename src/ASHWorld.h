#ifndef __ASHWORLD_H__
#define __ASHWORLD_H__

#include "ASHNoise.h"
#include <vector>
#include <memory>

class ASHWorld {
    private:

        typedef std::vector< int > region_strip_t;
        typedef std::unique_ptr< region_strip_t > region_strip_ptr;
        typedef std::vector< region_strip_ptr > region_square_t;
        typedef std::unique_ptr< region_square_t > region_square_ptr;
        typedef std::vector< region_square_ptr > region_cube_t;

        std::unique_ptr< ASHNoise > _hNoise;
        std::unique_ptr< ASHNoise > _dNoise;
        int _depth, _height;
                
        void init();
        region_cube_ptr initRegionCube(int xspan, int yspan, int zspan);
        region_square_ptr initRegionSquare(int xspan, int yspan);

    public:
        typedef std::unique_ptr< region_cube_t > region_cube_ptr;
        struct span_t {
            int start;
            unsigned int span;
        }

        ASHWorld(restrict unsigned int depth, restrict unsigned int height);
       
        region_cube_ptr getRegion(const int xmin, const unsigned int xspan, const int ymin, const unsigned int yspan, const int zmin, const unsigned int zspan);

        region_cube_ptr getRegion(span_t xspan, span_t yspan, span_t zspan); 
};

#endif
