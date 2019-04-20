#include <PlayerShip.h>
#include <Position.h>
#include <math.h>
#include <Bullet.h>
#include <Object.h>
#include <stdio.h>
#include <vector>
#include <ObjectModel.h>

PlayerShip::PlayerShip(Position* _initialPosition, ObjectModel* _model, ObjectModel* _bulletModel) :
    Object(_initialPosition, 0, 0, _model)
{
    health = 3;
    angle = 0;
    speed = 5;
    width = 2;
    height = 3;
    bulletModel = _bulletModel;
}

PlayerShip::~PlayerShip()
{
    //dtor
}

void PlayerShip::MoveShip(int minX,int maxX,int minY,int maxY)
{
    coordinate->x += cos(angle*(M_PI/180)) * speed;
    coordinate->y += sin(angle*(M_PI/180)) * speed;

    if(coordinate->x < minX) coordinate->x = minX;
    else if(coordinate->x > maxX) coordinate->x = maxX;
    if(coordinate->y < minY) coordinate->y = minY;
    else if(coordinate->y > maxY) coordinate->y = maxY;
}

void PlayerShip::Rotate(bool toRight)
{
    angle += (toRight) ? -15:15;
}

void PlayerShip::Shoot(int widthScreen, int heightScreen)
{
    if(bullets.size() <= 10)
    {
        Bullet* bullet = new Bullet(new Position(coordinate->x,coordinate->y),angle,widthScreen,heightScreen, bulletModel);
        bullets.push_back(bullet);
    }
}

void PlayerShip::TakeDamage()
{
    health--;
    if(health <= 0) inGame = false;
}


