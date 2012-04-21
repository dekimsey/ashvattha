#include "ASHTerrain.h"

const int ASHTerrain::MIN_DENSITY = 0;
const int ASHTerrain::MAX_DENSITY = 255;

ASHTerrain::ASHTerrain(unsigned int depth, unsigned int height) : 
    _depth(-depth), _height(height) {
    init();
}

void ASHTerrain::init() {
    //set low, high based on density properties of blocks
    _dNoise.setLow(ASHTerrain::MIN_DENSITY);
    _dNoise.setHigh(ASHTerrain::MAX_DENSITY); 

    //set low, high on height noise
    _hNoise.setLow(_depth);
    _hNoise.setHigh(_height);
}

ASHRegion::RegionCube ASHTerrain::getRegionCube(
       ASHRegion::Bounds bounds) {
    int xmax = bounds.xmin + bounds.xspan;
    int ymax = bounds.ymin + bounds.yspan;
    int zmax = bounds.zmin + bounds.zspan;

    //constrain the zvalues to the _depth and _height
    if(bounds.zmin < _depth) {
        bounds.zmin = _depth;
    }
    if(zmax > _height) {
        bounds.zspan = _height - bounds.zmin;
    }

    auto regionCube = ASHRegion::initRegionCube(bounds.xspan, 
            bounds.yspan, bounds.zspan);


    //populate the region_cube with information up 
    //to height and down to depth
    for(int x = bounds.xmin; x < xmax; ++x) {
        for(int y = bounds.ymin; y < ymax; ++y) {
            regionCube[x][y] = fillZTerrain(bounds);
        }
    }

    return regionCube;
}

//get the corresponding z terrain for the given x, y, and z values
//using the heightmap
//and storing in rcubePtr
ASHRegion::RegionStrip ASHTerrain::fillZTerrain(
        const ASHRegion::Bounds& bounds) {
    auto heightmap = getHeightMap(bounds);
    auto strip = ASHRegion::initRegionStrip(bounds.zspan); 
    int zmax = bounds.zmin + bounds.zspan;
    const int x = bounds.xmin;
    const int y = bounds.ymin;

    //account for depth and heightmap height
    //z < 0 is filled from _depth to 0
    //z > 0 is filled from 0 to heighmap[x][y]
    //this creates a relatively filled underground
    //and an aboveground of varied height
    if(bounds.zmin < 0) {
        if(zmax < 0) {
            for(int z = bounds.zmin; z < zmax; ++z) {
                strip[z] = _dNoise.octave(x, y, z);
            }
        } else {
            //guaranteed to pass through zero
            for(int z = bounds.zmin; z < 0; ++z) {
                strip[z] = _dNoise.octave(x, y, z);
            }
            for(int z = 0; z < heightmap[x][y] && z < zmax; ++z) {
                strip[z] = _dNoise.octave(x, y, z);
            }
        } 
    }
    else {
        for(int z = bounds.zmin; z < heightmap[x][y] && z < zmax; ++z) {
            strip[z] = _dNoise.octave(x, y, z);
        }
    }

    return strip;
}

ASHRegion::RegionSquare ASHTerrain::getHeightMap(
        const ASHRegion::Bounds& bounds) {
    auto heightmap = ASHRegion::initRegionSquare(
            bounds.xspan, bounds.yspan);
    int xmax = bounds.xmin + bounds.xspan;
    int ymax = bounds.ymin + bounds.yspan;

    for(int x = bounds.xmin; x < xmax; ++x) {
        for(int y = bounds.ymin; y < ymax; ++y) {
            heightmap[x][y] = _hNoise.octave(x, y);
        } 
    }

    return heightmap;
}

