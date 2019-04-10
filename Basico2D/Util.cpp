#include <cmath>

class Object
{
public:
    float x;
    float y;
    float angle;
    float speed;
    int width;
    int height;
};

class Bullet : public Object
{
public:
    bool inGame;
};

class PlayerShip : public Object
{
public:
    int forceRotate;

    PlayerShip()
    {
        x = 0;
        y = 0;
        angle = 90;
        speed = 5;
        width = 2;
        height = 3;

        forceRotate = 15;
    }

    void moveShip(int minX,int maxX,int minY,int maxY)
    {
        x += cos(angle*(M_PI/180)) * speed;
        y += sin(angle*(M_PI/180)) * speed;

        if(x < minX) x = minX;
        else if(x > maxX) x = maxX;
        if(y < minY) y = minY;
        else if(y > maxY) y = maxY;
    }

    void rotate(bool toLeft)
    {
        angle += (toLeft) ? forceRotate:-forceRotate;
    }
};








