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
        double dist_piso = -0.505;

        glPushMatrix();

            //glColor3f(0.62,0.56,0.0038);
            glTranslated(0,0,PosZ);
            ///right
            glNormal3f(0,0,-10);
            glBegin(GL_QUADS);
            glTexCoord2f(3*cord_text_x, cord_text_y     ); glVertex3f(tam_stage, dist_piso   ,z);
            glTexCoord2f(3*cord_text_x, 2*cord_text_y   ); glVertex3f(tam_stage, tam_stage   ,z);
            glTexCoord2f(2*cord_text_x, 2*cord_text_y   ); glVertex3f(tam_stage, tam_stage   ,distTodisplay);
            glTexCoord2f(2*cord_text_x, cord_text_y     ); glVertex3f(tam_stage, dist_piso   ,distTodisplay);
            glEnd();

            ///left
            glNormal3f(0,0,-10);
            glBegin(GL_QUADS);
            glTexCoord2f(cord_text_x , cord_text_y      ); glVertex3f(-tam_stage, dist_piso  ,distTodisplay);
            glTexCoord2f(cord_text_x , 2*cord_text_y    ); glVertex3f(-tam_stage, tam_stage  ,distTodisplay);
            glTexCoord2f(0.0f        , 2*cord_text_y    ); glVertex3f(-tam_stage, tam_stage  ,z);
            glTexCoord2f(0.0f        , cord_text_y      ); glVertex3f(-tam_stage, dist_piso  ,z);
            glEnd();

            ///top
            glNormal3f(0,1,0);
            glBegin(GL_QUADS);
            glTexCoord2f(2*cord_text_x, 2*cord_text_y   ); glVertex3f( tam_stage, tam_stage  ,distTodisplay);
            glTexCoord2f(2*cord_text_x, 3*cord_text_y   ); glVertex3f( tam_stage, tam_stage  ,z);
            glTexCoord2f(cord_text_x  , 3*cord_text_y   ); glVertex3f(-tam_stage, tam_stage  ,z);
            glTexCoord2f(cord_text_x  , 2*cord_text_y   ); glVertex3f(-tam_stage, tam_stage  ,distTodisplay);
            glEnd();

            ///front
            glNormal3f(0,0,-1);
            glBegin(GL_QUADS);
            glTexCoord2f(2*cord_text_x, cord_text_y     ); glVertex3f( tam_stage, dist_piso  ,distTodisplay);
            glTexCoord2f(2*cord_text_x, 2*cord_text_y   ); glVertex3f( tam_stage, tam_stage  ,distTodisplay);
            glTexCoord2f(cord_text_x  , 2*cord_text_y   ); glVertex3f(-tam_stage, tam_stage  ,distTodisplay);
            glTexCoord2f(cord_text_x  , cord_text_y     ); glVertex3f(-tam_stage, dist_piso  ,distTodisplay);
            glEnd();

            ///bottom
            //glNormal3f(0,1,0);
            glBegin(GL_QUADS);
            glTexCoord2f(2*cord_text_x, 0               ); glVertex3f( tam_stage, dist_piso  ,z+2);
            glTexCoord2f(2*cord_text_x, cord_text_y     ); glVertex3f( tam_stage, dist_piso  ,distTodisplay);
            glTexCoord2f(cord_text_x  , cord_text_y     ); glVertex3f(-tam_stage, dist_piso  ,distTodisplay);
            glTexCoord2f(cord_text_x  , 0               ); glVertex3f(-tam_stage, dist_piso  ,z+2);
            glEnd();


        glPopMatrix();

    }

};



