#include<iostream>
#include<GL/glut.h>
#include <random>
#include <time.h>
#include "TextureManager.h"

using namespace std;


class stage{
public:
    double PosZ;
    double tam_stage;

    stage(){
        PosZ = 0;
        tam_stage = 3;

    }

    void display(double z){

        double distTodisplay = z - 50;
        double cord_text_x = 1.0/4.0;
        double cord_text_y = 1.0/3.0;

        glPushMatrix();

            //glColor3f(0.62,0.56,0.0038);
            glTranslated(0,0,PosZ);
            ///right
            glBegin(GL_QUADS);
            glTexCoord2f(3*cord_text_x, cord_text_y     ); glVertex3f(tam_stage, 0           ,z);
            glTexCoord2f(3*cord_text_x, 2*cord_text_y   ); glVertex3f(tam_stage, tam_stage   ,z);
            glTexCoord2f(2*cord_text_x, 2*cord_text_y   ); glVertex3f(tam_stage, tam_stage   ,distTodisplay);
            glTexCoord2f(2*cord_text_x, cord_text_y     ); glVertex3f(tam_stage, 0           ,distTodisplay);
            glEnd();

            ///left
            glBegin(GL_QUADS);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(-tam_stage, 0          ,distTodisplay);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(-tam_stage, tam_stage  ,distTodisplay);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-tam_stage, tam_stage  ,z);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-tam_stage, 0          ,z);
            glEnd();

            ///up
            glBegin(GL_QUADS);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( tam_stage, tam_stage  ,distTodisplay);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( tam_stage, tam_stage  ,z);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-tam_stage, tam_stage  ,z);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-tam_stage, tam_stage  ,distTodisplay);
            glEnd();

            ///background face
            glBegin(GL_QUADS);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( tam_stage, 0          ,distTodisplay);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( tam_stage, tam_stage  ,distTodisplay);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-tam_stage, tam_stage  ,distTodisplay);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-tam_stage, 0          ,distTodisplay);
            glEnd();

        glPopMatrix();

    }

};



