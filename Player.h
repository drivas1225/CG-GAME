#include<iostream>
#include "math.h"
#include<GL/glut.h>

using namespace std;

class Player
{

public:
    double PosX;
    double PosY;
    double PosZ;
    bool jump = false;
    bool slide = false;
    bool hit = false;
    double alpha = 0;
    int cantpoints = 50;
    double angulo = 360/cantpoints;

    Player()
    {
        PosX = 0;
        PosY = 0;
        PosZ = 0;
    }

    void display(double dt, bool GameOver)
    {

        glPushMatrix();
        if(hit){
            alpha += 300*dt;
            if (alpha >=180){
              hit = false;
              alpha = 0;
            }
        }
        if(jump){
            double y2 = 1.5*(sin(alpha*3.1416/180));
            //if (y2<0) y2=y2*-1;
            alpha = alpha + 300* dt ;
            if(!GameOver) PosY = y2;
            if (alpha >=180){
              jump = false;
              alpha = 0;
            }
        }
        if(slide && !jump){
            alpha = alpha + 300*dt;
            //glPushMatrix();
            glScaled(1,1/2,1);
            //glTranslated(PosX,PosY,PosZ);
            //glRotatef(45,1,1,0);
            //glTranslated(0,0,0);
            //glPopMatrix();
            if (alpha >=180){
              slide = false;
              alpha = 0;
            }
        }

        PosZ -= 30*dt*(!GameOver);
        glTranslated(PosX,PosY,PosZ);
        glRotatef(90,0,1,0);
        glColor3f(1.0,1.0,0);
        glutSolidTeapot(0.5);
        glPopMatrix();
    }

    void move(int key)
    {
        glPushMatrix();
        switch (key)
        {
        case GLUT_KEY_UP:
            jump = true;
            if(slide){
              alpha = 0;
              slide = false;
            }

            break;

        case GLUT_KEY_DOWN:
            slide = true;
            glutPostRedisplay();			// et on demande le réaffichage.
            break;

        case GLUT_KEY_LEFT:
            if(PosX >-1 ) PosX--;
            glutPostRedisplay();			// et on demande le réaffichage.
            break;

        case GLUT_KEY_RIGHT:
            if(PosX < 1) PosX++;
            glutPostRedisplay();			// et on demande le réaffichage.
            break;
        }
        glPopMatrix();
    }

    void hitObject(){
        hit = true;
        //alpha = 0;
    }

    void displayGameOver(){
        glPushMatrix();
        glColor4f(0.5F,0.0F,0.5F,0.1f);

        //glTranslated(PosX,PosY+2,PosZ-1);
        glBegin(GL_QUADS);
        glVertex3d(-1, 2,PosZ);
        glVertex3d(1, 2,PosZ);
        glVertex3d(1, 3,PosZ);
        glVertex3d(-1, 3,PosZ);
        glEnd();
        glPopMatrix();

    }


};
