#ifndef TEXT_H
#define TEXT_H
#include <Position.h>

class Text
{
    public:

        char text[1024];
        int length;
        int scale;
        Position* pos;

        Text(char _text[], int _length, int _scale, Position* _pos);
        virtual ~Text();

    protected:

    private:
};

#endif // TEXT_H
