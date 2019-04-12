#include <cmath>
#include <cstddef>

class Point{
public:
    float x;
    float y;

    Point(){}
    Point(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
};

class Object
{
public:
    Point coordinate;
    float angle;
    float speed;
    int width;
    int height;

    Object(){}
    Object(Point _coordinate, float _angle, float _speed)
    {
        coordinate = _coordinate;
        angle = _angle;
        speed = _speed;
    }
};

class Bullet : public Object
{
public:
    float limitX;
    bool inGame;

    Bullet()
    {
        inGame = true;
    }

    Bullet(float _limitX)
    {
        limitX = _limitX;
        inGame = true;
    }

    void moveBullet()
    {
        coordinate.x += cos(angle*(M_PI/180)) * speed;
        if(coordinate.x >= limitX) inGame = false;
    }
};

class PlayerShip : public Object
{
public:
    int forceRotate;
    Bullet bullets[10];
    int currentBullets;

    PlayerShip()
    {
        coordinate.x = 0;
        coordinate.y = 0;
        angle = 90;
        speed = 5;
        width = 2;
        height = 3;
        currentBullets = 0;
        forceRotate = 15;
    }

    void moveShip(int minX,int maxX,int minY,int maxY)
    {
        coordinate.x += cos(angle*(M_PI/180)) * speed;
        coordinate.y += sin(angle*(M_PI/180)) * speed;

        if(coordinate.x < minX) coordinate.x = minX;
        else if(coordinate.x > maxX) coordinate.x = maxX;
        if(coordinate.y < minY) coordinate.y = minY;
        else if(coordinate.y > maxY) coordinate.y = maxY;
    }

    void rotate(bool toLeft)
    {
        angle += (toLeft) ? forceRotate:-forceRotate;
    }

    bool canShoot()
    {
        return currentBullets < 10;
    }

    void Shoot(int widthScreen)
    {
        Bullet bullet(widthScreen*2);
        bullet.coordinate.x = coordinate.x;
        bullet.coordinate.y = coordinate.y;
        bullet.angle = angle;
        bullet.speed = speed;

        bullets[currentBullets++] = bullet;
    }

    void moveBullets()
    {
        Bullet *bullet;
        for(int i=0; i<currentBullets; i++)
        {
            bullet = &bullets[i];
            bullet->moveBullet();
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
};

class EnemyShip
{

};






