#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H
#include <Text.h>

class TextManager
{
    public:
        Text* title;
        Text* start;
        Text* name;
        Text* scoreInGame;
        Text* gameOver;
        Text* win;
        Text* lose;
        Text* score;
        Text* bestScore;
        Text* restart;
        Text* quit;

        TextManager();
        virtual ~TextManager();

    protected:

    private:
};

#endif // TEXTMANAGER_H
