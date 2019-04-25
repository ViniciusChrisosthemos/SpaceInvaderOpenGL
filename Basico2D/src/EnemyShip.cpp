#include <EnemyShip.h>
#include <stdlib.h>
#include <time.h>
#include <Position.h>
#include <math.h>
#include <stdio.h>
#include <ObjectModel.h>

// **********************************************************************
// EnemyShip(Position *_target, ObjectModel* _model, int _xLimit, int _yLimit): Object(new Position(0,0), 0, 0.004, _model)
// Construtor da Classe EnemyShip
// **********************************************************************
EnemyShip::EnemyShip(Position *_target, ObjectModel* _model, int _xLimit, int _yLimit, ObjectModel* _bulletModel) :
    Object(new Position(0,0), 0, 0, _model)
{
        target = _target;
        xLimit = _xLimit;
        yLimit = _yLimit;
        bulletModel = _bulletModel;

        srand(rand()%1000);
        fireRate = rand()%4 + 1;

        time(NULL);
        time(&currentTime);
        nextShoot = currentTime + fireRate;

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
        p1 = new Position(rand()%xLimit,rand()%yLimit);
        p2 = new Position(rand()%xLimit,rand()%yLimit);
        p3 = new Position(target->x,target->y);
        t = 0;

        speed = 3;
    }
// **********************************************************************
// ~EnemyShip()
// Desconstrutor da Classe EnemyShip
// **********************************************************************
EnemyShip::~EnemyShip()
{

}
// **********************************************************************
// void MoveEShip()
// Move a nave inimiga, alterando o valor de t na equa��o da B�zire,
// se t == 1, calcula o segundo ponto e gera o terceiro com base na posi��o do target
// **********************************************************************
void EnemyShip::MoveEShip(float _fps)
{
    float aux = 1-t;
    coordinate->x = pow(aux,3)*p0->x + 3*t*pow(aux,2)*p1->x + 3*t*t*aux*p2->x + t*t*t*p3->x;
    coordinate->y = pow(aux,3)*p0->y + 3*t*pow(aux,2)*p1->y + 3*t*t*aux*p2->y + t*t*t*p3->y;
    t += 0.0016/speed;
    LookToTarget();

    if(t > 1)
    {
        t = 0;
        p0 = p3;
        p1 = new Position(p3->x*2.0 - p2->x,p3->y*2.0 - p2->y);
        p2 = new Position(rand()%xLimit,rand()%yLimit);
        p3 = new Position(target->x,target->y);
    };
}
// **********************************************************************
// void LookToTarget()
// Define o angulo da nave em rela��o ao seu target(nave do jogador)
// **********************************************************************
void EnemyShip::LookToTarget()
{
    Position v1 = Position(target->x - coordinate->x, target->y - coordinate->y);
    Position v2 = Position(800 - coordinate->x, 0);

    float scaleProduct = v1.x*v2.x + v1.y*v2.y;
    float module = sqrt(v1.x*v1.x + v1.y*v1.y)*sqrt(v2.x*v2.x + v2.y*v2.y);
    float newAngle = acos(scaleProduct/module) * (180/M_PI);

    angle = (target->y < coordinate->y) ? (-newAngle - 0):(newAngle - 0);
}

void EnemyShip::Shoot()
{
    Bullet* bullet = new Bullet(new Position(coordinate->x,coordinate->y),angle,xLimit,yLimit, bulletModel);
    bullets.push_back(bullet);
}

bool EnemyShip::CanShoot()
{
    time(&currentTime);

    if(currentTime >= nextShoot)
    {
        nextShoot = currentTime + fireRate;
        return true;
    }
    return false;
}
