#include "ObjectModel.h"
#include <stdio.h>

ObjectModel::ObjectModel()
{
}

ObjectModel::~ObjectModel()
{
    //dtor
}

void ObjectModel::printModel()
{
    for(int xcount=0; xcount<x; xcount++)
    {
        for(int ycount=0; ycount<y; ycount++)
        {
            printf("%d ", model[xcount][ycount]);
        }
        printf("\n");
    }
}
