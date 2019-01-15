#include<iostream>
#include<GL/glut.h>
#include <random>
#include <time.h>

using namespace std;


class Obstacle{
public:
    int PosX;
    int PosY;
    double PosZ;

    Obstacle(int i){
        PosX = rand()%3-1;;
        PosY = rand()%2;
        PosZ = -30- i*(rand()%100);
    }
    void updatePositions(double z, int i){
        srand(time(NULL));
        PosX = rand()%3-1;
        PosY = rand()%2;
        PosZ = z- 30 - (i+1)*(rand()%100);
        cout<< PosX << " "<<PosY<<" "<<PosZ<<endl;
    }

    void display(){
        glPushMatrix();
        glTranslated(PosX,PosY,PosZ);
        glutSolidSphere(0.5,50,50);
        glPopMatrix();
    }

};



