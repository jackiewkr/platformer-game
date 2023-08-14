#include "point.h"

struct Point pnt_init( double x, double y, double z )
{
        struct Point pnt;
        pnt.x = x;
        pnt.y = y;
        pnt.z = z;

        return pnt;
}
