#ifndef REVYV_GEOMETRY_H
#define REVYV_GEOMETRY_H

namespace revyv {

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    double width;
    double height;
} Size;

typedef struct {
    Point location;
    Size size;
} Rect;

inline Rect make_rect(double x, double y, double width, double height)
{
    Rect rect;
    rect.location.x = x;
    rect.location.y = y;
    rect.size.width = width;
    rect.size.height = height;
    return rect;
}

inline Point make_point(double x, double y)
{
    Point point;
    point.x = x;
    point.y = y;
    return point;
}

inline Size make_size(double w, double h)
{
    Size size;
    size.width = w;
    size.height = h;
    return size;
}
}

#endif
