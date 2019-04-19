#ifndef OBJECT_H
#define OBJECT_H
#include <Point.h>
#include <ObjectModel.h>

class Object
{
    public:
        float angle;
        float speed;
        int width;
        int height;
        Point *coordinate;
        ObjectModel* model;

        Object(Point* _coordinate, float _angle, float _speed, ObjectModel* _model);
        virtual ~Object();

    protected:

    private:
};

#endif // OBJECT_H
