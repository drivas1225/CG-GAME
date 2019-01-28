#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <string>
#include <sstream>
#include <GL/glut.h>
#include <GL/glext.h>
#include <ctime>

#include "Player.h"
#include "Obstacle.h"
#include "Coin.h"
#include "TextureManager.h"

using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27
#define SPACE_BAR 32
#define INTRO 13

void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);

bool GameOver = false;
time_t start,end;

///Putaje
int SCORE = 0;


///Player
Player pl;
GLint sprite;
GLint spike;


///coins
vector<Coin> coins;
int numCoins = 10;


///Obstacles
vector<Obstacle> obstacles;
int enemies = 5;


GLUquadricObj *sphere = NULL;



///Variables de la camara
double CamPosX = 0;
double CamPosY = 20;
double CamPosZ = 40;

double CentX = 0;
double CentY = 0;
double CentZ = 0;

double AngX = 0;
double AngY = 1;
double AngZ = 0;

double AngRotX = 0;
double AngRotY = 0;

double temDTX = 0;
double temDTY = 0;

double velCam = 1;
double VelAngRot = 1;

///variables
float angle = 0;
float posXG = 0;

int cantpoints = 100;
double angulo = 360/cantpoints;
double alpha = 0;

float MAX = 8;
float MIN = -8;
bool Sentido = 0;

int time_h=0;
int timebase=0;
float dt;


bool boom = false;

//texturas
GLint ground;
GLint texture_teaPot;
GLint texture_gameOver;
GLint texture_shield;




//function called on each frame
GLvoid window_idle();


///////////////////////////////////////////////////////////////////////////////
//(1)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_special(int key, int x, int y)
{
	if(!GameOver)
	{
	    switch (key)
	    {
	    case GLUT_KEY_UP:
	        pl.move(key);
	        glutPostRedisplay();			// et on demande le réaffichage.
	        break;

	    case GLUT_KEY_DOWN:
	        pl.move(key);
	        glutPostRedisplay();			// et on demande le réaffichage.
	        break;

	    case GLUT_KEY_LEFT:
	        pl.move(key);
	        glutPostRedisplay();			// et on demande le réaffichage.
	        break;

	    case GLUT_KEY_RIGHT:
	        pl.move(key);
	        glutPostRedisplay();			// et on demande le réaffichage.
	        break;
	    }
	}
}



///////////////////////////////////////////////////////////////////////////////
//(2)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
    {
        temDTX = 0;
        temDTY = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////
//(3)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_motion(int x, int y)
{
    AngRotX = x - temDTX;
    AngRotY = y - temDTY;
    glutPostRedisplay();
}

void RotateCamera()
{
    glRotated(AngRotY,1.0f,0.0f,0.0f);
    glRotated(AngRotX,0.0f,1.0f,0.0f);


}
int main(int argc, char **argv)
{

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


    glutInitWindowSize(800, 800);
    glutInitWindowPosition(400, 100);
    glutCreateWindow("Teapot Runner");


    initGL();
    init_scene();

    time (&start);



    ground = TextureManager::Inst()->LoadTexture("C:/spring/work space/CG-GAME/grass2.jpg", GL_RGB, GL_RGB);
    texture_teaPot = TextureManager::Inst()->LoadTexture("C:/spring/work space/CG-GAME/teapot.png", GL_BGRA_EXT, GL_BGRA);
    texture_gameOver = TextureManager::Inst()->LoadTexture("C:/spring/work space/CG-GAME/game_over.png", GL_BGRA, GL_RGBA);
    texture_shield = TextureManager::Inst()->LoadTexture("C:/spring/work space/CG-GAME/shield_tr.png", GL_BGRA, GL_RGBA);
    spike = TextureManager::Inst()->LoadTexture("C:/spring/work space/CG-GAME/tnt.jpg", GL_RGB, GL_RGB);
    //ground = TextureManager::Inst()->LoadTexture("C:/spring/work space/CG-GAME/grass2.jpg", GL_RGB, GL_RGB);
    //texture_teaPot = TextureManager::Inst()->LoadTexture("C:/spring/work space/CG-GAME/teapot.png", GL_BGRA_EXT, GL_BGRA);
    //texture_gameOver = TextureManager::Inst()->LoadTexture("C:/spring/work space/CG-GAME/game_over.png", GL_BGRA_EXT, GL_RGBA);
    //spike = TextureManager::Inst()->LoadTexture("C:/spring/work space/CG-GAME/tnt.jpg", GL_RGB, GL_RGB);

    glutDisplayFunc(&window_display);

    glutReshapeFunc(&window_reshape);

    glutKeyboardFunc(&window_key);

    glutSpecialFunc(&callback_special);
    glutMouseFunc(&callback_mouse);
    glutMotionFunc(&callback_motion);

    //function called on each frame
    glutIdleFunc(&window_idle);


    for(int i=0; i<enemies; i++){
        Obstacle obs(i);
        obstacles.push_back(obs);
    }
    for(int i=0; i<numCoins; i++){
    	Coin coin;
    	coins.push_back(coin);
    }



    glutMainLoop();

    return 1;
}


//dibuja el suelo
void displayGizmo()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ground);
    glBegin(GL_QUADS);
    //glColor3f(0.156f,0.396f,0.721f);
    glTexCoord2f(1.0, 1.0);
    glVertex3d(1.5, -0.5,pl.PosZ - 170);
    glTexCoord2f(1.0, 0.0f);
    glVertex3d(2, -0.5,-10-pl.PosZ);
    glTexCoord2f(0.0, 0.0f);
    glVertex3d(-2, -0.5,-10-pl.PosZ);
    glTexCoord2f(0.0, 1.0);
    glVertex3d(-2, -0.5,pl.PosZ - 170);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}




GLvoid initGL()
{
    GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };

    //enable light : try without it
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);
    //light 0 "on": try without it
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);
    //glShadeModel(GL_SMOOTH); // modelo de shading try GL_FLAT
    //glEnable(GL_CULL_FACE); //no trata las caras escondidas
    //glEnable(GL_DEPTH_TEST); // Activa el Z-Buffer
    //glDepthFunc(GL_LEQUAL); //Modo de funcionamiento del Z-Buffer
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Activa la corrección de perspectiva


    //shading model : try GL_FLAT
    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);

    //enable material : try without it
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(RED, GREEN, BLUE, ALPHA);
}

float distancia_euclideana(Player jugador, Obstacle obstaculo){
    return sqrt(pow(jugador.PosX-obstaculo.PosX,2)+pow(jugador.PosY-obstaculo.PosY,2)+pow(jugador.PosZ-obstaculo.PosZ,2));
}

float distancia_euclideana_coin(Player jugador, Coin obstaculo){
    return sqrt(pow(jugador.PosX-obstaculo.PosX,2)+pow(jugador.PosY-obstaculo.PosY,2)+pow(jugador.PosZ-obstaculo.PosZ,2));
}




GLvoid window_display()
{
    clock_t end = clock();
    time_h = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
    dt = float(time_h -timebase)/1000.0;// delta time
    timebase = time_h;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//funcion de transparencia
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0,0,800,700);

    gluPerspective(45,1,0.1,100);
    gluLookAt(0, 1.5, pl.PosZ+5, 0, 0, pl.PosZ-5, 0, 1, 0);


	glEnable(GL_BLEND);

    displayGizmo();
    for(int i =0; i<obstacles.size(); i++){
        float dist = distancia_euclideana(pl,obstacles[i]);
        if(!GameOver && dist < 0.75) {

            if(!obstacles[i].exploited && pl.hit)
            {
            	obstacles[i].exploited = true;

            }else if(!obstacles[i].exploited){
            	GameOver = true;
         		pl.displayGameOver();
         		break;
        	}
        }
        if(!GameOver&&obstacles[i].PosZ > pl.PosZ+2){
            obstacles[i].updatePositions(pl.PosZ,i);
        }
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, spike);
        time (&end);
        cout<<"the time is: "<<difftime(end,start)<<endl;
        obstacles[i].display(difftime(end,start));
        glDisable(GL_TEXTURE_2D);

    }
    for(int i =0; i<coins.size(); i++){
        float dist = distancia_euclideana_coin(pl,coins[i]);
        if(dist<0.75) {
            if(!coins[i].gotcha){
                SCORE++;
                coins[i].gotcha = true;
            }
        }
        if(coins[i].PosZ > pl.PosZ+2){
            coins[i].updatePositions(pl.PosZ);
        }
        coins[i].display();
    }

    ///drow player
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_teaPot);
    pl.display(dt,GameOver);
    if(pl.hit){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_shield);
        pl.display_shield();
        glDisable(GL_TEXTURE_2D);
    }
    //glDisable(GL_TEXTURE_2D);

    if (GameOver){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_gameOver);
        pl.displayGameOver();
        glDisable(GL_TEXTURE_2D);
    }


    glDisable(GL_BLEND);


    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);



    glLoadIdentity();
    glViewport(0,700,800,50);
    glDisable(GL_LIGHTING);
    glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);

    glBegin(GL_LINE_LOOP);
    glColor3f(1,1,1);
    glVertex3d(-25,-25,0);
    glVertex3d(25,-25,0);
    glVertex3d(25,25,0);
    glVertex3d(-25,25,0);
    glEnd();

    string s = "Score: " ;
    ostringstream convert;
    convert << SCORE;
    s += convert.str();

    glPushAttrib(GL_CURRENT_BIT);
    glColor3f(1,1,1);
    glRasterPos3f(-24, -5, 0);

	for (int i = 0; s[i] != '\0'; i ++)
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
	if(GameOver){
		string gameover = "GAME OVER!";
		glColor3f(1,1,1);
		glRasterPos3f(-5, 0, 0);
		for (int i = 0; gameover[i] != '\0'; i ++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, gameover[i]);
		gameover = "press intro key to start again";
		glRasterPos3f(-4.6, -10, 0);
		for (int i = 0; gameover[i] != '\0'; i ++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, gameover[i]);
	}




	glEnable(GL_LIGHTING);

    glutSwapBuffers();

    glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);

    glMatrixMode(GL_MODELVIEW);
}



void init_scene()
{

}

GLvoid window_key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ECHAP:
        exit(1);
        break;

    case SPACE_BAR:
    	pl.hit = true;
    	//pl.hitObject();
    	break;

    case INTRO:
    	if(GameOver) {
    		GameOver = false;
    		pl.PosZ = 0;
    		pl.PosY = 0;
    		pl.PosX = 0;
    		SCORE = 0;
    		obstacles.clear();
    		coins.clear();
    		for(int i=0; i<enemies; i++){
                Obstacle obs(i);
                obstacles.push_back(obs);
            }
            for(int i=0; i<numCoins; i++){
                Coin coin;
                coins.push_back(coin);
            }
            time(&start);
    	}
    	break;

    default:
        printf("La touche %d non active.\n", key);
        break;
    }
}


//function called on each frame
GLvoid window_idle()
{


    glutPostRedisplay();
}
