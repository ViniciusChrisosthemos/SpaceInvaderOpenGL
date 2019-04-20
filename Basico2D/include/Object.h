#ifndef OBJECT_H
#define OBJECT_H
#include <Position.h>
#include <ObjectModel.h>

class Object
{
    public:
        float angle;
        float speed;
        int width;
        int height;
        Position *coordinate;
        ObjectModel* model;
        bool inGame;

        Object(Position* _coordinate, float _angle, float _speed, ObjectModel* _model);
        virtual ~Object();

    protected:

    private:
};

#endif // OBJECT_H
