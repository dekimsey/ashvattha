#ifndef __VORONOI_H__
#define __VORONOI_H__

#include <vector>
#include <memory>
#include "geometry.h"

class Voronoi {
    public:
        Voronoi(int width, int height, int numSites);

    private:
        int xmax, ymax, xmin, ymin;
        std::vector< Point > _sites;
        void generateSites(int width, int height, int numSites);
};
#endif
