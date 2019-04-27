#include "Bullet.h"
#include "Position.h"
#include "math.h"
// **********************************************************************
// Bullet(Position* _coord, float _angle, float _limitX, float _limitY, ObjectModel* _model): Object(_coord, _angle, 10, _model)
// Construtor da Classe Bullet
// **********************************************************************
Bullet::Bullet(Position* _coord, float _angle, float _limitX, float _limitY, ObjectModel* _model):
    Object(_coord, _angle, 500, _model)
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
// **********************************************************************
// ~Bullet()
// Desconstrutor da Classe Bullet
// **********************************************************************
Bullet::~Bullet()
{

}
// **********************************************************************
// void MoveBullet()
// Move as a bala, alterando sua posição
// **********************************************************************
void Bullet::MoveBullet(float _deltaTime)
{
    float alfa  = speed * _deltaTime;
    coordinate->x += alfaX*alfa;
    coordinate->y += alfaY*alfa;

    if(coordinate->x > limitX) inGame = false;
    else if(coordinate->x < 0) inGame = false;
    if(coordinate->y > limitY) inGame = false;
    else if(coordinate->y < 0) inGame = false;
}
