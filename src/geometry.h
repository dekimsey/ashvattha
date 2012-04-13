#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <memory>

namespace VGeom {
    struct Point;
    struct Edge;

    struct Point {
        float x;
        float y;
    };

    struct Edge {
        Point src;
        Point dest;
    };
};
#endif
