#include<iostream>
#include "math.h"
#include<GL/glut.h>
#include "TextureManager.h"

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
    double alpha2 = 0;
    int cantpoints = 50;
    double angulo = 360/cantpoints;
    int shields = 4;

    GLUquadricObj * sphere = NULL;
    GLint texture_shield;

    Player()
    {
        PosX = 0;
        PosY = 0;
        PosZ = 0;

    }
    void display_shield(){

        sphere = gluNewQuadric();
        glPushMatrix();
        glTranslated(PosX,PosY,PosZ);
        gluQuadricDrawStyle(sphere, GLU_FILL);
        gluQuadricTexture(sphere, 1);
        gluQuadricNormals(sphere, GLU_SMOOTH);
        gluSphere(sphere,0.7,10,10);
        gluDeleteQuadric(sphere);
        glPopMatrix();
    }

    void display(double dt, bool GameOver)
    {

        glPushMatrix();
        if(shields <= 0){
            hit = false;
            alpha2 = 0;
        }
        if(hit && !jump && shields > -1){
            if (alpha2 >= 180 || GameOver){
              hit = false;
              alpha2 = 0;
            }else{
                alpha2 += 300*dt;
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



        PosZ -= 30*dt*(!GameOver);
        glTranslated(PosX,PosY,PosZ);
        glRotatef(90,0,1,0);
        //glColor3f(0.0,1.0,1.0);
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
        if(shields > 0)shields--;
    }

    void displayGameOver(){


        glPushMatrix();
        //glColor3f(1.0F,0.0F,0.0F);

        glTranslated(0,0,PosZ+2);
        glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 1.0f); glVertex2d(1, 2);
        glTexCoord2f(0.0f, 1.0f); glVertex2d(-1, 2);
        glTexCoord2f(0.0f, 0.0f); glVertex2d(-1, 1);
        glTexCoord2f(1.0f, 0.0f); glVertex2d(1, 1);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        glPopMatrix();

    }


};

