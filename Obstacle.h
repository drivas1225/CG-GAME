
#include<iostream>
#include<GL/glut.h>
#include <random>
#include <time.h>
#include <ctime>

using namespace std;


class Obstacle{
public:
    int PosX;
    double PosY;
    double PosZ;
    bool exploited;
    GLUquadricObj *sphere = NULL;
    float alpha = 0.0;

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
        //cout<< PosX << " "<<PosY<<" "<<PosZ<<endl;
        exploited = false;
        alpha = 0.0;
    }

    void display(double t){
        if(!exploited){
            glPushMatrix();
            //if(PosY>0) glColor3f(0,0,1);
            //else glColor3f(1,1,1);
            if(t>=10){
                double x2 = 1.5*(sin(alpha*3.1416/180));
                alpha += 300*0.01;
                PosX = x2;
            }

            glTranslated(PosX,PosY,PosZ);



            sphere = gluNewQuadric();
            gluQuadricDrawStyle(sphere, GLU_FILL);
            gluQuadricTexture(sphere, 1);
            gluQuadricNormals(sphere, GLU_SMOOTH);
            gluSphere(sphere,0.5,50,50);
            gluDeleteQuadric(sphere);
            //glutSolidSphere(0.5,50,50);
            glPopMatrix();
        }
    }

};




