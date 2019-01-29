
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

    GLint texture;


    Coin(){
        PosX = rand()%3-1;;
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
            glColor3f(0.62,0.56,0.0038);
            if(extra_shield>7)glColor3f(0.0,0.0,1.0);
            glutSolidCube(0.3);
            glDisable(GL_TEXTURE);
            //glutSolidSphere(0.3,50,50);
            glPopMatrix();
        }

    }

};



