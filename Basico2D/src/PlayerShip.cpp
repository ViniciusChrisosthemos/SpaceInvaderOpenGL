#include <PlayerShip.h>
#include <Position.h>
#include <math.h>
#include <Bullet.h>
#include <Object.h>
#include <stdio.h>
#include <vector>
#include <ObjectModel.h>
// **********************************************************************
// PlayerShip(Position* _initialPosition, ObjectModel* _model, ObjectModel* _bulletModel):Object(_initialPosition, 0, 0, _model)
// Construtor da classe PlayerShip
// **********************************************************************
PlayerShip::PlayerShip(Position* _initialPosition, ObjectModel* _model, ObjectModel* _bulletModel) :
    Object(_initialPosition, 0, 0, _model)
{
    health = 50;
    angle = 0;
    speed = 40;
    bulletModel = _bulletModel;
}
// **********************************************************************
// ~PlayerShip()
// Desconstrutor da classe PlayerShip
// **********************************************************************
PlayerShip::~PlayerShip()
{
    //dtor
}
// **********************************************************************
// void MoveShip(int minX,int maxX,int minY,int maxY)
// Move a nave, verificando e impedindo a saida da nave das extremidades da tela
// **********************************************************************
void PlayerShip::MoveShip(int minX,int maxX,int minY,int maxY)
{
    coordinate->x += (cos(angle*(M_PI/180)) * (speed/60.0));
    coordinate->y += (sin(angle*(M_PI/180)) * (speed/60.0));

    if(coordinate->x < minX) coordinate->x = minX;
    else if(coordinate->x > maxX) coordinate->x = maxX;
    if(coordinate->y < minY) coordinate->y = minY;
    else if(coordinate->y > maxY) coordinate->y = maxY;
}
// **********************************************************************
// void Rotate(bool toRight)
// Rotaciona a nave
// **********************************************************************
void PlayerShip::Rotate(bool toRight)
{
    float forceRotation = (30.0/66.0);
    angle += (toRight) ? -forceRotation:forceRotation;
}
// **********************************************************************
// void Shoot(int widthScreen, int heightScreen)
// Dispara uma bala, se possivel
// **********************************************************************
void PlayerShip::Shoot(int widthScreen, int heightScreen)
{
    if(bullets.size() <= 10)
    {
        Bullet* bullet = new Bullet(new Position(coordinate->x,coordinate->y),angle,widthScreen,heightScreen, bulletModel);
        bullets.push_back(bullet);
    }
}
// **********************************************************************
// void TakeDamage()
// Diminui a vida da nave em 1 ponto
// **********************************************************************
void PlayerShip::TakeDamage()
{
    health--;
    if(health <= 0) inGame = false;
}


