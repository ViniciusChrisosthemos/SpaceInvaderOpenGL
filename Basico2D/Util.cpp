#include <cmath>
#include <cstddef>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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
    Point *coordinate;
    float angle;
    float speed;
    int width;
    int height;

    Object(){}
    Object(Point _coordinate, float _angle, float _speed)
    {
        coordinate = &_coordinate;
        angle = _angle;
        speed = _speed;
    }
};

class Bullet : public Object
{
public:
    float limitX;
    float limitY;
    bool inGame;
    float alfaX;
    float alfaY;
    int i;

    Bullet()
    {
        inGame = true;
    }

    Bullet(float _x, float _y, float _angle, float _limitX, float _limitY)
    {
        coordinate = new Point(_x,_y);
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

    void moveBullet()
    {
        /*
        coordinate->x += cos(angle*(M_PI/180)) * speed;
        coordinate->y += sin(angle*(M_PI/180)) * speed;
        //coordinate->x += cos(angle*(M_PI/180)) * speed;
        //printf("Bullet move -> Bx=%f,By=%f,Bangle=%f\n",coordinate->x,coordinate->y,angle);
        if(coordinate->x >= limitX) inGame = false;
            */

        coordinate->x += alfaX*i;
        coordinate->y += alfaY*i;

        if(coordinate->x > limitX) inGame = false;
        else if(coordinate->x < 0) inGame = false;
        if(coordinate->y > limitY) inGame = false;
        else if(coordinate->y < 0) inGame = false;
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
        coordinate = new Point(0,0);
        angle = 0.1;
        speed = 5;
        width = 2;
        height = 3;
        currentBullets = 0;
        forceRotate = 15;
    }

    void moveShip(int minX,int maxX,int minY,int maxY)
    {
        coordinate->x += cos(angle*(M_PI/180)) * speed;
        coordinate->y += sin(angle*(M_PI/180)) * speed;

        if(coordinate->x < minX) coordinate->x = minX;
        else if(coordinate->x > maxX) coordinate->x = maxX;
        if(coordinate->y < minY) coordinate->y = minY;
        else if(coordinate->y > maxY) coordinate->y = maxY;
    }

    void rotate(bool toLeft)
    {
        angle += (toLeft) ? forceRotate:-forceRotate;
    }

    bool canShoot()
    {
        return currentBullets < 10;
    }

    void Shoot(int widthScreen, int heightScreen)
    {
        Bullet bullet(coordinate->x,coordinate->y, angle, widthScreen, heightScreen);
        //bullet.angle = angle;
        bullet.speed = speed;
        /*
        printf("Bx=%f,By=%f,Bangle=%f\n",bullet.coordinate->x,bullet.coordinate->y,bullet.angle);
        printf("Sx=%f,Sy=%f,Sangle=%f\n",coordinate->x,coordinate->y,angle);
        */
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



//https://stackoverflow.com/questions/1108780/why-do-i-always-get-the-same-sequence-of-random-numbers-with-rand

class EnemyShip : public Object
{
public:
    Point *p1;
    Point *p2;
    Point *p3;
    float t;

    EnemyShip()
    {
        srand(time(NULL));
        coordinate = new Point(rand()%800,rand()%600);
        printf("Initial pos : (%f,%f)",coordinate->x,coordinate->y);
        p1 = new Point(coordinate->x,coordinate->y);
        p2 = new Point(p1->x + (rand()%100 - 200),p1->y + (rand()%100 - 200));
        p3 = new Point(p1->x + (rand()%100 - 200),(rand()%100 - 200));
        printf("P1(%f,%f),P2(%f,%f),P3(%f,%f)\n",p1->x,p1->y,p2->x,p2->y,p3->x,p3->y);
        t = 0.001;
    }

    void moveEShip()
    {
        float aux = 1-t;
        /*
        coordinate->x += pow(aux,3)*100 + 3*t*pow(aux,2)*100 + 3*t*t*aux*400 + t*t*t*500;
        coordinate->y += pow(aux,3)*100 + 3*t*pow(aux,2)*350 + 3*t*t*aux*450 + t*t*t*200;
        */

        coordinate->x = aux*aux*(p1->x) + 2*aux*t*(p2->x) + t*t*(p3->x);
        coordinate->y = aux*aux*(p1->y) + 2*aux*t*(p2->y) + t*t*(p3->y);

        //printf("%f,%f,%f\n",coordinate->x,coordinate->y,t);

        t += 0.007;

        if(t > 1)
        {
            t = 0;

            p1 = new Point(p2->x,p2->y);
            p2 = new Point(abs(p3->x - p2->x + p3->x), abs(p3->y - p2->y + p3->y));
            p3 = new Point((rand()%100 - 200),(rand()%100 - 200));

            printf("P1(%f,%f),P2(%f,%f),P3(%f,%f)\n",p1->x,p1->y,p2->x,p2->y,p3->x,p3->y);
        };
    }
};




