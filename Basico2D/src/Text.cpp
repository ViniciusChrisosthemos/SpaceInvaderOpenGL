#include "Text.h"
#include <Position.h>

Text::Text(char _text[1024], int _length, int _scale, Position* _pos)
{
    for(int i=0; i<_length; i++)
    {
        text[i] = _text[i];
    }
    length = _length;
    scale = _scale;
    pos = _pos;
}

Text::~Text()
{
    //dtor
}
