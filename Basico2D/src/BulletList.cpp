#include "BulletList.h"
#include <stddef.h>

BulletList::BulletList()
{
    //ctor
}

BulletList::~BulletList()
{
    //dtor
}

void BulletList::AddBullet(Bullet* newBullet)
{
    AddNode(root,newBullet);
    sizeList++;
}

Bullet* BulletList::GetBullet(int index)
{
    if(index >= sizeList) return NULL;

    Node* temp = root;
    while(index > 0) temp = root->next;

    return temp->bullet;
}

void BulletList::AddNode(Node* root, Bullet* newBullet)
{
    Node *newNode;
    newNode->bullet = newBullet;
    newNode->next = NULL;

    if(root == NULL)
    {
        root = newNode;
    }
    else
    {
        Node *temp = root;

        while(root->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
