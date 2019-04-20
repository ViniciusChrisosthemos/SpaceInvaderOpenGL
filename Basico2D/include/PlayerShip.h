#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H
#include <Object.h>
#include <Bullet.h>
#include <vector>
#include <ObjectModel.h>

class PlayerShip : public Object
{
    public:
        std::vector<Bullet*> bullets;
        ObjectModel* bulletModel;
        int health;

        PlayerShip(Position* _initialPosition, ObjectModel* _model, ObjectModel* _bulletModel);
        virtual ~PlayerShip();

        void MoveShip(int minX,int maxX,int minY,int maxY);
        void Rotate(bool toRight);
        void Shoot(int widthScreen, int heightScreen);
        void TakeDamage();

    protected:

    private:
};

#endif // PLAYERSHIP_H
