#ifndef OBJECT_H
#define OBJECT_H
#include "Point.h"

class Object
{
    public:
        Point *coordinate;
        float angle;
        float speed;
        int width;
        int height;

        Object(Point _coordinate, float _angle, float _speed);
        virtual ~Object();

    protected:

    private:
};

#endif // OBJECT_H
