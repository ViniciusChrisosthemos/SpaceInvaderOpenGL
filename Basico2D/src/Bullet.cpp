#include "Bullet.h"
#include "Point.h"
#include "math.h"

Bullet::Bullet(Point* _coord, float _angle, float _limitX, float _limitY, ObjectModel* _model):
    Object(_coord, _angle, 10, _model)
{
    limitX = _limitX;
    limitY = _limitY;
    angle = _angle;
    inGame = true;

    float auxX = cos(angle*(M_PI/180)) * 20;
    float auxY = sin(angle*(M_PI/180)) * 20;
    float alfa = sqrt(auxX*auxX + auxY*auxY);
    alfaX = auxX/alfa;
    alfaY = auxY/alfa;
}

Bullet::~Bullet()
{

}

void Bullet::MoveBullet()
{
    coordinate->x += alfaX*speed;
    coordinate->y += alfaY*speed;

    if(coordinate->x > limitX) inGame = false;
    else if(coordinate->x < 0) inGame = false;
    if(coordinate->y > limitY) inGame = false;
    else if(coordinate->y < 0) inGame = false;
}
