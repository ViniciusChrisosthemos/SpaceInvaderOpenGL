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
#include <list>
#include <iterator>

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

int width = 400;
int height = 300;
int size = 10;

class Object {

public:
    float x;
    float y;
    float angle;
    float speed;
    //int width;
    //int height;
    //int image[];
    bool inGame;

    Object(/*int _image[], int _width, int _height, float _speed*/)
    {
        x = 0;
        y = 0;
        angle = 90;
        speed = 5;
        inGame = true;
        /*
        width = _width;
        height = _height;

        int length = width*height;

        image[length];
        for(int i=0; i<length; i++)
        {
            image[i] = _image[i];
        }
        */
    }


    void DrawBullet()
    {
        if((x < 0 || x > width) && (y < 0 || y > height))
        {
            inGame = false;
            return;
        }

        glPushMatrix();
        {
            glTranslatef(x,y,0);
            glRotatef(angle,0,0,1);
            float size = 5/2;
            glBegin(GL_POLYGON);
              glVertex2f(-size,-size);
              glVertex2f(-size,size);
              glVertex2f(size,size);
              glVertex2f(size,-size);
              glVertex2f(-size,-size);
            glEnd();
        }
        glPopMatrix();
    }

    void MoveObject()
    {
        float degree = angle * (M_PI/180);
        x += cos(degree) * speed;
        y += sin(degree) * speed;
    }
};

class PlayerShip{
private:
    int MAXBULLET = 10;
    int ROTATION = 15;
public:
    Object object;
    list<Object> bullets;

    PlayerShip(){
    }

    void Shoot()
    {
        if(bullets.size() >= MAXBULLET) return;

        Object bullet;
        bullet.x = object.x;
        bullet.y = object.y;
        bullet.angle = object.angle;
        bullet.speed = 20;

        bullets.push_front(bullet);
    }

    void MovePlayerShip()
    {
        object.MoveObject();
    }

    void Rotate(bool right)
    {
        if(right) object.angle += ROTATION;
        else object.angle -= ROTATION;
    }

    float GetX()
    {
        return object.x;
    }

    float GetY()
    {
        return object.y;
    }

    float GetAngle()
    {
        return object.angle;
    }
};


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

void display( void )
{

	// Limpa a tela coma cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);

    // Define os limites lógicos da área OpenGL dentro da Janela
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(-width,width,-height,height,0,1);

	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// Coloque aqui as chamadas das rotinas que desenha os objetos
	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	for (std::list<Object>::iterator it = p.bullets.begin(); it != p.bullets.end(); ++it){
        it->MoveObject();
        it->DrawBullet();
    }

    //DrawBullet();
	glLineWidth(3);
	glColor3f(0,1,0);
	glTranslatef(p.object.x,p.GetY(),0);
    glRotatef(p.GetAngle(),0,0,1);
	glBegin(GL_POLYGON);
	  glVertex2f(-size,-size);
	  glVertex2f(-size,size);
	  glVertex2f(size,size);
	  glVertex2f(size,-size);
	  glVertex2f(-size,-size);
	glEnd();
	/*
    glBegin(GL_LINES);
    {
        glVertex2f(-width,0);
        glVertex2f(width,0);
        glVertex2f(0,-height);
        glVertex2f(0,height);
    }
    glEnd();
    */
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
        case 'd':
            p.Rotate(false);
            break;
        case 'a':
            p.Rotate(true);
            break;
        case 'w':
            p.MovePlayerShip();
            break;
        case ' ':
            p.Shoot();
            printf("Bullet in game : %i\n",p.bullets.size());
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
    PlayerShip p;
    p.Shoot();


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
