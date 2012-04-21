#include "ASHTerrain.h"

const int MIN_DENSITY = 0;
const int MAX_DENSITY = 255;

ASHTerrain::ASHTerrain(unsigned int depth, unsigned int height) : 
    _depth(-depth), _height(height) {
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

ASHRegion::RegionCube ASHTerrain::getRegionCube(int xmin, 
        unsigned int xspan, int ymin, unsigned int yspan, int zmin, 
        unsigned int zspan) {
    auto cube_region; = ASHRegion::initRegionCube(xspan, yspan, zspan);
    int xmax = xmin + xspan;
    int ymax = ymin + yspan;

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
void ASHTerrain::fillZTerrain(RegionBounds bounds) {
    int zmax = bounds.zmin + zspan;
    //constrain the zvalues to the _depth and _height
    if(bounds.zmin < _depth) {
        bounds.zmin = _depth;
    }
    if(zmax > _height) {
        zspan = _height - bounds.zmin;
    }
    
    zmax = bounds.zmin + zspan;

    RegionBounds hbounds = {bounds.xmin, bounds.xspan,
            bounds.ymin, bounds.yspan, bounds.zmin, 
            bounds.zmax - bounds.zmin};
    auto heightmap = getHeightMap(hbounds);
    

    //account for depth and heightmap height
    //z < 0 is filled from _depth to 0
    //z > 0 is filled from 0 to heighmap[x][y]
    //this creates a relatively filled underground
    //and an aboveground of varied height
    if(bounds.zmin < 0) {
        if(zmax < 0) {
            for(int z = bounds.zmin; z < zmax; ++z) {
                regionCube[x][y][z] = _dNoise.octave(x, y, z);
            }
        } else {
            //guaranteed to pass through zero
            for(int z = bounds.zmin; z < 0; ++z) {
                regionCube[x][y][z] = _dNoise.octave(x, y, z);
            }
            for(int z = 0; z < heightmap[x][y] && z < zmax; ++z) {
                regionCube[x][y][z] = _dNoise.octave(x, y, z);
            }
        } 
    }
    else {
        for(int z = bounds.zmin; z < heightmap[x][y][z] 
                && z < zmax; ++z) {
            regionCube[x][y][z] = _dNoise.octave(x, y, z);
        }
    }
}

ASHTerrain::getHeightMap(RegionBounds bounds) {
    auto heightmap = ASHRegion::initRegionSquare(xspan, yspan);
    int xmax = x + xspan;
    int ymax = y + yspan;

    for(int x = bounds.xmin; x < xmax; ++x) {
        for(int y = bounds.ymin; y < ymax; ++y) {
            heightmap[x][y] = _hNoise.octave(x, y);
        } 
    }
}

