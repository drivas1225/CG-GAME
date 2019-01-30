#include<iostream>
#include<GL/glut.h>
#include <random>
#include <time.h>

using namespace std;


class Terrain{
public:
    double PosZ;
    bool to_display;

    Terrain(int i){
        PosZ = 1.5*i;
    }

    void updatePositions(){
        //srand(time(NULL));
        PosZ = PosZ-50 ;
        cout<<PosZ<<endl;

    }

    void display(int non_display=0){
		//if(!to_display){
            glColor3f(1,1,1);
         	glNormal3f(0, 1, 0);
		    glBegin(GL_QUADS);
		    glTexCoord2f(1.0, 1.0)  ;glVertex3d(-0.65, -0.5,PosZ-1);
		    glTexCoord2f(0.0, 1.0)  ;glVertex3d(-2, -0.5,PosZ-1);
		    glTexCoord2f(0.0, 0.0f) ;glVertex3d(-2, -0.5,-0.5-PosZ);
		    glTexCoord2f(1.0, 0.0f) ;glVertex3d(-0.65, -0.5,-0.5-PosZ);
		    glEnd();

	        glNormal3f(0, 1, 0);
		    glBegin(GL_QUADS);
		    glTexCoord2f(1.0, 1.0); glVertex3d(0.65, -0.5,PosZ - 1);
		    glTexCoord2f(0.0, 1.0); glVertex3d(-0.65, -0.5,PosZ - 1);
		    glTexCoord2f(0.0, 0.0f);glVertex3d(-0.65, -0.5,-0.5-PosZ);
		    glTexCoord2f(1.0, 0.0f);glVertex3d(0.65, -0.5,-0.5-PosZ);
		    glEnd();


	        glNormal3f(0, 1, 0);
	        glBegin(GL_QUADS);
	        glTexCoord2f(1.0, 1.0)  ;glVertex3d(2, -0.5,PosZ - 1);
	        glTexCoord2f(0.0, 1.0)  ;glVertex3d(0.65, -0.5,PosZ - 1);
	        glTexCoord2f(0.0, 0.0f) ;glVertex3d(0.65, -0.5,-0.5-PosZ);
	        glTexCoord2f(1.0, 0.0f) ;glVertex3d(2, -0.5,-0.5-PosZ);
	        glEnd();

    //}
    }


};
