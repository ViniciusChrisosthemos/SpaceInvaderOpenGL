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
EnemyShip::EnemyShip(Position *_target, ObjectModel* _model, int _xLimit, int _yLimit, ObjectModel* _bulletModel, std::vector<Bullet*> *_bullets) :
    Object(new Position(0,0), 0, 0, _model)
{
        target = _target;
        xLimit = _xLimit;
        yLimit = _yLimit;
        bulletModel = _bulletModel;
        bullets = _bullets;

        srand(rand()%1000);
        fireRate = rand()%3 + 2;

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

        speed = rand()%3 + 3;
    }
// **********************************************************************
// ~EnemyShip()
// Desconstrutor da Classe EnemyShip
// **********************************************************************
EnemyShip::~EnemyShip()
{
    delete p0;
    delete p1;
    delete p2;
    delete p3;
    delete target;
    delete bullets;
    delete bulletModel;
}
// **********************************************************************
// void MoveEShip()
// Move a nave inimiga, alterando o valor de t na equação da Bézire,
// se t == 1, calcula o segundo ponto e gera o terceiro com base na posição do target
// **********************************************************************
void EnemyShip::MoveEShip(float _deltaTime)
{
    float aux = 1-t;
    coordinate->x = pow(aux,3)*p0->x + 3*t*pow(aux,2)*p1->x + 3*t*t*aux*p2->x + t*t*t*p3->x;
    coordinate->y = pow(aux,3)*p0->y + 3*t*pow(aux,2)*p1->y + 3*t*t*aux*p2->y + t*t*t*p3->y;
    t += 1.0 / (speed/_deltaTime);
    LookToTarget();

    if(t > 1)
    {
        t = 0;
        p0 = p3;

        float nextX = p3->x*2.0 - p2->x;
        float nextY = p3->y*2.0 - p2->y;
        float x,y,m1;

        //Limita a continuação de derivada a não passar da tela
        if(nextX >= xLimit)
        {
            x = xLimit;
            m1 =  (nextY - p3->y)/ (nextX - p3->x);
            y = p3->y + (xLimit - p3->x) * m1;

        }else if(nextX <= 0)
        {
            x = 0;
            m1 = (nextY - p3->y) / (nextX - p3->x);
            y = p3->y + (0 - p3->x) * m1;
        }else if(nextY >= yLimit)
        {
            m1 = (nextX - p3->x) / (nextY - p3->y);
            x = p3->x + (yLimit - p3->y) * m1;
            y = yLimit;
        }else if(nextY <= 0)
        {
            m1 = (nextX - p3->x) / (nextY - p3->y);
            x = p3->x + (0 - p3->y) * m1;
            y = 0;
        }else
        {
            x = nextX;
            y = nextY;
        }

        p1 = new Position(x,y);
        p2 = new Position(rand()%xLimit,rand()%yLimit);
        if(rand()%2)
        {
            p3 = new Position(target->x,target->y);
        }else
        {
            p2 = new Position(rand()%xLimit,rand()%yLimit);
        }
    };
}
// **********************************************************************
// void LookToTarget()
// Define o angulo da nave em relação ao seu target(nave do jogador)
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
// **********************************************************************
// void Shoot()
// Dispara uma bala no cenario
// **********************************************************************
void EnemyShip::Shoot()
{
    Bullet* bullet = new Bullet(new Position(coordinate->x,coordinate->y),angle,xLimit,yLimit, bulletModel);
    bullets->push_back(bullet);
}
// **********************************************************************
// bool CanShoot()
// Verifica se a nave pode atirar, calculo em relação ao tempo do ultimo disparo
// **********************************************************************
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
