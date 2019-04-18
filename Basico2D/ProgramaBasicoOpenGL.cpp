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
#include <stdlib.h>
#include <ObjectModel.h>

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



// Variáveis Globais
int WIDTHSCREEN;
int HEIGHTSCREEN;
int ENEMYAMOUNT;
vector<ObjectModel*> modelsList;
vector<EnemyShip*> enemysList;
PlayerShip* player;

// Métodos OpenGL
void animate();
void init(void);
void reshape( int w, int h );
void display( void );
void keyboard ( unsigned char key, int x, int y );
void arrow_keys ( int a_keys, int x, int y );

// Métodos do Jogo
void DrawObject(int* _model[], int _x, int _y, float angle);
void DrawSquare(int _ix, int _iy, int _fx, int _fy);
void LoadColorsMatriz();
void LoadModelsObjects();
void InitializeVariables();
void Process();
void Draw();


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
	// Define a cor do fundo da tela (AZUL)
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

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
    glOrtho(0,gameManager->WIDTHSCREEN,0,gameManager->HEIGHTSCREEN,0,1);
    glTranslated(400,300,0);
	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// Coloque aqui as chamadas das rotinas que desenha os objetos
	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



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
            break;

        case 'a':
            break;

        case 'd':
            break;

        case ' ':
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

void InitializeVariables()
{
    //Inicia variaveis do ambiente
    WIDTHSCREEN = 800;
    HEIGHTSCREEN = 600;
    ENEMYAMOUNT = 6;

    //Inicia a nave do jogador
    player = new PlayerShip();
    /*
    //Inicia as naves inimigas
    for(int i=0; i<ENEMYAMOUNT; i++)
    {

    }
    */
}

void LoadColorsMatriz()
{
    ifstream file;
    int currentInt,i,temp;

    file.open("colors.txt");

    if(!file)
    {
        printf("Erro ao ler o arquivo!");
        return;
    }

    file >> temp;
    int colorMatriz[temp][3];

    while(file >> currentInt)
    {
        for(i=0; i<3; i++)
        {
            file >> temp;
            colorMatriz[currentInt-1][i] = temp;
        }
    }

    file.close();
}

//https://www.quora.com/How-do-I-open-files-using-an-array-in-C
void LoadModelsObjects()
{
    ifstream file;
    int enemyshipModels;
    char fileName[1024];

    cout << "Informe o número de modelos de naves: ";
    cin >> enemyshipModels;
    int x,y;
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
        printf("Open %s\n",fileName);
        printf("Processing ............%s\n",fileName);

        file >> x;
        file >> y;

        modelObj = new ObjectModel();
        modelObj->model[x];
        modelObj->x = x;
        modelObj->y = y;
        printf("X=%d  Y=%d\n",modelObj->x,modelObj->y);
        printf("Matriz[%d][%d]\n",x,y);
        for(int line=0; line < x; line++)
        {
            modelObj->model[line] = new int[y];
            printf("%d  ", line);
            for(int column=0; column < y; column++)
            {
                file >> modelObj->model[line][column];
                printf("%d ",modelObj->model[line][column]);
            }
            printf("\n");
        }
        printf("X=%d  Y=%d\n",modelObj->x,modelObj->y);
        modelsList.push_back(modelObj);
        printf("X=%d  Y=%d\n",modelsList.at(0)->x,modelsList.at(0)->y);

        fprintf(stderr,"%s carregado com sucesso!\n", fileName);
        printf("Closing %s\n",fileName);
        enemyshipModels--;
        file.close();
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

void DrawObject(int* _model[], int _x, int _y, float angle)
{
    int sizeCell = 5;
    int currentX=0,currentY=0,nextX,nextY;

    glPushMatrix();
    {
        glRotated(angle,0,0,1);
        for(int line=_x-1; line>=0; line--)
        {
            nextY = currentY + sizeCell;
            for(int column=0; column<_y; column++)
            {
                nextX = currentX + sizeCell;
                if(_model[line][column] != 0)
                {
                    DrawSquare(currentX,currentY,nextX,nextY);
                }
                currentX = nextX;
            }
            currentY = nextY;
            currentX = 0;
            nextX = 0;
        }
    }
    glPopMatrix();
}



// **********************************************************************
//  void main ( int argc, char** argv )
// **********************************************************************
int  main ( int argc, char** argv )
{

    LoadColorsMatriz();
    LoadModelsObjects();
    InitializeVariables();

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
