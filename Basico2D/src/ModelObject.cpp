#include "ModelObject.h"

ModelObject::ModelObject(int _model[], int _length)
{
    for(_length=_length-1; _length >= 0; _length--) model[_length] = _model[_length];
}

ModelObject::~ModelObject()
{
    //dtor
}
