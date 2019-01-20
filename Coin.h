
#include<iostream>
#include<GL/glut.h>
#include <random>
#include <time.h>

using namespace std;


class Coin{
public:
    int PosX;
    double PosY;
    double PosZ;
    bool gotcha;

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

            glutSolidCube(0.3);
            //glutSolidSphere(0.3,50,50);
            glPopMatrix();
        }

    }

};



