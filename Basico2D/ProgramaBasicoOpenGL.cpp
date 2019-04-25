// **********************************************************************
// PUCRS/Escola PolitŽcnica
// COMPUTA‚ÌO GRçFICA
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

// Variáveis Globais
State state;
float FPS;
bool debug;
int displayCount;
int WIDTHSCREEN;
int HEIGHTSCREEN;
int ENEMYAMOUNT;
int ENEMYMODELS;
int BULLETMODELS;
vector<ObjectModel*> enemysModels;
vector<ObjectModel*> bulletModels;
vector<EnemyShip*> enemysList;
vector<ColorRGB*> colorsList;
ObjectModel* playerModel;
ObjectModel* heartModel;
PlayerShip* player;


// Métodos OpenGL
void animate();
void init(void);
void reshape( int w, int h );
void display( void );
void keyboard ( unsigned char key, int x, int y );
void arrow_keys ( int a_keys, int x, int y );

// Métodos do Jogo
void DrawObject(Position* pos, ObjectModel* _model, float _angle, float _sizeCell);
void DrawRectangle(int _ix, int _iy, int _fx, int _fy);
void LoadColorsList();
void LoadModelsObjects();
void InitializeVariables();
void Process();
void Draw();
bool IsColliding(Object* obj1, Object* obj2);
void GameOver();
void DrawGUI();
void VerifyUserActions();
void Debug();
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
        FPS = 1.0/dt;
        cout << dt << " FPS"<< endl;
        AccumTime = 0;
    }
    // cout << "AccumTime: " << AccumTime << endl;
    // Anima cubos
    //AngY++;
    // Salva o tempo para o pr—ximo ciclo de rendering
    last_idle_time = time_now;

    //if  (GetAsyncKeyState(32) & 0x8000) != 0)
    //  cout << "Espaco Pressionado" << endl;

    // Redesenha
    glutPostRedisplay();
}
// **********************************************************************
//  void init(void)
//  Inicializa os parâmetros globais de OpenGL
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
    // Define a area a ser ocupada pela área OpenGL dentro da Janela
    glViewport(0, 0, w, h);

    // Define os limites lógicos da área OpenGL dentro da Janela
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

    // Define os limites lógicos da área OpenGL dentro da Janela
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
        case ' ':
            player->Shoot(WIDTHSCREEN,HEIGHTSCREEN);
            break;
        case 'p':
            debug = !debug;
            break;
            /*
        case 'w':
            player->MoveShip(0,WIDTHSCREEN,0,HEIGHTSCREEN);
            break;
        case 'a':
            player->Rotate(false);
            break;
        case 'd':
            player->Rotate(true);
            break;
        */
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
// **********************************************************************
//  void Draw ()
// Desenha todos os objetos do jogo na tela
// **********************************************************************
void Draw()
{
    int i,j;
    DrawObject(player->coordinate, player->model,player->angle-90, player->model->sizePixel);

    EnemyShip* enemy;
    Bullet* bullet;
    for(i=0; i<enemysList.size(); i++)
    {
        enemy = enemysList.at(i);
        DrawObject(enemy->coordinate, enemy->model, enemy->angle, enemy->model->sizePixel);
        for(j=0; j<enemy->bullets.size(); j++)
        {
            bullet = enemy->bullets.at(j);
            DrawObject(bullet->coordinate, bullet->model, bullet->angle, bullet->model->sizePixel);
        }
    }

    for(i=0; i<player->bullets.size(); i++)
    {
        bullet = player->bullets.at(i);
        DrawObject(bullet->coordinate, bullet->model, bullet->angle, bullet->model->sizePixel);
    }

    DrawGUI();
    if(debug) Debug();
}
// **********************************************************************
//  void VerifyUserActions()
// Verifica quais ações o jogado quer realizar com a nave
// **********************************************************************
void VerifyUserActions()
{
    if(GetKeyState('W') & 0x8000)
    {
        player->MoveShip(0,WIDTHSCREEN,0,HEIGHTSCREEN);
    }

    if(GetKeyState('A') & 0x8000)
    {
        player->Rotate(false);
    }

    if(GetKeyState('D') & 0x8000)
    {
        player->Rotate(true);
    }
}

// **********************************************************************
//  bool IsColliding(Object* obj1, Object* obj2)
// Verifica a colisão entre dois objetos
// **********************************************************************
bool IsColliding(Object* obj1, Object* obj2)
{
    if((obj2->coordinate->x + obj2->width) < obj1->coordinate->x) return false;
    if((obj2->coordinate->x - obj2->width) > obj1->coordinate->x) return false;
    if((obj2->coordinate->y + obj2->height) < obj1->coordinate->y) return false;
    if((obj2->coordinate->y - obj2->height) > obj1->coordinate->y) return false;
    return true;
}
// **********************************************************************
//  void InitializeVariables()
// Inicia as variaveis do jogo e instancia as naves inimigas
// **********************************************************************
void InitializeVariables()
{
    //Inicia variaveis do ambiente
    state = INGAME;
    FPS = INFINITE;
    debug = false;
    displayCount = 0;
    WIDTHSCREEN = 800;
    HEIGHTSCREEN = 600;
    ENEMYAMOUNT = 3;
    ENEMYMODELS = 5;
    BULLETMODELS = 4;

    LoadColorsList();
    LoadModelsObjects();

    //Inicia a nave do jogador
    player = new PlayerShip(new Position(WIDTHSCREEN/2,HEIGHTSCREEN/2),playerModel, bulletModels.at(rand()%BULLETMODELS));

    //Naves inimigas obrigatorias e Naves randomizadas
    for(int i=0; i<ENEMYAMOUNT; i++)
    {
        if(i < ENEMYMODELS) enemysList.push_back(new EnemyShip(player->coordinate, enemysModels.at(i), WIDTHSCREEN, HEIGHTSCREEN,bulletModels.at(i)));
        else enemysList.push_back(new EnemyShip(player->coordinate, enemysModels.at(i), WIDTHSCREEN, HEIGHTSCREEN,bulletModels.at(rand()%BULLETMODELS)));
    }
}
// **********************************************************************
//  void LoadColorsList()
// Carrega as cores do arquivo "colors.txt" que serão utilizadas nas
// naves
// **********************************************************************
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
// **********************************************************************
//  void GameOver()
// Desenha a tela de Game Over
// **********************************************************************
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
// **********************************************************************
//  void LoadModel(ObjectModel* _modelObj, char fileName[])
// Método auxiliar para carregar os objetos modelo
// **********************************************************************
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
// **********************************************************************
//  void LoadModelsObjects()
// Carrega os modelos dos arquivos txt
// **********************************************************************
void LoadModelsObjects()
{
    char fileName[1024];
    ObjectModel* enemyModel;
    ObjectModel* bulletModel;
    //Carrega todos os modelos das naves inimigas
    for(int currentEShip=1; currentEShip<=ENEMYMODELS; currentEShip++)
    {
        sprintf(fileName,"EShip%d.txt",currentEShip);
        enemyModel = new ObjectModel();
        LoadModel(enemyModel,fileName);
        enemysModels.push_back(enemyModel);
    }
    //Carrega todos os modelos de disparos
    for(int currentBullet=1; currentBullet<=BULLETMODELS; currentBullet++)
    {
        sprintf(fileName,"Bullet%d.txt",currentBullet);
        bulletModel = new ObjectModel();
        LoadModel(bulletModel,fileName);
        bulletModels.push_back(bulletModel);
    }
    playerModel = new ObjectModel();
    LoadModel(playerModel, "PShip.txt");
    heartModel = new ObjectModel();
    LoadModel(heartModel, "Heart.txt");
}
// **********************************************************************
//  void DrawGUI()
// Desenha a interface do jogo
// **********************************************************************
void DrawGUI()
{
    glColor3f(1.0,0.0,0.0);
    int x=20, y=HEIGHTSCREEN-20, i, bulletCount;
    //Desenha as vidas do player
    for(i=0; i<player->health; i++)
    {
        DrawObject(new Position(x,y),heartModel,0,heartModel->sizePixel);
        x+=heartModel->model.at(0).size() * heartModel->sizePixel + 5;
    }

    x = 15;
    y = HEIGHTSCREEN - 100;
    bulletCount = 10 - player->bullets.size();
    glColor3f(1.0,1.0,1.0);
    //Desenha as balas disponiveis do jogador
    for(i=0; i<bulletCount; i++)
    {
        DrawRectangle(x,y,x+10,y+10);
        y-=15;
    }

    EnemyShip* enemy;
    x = WIDTHSCREEN - 10;
    y = 10;
    //Desenha as naves inimigas que ainda estão vivas
    for(i=0; i<enemysList.size(); i++)
    {
        enemy = enemysList.at(i);
        DrawObject(new Position(x,y),enemy->model, 90, 2);
        x -= 30;
    }
}
// **********************************************************************
//  void DrawRectangle(int _ix, int _iy, int _fx, int _fy)
// Método auxiliar que desenha um quadrado
// **********************************************************************
void DrawRectangle(int _ix, int _iy, int _fx, int _fy)
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
// **********************************************************************
//  void void DrawObject(Position* _pos, ObjectModel* _model, float _angle, float _sizeCell)
// Desenha um objeto especifico
// **********************************************************************
void DrawObject(Position* _pos, ObjectModel* _model, float _angle, float _sizeCell)
{
    int nextX, nextY;
    int y = _model->model.size();
    int x = _model->model.at(0).size();
    int currentX = -(x/2) * _sizeCell;
    int currentY = -(y/2) * _sizeCell;
    ColorRGB* color;
    vector<int> temp;

    glPushMatrix();
    {
        glTranslatef(_pos->x,_pos->y,0);
        glRotated(_angle,0,0,1);

        for(int line=y-1; line>=0; line--)
        {
            temp = _model->model.at(line);
            nextY = currentY + _sizeCell;

            for(int column=0; column<x; column++)
            {
                nextX = currentX + _sizeCell;
                if(temp.at(column))
                {
                    color = colorsList.at(temp.at(column));
                    glColor3f(color->r,color->g,color->b);
                    DrawRectangle(currentX,currentY,nextX,nextY);
                }
                currentX = nextX;
            }
            currentY = nextY;
            currentX = -(x/2) * _sizeCell;
            nextX = 0;
        }
    }
    glPopMatrix();
}
void Debug()
{
    glPushMatrix();
    {
        glTranslated(player->coordinate->x,player->coordinate->y,0);
        glRotated(player->angle,0,0,1);
        glBegin(GL_LINES);
        {
            glVertex2d(-(WIDTHSCREEN/2),0);
            glVertex2d(WIDTHSCREEN/2,0);
            glVertex2d(0,HEIGHTSCREEN/2);
            glVertex2d(0,-(HEIGHTSCREEN/2));
        }
        glEnd();
    }
    glPopMatrix();
}
// **********************************************************************
//  void ClearObjects()
// Remove do jogo qualquer objeto que tenha o atributo "inGame" como false
// **********************************************************************
void ClearObjects()
{
    int i,j;
    EnemyShip* enemy;
    //Verifica se alguma nave inimiga não está mais no jogo
    for(i=0; i<enemysList.size(); i++)
    {
        enemy = enemysList.at(i);
        if(!enemy->inGame) enemysList.erase(enemysList.begin()+i);

        for(j=0; j<enemy->bullets.size(); j++)
        {
            if(!enemy->bullets.at(j)->inGame) enemy->bullets.erase(enemy->bullets.begin()+j);
        }
    }
    //Verifica sem algum disparo não está mais no jogo
    for(i=0; i<player->bullets.size(); i++)
    {
        if(!player->bullets.at(i)->inGame) player->bullets.erase(player->bullets.begin()+i);
    }
}
// **********************************************************************
//  void Process()
// Processa todas as ações do objetos presentes no jogo
// **********************************************************************
void Process()
{
    if(!player->inGame)
    {
        state = GAMEOVER;
        return;
    }

    ClearObjects();

    VerifyUserActions();

    //Move todas as naves inimigas e seus disparos
    EnemyShip* enemy;
    Bullet* bullet;
    for(int i=0; i<enemysList.size(); i++)
    {
        enemy = enemysList.at(i);
        enemy->MoveEShip(FPS);

        for(int j=0; j<enemy->bullets.size(); j++)
        {
            bullet = enemy->bullets.at(j);
            bullet->MoveBullet();
            //Verifica colisão do disparo inimigo com o player
            if(IsColliding(player,bullet))
            {
                player->TakeDamage();
                bullet->inGame = false;
                return;
            }
        }
        //Verifica colisão da nave com o player
        if(IsColliding(player,enemy))
        {
            player->TakeDamage();
            enemy->inGame = false;
            return;
        }
        //Faz a nave inimiga disparar, caso seja possivel
        if(enemy->CanShoot()) enemy->Shoot();
    }

    //Move todas as balas disparadas pelo player
    for(int i=0; i<player->bullets.size(); i++)
    {
        bullet = player->bullets.at(i);
        bullet->MoveBullet();

        //Verifica colisão com todas as naves inimigas
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
    InitializeVariables();
    printf("Variaveis iniciadas\n");

    glutInit            ( &argc, argv );
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
    glutInitWindowPosition (0,0);

    // Define o tamanho inicial da janela grafica do programa
    glutInitWindowSize  ( 650, 500);

    // Cria a janela na tela, definindo o nome da
    // que aparecera na barra de título da janela.
    glutCreateWindow    ( "Primeiro Programa em OpenGL" );

    // executa algumas inicializações
    init ();

    // Define que o tratador de evento para
    // o redesenho da tela. A funcao "display"
    // será chamada automaticamente quando
    // for necessário redesenhar a janela
    glutDisplayFunc ( display );
    glutIdleFunc(animate);

    // Define que o tratador de evento para
    // o redimensionamento da janela. A funcao "reshape"
    // será chamada automaticamente quando
    // o usuário alterar o tamanho da janela
    glutReshapeFunc ( reshape );

    // Define que o tratador de evento para
    // as teclas. A funcao "keyboard"
    // será chamada automaticamente sempre
    // o usuário pressionar uma tecla comum
    glutKeyboardFunc ( keyboard );

    // Define que o tratador de evento para
    // as teclas especiais(F1, F2,... ALT-A,
    // ALT-B, Teclas de Seta, ...).
    // A funcao "arrow_keys" será chamada
    // automaticamente sempre o usuário
    // pressionar uma tecla especial
    glutSpecialFunc ( arrow_keys );

    // inicia o tratamento dos eventos
    glutMainLoop ( );

    return 0;
}
