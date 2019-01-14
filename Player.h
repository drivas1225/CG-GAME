#include<iostream>
#include "math.h"
#include<GL/glut.h>

using namespace std;

class Player {

private:
  double PosX;
  double PosY;
  double PosZ;
  double Jump;
  double alpha = 0;
  int cantpoints = 50;
  double angulo = 360/cantpoints;

public:
    Player(){
        PosX = 0;
        PosY = 0;
        PosZ = 0;
    }

    display(){
        glPushMatrix();
        double y2 = 4*(cos(alpha*3.1416/180));
        if (y2<0) y2=y2*-1;
        alpha = alpha + angulo*0.01 ;
        PosY = y2;
        glTranslated(PosX,PosY,PosZ);
        glColor3f(1.0,1.0,1.0);
        glutSolidTeapot(1);
        glPopMatrix();
    }

    void move(int key){
        glPushMatrix();
        switch (key)
        {
        case GLUT_KEY_UP:
            //PosY++;
            break;

        case GLUT_KEY_DOWN:
            PosY--;
            glutPostRedisplay();			// et on demande le réaffichage.
            break;

        case GLUT_KEY_LEFT:
            glutPostRedisplay();			// et on demande le réaffichage.
            break;

        case GLUT_KEY_RIGHT:
            glutPostRedisplay();			// et on demande le réaffichage.
            break;
        }
        glPopMatrix();
    }


};
