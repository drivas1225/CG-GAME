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
        if(hit && !jump){
            alpha += 600*dt;
            if (alpha >= 180){
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
            glScaled(1,1/2,1);
            if (alpha >=180){
              slide = false;
              alpha = 0;
            }
        }

        if(hit){
            glPushMatrix();

            glTranslated(PosX,PosY,PosZ);
            glColor4f(0.0f,0.0f,1.0f,0.0f);
            glutSolidSphere(0.5,10,10);
            glPopMatrix();
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
            //hit = false;
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
        glColor4f(1.0F,0.0F,0.0F,0.7f);

        glTranslated(PosX,PosY,PosZ-2);
        glBegin(GL_QUADS);
        glVertex2d(-1, 1);
        glVertex2d(1, 1);
        glVertex2d(1, 2);
        glVertex2d(-1, 2);
        glEnd();

        glPopMatrix();

    }


};
