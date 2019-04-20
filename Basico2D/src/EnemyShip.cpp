#include <EnemyShip.h>
#include <stdlib.h>
#include <time.h>
#include <Position.h>
#include <math.h>
#include <stdio.h>
#include <ObjectModel.h>

EnemyShip::EnemyShip(Position *_target, ObjectModel* _model, int _xLimit, int _yLimit) :
    Object(new Position(0,0), 0, 0, _model)
{
        srand(rand()%1000);
        target = _target;
        xLimit = _xLimit;
        yLimit = _yLimit;

        switch(rand()%4)
        {
            case 0:
                coordinate = new Position(rand()%xLimit,0);
                break;
            case 1:
                coordinate = new Position(rand()%xLimit,yLimit);
                break;
            case 2:
                coordinate = new Position(0,rand()%yLimit);
                break;
            case 3:
                coordinate = new Position(xLimit,rand()%yLimit);
                break;
        }

        p0 = new Position(coordinate->x,coordinate->y);
        p1 = new Position(rand()%800,rand()%600);
        p2 = new Position(rand()%800,rand()%600);
        p3 = new Position(target->x,target->y);
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
        p1 = new Position(p3->x*2.0 - p2->x,p3->y*2.0 - p2->y);
        p2 = new Position(rand()%xLimit,rand()%yLimit);
        p3 = new Position(target->x,target->y);
        //p3 = new Point(rand()%xLimit,rand()%yLimit);
        printf("P2(%f,%f),P1(%f,%f),P2(%f,%f),P3(%f,%f)\n",p0->x,p0->y,p1->x,p1->y,p2->x,p2->y,p3->x,p3->y);
    };
}
