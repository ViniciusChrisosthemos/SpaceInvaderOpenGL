#include "Object.h"

Object::Object(Position* _coordinate, float _angle, float _speed, ObjectModel* _model)
{
    coordinate = _coordinate;
    angle = _angle;
    speed = _speed;
    model = _model;
    width = _model->model.at(0).size() * _model->sizePixel;
    height = _model->model.size() * _model->sizePixel;
    inGame = true;
}

Object::~Object()
{
    delete coordinate;
    delete model;
}
