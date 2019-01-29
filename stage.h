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
        tam_stage = 4;

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
            glTexCoord2f(3*cord_text_x, cord_text_y     ); glVertex3f(tam_stage, -1          ,z);
            glTexCoord2f(3*cord_text_x, 2*cord_text_y   ); glVertex3f(tam_stage, tam_stage   ,z);
            glTexCoord2f(2*cord_text_x, 2*cord_text_y   ); glVertex3f(tam_stage, tam_stage   ,distTodisplay);
            glTexCoord2f(2*cord_text_x, cord_text_y     ); glVertex3f(tam_stage, -1          ,distTodisplay);
            glEnd();

            ///left
            glBegin(GL_QUADS);
            glTexCoord2f(cord_text_x , cord_text_y      ); glVertex3f(-tam_stage, -1         ,distTodisplay);
            glTexCoord2f(cord_text_x , 2*cord_text_y    ); glVertex3f(-tam_stage, tam_stage  ,distTodisplay);
            glTexCoord2f(0.0f        , 2*cord_text_y    ); glVertex3f(-tam_stage, tam_stage  ,z);
            glTexCoord2f(0.0f        , cord_text_y      ); glVertex3f(-tam_stage, -1         ,z);
            glEnd();

            ///top
            glBegin(GL_QUADS);
            glTexCoord2f(2*cord_text_x, 2*cord_text_y   ); glVertex3f( tam_stage, tam_stage  ,distTodisplay);
            glTexCoord2f(2*cord_text_x, 3*cord_text_y   ); glVertex3f( tam_stage, tam_stage  ,z);
            glTexCoord2f(cord_text_x  , 3*cord_text_y   ); glVertex3f(-tam_stage, tam_stage  ,z);
            glTexCoord2f(cord_text_x  , 2*cord_text_y   ); glVertex3f(-tam_stage, tam_stage  ,distTodisplay);
            glEnd();

            ///front
            glBegin(GL_QUADS);
            glTexCoord2f(2*cord_text_x, cord_text_y     ); glVertex3f( tam_stage, -1         ,distTodisplay);
            glTexCoord2f(2*cord_text_x, 2*cord_text_y   ); glVertex3f( tam_stage, tam_stage  ,distTodisplay);
            glTexCoord2f(cord_text_x  , 2*cord_text_y   ); glVertex3f(-tam_stage, tam_stage  ,distTodisplay);
            glTexCoord2f(cord_text_x  , cord_text_y     ); glVertex3f(-tam_stage, -1         ,distTodisplay);
            glEnd();

        glPopMatrix();

    }

};



