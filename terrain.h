#include<iostream>
#include<GL/glut.h>
#include <random>
#include <time.h>

using namespace std;


class Ground{
public:
    double PosZ;
    bool to_display;

    stage(int i){
        PosZ = 1.5*i;
    }

    void updatePositions(double z){
        srand(time(NULL));
        PosX = rand()%3-1;
        PosY = rand()%2;
        if(PosY>0) PosY = 1.5;
        PosZ = z- 50 -(rand()%100);
        gotcha = false;
    }

    void display(int non_display=0){
		if(!to_display){
         	glNormal3f(0, 1, 0);
		    glBegin(GL_QUADS);
		    glTexCoord2f(1.0, 1.0);
		    glVertex3d(-0.8, -0.5,PosZ-1);
		    glTexCoord2f(0.0, 1.0);
		    glVertex3d(-2, -0.5,PosZ-1);
		    glTexCoord2f(0.0, 0.0f);
		    glVertex3d(-2, -0.5,PosZ);
		    glTexCoord2f(1.0, 0.0f);
		    glVertex3d(-0.8, -0.5,-0.5-PosZ);
		    glEnd();

	        glNormal3f(0, 1, 0);
		    glBegin(GL_QUADS);
		    glTexCoord2f(1.0, 1.0);
		    glVertex3d(0.65, -0.5,PosZ - 1);
		    glTexCoord2f(0.0, 1.0);
		    glVertex3d(-0.65, -0.5,PosZ - 1);
		    glTexCoord2f(0.0, 0.0f);
		    glVertex3d(-0.65, -0.5,-0.5-PosZ);
		    glTexCoord2f(1.0, 0.0f);
		    glVertex3d(0.65, -0.5,-0.5-PosZ);
		    glEnd();


	        glNormal3f(0, 1, 0);
	        glBegin(GL_QUADS);
	        glTexCoord2f(1.0, 1.0);
	        glVertex3d(2, -0.5,PosZ - 1);
	        glTexCoord2f(0.0, 1.0);
	        glVertex3d(0.65, -0.5,PosZ - 1);
	        glTexCoord2f(0.0, 0.0f);
	        glVertex3d(0.65, -0.5,-0.5-PosZ);
	        glTexCoord2f(1.0, 0.0f);
	        glVertex3d(2, -0.5,-0.5-PosZ);
	        glEnd();

    }


};
