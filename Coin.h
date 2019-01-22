
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
    GLint texture;

    Coin(){
        PosX = rand()%3-1;;
        PosY = rand()%2;
        PosZ = -50- (rand()%100);
        gotcha = false;
        texture = TextureManager::Inst()->LoadTexture("C:/spring/work space/CG-GAME/background.png", GL_BGR_EXT, GL_RGB);
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
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTranslated(PosX,PosY,PosZ);
            glColor3f(0.62,0.56,0.0038);
            glutSolidCube(0.3);
            glDisable(GL_TEXTURE);
            //glutSolidSphere(0.3,50,50);
            glPopMatrix();
        }

    }

};



