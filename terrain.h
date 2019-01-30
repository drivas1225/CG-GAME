#include<iostream>
#include<GL/glut.h>
#include <random>
#include <time.h>

using namespace std;


class Terrain{
public:
    double PosZ;
    bool to_display;
    int non_display;

    Terrain(int i){
        PosZ = 2*i;
        non_display = 0;
    }

    void updatePositions(double t){
        //srand(time(NULL));
        PosZ = PosZ-50 ;
        if(t<3) non_display = 0;
        else{
	        srand(time(NULL));
	        non_display = rand()%4-0;
        }
        //cout<<PosZ<<endl;


    }

    void display(){
		//if(!to_display){
            if(non_display!=1){
                glNormal3f(0, 1, 0);
                glBegin(GL_QUADS);
                glTexCoord2f(1.0, 1.0)  ;glVertex3d(-0.65, -0.5,PosZ);
                glTexCoord2f(0.0, 1.0)  ;glVertex3d(-2, -0.5,PosZ);
                glTexCoord2f(0.0, 0.0f) ;glVertex3d(-2, -0.5,PosZ+2);
                glTexCoord2f(1.0, 0.0f) ;glVertex3d(-0.65, -0.5,PosZ+2);
                glEnd();
            }

            if(non_display!=2){
                glNormal3f(0, 1, 0);
                glBegin(GL_QUADS);
                glTexCoord2f(1.0, 1.0); glVertex3d(0.65, -0.5,PosZ);
                glTexCoord2f(0.0, 1.0); glVertex3d(-0.65, -0.5,PosZ);
                glTexCoord2f(0.0, 0.0f);glVertex3d(-0.65, -0.5,PosZ+2);
                glTexCoord2f(1.0, 0.0f);glVertex3d(0.65, -0.5,PosZ+2);
                glEnd();
            }

            if(non_display!=3){
                glNormal3f(0, 1, 0);
                glBegin(GL_QUADS);
                glTexCoord2f(1.0, 1.0)  ;glVertex3d(2, -0.5,PosZ);
                glTexCoord2f(0.0, 1.0)  ;glVertex3d(0.65, -0.5,PosZ);
                glTexCoord2f(0.0, 0.0f) ;glVertex3d(0.65, -0.5,PosZ+2);
                glTexCoord2f(1.0, 0.0f) ;glVertex3d(2, -0.5,PosZ+2);
                glEnd();
            }

    //}
    }


};
