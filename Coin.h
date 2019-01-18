
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
    int r = 0;

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
        PosZ = z- 50 -(rand()%100) - r;
        r++;
        if(r>=10)r=0;
        cout<<"The final possition of z"<<PosZ<<endl;
        gotcha = false;
    }

    void display(){
        if(!gotcha){
            glPushMatrix();
            glTranslated(PosX,PosY,PosZ);
            //if(PosY>0) glColor3f(0,0,1);
            /*else*/ glColor3f(0.62,0.56,0.0038);

            glutSolidCube(0.3);
            //glutSolidSphere(0.3,50,50);
            glPopMatrix();
        }

    }

};



