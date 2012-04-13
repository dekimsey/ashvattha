#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <memory>

namespace VGeom {
    struct Point;
    struct Edge;

    typedef shared_pt< Point > PointPtr;

    struct Point {
        float x;
        float y;
    };

    struct Edge {
        PointPtr src;
        PointPtr dest;
    };
};
#endif
