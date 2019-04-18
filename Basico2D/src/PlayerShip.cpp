#include <PlayerShip.h>
#include <Point.h>
#include <math.h>
#include <Bullet.h>
#include <Object.h>
#include <stdio.h>
#include <vector>

PlayerShip::PlayerShip() :
    Object(Point(0,0), 0, 0)
{
    coordinate = new Point(0,0);
    angle = 0.1;
    speed = 5;
    width = 2;
    height = 3;
    currentBullets = 0;
    forceRotate = 15;
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

void PlayerShip::Rotate(bool toLeft)
{
    angle += (toLeft) ? forceRotate:-forceRotate;
}

void PlayerShip::Shoot(int widthScreen, int heightScreen)
{
    if(currentBullets < 10)
    {
        Bullet* bullet = new Bullet(coordinate->x,coordinate->y,angle,0,0);

        bullets.push_back(bullet);
        currentBullets++;
    }
}

void PlayerShip::MoveBullets()
{
    int i;
    Bullet* bullet;
    for(i=0; i<currentBullets; i++)
    {
        bullet = bullets.at(i);
        bullet->MoveBullet();
        if(!bullet->inGame)
        {
            bullets.erase(bullets.begin()+i);
            currentBullets--;
        }
    }
}
