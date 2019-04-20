// **********************************************************************
// PUCRS/Escola Polit�cnica
// COMPUTA��O GR�FICA
//
// Programa basico para criar aplicacoes 2D em OpenGL
//
// Marcio Sarroglia Pinho
// pinho@pucrs.br
// **********************************************************************


// Para uso no Xcode:
// Abra o menu Product -> Scheme -> Edit Scheme -> Use custom working directory
// Selecione a pasta onde voce descompactou o ZIP que continha este arquivo.
//

#include <iostream>
#include <cmath>
#include <ctime>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <EnemyShip.h>
#include <PlayerShip.h>
#include <ObjectModel.h>
#include <Position.h>
#include <ColorRGB.h>

using namespace std;

#ifdef WIN32
#include <windows.h>
#include <glut.h>
static DWORD last_idle_time;
#else
#include <sys/time.h>
static struct timeval last_idle_time;
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <glut.h>
#endif

enum State{INGAME,GAMEOVER};

// Vari�veis Globais
State state;
int WIDTHSCREEN;
int HEIGHTSCREEN;
int ENEMYAMOUNT;
int ENEMYMODELS = 5;
vector<ObjectModel*> modelsList;
vector<EnemyShip*> enemysList;
vector<ColorRGB*> colorsList;
ObjectModel* playerModel;
ObjectModel* bulletModel;
PlayerShip* player;


// M�todos OpenGL
void animate();
void init(void);
void reshape( int w, int h );
void display( void );
void keyboard ( unsigned char key, int x, int y );
void arrow_keys ( int a_keys, int x, int y );

// M�todos do Jogo
void DrawObject(Position* pos, ObjectModel* _model, float _angle);
void DrawSquare(int _ix, int _iy, int _fx, int _fy);
void LoadColorsList();
void LoadModelsObjects();
void InitializeVariables();
void Process();
void Draw();
bool IsColliding(Object* obj1, Object* obj2);
void GameOver();
void DrawGUI();

// **********************************************************************
//  void animate ( unsigned char key, int x, int y )
// **********************************************************************
void animate()
{
    static float dt;
    static float AccumTime=0;

#ifdef _WIN32
    DWORD time_now;
    time_now = GetTickCount();
    dt = (float) (time_now - last_idle_time) / 1000.0;
#else
    // Figure out time elapsed since last call to idle function
    struct timeval time_now;
    gettimeofday(&time_now, NULL);
    dt = (float)(time_now.tv_sec  - last_idle_time.tv_sec) +
    1.0e-6*(time_now.tv_usec - last_idle_time.tv_usec);
#endif
    AccumTime +=dt;
    if (AccumTime >=3) // imprime o FPS a cada 3 segundos
    {
        cout << 1.0/dt << " FPS"<< endl;
        AccumTime = 0;
    }
    // cout << "AccumTime: " << AccumTime << endl;
    // Anima cubos
    //AngY++;
    // Salva o tempo para o pr�ximo ciclo de rendering
    last_idle_time = time_now;

    //if  (GetAsyncKeyState(32) & 0x8000) != 0)
    //  cout << "Espaco Pressionado" << endl;

    // Redesenha
    glutPostRedisplay();
}
// **********************************************************************
//  void init(void)
//  Inicializa os par�metros globais de OpenGL
// **********************************************************************
void init(void)
{
	// Define a cor do fundo da tela (PRETO)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

// **********************************************************************
//  void reshape( int w, int h )
//  trata o redimensionamento da janela OpenGL
// **********************************************************************
void reshape( int w, int h )
{
    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define a area a ser ocupada pela �rea OpenGL dentro da Janela
    glViewport(0, 0, w, h);

    // Define os limites l�gicos da �rea OpenGL dentro da Janela
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0,10,0,10,0,1);
}

// **********************************************************************
//  void display( void )
// **********************************************************************
void display( void )
{

	// Limpa a tela coma cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);

    // Define os limites l�gicos da �rea OpenGL dentro da Janela
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glOrtho(-WIDTHSCREEN,WIDTHSCREEN,-HEIGHTSCREEN,HEIGHTSCREEN,0,1);
    glOrtho(0,WIDTHSCREEN,0,HEIGHTSCREEN,0,1);
	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// Coloque aqui as chamadas das rotinas que desenha os objetos
	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    switch(state)
    {
        case INGAME:
            Process();
            Draw();
            break;
        case GAMEOVER:
            GameOver();
            break;
    }
	glutSwapBuffers();
}

// **********************************************************************
//  void keyboard ( unsigned char key, int x, int y )
// **********************************************************************
void keyboard ( unsigned char key, int x, int y )
{

	switch ( key )
	{
		case 27:        // Termina o programa qdo
			exit ( 0 );   // a tecla ESC for pressionada
			break;

        case 'w':
            player->MoveShip(0,WIDTHSCREEN,0,HEIGHTSCREEN);
            break;

        case 'a':
            player->Rotate(false);
            break;

        case 'd':
            player->Rotate(true);
            break;

        case ' ':
            player->Shoot(WIDTHSCREEN,HEIGHTSCREEN);
            break;

		default:
			break;
	}
}

// **********************************************************************
//  void arrow_keys ( int a_keys, int x, int y )
// **********************************************************************
void arrow_keys ( int a_keys, int x, int y )
{
	switch ( a_keys )
	{
		case GLUT_KEY_UP:       // Se pressionar UP
			glutFullScreen ( ); // Vai para Full Screen
			break;
	    case GLUT_KEY_DOWN:     // Se pressionar UP
								// Reposiciona a janela
            glutPositionWindow (50,50);
			glutReshapeWindow ( 700, 500 );
			break;
		default:
			break;
	}
}

void Draw()
{
    int i;
    DrawObject(player->coordinate, player->model,player->angle);

    EnemyShip* temp;
    for(i=0; i<enemysList.size(); i++)
    {
        temp = enemysList.at(i);
        DrawObject(temp->coordinate, temp->model, temp->angle);
    }
    Bullet* bullet;
    for(i=0; i<player->bullets.size(); i++)
    {
        bullet = player->bullets.at(i);
        DrawObject(bullet->coordinate, bullet->model, bullet->angle);
    }

    DrawGUI();
}

bool IsColliding(Object* obj1, Object* obj2)
{
    if((obj2->coordinate->x + obj2->width) < obj1->coordinate->x) return false;
    if((obj2->coordinate->x - obj2->width) > obj1->coordinate->x) return false;
    if((obj2->coordinate->y + obj2->height) < obj1->coordinate->y) return false;
    if((obj2->coordinate->y - obj2->height) > obj1->coordinate->y) return false;
    return true;
}

void InitializeVariables()
{
    //Inicia variaveis do ambiente
    state = INGAME;
    WIDTHSCREEN = 800;
    HEIGHTSCREEN = 600;
    ENEMYAMOUNT = 5;

    //Inicia a nave do jogador
    player = new PlayerShip(new Position(WIDTHSCREEN/2,HEIGHTSCREEN/2),playerModel, bulletModel);

    srand(rand()%1000);

    for(int i=0; i<ENEMYAMOUNT; i++)
    {
        enemysList.push_back(new EnemyShip(player->coordinate, modelsList.at(rand()%modelsList.size()), WIDTHSCREEN, HEIGHTSCREEN));
    }
}

void LoadColorsList()
{
    ifstream file;
    int temp;
    float r,g,b;

    file.open("colors.txt");

    if(!file)
    {
        printf("Erro ao ler o arquivo!");
        return;
    }

    file >> temp;

    while(file >> temp)
    {
        file >> r;
        file >> g;
        file >> b;
        colorsList.push_back(new ColorRGB(r/255,g/255,b/255));
    }

    file.close();
}

void GameOver()
{
    //printf("GAME OVER!!!\n");
    glPushMatrix();
    {
        glTranslated(400,300,0);
        glBegin(GL_LINES);
        {
            glVertex2d(0,0);
            glVertex2d(40,0);
            glVertex2d(40,25);
            glVertex2d(25,25);
            glVertex2d(25,20);
            glVertex2d(35,20);
            glVertex2d(35,10);
            glVertex2d(10,10);
            glVertex2d(10,40);
            glVertex2d(40,40);
            glVertex2d(40,50);
            glVertex2d(0,50);
            glVertex2d(0,0);
        }
        glEnd();
    }
    glPopMatrix();

    //exit(0);
}

void LoadModel(ObjectModel* _modelObj, char fileName[])
{
    int x,y,line,column;
    ifstream file;

    file.open(fileName);
    if(!file)
    {
        fprintf(stderr,"%s nao encontrado!\n", fileName);
        return;
    }

    file >> y;
    file >> x;

    _modelObj = new ObjectModel();
    file >> _modelObj->sizePixel;

    for(line=0; line < y; line++)
    {
        vector<int> temp(x);
        for(column=0; column < x; column++)
        {
            file >> temp.at(column);
        }
        _modelObj->model.push_back(temp);
    }

    fprintf(stderr,"%s carregado com sucesso!\n", fileName);
    file.close();
}

//https://www.quora.com/How-do-I-open-files-using-an-array-in-C
void LoadModelsObjects()
{
    ifstream file;
    char fileName[1024];
    int x,y,line,column;
    int enemyshipModels = ENEMYMODELS;
    ObjectModel* modelObj;

    while(enemyshipModels)
    {
        sprintf(fileName,"EShip%d.txt",enemyshipModels);
        file.open(fileName);

        if(!file)
        {
            fprintf(stderr,"%s nao encontrado!\n", fileName);
            return;
        }

        file >> y;
        file >> x;

        modelObj = new ObjectModel();
        file >> modelObj->sizePixel;
        for(line=0; line < y; line++)
        {
            vector<int> temp(x);
            for(column=0; column < x; column++)
            {
                file >> temp.at(column);
            }
            modelObj->model.push_back(temp);
        }

        modelsList.push_back(modelObj);

        fprintf(stderr,"%s carregado com sucesso!\n", fileName);
        enemyshipModels--;
        file.close();
    }

    file.open("PShip.txt");
    if(!file)
    {
        printf("Erro ao carregar o model do jogador!\n");
        return;
    }

    file >> x;
    file >> y;
    playerModel = new ObjectModel();
    file >> playerModel->sizePixel;
    for(line=0; line<x; line++)
    {
        vector<int> temp(y);
        for(column=0; column<y; column++)
        {
            file >> temp.at(column);
        }
        playerModel->model.push_back(temp);
    }
    file.close();
    printf("PlayerShip carregado com sucesso!\n");

    file.open("Bullet.txt");

    if(!file)
    {
        printf("Erro ao carregar o modelo do disparo!\n");
        return;
    }

    file >> y;
    file >> x;
    bulletModel = new ObjectModel();
    file >> bulletModel->sizePixel;
    for(line=0; line<y; line++)
    {
        vector<int> temp(x);
        for(column=0; column<x; column++)
        {
            file >> temp.at(column);
        }
        bulletModel->model.push_back(temp);
    }

    file.close();

    printf("Bullet carregado com sucesso!\n");
/*
    for(int i=0; i<playerModel->model.size(); i++)
    {
        for(int j=0; j<playerModel->model.at(i).size(); j++)
        {
            printf("%d ",playerModel->model.at(i).at(j));
        }
        printf("\n");
    }
*/

}

void DrawGUI()
{
    glColor3f(1.0,0.0,0.0);

    int x=20, y=550, i, bulletCount;
    for(i=0; i<player->health; i++)
    {
        DrawSquare(x,y,x+10,y+30);
        x+=15;
    }

    x = 20;
    y = 500;
    bulletCount = 10 - player->bullets.size();

    glColor3f(1.0,1.0,1.0);

    for(i=0; i<bulletCount; i++)
    {
        DrawSquare(x,y,x+10,y+10);
        y-=15;
    }
}

void DrawSquare(int _ix, int _iy, int _fx, int _fy)
{
    glBegin(GL_QUADS);
    {
        glVertex2d(_ix,_iy);
        glVertex2d(_fx,_iy);
        glVertex2d(_fx,_fy);
        glVertex2d(_ix,_fy);
    }
    glEnd();
}

void DrawObject(Position* _pos, ObjectModel* _model, float _angle)
{
    int nextX, nextY;
    int sizeCell = _model->sizePixel;
    int y = _model->model.size();
    int x = _model->model.at(0).size();
    int currentX = -(x/2) * sizeCell;
    int currentY = -(y/2) * sizeCell;
    ColorRGB* color;
    vector<int> temp;

    glPushMatrix();
    {
        glTranslatef(_pos->x,_pos->y,0);
        glRotated(_angle,0,0,1);

        for(int line=y-1; line>=0; line--)
        {
            temp = _model->model.at(line);
            nextY = currentY + sizeCell;

            for(int column=0; column<x; column++)
            {
                nextX = currentX + sizeCell;
                color = colorsList.at(temp.at(column));
                glColor3f(color->r,color->g,color->b);
                DrawSquare(currentX,currentY,nextX,nextY);
                currentX = nextX;
            }
            currentY = nextY;
            currentX = -(x/2) * sizeCell;
            nextX = 0;
        }
    }
    glPopMatrix();
}

void ClearObjects()
{
    int i;
    for(i=0; i<enemysList.size(); i++)
    {
        if(!enemysList.at(i)->inGame)
        {
            enemysList.erase(enemysList.begin()+i);
        }
    }

    for(i=0; i<player->bullets.size(); i++)
    {

        if(!player->bullets.at(i)->inGame)
        {
            player->bullets.erase(player->bullets.begin()+i);
        }
    }
}

void Process()
{
    if(!player->inGame)
    {
        state = GAMEOVER;
        return;
    }

    ClearObjects();

    EnemyShip* enemy;
    for(int i=0; i<enemysList.size(); i++)
    {
        enemy = enemysList.at(i);
        enemy->MoveEShip();

        if(IsColliding(player,enemy))
        {
            player->TakeDamage();
            enemy->inGame = false;
        }
    }


    Bullet* bullet;
    for(int i=0; i<player->bullets.size(); i++)
    {
        bullet = player->bullets.at(i);
        bullet->MoveBullet();

        for(int j=0; j<enemysList.size(); j++)
        {
            enemy = enemysList.at(j);
            if(IsColliding(bullet,enemy))
            {
                enemy->inGame = false;
                bullet->inGame = false;
                break;
            }
        }
    }



}


// **********************************************************************
//  void main ( int argc, char** argv )
// **********************************************************************
int  main ( int argc, char** argv )
{

    LoadColorsList();
    printf("Carrega cores\n");
    LoadModelsObjects();
    printf("Carrega modelos\n");
    InitializeVariables();
    printf("Carrega variaveis\n");

    glutInit            ( &argc, argv );
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
    glutInitWindowPosition (0,0);

    // Define o tamanho inicial da janela grafica do programa
    glutInitWindowSize  ( 650, 500);

    // Cria a janela na tela, definindo o nome da
    // que aparecera na barra de t�tulo da janela.
    glutCreateWindow    ( "Primeiro Programa em OpenGL" );

    // executa algumas inicializa��es
    init ();

    // Define que o tratador de evento para
    // o redesenho da tela. A funcao "display"
    // ser� chamada automaticamente quando
    // for necess�rio redesenhar a janela
    glutDisplayFunc ( display );
    glutIdleFunc(animate);

    // Define que o tratador de evento para
    // o redimensionamento da janela. A funcao "reshape"
    // ser� chamada automaticamente quando
    // o usu�rio alterar o tamanho da janela
    glutReshapeFunc ( reshape );

    // Define que o tratador de evento para
    // as teclas. A funcao "keyboard"
    // ser� chamada automaticamente sempre
    // o usu�rio pressionar uma tecla comum
    glutKeyboardFunc ( keyboard );

    // Define que o tratador de evento para
    // as teclas especiais(F1, F2,... ALT-A,
    // ALT-B, Teclas de Seta, ...).
    // A funcao "arrow_keys" ser� chamada
    // automaticamente sempre o usu�rio
    // pressionar uma tecla especial
    glutSpecialFunc ( arrow_keys );

    // inicia o tratamento dos eventos
    glutMainLoop ( );

    return 0;
}
