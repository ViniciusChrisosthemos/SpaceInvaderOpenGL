#include "TextManager.h"
#include <Text.h>
// **********************************************************************
// TextManager::TextManager()
// Construtor
// **********************************************************************
TextManager::TextManager()
{
    title =         new Text("space invaders", 14, 10, new Position(45, 550));
    start =         new Text("press /s/ to start", 18, 4, new Position(215, 300));
    name =          new Text("vinicius chrisosthemos teixeira", 31, 2, new Position(170, 20));
    scoreInGame =   new Text("score", 5, 2, new Position(600, 580));
    gameOver =      new Text("game over", 9, 15, new Position(80, 550));
    win =           new Text("you won", 7, 7, new Position(270, 400));
    lose =          new Text("you lost", 8, 7, new Position(270, 400));
    score =         new Text("score", 5, 4, new Position(100, 290));
    bestScore =     new Text("best score", 10, 4, new Position(100, 250));
    restart =       new Text("press /r/ to restart", 20, 4, new Position(200, 100));
    quit =          new Text("press /esc/ to quit", 19, 4, new Position(190, 50));
}
// **********************************************************************
// TextManager::~TextManager()
// Desconstrutor
// **********************************************************************
TextManager::~TextManager()
{
    //dtor
}
