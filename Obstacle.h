
#include<iostream>
#include<GL/glut.h>
#include <random>
#include <time.h>

using namespace std;


class Obstacle{
public:
    int PosX;
    double PosY;
    double PosZ;
    bool exploited;

    Obstacle(int i){
        PosX = rand()%3-1;;
        PosY = rand()%2;
        PosZ = -30- i*(rand()%100);
        exploited = false;
    }
    void updatePositions(double z, int i){
        srand(time(NULL));
        PosX = rand()%3-1;
        PosY = rand()%2;
        if(PosY>0) PosY = 1;
        PosZ = z- 30 - (i+1)*(rand()%100);
        cout<< PosX << " "<<PosY<<" "<<PosZ<<endl;
        exploited = false;
    }

    void display(){
        if(!exploited){
            glPushMatrix();
            glTranslated(PosX,PosY,PosZ);
            if(PosY>0) glColor3f(0,0,1);
            else glColor3f(1,1,1);

            glutSolidSphere(0.5,50,50);
            glPopMatrix();
        }
    }

};




