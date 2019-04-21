#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H
#include <Position.h>
#include <Object.h>
#include <ObjectModel.h>
#include <time.h>
#include <Bullet.h>
#include <vector>

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
        time_t nextShoot;
        time_t currentTime;
        char fireRate;
        std::vector<Bullet*> bullets;
        ObjectModel* bulletModel;

        EnemyShip(Position *_target, ObjectModel* _model, int _xLimit, int _yLimit, ObjectModel* _bulletModel);
        virtual ~EnemyShip();

        void MoveEShip();
        void LookToTarget();
        void Shoot();
        bool CanShoot();

    protected:

    private:
};

#endif // ENEMYSHIP_H
