#include "ASHTerrain.h"

const int MIN_DENSITY = 0;
const int MAX_DENSITY = 255;

ASHTerrain::ASHTerrain(unsigned int depth, unsigned int height) : 
    _depth(-depth), _height(height) {
    _dNoise.reset(new ASHNoise::ASHNoise{});
    _hNoise.reset(new ASHNoise::ASHNoise{});
    init();
}

void ASHTerrain::init() {
    //set low, high based on density properties of blocks
    _dNoise->setLow(ASHTerrain::MIN_DENSITY);
    _dNoise->setHigh(ASHTerrain::MAX_DENSITY); 

    //set low, high on height noise
    _hNoise->setLow(_depth);
    _hNoise->setHigh(_height);
}

ASHRegion::region_cube_ptr ASHTerrain::getRegionCube(int xmin, 
        unsigned int xspan, int ymin, unsigned int yspan, int zmin, 
        unsigned int zspan) {
    auto region_ptr = ASHRegion::initRegionCube(xspan, yspan, zspan);
    auto heightmap = ASHRegion::initRegionSquare(xspan, yspan);
    int xmax = xmin + xspan;
    int ymax = ymin + yspan;

    for(int x = xmin; x < xmax; ++x) {
        for(int y = ymin; y < ymax; ++y) {
            heightmap->at(x)->at(y) = _hNoise->octave(x, y);
        } 
    }
    //populate the region_cube with information up to height and down to depth
    for(int x = xmin; x < xmax; ++x) {
        for(int y = ymin; y < ymax; ++y) {
            fillZTerrain(x, y, zmin, zspan, heightmap, region_ptr);
        }
    }

    return region_ptr;
}

//get the corresponding z terrain for the given x, y, and z values
//using the heightmap
//and storing in rcubePtr
void ASHTerrain::fillZTerrain(int x, int y, int zmin, unsigned int zspan, 
        const ASHRegion::region_square_ptr& heightmap,
        const ASHRegion::region_cube_ptr& rcubePtr) {
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
                rcubePtr->at(x)->at(y)->at(z) = _dNoise->octave(x, y, z);
            }
        } else {
            //guaranteed to pass through zero
            for(int z = zmin; z < 0; ++z) {
                rcubePtr->at(x)->at(y)->at(z) = _dNoise->octave(x, y, z);
            }
            for(int z = 0; z < heightmap->at(x)->at(y) && z < zmax; ++z) {
                rcubePtr->at(x)->at(y)->at(z) = _dNoise->octave(x, y, z);
            }
        } 
    }
    else {
        for(int z = zmin; z < heightmap->at(x)->at(y) && z < zmax; ++z) {
            rcubePtr->at(x)->at(y)->at(z) = _dNoise->octave(x, y, z);
        }
    }
}


