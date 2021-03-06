
#include<iostream>
#include<GL/glut.h>
#include <random>
#include <time.h>
#include "TextureManager.h"

using namespace std;


class Coin{
public:
    int PosX;
    double PosY;
    double PosZ;
    bool gotcha;
    int extra_shield = rand()%10;
    GLUquadricObj *sphere= NULL;



    Coin(){
        PosX = rand()%3-1;
        PosY = rand()%2;
        PosZ = -50- (rand()%100);
        gotcha = false;
    }
    void updatePositions(double z){
        srand(time(NULL));
        PosX = rand()%3-1;
        PosY = rand()%2;
        if(PosY>0) PosY = 1.5;
        PosZ = z- 50 -(rand()%100);
        gotcha = false;
    }

    void display(){

        if(!gotcha){
            glPushMatrix();
            glTranslated(PosX,PosY,PosZ);
            //glColor3f(0.62,0.56,0.0038);
            //if(extra_shield>8)glColor3f(0.0,0.0,1.0);
           /*glRotatef(-90, 1, 0, 0);
            cylinder = gluNewQuadric();
            gluQuadricDrawStyle(cylinder, GLU_FILL);
            gluQuadricTexture(cylinder, TRUE);
            gluQuadricNormals(cylinder, GLU_SMOOTH);
            gluCylinder(cylinder,0.2,0.2,0.2,30,30);
            gluDeleteQuadric(cylinder);*/

            sphere = gluNewQuadric();
            gluQuadricDrawStyle(sphere, GLU_FILL);
            gluQuadricTexture(sphere, 1);
            gluQuadricNormals(sphere, GLU_SMOOTH);
            gluSphere(sphere,0.15,50,50);
            gluDeleteQuadric(sphere);
            //glutSolidCube(0.15);
            //glutSolidSphere(0.15,30,30);
            //glDisable(GL_TEXTURE);
            //glutSolidSphere(0.3,50,50);
            glPopMatrix();
        }

    }

};



