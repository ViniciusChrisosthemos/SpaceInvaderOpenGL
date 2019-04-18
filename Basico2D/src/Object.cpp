#include "Object.h"

Object::Object(Point* _coordinate, float _angle, float _speed, ObjectModel* _model)
{
    coordinate = _coordinate;
    angle = _angle;
    speed = _speed;
    model = _model;
}

Object::~Object()
{
    delete coordinate;
    delete model;
}

void Object::SetObjectModel(ObjectModel* _newModel)
{
    model = _newModel;
}
