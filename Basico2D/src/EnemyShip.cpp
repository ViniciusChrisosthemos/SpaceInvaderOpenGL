#include <EnemyShip.h>
#include <stdlib.h>
#include <time.h>
#include <Point.h>
#include <math.h>
#include <stdio.h>
#include <ObjectModel.h>

EnemyShip::EnemyShip(Point *_target, ObjectModel* _model, int _xLimit, int _yLimit) :
    Object(new Point(0,0), 0, 0, _model)
{
        srand(rand()%1000);
        target = _target;
        xLimit = _xLimit;
        yLimit = _yLimit;
        if(rand()%2)
        {
            coordinate = new Point(rand()%xLimit,0);
        }else
        {
            coordinate = new Point(rand()%xLimit,yLimit);
        }
        p0 = new Point(coordinate->x,coordinate->y);
        p1 = new Point(rand()%800,rand()%600);
        p2 = new Point(rand()%800,rand()%600);
        p3 = new Point(target->x,target->y);
        t = 0.001;
    }

EnemyShip::~EnemyShip()
{
    //dtor
}

void EnemyShip::MoveEShip()
{
    float aux = 1-t;

    coordinate->x = pow(aux,3)*p0->x + 3*t*pow(aux,2)*p1->x + 3*t*t*aux*p2->x + t*t*t*p3->x;
    coordinate->y = pow(aux,3)*p0->y + 3*t*pow(aux,2)*p1->y + 3*t*t*aux*p2->y + t*t*t*p3->y;

    t += 0.003;

    if(t > 1)
    {
        t = 0;
        p0 = p3;
        p1 = new Point(p3->x*2.0 - p2->x,p3->y*2.0 - p2->y);
        p2 = new Point(rand()%xLimit,rand()%yLimit);
        p3 = new Point(target->x,target->y);
        printf("P2(%f,%f),P1(%f,%f),P2(%f,%f),P3(%f,%f)\n",p0->x,p0->y,p1->x,p1->y,p2->x,p2->y,p3->x,p3->y);
    };
}
