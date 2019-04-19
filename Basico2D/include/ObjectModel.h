#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H
#include <vector>

class ObjectModel
{
    public:
        float sizePixel;
        std::vector< std::vector<int> > model;

        ObjectModel();
        virtual ~ObjectModel();

    protected:

};

#endif // OBJECTMODEL_H
