#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Player.h"
#include "Obstacle.h"
#include "Coin.h"
#include <vector>


#include <GL/glut.h>
using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27

void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);

bool GameOver = false;

///Putaje
int SCORE = 0;


///Player
Player pl;

///coins
vector<Coin> coins;
int numCoins = 10;


///Obstacles
vector<Obstacle> obstacles;
int enemies = 5;


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





//dibuja un simple gizmo
void displayGizmo()
{
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex3d(-2, -1,-10-pl.PosZ);
    glVertex3d(2, -1,-10-pl.PosZ);
    glVertex3d(1.5, -1,pl.PosZ - 170);
    glVertex3d(-2, -1,pl.PosZ - 170);
    glEnd();
    }

//function called on each frame
GLvoid window_idle();


///////////////////////////////////////////////////////////////////////////////
//(1)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_special(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        //CamPosZ = CamPosZ - velCam;
        //CentZ = CentZ - velCam;
        pl.move(key);
        glutPostRedisplay();			// et on demande le réaffichage.
        break;

    case GLUT_KEY_DOWN:
        //CamPosZ = CamPosZ + velCam;
        //CentZ = CentZ + velCam;
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
    for(int i=0; i<enemies; i++){
        Obstacle obs(i);
        obstacles.push_back(obs);
    }
    for(int i=0; i<numCoins; i++){
    	Coin coin;
    	coins.push_back(coin);
    }

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("TP 2 : Transformaciones");


    initGL();
    init_scene();

    glutDisplayFunc(&window_display);

    glutReshapeFunc(&window_reshape);

    glutKeyboardFunc(&window_key);

    glutSpecialFunc(&callback_special);
    glutMouseFunc(&callback_mouse);
    glutMotionFunc(&callback_motion);

    //function called on each frame
    glutIdleFunc(&window_idle);

    glutMainLoop();

    return 1;
}



GLvoid initGL()
{
    GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };

    //enable light : try without it
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);
    //light 0 "on": try without it
    glEnable(GL_LIGHT0);

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
    time_h = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
    dt = float(time_h -timebase)/1000.0;// delta time
    timebase = time_h;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//funcion de transparencia
	glEnable(GL_BLEND);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);
    gluPerspective(45,1,0.1,100);
    //glTranslated(0,0,-30);

    ///Mover la esecena
    //gluLookAt(CamPosX,CamPosY,CamPosZ,CentX,CentY,CentZ,AngX,AngY,AngZ);
    gluLookAt(0, 1.5, pl.PosZ+5, 0, 0, pl.PosZ-5, 0, 1, 0);


        pl.display(dt,GameOver);
        displayGizmo();
        for(int i =0; i<obstacles.size(); i++){
            float dist = distancia_euclideana(pl,obstacles[i]);
            if(dist<0.75) {

                cout<<"GAME OVER!!! ->"<<dist<<endl;
                GameOver = true;
                pl.displayGameOver();
            }
            if(obstacles[i].PosZ > pl.PosZ+2){
                obstacles[i].updatePositions(pl.PosZ,i);
            }
            obstacles[i].display();
        }
        for(int i =0; i<obstacles.size(); i++){
            float dist = distancia_euclideana_coin(pl,coins[i]);
            if(dist<0.75) {
                if(!coins[i].gotcha){
                    SCORE++;
                    coins[i].gotcha = true;
                    cout<<"SCORE: "<<SCORE<<endl;
                }
            }
            if(coins[i].PosZ > pl.PosZ+2){
                coins[i].updatePositions(pl.PosZ);
            }
            coins[i].display();
        }


//    pl.move();
    /*dibujar aqui*/

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    //glViewport(0, 0, 0, 10);

    glDisable(GL_BLEND);

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
