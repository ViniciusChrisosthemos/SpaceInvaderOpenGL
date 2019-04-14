#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H
#include "Point.h"
#include "Object.h"

class EnemyShip : public Object
{
    public:
        Point *p0;
        Point *p1;
        Point *p2;
        Point *p3;
        Point *target;
        float t;

        EnemyShip(Point *_target);
        virtual ~EnemyShip();
        void MoveEShip();

    protected:

    private:
};

#endif // ENEMYSHIP_H
