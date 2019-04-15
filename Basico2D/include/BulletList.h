#ifndef BULLETLIST_H
#define BULLETLIST_H
#include <Bullet.h>

class BulletList
{
    private:
        struct Node
        {
            Bullet *bullet;
            Node *next;
        };
        void AddNode(Node *root, Bullet *newBullet);

    public:
        Node *root;
        int sizeList;

        BulletList();
        virtual ~BulletList();
        void AddBullet(Bullet* newBullet);
        Bullet* GetBullet(int index);

    protected:

};





#endif // BULLETLIST_H
