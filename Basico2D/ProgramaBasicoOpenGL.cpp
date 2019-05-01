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
#include <unistd.h>

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
float deltaTime;
bool canProcess = false;
bool debug;
bool win;
int WIDTHSCREEN;
int HEIGHTSCREEN;
int ENEMYAMOUNT;
int ENEMYMODELS;
int BULLETMODELS;
int score;
vector<ObjectModel*> enemysModels;
vector<ObjectModel*> bulletModels;
vector<ObjectModel*> numbers;
vector<ObjectModel*> lyrics;
vector<EnemyShip*> enemysList;
vector<ColorRGB*> colorsList;
vector<Bullet*> bulletsInGame;
ObjectModel* playerModel;
ObjectModel* heartModel;
ObjectModel* gameOverScreen;
ObjectModel* winMessage;
ObjectModel* loseMessage;
PlayerShip* player;
ColorRGB* backgroundColor;


// Métodos OpenGL
void animate();
void init(void);
void reshape( int w, int h );
void display( void );
void keyboard ( unsigned char key, int x, int y );
void arrow_keys ( int a_keys, int x, int y );

// Métodos do Jogo
void InitializeVariables();
void LoadColorsList();
void LoadModelsObjects();
void LoadModel(ObjectModel* _modelObj, char fileName[]);
void LoadConfig();
void LoadNumbersModels();
void LoadAlphabet();
void Process();
void GameOver();
void VerifyUserActions();
void Draw();
void DrawGUI();
void DrawScore();
void DrawWord(char _word[], int _length, int _size, Position* pos);
void DrawObject(Position* pos, ObjectModel* _model, float _angle, float _sizeCell);
void DrawQuad(int _ix, int _iy);
void Debug();
bool IsColliding(Object* obj1, Object* obj2);
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
    deltaTime = (dt < 1) ? dt:deltaTime;
    if (AccumTime >=3) // imprime o FPS a cada 3 segundos
    {
        cout << 1.0/dt << " FPS"<< endl;
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
    if(deltaTime < 1 & deltaTime != 0) canProcess = true;
    glutPostRedisplay();
}
// **********************************************************************
//  void init(void)
//  Inicializa os parâmetros globais de OpenGL
// **********************************************************************
void init(void)
{
	// Define a cor do fundo da tela (PRETO)
    glClearColor(backgroundColor->r, backgroundColor->g, backgroundColor->b, 1.0f);

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
    if(canProcess)
    {

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
            player->Shoot();
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
//  LoadNumbersModels()
//  Carrega os modelos dos numeros
// **********************************************************************
void LoadNumbersModels()
{
    ifstream file;
    char fileName[10];
    ObjectModel* numberModel;

    for(int i=0; i<10; i++)
    {
        sprintf(fileName,"%d.txt",i);

        file.open(fileName);

        if(file == NULL)
        {
            printf("%d.txt não encontrado!\n",i);
            return;
        }

        numberModel = new ObjectModel();
        LoadModel(numberModel, fileName);
        numbers.push_back(numberModel);

        file.close();
    }
    printf("Numeros carregados com sucesso!\n");
}
// **********************************************************************
//  void DrawScore()
//  Desenha a pontuação do jogador no canto superior direito da tela
// **********************************************************************
void DrawScore()
{
    //Desenha o numero
    Position pos(WIDTHSCREEN-10,HEIGHTSCREEN-10);
    ObjectModel* number;
    int aux = score;
    while(aux > 0)
    {
        number = numbers.at(aux%10);
        DrawObject(&pos, number, 0, number->sizePixel);
        aux = aux/10;
        pos.x  -= number->model.at(0).size() * (number->sizePixel+1);
    }

    pos.x -= 100;

    //Desenha a palavra
    DrawWord("score", 5, 3, &pos);
}

// **********************************************************************
//  void Draw ()
// Desenha todos os objetos do jogo na tela
// **********************************************************************
void Draw()
{
    int i;
    //Desenha Player
    DrawObject(player->coordinate, player->model,player->angle-90, player->model->sizePixel);
    //Desenha naves inimigas
    EnemyShip* enemy;
    for(i=0; i<enemysList.size(); i++)
    {
        enemy = enemysList.at(i);
        DrawObject(enemy->coordinate, enemy->model, enemy->angle, enemy->model->sizePixel);
    }
    //Desenha balas
    Bullet* bullet;
    for(i=0; i<bulletsInGame.size(); i++)
    {
        bullet = bulletsInGame.at(i);
        DrawObject(bullet->coordinate, bullet->model, bullet->angle, bullet->model->sizePixel);
    }
    //Desenha balas do Jogador
    for(i=0; i<player->bullets.size(); i++)
    {
        bullet = player->bullets.at(i);
        DrawObject(bullet->coordinate, bullet->model, bullet->angle, bullet->model->sizePixel);
    }

    //Desenha GUI
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
        player->MoveShip(deltaTime);
    }

    if(GetKeyState('A') & 0x8000)
    {
        player->Rotate(false, deltaTime);
    }

    if(GetKeyState('D') & 0x8000)
    {
        player->Rotate(true, deltaTime);
    }
}
// **********************************************************************
//  void LoadConfig()
// Carraga a quantidade de inimigos a ser combatido na partida, assim
// como a quantidade de modelos de naves e disparos
// **********************************************************************
void LoadConfig()
{
    ifstream file;

    file.open("Config.txt");
    if(!file)
    {
        printf("Config.txt nao encontrado!\n");
        return;
    }

    file >> ENEMYAMOUNT;
    file >> ENEMYMODELS;
    file >> BULLETMODELS;

    printf("Config.txt carregado com sucesso!\n");
    file.close();
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
    debug = false;
    WIDTHSCREEN = 800;
    HEIGHTSCREEN = 600;
    score = 0;
    backgroundColor = colorsList.at(0);

    //Inicia a nave do jogador
    player = new PlayerShip(new Position(WIDTHSCREEN/2,HEIGHTSCREEN/2),playerModel, bulletModels.at(rand()%BULLETMODELS), WIDTHSCREEN, HEIGHTSCREEN);

    //Naves inimigas obrigatorias e Naves randomizadas
    enemysList.clear();
    for(int i=0; i<ENEMYAMOUNT; i++)
    {
        if(i < ENEMYMODELS) enemysList.push_back(new EnemyShip(player->coordinate, enemysModels.at(i), WIDTHSCREEN, HEIGHTSCREEN,bulletModels.at(rand()%BULLETMODELS), &bulletsInGame));
        else enemysList.push_back(new EnemyShip(player->coordinate, enemysModels.at(i%ENEMYMODELS), WIDTHSCREEN, HEIGHTSCREEN,bulletModels.at(rand()%BULLETMODELS), &bulletsInGame));
    }

    bulletsInGame.clear();
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
    int padding = 50;
    Position* pos = new Position(WIDTHSCREEN/2,HEIGHTSCREEN-(gameOverScreen->model.size()/2) * gameOverScreen->sizePixel - padding);
    DrawObject(pos, gameOverScreen, 0, gameOverScreen->sizePixel);

    if(win)
    {
        pos->y = padding + winMessage->model.size()*winMessage->sizePixel;
        DrawObject(pos, winMessage, 0, winMessage->sizePixel);
    }else
    {
        pos->y = padding + loseMessage->model.size()*loseMessage->sizePixel;
        DrawObject(pos, loseMessage, 0, loseMessage->sizePixel);
    }

    if(GetKeyState('R') & 0x8000)
    {
        InitializeVariables();
        return;
    }
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
    gameOverScreen = new ObjectModel();
    LoadModel(gameOverScreen, "GameOverScreen.txt");
    winMessage = new ObjectModel();
    LoadModel(winMessage, "WinMessage.txt");
    loseMessage = new ObjectModel();
    LoadModel(loseMessage, "LoseMessage.txt");

    //Le os modelos dos numeros
    LoadNumbersModels();
}
// **********************************************************************
//  void DrawGUI()
// Desenha a interface do jogo
// **********************************************************************
void DrawGUI()
{
    glColor3f(1.0,0.0,0.0);
    Position* pos = new Position(20, HEIGHTSCREEN-20);
    int i, bulletCount;
    //Desenha as vidas do player
    for(i=0; i<player->health; i++)
    {
        DrawObject(pos,heartModel,0,heartModel->sizePixel);
        pos->x+=heartModel->model.at(0).size() * heartModel->sizePixel + 5;
    }

    pos->x = 15;
    pos->y = HEIGHTSCREEN - 50;
    bulletCount = 10 - player->bullets.size();
    glColor3f(1.0,1.0,1.0);
    //Desenha as balas disponiveis do jogador
    for(i=0; i<bulletCount; i++)
    {
        DrawObject(pos,player->bulletModel,0,3);
        pos->y-=15;
    }

    EnemyShip* enemy;
    pos->x = WIDTHSCREEN - 10;
    pos->y = 15;
    //Desenha as naves inimigas que ainda estão vivas
    for(i=0; i<enemysList.size(); i++)
    {
        enemy = enemysList.at(i);
        DrawObject(pos,enemy->model, 90, 2);
        pos->x -= 30;
    }

    //Desenha Score
    DrawScore();
}
// **********************************************************************
//  void DrawQuad(int _ix, int _iy)
// Método auxiliar que desenha um quadrado
// **********************************************************************
void DrawQuad(float _ix, float _iy)
{
    glBegin(GL_QUADS);
    {
        glVertex2d(_ix,_iy);
        glVertex2d(_ix+1,_iy);
        glVertex2d(_ix+1,_iy+1);
        glVertex2d(_ix,_iy+1);
    }
    glEnd();
}
// **********************************************************************
//  void void DrawObject(Position* _pos, ObjectModel* _model, float _angle, float _sizeCell)
// Desenha um objeto especifico
// **********************************************************************
void DrawObject(Position* _pos, ObjectModel* _model, float _angle, float _sizeCell)
{
    int i,j;
    float x = _model->model.at(0).size();
    float y = _model->model.size();
    float currentX = x/-2.0;
    float currentY = y/-2.0;
    float baseX = currentX;
    ColorRGB* color;
    vector<int> temp;

    glPushMatrix();
    {
        glTranslatef(_pos->x - (x/2),_pos->y - (y/2),0);
        glScaled(_sizeCell,_sizeCell,1);
        glRotated(_angle,0,0,1);

        for(i=y-1; i>=0; i--)
        {
            temp = _model->model.at(i);
            for(j=0; j<x; j++)
            {
                color = colorsList.at(temp.at(j));
                if(color != backgroundColor)
                {
                    glColor3f(color->r,color->g, color->b);
                    DrawQuad(currentX,currentY);
                }
                currentX++;
            }
            currentY++;
            currentX = baseX;
        }

    }
    glPopMatrix();
}
// **********************************************************************
//  void Debug()
// Desenha algumas informações uteis na tela
// **********************************************************************
void Debug()
{
    EnemyShip* enemy;

    for(int i=0; i<enemysList.size(); i++)
    {
        enemy = enemysList.at(i);
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_LINES);
        {
            glVertex2f(enemy->p0->x,enemy->p0->y);
            glVertex2f(enemy->p1->x,enemy->p1->y);
            glVertex2f(enemy->p1->x,enemy->p1->y);
            glVertex2f(enemy->p2->x,enemy->p2->y);
            glVertex2f(enemy->p2->x,enemy->p2->y);
            glVertex2f(enemy->p3->x,enemy->p3->y);
        }
        glEnd();
    }

    glPushMatrix();
    {
        glTranslated(player->coordinate->x,player->coordinate->y,0);
        glRotated(player->angle,0,0,1);
        glColor3f(1.0,1.0,1.0);
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
    int i;
    EnemyShip* enemy;
    //Verifica se alguma nave inimiga não está mais no jogo
    for(i=0; i<enemysList.size(); i++)
    {
        enemy = enemysList.at(i);
        if(!enemy->inGame) enemysList.erase(enemysList.begin()+i);
    }
    Bullet* bullet;
    //Verifica se alguma bala não está no jogo
    for(i=0; i<bulletsInGame.size(); i++)
    {
        bullet = bulletsInGame.at(i);
        if(!bullet->inGame) bulletsInGame.erase(bulletsInGame.begin()+i);
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
    //Verifica se o jogador esta no jogo
    if(!player->inGame)
    {
        state = GAMEOVER;
        win = false;
        return;
    }
    //verifica se o jogador ganhou
    if(enemysList.empty())
    {
        state = GAMEOVER;
        win = true;
        return;
    }
    //limpa ohjetos que não estão mais no jogo
    ClearObjects();
    //verifica input do jogador
    VerifyUserActions();
    //Move todas as naves inimigas
    EnemyShip* enemy;
    for(int i=0; i<enemysList.size(); i++)
    {
        enemy = enemysList.at(i);
        enemy->MoveEShip(deltaTime);

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
    //Move balas em jogo
    Bullet* bullet;
    for(int j=0; j<bulletsInGame.size(); j++)
    {
        bullet = bulletsInGame.at(j);
        bullet->MoveBullet(deltaTime);
        //Verifica colisão do disparo inimigo com o player
        if(IsColliding(player,bullet))
        {
            player->TakeDamage();
            bullet->inGame = false;
            return;
        }
    }

    //Move todas as balas disparadas pelo player
    for(int i=0; i<player->bullets.size(); i++)
    {
        bullet = player->bullets.at(i);
        bullet->MoveBullet(deltaTime);

        //Verifica colisão com todas as naves inimigas
        for(int j=0; j<enemysList.size(); j++)
        {
            enemy = enemysList.at(j);
            if(IsColliding(bullet,enemy))
            {
                enemy->inGame = false;
                bullet->inGame = false;
                score += enemy->value;
                break;
            }
        }
    }
}
// **********************************************************************
// void DrawWord(char _word[], int _length, int _size, Position* _pos)
// Desenha uma palavra na tela
// **********************************************************************
void DrawWord(char _word[], int _length, int _size, Position* _pos)
{
    int index,offset = 97;
    ObjectModel* lyric;
    for(index = 0; index < _length; index++)
    {
        if(_word[index] != 32)
        {
            lyric = lyrics.at(_word[index] - offset);
            DrawObject(_pos, lyric, 0, _size);
        }
        _pos->x += lyric->model.at(0).size() * _size + 5;
    }
}
// **********************************************************************
// void LoadAlphabet()
// Carrega as letras do alfabeto
// **********************************************************************
void LoadAlphabet()
{
    ifstream file;
    char fileName[10];
    ObjectModel* lyricModel;

    for(int i=97; i<123; i++)
    {
        sprintf(fileName,"%c.txt",i);

        file.open(fileName);

        if(file == NULL)
        {
            printf("%c.txt não encontrado!\n",i + '0');
            return;
        }

        lyricModel = new ObjectModel();
        LoadModel(lyricModel, fileName);
        lyrics.push_back(lyricModel);

        file.close();
    }
    printf("Alfabeto carregados com sucesso!\n");
}

// **********************************************************************
//  void main ( int argc, char** argv )
// **********************************************************************
int  main ( int argc, char** argv )
{
    LoadConfig();
    LoadColorsList();
    LoadModelsObjects();
    InitializeVariables();
    printf("Variaveis iniciadas\n");

    LoadAlphabet();

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
