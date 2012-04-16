#include "ASHNoise.h"

ASHTerrain::ASHTerrain(restrict unsigned int depth, restrict unsigned int height) : _depth(-depth), _height(height) {
    _noise = new ASHNoise{}; 
}

void ASHTerrain::init() {
    //set low, high based on density properties of blocks
    _noise->setLow(_depth);
    _noise->setHigh(_height);
}

region_cube_ptr ASHTerrain::getRegionCube(const int xmin, const unsigned int xspan, const int ymin, const unsigned int yspan, const int zmin, const unsigned int zspan) {
    auto rcubePtr = initRegionCube(xspan, yspan, zspan);
    auto heightmap = initRegionSquare(xspan, yspan);

    for(int x = xmin; x < xmin + xspan; ++x) {
        for(int y = ymin; y < ymin + yspan; ++y) {
            heightmap[x][y] = _hNoise->octave(x, y);
        } 
    }
    //populate the region_cube with information up to height and down to depth
    for(int x = xmin; x < xmin + xspan; ++x) {
        for(int y = ymin; y < ymin + yspan; ++y) {
            fillZTerrain(x, y, zmin, zpan, heightmap, rcubePtr);
        }
    }
}

//get the corresponding z terrain for the given x, y, and z values
//using the heightmap
//and storing in rcubePtr
int ASHTerrain::fillZTerrain(const int x, const int y, const int zmin, const unsigned int zspan, region_square_ptr heightmap, region_cube_ptr rcubePtr) {
    int zmax = zmin + zspan;

    //constrain the zvalues to the _depth and _height
    if(zmin < _depth) {
        zmin = _depth;
    }
    if(zmax > _height) {
        zspan = _height - zmin;
    }
    
    zmax = zmin + zspan;

    //account for depth and heightmap height
    //z < 0 is filled from _depth to 0
    //z > 0 is filled from 0 to heighmap[x][y]
    //this creates a relatively filled underground
    //and an aboveground of varied height
    if(zmin < 0) {
        if(zmax < 0) {
            for(int z = zmin; z < zmax; ++z) {
                rcubePtr[x][y][z] = noise->octave(x, y, z);
            }
        } else {
            //guaranteed to pass through zero
            for(int z = zmin; z < 0; ++z) {
                rcubePtr[x][y][z] = noise->octave(x, y, z);
            }
            for(int z = 0; z < heightmap[x][y] && z < zmax; ++z) {
                rcubePtr[x][y][z] = noise->octave(x, y, z);
            }
        } 
    }
    else {
        for(int z = zmin; z < heightmap[x][y] && z < zmax; ++z) {
            rcubePtr[x][y][z] = noise->octave(x, y, z);
        }
    }
}

region_cube_ptr ASHTerrain::initRegionCube(int xspan, int yspan, int zspan) {
    region_cube_ptr rptr = new region_cube_t(xspan);

    for(int x = 0; x < xspan; ++x) {
        rptr[x]->push_back(new region_square_t(yspan));

        for(int y = 0; y < yspan; ++y) {
            rptr[x][y]->push_back(new region_strip_t(zspan));

            for(int z = 0; z < zspan; ++z) {
                rptr[x][y][z]->push_back(0);
            }
        }
    }

    return rptr; 
}

ASHTerrain::region_square_ptr ASHTerrain::initRegionSquare(int xspan, int yspan) {
    region_square_ptr rptr = new region_square_t(xspan);

    for(int x = 0; x < xspan; ++x) {
        rptr[x]->push_back(new region_strip_t(yspan));

        for(int y = 0; y < yspan; ++y) {
            rptr[x][y]->push_back(0);
        }
    }
    return rptr
}

