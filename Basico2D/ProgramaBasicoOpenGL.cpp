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
#include "Util.cpp"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


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

int WIDTHSCREEN = 800;
int HEIGHTSCREEN = 600;
PlayerShip player;

void Draw();

void Draw()
{
    int size = 5;
    glBegin(GL_TRIANGLES);
    {
        glVertex2d(-size,size);
        glVertex2d(size,0);
        glVertex2d(-size,-size);
    }
    glEnd();
}


// **********************************************************************
//  void animate ( unsigned char key, int x, int y )
//
//
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
//
// **********************************************************************
void init(void)
{
	// Define a cor do fundo da tela (AZUL)
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

}

// **********************************************************************
//  void reshape( int w, int h )
//  trata o redimensionamento da janela OpenGL
//
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

PlayerShip p;

// **********************************************************************
//  void display( void )
//
// **********************************************************************
void DrawBullet()
{
    int size = 2;
    glBegin(GL_QUADS);
    {
        glVertex2d(-size,-size);
        glVertex2d(size,-size);
        glVertex2d(size,size);
        glVertex2d(-size,size);
    }
    glEnd();
}

EnemyShip es0(p.coordinate);
EnemyShip es1(p.coordinate);
EnemyShip es2(p.coordinate);
EnemyShip es3(p.coordinate);
EnemyShip es4(p.coordinate);

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
    glPushMatrix();
        glTranslated(player.coordinate->x,player.coordinate->y,0);
        glRotatef(player.angle,0,0,1);
        Draw();
    glPopMatrix();
    player.moveBullets();

    for(int i=0; i<player.currentBullets; i++)
    {
        glPushMatrix();
            glTranslatef(player.bullets[i].coordinate->x,player.bullets[i].coordinate->y,0);
            glRotatef(player.bullets[i].angle,0,0,1);
            DrawBullet();
        glPopMatrix();
    }

    es0.moveEShip();
    glPushMatrix();
        glTranslated(es0.coordinate->x,es0.coordinate->y,0);
        Draw();
    glPopMatrix();
    es1.moveEShip();
    glPushMatrix();
        glTranslated(es1.coordinate->x,es1.coordinate->y,0);
        Draw();
    glPopMatrix();
    es2.moveEShip();
    glPushMatrix();
        glTranslated(es2.coordinate->x,es2.coordinate->y,0);
        Draw();
    glPopMatrix();
    es3.moveEShip();
    glPushMatrix();
        glTranslated(es3.coordinate->x,es3.coordinate->y,0);
        Draw();
    glPopMatrix();

    player.moveBullets();

	glutSwapBuffers();
}


// **********************************************************************
//  void keyboard ( unsigned char key, int x, int y )
//
// **********************************************************************

void keyboard ( unsigned char key, int x, int y )
{

	switch ( key )
	{
		case 27:        // Termina o programa qdo
			exit ( 0 );   // a tecla ESC for pressionada
			break;

        case 'w':
            player.moveShip(0,WIDTHSCREEN,0,HEIGHTSCREEN);
            break;

        case 'a':
            player.rotate(true);
            break;

        case 'd':
            player.rotate(false);
            break;

        case ' ':
            if(player.canShoot()) player.Shoot(WIDTHSCREEN,HEIGHTSCREEN);
            //printf("Bx=%f,By=%f\n",player.bullets[0].coordinate->x,player.bullets[0].coordinate->y);
            break;

		default:
			break;
	}
}


// **********************************************************************
//  void arrow_keys ( int a_keys, int x, int y )
//
//
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
//  void main ( int argc, char** argv )
//
//
// **********************************************************************
int  main ( int argc, char** argv )
{
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
