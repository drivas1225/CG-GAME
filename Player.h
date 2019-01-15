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
    double alpha = 0;
    int cantpoints = 50;
    double angulo = 360/cantpoints;

    Player()
    {
        PosX = 0;
        PosY = 0;
        PosZ = 0;
    }

    void display(double dt)
    {

        glPushMatrix();
        if(jump){
            double y2 = 1.5*(sin(alpha*3.1416/180));
            //if (y2<0) y2=y2*-1;
            alpha = alpha + 300* dt ;
            PosY = y2;
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
        //gluLookAt(PosX, PosY, PosZ+1, PosX, PosY, PosZ, 0, 1, 0);

        PosZ -= 30*dt;
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


};
