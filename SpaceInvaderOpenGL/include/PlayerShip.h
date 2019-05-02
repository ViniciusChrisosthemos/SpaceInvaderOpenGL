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
        int widthScreen;
        int heightScreen;

        PlayerShip(Position* _initialPosition, ObjectModel* _model, ObjectModel* _bulletModel, int _widthScreen, int _heightScreen);
        virtual ~PlayerShip();

        void MoveShip(float _deltaTime);
        void Rotate(bool _toRight, float _deltaTime);
        void Shoot();
        void TakeDamage();

    protected:

    private:
};

#endif // PLAYERSHIP_H
