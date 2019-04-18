#include "EnemyShip.h"
#include <stdlib.h>
#include <time.h>
#include <Point.h>
#include <math.h>
#include <stdio.h>
#include <ObjectModel.h>

EnemyShip::EnemyShip(Point *_target, ObjectModel* _model) :
    Object(new Point(0,0), 0, 0, _model)
{
        srand(time(NULL));

        this->target = _target;
        this->coordinate = new Point(0,600);
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
        /*
        coordinate->x += pow(aux,3)*100 + 3*t*pow(aux,2)*100 + 3*t*t*aux*400 + t*t*t*500;
        coordinate->y += pow(aux,3)*100 + 3*t*pow(aux,2)*350 + 3*t*t*aux*450 + t*t*t*200;
        */

    this->coordinate->x = pow(aux,3)*p0->x + 3*t*pow(aux,2)*p1->x + 3*t*t*aux*p2->x + t*t*t*p3->x;
    this->coordinate->y = pow(aux,3)*p0->y + 3*t*pow(aux,2)*p1->y + 3*t*t*aux*p2->y + t*t*t*p3->y;

        //printf("%f,%f,%f\n",coordinate->x,coordinate->y,t);

    t += 0.004;

        if(t > 1)
        {
            t = 0;
            /*
            p1 = new Point(p2->x,p2->y);
            p2 = new Point(abs(p3->x - p2->x + p3->x), abs(p3->y - p2->y + p3->y));
            p3 = new Point((rand()%100 - 200),(rand()%100 - 200));
*/          p0 = p3;
            p1 = new Point(p3->x*2.0 - p2->x,p3->y*2.0 - p2->y);
            p2 = new Point(rand()%800,rand()%600);
            p3 = new Point(target->x,target->y);
            printf("P2(%f,%f),P1(%f,%f),P2(%f,%f),P3(%f,%f)\n",p0->x,p0->y,p1->x,p1->y,p2->x,p2->y,p3->x,p3->y);
        };
    }
