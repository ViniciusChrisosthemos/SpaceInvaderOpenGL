#include "Bullet.h"
#include "Point.h"
#include "math.h"

Bullet::Bullet(float _x, float _y, float _angle, float _limitX, float _limitY):
    Object(Point(_x,_y), _angle, 10)
{
    limitX = _limitX;
    limitY = _limitY;
    inGame = true;
    angle = _angle;

    float auxX = cos(angle*(M_PI/180)) * 20;
    float auxY = sin(angle*(M_PI/180)) * 20;
    float alfa = sqrt(auxX*auxX + auxY*auxY);
    alfaX = auxX/alfa;
    alfaY = auxY/alfa;
    i = 10;
}

Bullet::~Bullet()
{
    //dtor
}

void Bullet::MoveBullet()
{
    this->coordinate->x += alfaX*i;
    coordinate->y += alfaY*i;

    if(coordinate->x > limitX) inGame = false;
    else if(coordinate->x < 0) inGame = false;
    if(coordinate->y > limitY) inGame = false;
    else if(coordinate->y < 0) inGame = false;
}
