#ifndef BULLET_H
#define BULLET_H
#include "Object.h"
#include <ObjectModel.h>

class Bullet : public Object
{
    public:
        float limitX;
        float limitY;
        bool inGame;
        float alfaX;
        float alfaY;

        Bullet(Position* _coord, float _angle, float _limitX, float _limitY, ObjectModel* _model);
        virtual ~Bullet();
        void MoveBullet(float _deltaTime);

    protected:

    private:
};

#endif // BULLET_H
