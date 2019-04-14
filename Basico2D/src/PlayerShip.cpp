#include <PlayerShip.h>
#include <Point.h>
#include <math.h>
#include <Bullet.h>
#include <Object.h>
#include <stdio.h>


PlayerShip::PlayerShip() :
    Object(Point(0,0), 0, 0)
{
    bullets[10];
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

bool PlayerShip::CanShoot()
{
    return currentBullets < 10;
}

void PlayerShip::Shoot(int widthScreen, int heightScreen)
{
    Bullet bullet(coordinate->x,coordinate->y, angle, widthScreen, heightScreen);
    bullet.speed = speed;

    printf("Bx=%f,By=%f,Bangle=%f\n",bullet.coordinate->x,bullet.coordinate->y,bullet.angle);
    printf("Sx=%f,Sy=%f,Sangle=%f\n",coordinate->x,coordinate->y,angle);

    bullets[currentBullets++] = bullet;
    printf("FIM SHOOT, Bullet(%f,%f,%f)\n",bullets[0].coordinate->x,bullets[0].coordinate->y,bullets[0].speed);
}

void PlayerShip::MoveBullets()
{
    printf("COMECO MOVEBULLETS \n");
    Bullet *bullet;
    for(int i=0; i<currentBullets; i++)
    {
        bullet = &bullets[i];
        printf("step1\n");
        bullet->MoveBullet();
        if(!bullet->inGame)
        {
            for(int j=i; j<currentBullets-1;j++)
            {
                bullets[j] = bullets[j+1];
            }
            currentBullets -= 1;
        }
    }
}
