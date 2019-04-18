#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H
#include <vector>

class ObjectModel
{
    public:
        int x;
        int y;
        std::vector< std::vector<int> > model;

        ObjectModel(int _x, int _y);
        virtual ~ObjectModel();

    protected:

};

#endif // OBJECTMODEL_H
