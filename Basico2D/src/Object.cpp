#include "Object.h"

Object::Object(Point _coordinate, float _angle, float _speed)
{
    coordinate = &_coordinate;
    angle = _angle;
    speed = _speed;
}

Object::~Object()
{
    delete coordinate;
}
