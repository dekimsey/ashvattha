#include "voronoi.h"
#include <random>
#include <algorithm>

Voronoi::Voronoi(int width, int height, int numSites) : xmax(0), ymax(0), xmin(0), ymin(0) {
    _sites = std::vector<int>::vector<int>(numSites);
    generateSites(width, height, numSites);
    relaxSites();
}

void Voronoi::generateSites(int width, int height, int numSites) {
    std::random_device rd;
    
    for (int i = 0; i < numSites; ++i) {
        int x = rd() % width;
        int y = rd() % height;
        _sites.push_back({x, y});

        //update min/max values
        _xmax = std::max(x, _xmax);
        _ymax = std::max(y, _ymax);
        _xmin = std::min(x, _xmin);
        _ymin = std::min(y, _ymin);
    }
}
