#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H
#include "Point.h"
#include "Object.h"
#include <ObjectModel.h>

class EnemyShip : public Object
{
    public:
        Point *p0;
        Point *p1;
        Point *p2;
        Point *p3;
        Point *target;
        int xLimit,yLimit;
        float t;

        EnemyShip(Point *_target, ObjectModel* _model, int _xLimit, int _yLimit);
        virtual ~EnemyShip();
        void MoveEShip();

    protected:

    private:
};

#endif // ENEMYSHIP_H
