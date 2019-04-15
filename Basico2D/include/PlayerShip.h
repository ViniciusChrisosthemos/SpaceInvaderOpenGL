#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H
#include <Object.h>
#include <Bullet.h>
#include <vector>
#include <BulletList.h>

class PlayerShip : public Object
{
    public:
        int forceRotate;
        //std::vector<Bullet*> bullets;
        BulletList bullets;
        int currentBullets;

        PlayerShip();
        virtual ~PlayerShip();
        void MoveShip(int minX,int maxX,int minY,int maxY);
        void Rotate(bool toLeft);
        bool CanShoot();
        void Shoot(int widthScreen, int heightScreen);
        void MoveBullets();

    protected:

    private:
};

#endif // PLAYERSHIP_H
