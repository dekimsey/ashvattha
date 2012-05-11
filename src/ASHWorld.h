#ifndef __ASHWORLD_H__
#define __ASHWORLD_H__

#include "ASHTerrain.h"
#include "ASHRegion.h"

class ASHWorld {
    private: 
        ASHTerrain m_terrain;
    public:
        ASHWorld(unsigned int depth, unsigned int height);
        void renderRegion(const ASHRegion::Bounds& region);
}
