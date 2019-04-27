#include <PlayerShip.h>
#include <Position.h>
#include <math.h>
#include <Bullet.h>
#include <Object.h>
#include <stdio.h>
#include <vector>
#include <ObjectModel.h>
// **********************************************************************
// PlayerShip(Position* _initialPosition, ObjectModel* _model, ObjectModel* _bulletModel):Object(_initialPosition, 0, 0, _model, int _widthScreen, int _heightScreen)
// Construtor da classe PlayerShip
// **********************************************************************
PlayerShip::PlayerShip(Position* _initialPosition, ObjectModel* _model, ObjectModel* _bulletModel, int _widthScreen, int _heightScreen) :
    Object(_initialPosition, 0, 0, _model)
{
    health = 50;
    angle = 0;
    speed = 250;
    bulletModel = _bulletModel;
    widthScreen = _widthScreen;
    heightScreen = _heightScreen;
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
// void MoveShip(float _deltaTime)
// Move a nave, verificando e impedindo a saida da nave das extremidades da tela
// **********************************************************************
void PlayerShip::MoveShip(float _deltaTime)
{
    float alfa = speed * _deltaTime;
    float radAngle = angle*(M_PI/180);
    coordinate->x += (cos(radAngle) * alfa);
    coordinate->y += (sin(radAngle) * alfa);

    if(coordinate->x < 0) coordinate->x = 0;
    else if(coordinate->x > widthScreen) coordinate->x = widthScreen;
    if(coordinate->y < 0) coordinate->y = 0;
    else if(coordinate->y > heightScreen) coordinate->y = heightScreen;
}
// **********************************************************************
// void Rotate(bool toRight, float _deltaTime)
// Rotaciona a nave
// **********************************************************************
void PlayerShip::Rotate(bool _toRight, float _deltaTime)
{
    float forceRotation = 250.0 * _deltaTime;
    angle += (_toRight) ? -forceRotation:forceRotation;
}
// **********************************************************************
// void Shoot()
// Dispara uma bala, se possivel
// **********************************************************************
void PlayerShip::Shoot()
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


