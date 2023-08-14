#ifndef __POINT_H
#define __POINT_H

/**
 * struct Pos
 * ----------
 * Stores a point in 3D space.
 * (note: z-position only used for draw order)
 */
struct Point {
        double x, y, z;
};

struct Point pnt_init( double x, double y, double z );

#endif //__POINT_H
