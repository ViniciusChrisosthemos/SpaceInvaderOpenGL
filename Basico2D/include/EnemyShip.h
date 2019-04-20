#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H
#include "Position.h"
#include "Object.h"
#include <ObjectModel.h>

class EnemyShip : public Object
{
    public:
        Position *p0;
        Position *p1;
        Position *p2;
        Position *p3;
        Position *target;
        int xLimit,yLimit;
        float t;

        EnemyShip(Position *_target, ObjectModel* _model, int _xLimit, int _yLimit);
        virtual ~EnemyShip();
        void MoveEShip();

    protected:

    private:
};

#endif // ENEMYSHIP_H
