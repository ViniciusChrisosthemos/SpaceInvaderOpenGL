#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H
#include <Object.h>
#include <Bullet.h>
#include <vector>
#include <BulletList.h>
#include <ObjectModel.h>

class PlayerShip : public Object
{
    public:
        int forceRotate;
        std::vector<Bullet*> bullets;
        int currentBullets;

        PlayerShip(Point* _initialPosition, ObjectModel* _model);
        virtual ~PlayerShip();
        void MoveShip(int minX,int maxX,int minY,int maxY);
        void Rotate(bool toRight);
        void Shoot(int widthScreen, int heightScreen);
        void MoveBullets();

    protected:

    private:
};

#endif // PLAYERSHIP_H
