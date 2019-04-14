#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <PlayerShip.h>
#include <EnemyShip.h>

class GameManager
{
    public:
        //enum State{MENU,INITING,INGAME,GAMEOVER};

        PlayerShip playerShip;
        EnemyShip enemys[];
        //State state;
        int WIDTHSCREEN;
        int HEIGHTSCREEN;

        GameManager();
        virtual ~GameManager();
        void Init();
        void Process();
        void Draw();
        void LoadShipModel();


    protected:

    private:
};

#endif // GAMEMANAGER_H
