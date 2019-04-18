#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H


class ObjectModel
{
    public:
        int x;
        int y;
        int* model[];

        ObjectModel();
        virtual ~ObjectModel();
        void printModel();

    protected:

    private:
};

#endif // OBJECTMODEL_H
