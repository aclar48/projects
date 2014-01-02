#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include "bitmap.h"

#define WIN_X        1244.444
#define WIN_Y        700.0
#define F           2000.0
#define N              1.0
#define MSEC            33
#define AXIS_LENGTH 1000.0
#define EYEx           10.0
#define EYEy           10.0
#define EYEz           10.0
#define GAZEx          0.0
#define GAZEy          0.0
#define GAZEz          5.0
#define UPx            0.0
#define UPy            0.0
#define UPz            1.0
#define VIEW_ANGLE    80.0
#define ASPECT_RATIO   1.0

#define NUM_TEXTURES 5

BITMAPINFO *TexInfo[NUM_TEXTURES];
GLubyte *TexBits[NUM_TEXTURES];
static GLuint texture[NUM_TEXTURES];
static GLUquadric* myQuadric ;        /* Reference to a quadric sphere */
static GLfloat spin = 0;    //spin the sphere
static GLfloat tip = 0;     //tip the teapot

GLfloat t = 0.0 ;
GLfloat theta = 0.0;
GLfloat ambientlight[] = {0.2,0.2,0.2,1.0} ;
GLfloat diffuselight[] = {0.8,0.8,0.8,1.0} ;
GLfloat specular[] = {1.0,1.0,1.0,1.0} ;
GLfloat specref[] = {1.0,1.0,1.0,1.0} ;
/*
 * Deal with errors from the gluquadratic
 * Author: Taken from class notes
 */
void errorCallback(GLenum errorCode) {
const GLubyte *estring ;

  estring = gluErrorString(errorCode) ;
  fprintf(stderr,"Quadric Error: %s\n",estring) ;
  exit(0) ;
}
/*
 * Initalize the textures
 * Author: Taken from class website
 */
void InitTex(GLint tex) {

    glGenTextures(tex,&texture[tex]);
    glBindTexture(GL_TEXTURE_2D,texture[tex]);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,TexInfo[tex]->bmiHeader.biWidth,TexInfo[tex]->bmiHeader.biHeight,0,GL_RGB,GL_UNSIGNED_BYTE,TexBits[tex]);
}
/*
 * Draw a textureable square
 * Author: Alex Clarke
 */
void drawQuadFace() {
    glBegin(GL_QUADS) ;
    glNormal3d(0.0,0.0,1.0);
    glTexCoord2f(0.0,0.0) ; glVertex3f(0.0,0.0,0.0) ;
    glTexCoord2f(0.0,1.0) ; glVertex3f(0.0,1.0,0.0) ;
    glTexCoord2f(1.0,1.0) ; glVertex3f(0.0,1.0,0.0) ;
    glTexCoord2f(1.0,0.0) ; glVertex3f(0.0,0.0,0.0) ;

    glTexCoord2f(0.0,0.0) ; glVertex3f(0.0,0.0,0.0) ;
    glTexCoord2f(0.0,1.0) ; glVertex3f(0.0,1.0,0.0) ;
    glTexCoord2f(1.0,1.0) ; glVertex3f(1.0,1.0,0.0) ;
    glTexCoord2f(1.0,0.0) ; glVertex3f(1.0,0.0,0.0) ;

    glEnd() ;
}
/*
 * Draw a solid cube
 * Author: Author Alex Clarke
 */
void drawCube() {
    glBegin(GL_QUADS);
    glNormal3d(0.0,1.0,0.0);
    glTexCoord2f(0.0,0.0) ; glVertex3f(1.0,1.0,-1.0) ;  //front of the cube
    glTexCoord2f(0.0,1.0) ; glVertex3f(-1.0,1.0,-1.0) ;
    glTexCoord2f(1.0,1.0) ; glVertex3f(-1.0,1.0,1.0) ;
    glTexCoord2f(1.0,0.0) ; glVertex3f(1.0,1.0,1.0) ;

    glNormal3d(0.0,-1.0,0.0);
    glTexCoord2f(0.0,0.0) ; glVertex3f(1.0,-1.0,1.0) ;  //back of the cube
    glTexCoord2f(0.0,1.0) ; glVertex3f(-1.0,-1.0,1.0) ;
    glTexCoord2f(1.0,1.0) ; glVertex3f(-1.0,-1.0,-1.0) ;
    glTexCoord2f(1.0,0.0) ; glVertex3f(1.0,-1.0,-1.0) ;

    glNormal3d(0.0,0.0,1.0);
    glTexCoord2f(0.0,0.0) ; glVertex3f(1.0,1.0,1.0) ;  //top of the cube
    glTexCoord2f(0.0,1.0) ; glVertex3f(-1.0,1.0,1.0) ;
    glTexCoord2f(1.0,1.0) ; glVertex3f(-1.0,-1.0,1.0) ;
    glTexCoord2f(1.0,0.0) ; glVertex3f(1.0,-1.0,1.0) ;

    glNormal3d(0.0,0.0,-1.0);
    glTexCoord2f(0.0,0.0) ; glVertex3f(1.0,-1.0,-1.0) ;  //bottom of the cube
    glTexCoord2f(0.0,1.0) ; glVertex3f(-1.0,-1.0,-1.0) ;
    glTexCoord2f(1.0,1.0) ; glVertex3f(-1.0,1.0,-1.0) ;
    glTexCoord2f(1.0,0.0) ; glVertex3f(1.0,1.0,-1.0) ;

    glNormal3d(1.0,0.0,0.0);
    glTexCoord2f(0.0,0.0) ; glVertex3f(-1.0,1.0,1.0) ;  //left of the cube
    glTexCoord2f(0.0,1.0) ; glVertex3f(-1.0,1.0,-1.0) ;
    glTexCoord2f(1.0,1.0) ; glVertex3f(-1.0,-1.0,-1.0) ;
    glTexCoord2f(1.0,0.0) ; glVertex3f(-1.0,-1.0,1.0) ;

    glNormal3d(-1.0,0.0,0.0);
    glTexCoord2f(0.0,0.0) ; glVertex3f(1.0,1.0,-1.0) ;  //right of the cube
    glTexCoord2f(0.0,1.0) ; glVertex3f(1.0,1.0,1.0) ;
    glTexCoord2f(1.0,1.0) ; glVertex3f(1.0,-1.0,1.0) ;
    glTexCoord2f(1.0,0.0) ; glVertex3f(1.0,-1.0,-1.0) ;

    glEnd();
}
/*
 * Draw a simple hollow cone
 * Author: Alex Clarke
 */
void drawCone() {
    GLfloat p1[3], p2[3], p3[3], p4[3], a[3], b[3], normal[3];
    GLfloat DeltaU = 2.0*M_PI/96.0;
    GLfloat DeltaV = 0.1;
        /* For the generic cone, u varies from 0 to 2PI and v from 0 to 1 */
    for (GLfloat u = 0.0 ; u < 2.0*M_PI ; u += DeltaU) {
        for (GLfloat v = 0.0 ; v < 1.0 ; v += DeltaV) {
                             /* Compute P(u0,v0)=(X(u0,v0),Y(u0,v0),Z(u0,v0)) */
          p1[0] = (1.0 - v)*cos(u) ;
          p1[1] = (1.0 - v)*sin(u) ;
          p1[2] = v ;

                 /* Compute P(u0,v0+dv)=(X(u0,v0+dv),Y(u0,v0+dv),Z(u0,v0+dv)) */
          p2[0] = (1.0 - (v + DeltaV))*cos(u) ;
          p2[1] = (1.0 - (v + DeltaV))*sin(u) ;
          p2[2] = v + DeltaV ;

               /* Compute P(u0+du,v0) = (X(u0+du,v0),Y(u0+du,v0),Z(u0+du,v0)) */
          p3[0] = (1.0 - v)*cos(u + DeltaU) ;
          p3[1] = (1.0 - v)*sin(u + DeltaU) ;
          p3[2] = v ;

        /* Compute P(u0+du,v0+dv)=(X(u0+du,v0+dv),Y(u0+du,v0+dv),Z(u0+du,v0+dv)) */
          p4[0] = (1.0 - (v + DeltaV))*cos(u + DeltaU) ;
          p4[1] = (1.0 - (v + DeltaV))*sin(u + DeltaU) ;
          p4[2] = v + DeltaV ;


          /* compute vectors a and b */
          a[0] = p1[0] - p3[0] ;
          a[1] = p1[1] - p3[1] ;
          a[2] = p1[2] - p3[2] ;

          b[0] = p1[0] - p2[0] ;
          b[1] = p1[1] - p2[1] ;
          b[2] = p1[2] - p2[2] ;

          /* compute normal through cross product */

          normal[0] = a[1]*b[2] - a[2]*b[1] ;
          normal[1] = a[2]*b[0] - a[0]*b[2] ;
          normal[2] = a[0]*b[1] - a[1]*b[0] ;

          GLfloat nl = 10.0*sqrt(pow(normal[0],2.0)+pow(normal[1],2.0)+pow(normal[2],2.0)) ;

          normal[0] /= nl ;
          normal[1] /= nl ;
          normal[2] /= nl ;

          glBegin(GL_TRIANGLES);
          glNormal3d(normal[0],normal[1],normal[2]);
            glTexCoord2f(0.0,0.0);
            glVertex3d(p1[0],p1[1],p1[2]) ;
            glTexCoord2f(1.0,0.0);
            glVertex3d(p2[0],p2[1],p2[2]) ;
            glTexCoord2f(0.5,1.0);
            glVertex3d(p3[0],p3[1],p3[2]) ;
         glEnd();

         /* compute vectors a and b */
         a[0] = p3[0] - p4[0] ;
         a[1] = p3[1] - p4[1] ;
         a[2] = p3[2] - p4[2] ;

         b[0] = p3[0] - p2[0] ;
         b[1] = p3[1] - p2[1] ;
         b[2] = p3[2] - p2[2] ;

         /* compute normal through cross product */

         normal[0] = a[1]*b[2] - a[2]*b[1] ;
         normal[1] = a[2]*b[0] - a[0]*b[2] ;
         normal[2] = a[0]*b[1] - a[1]*b[0] ;

         nl = 10.0*sqrt(pow(normal[0],2.0)+pow(normal[1],2.0)+pow(normal[2],2.0)) ;

         normal[0] /= nl ;
         normal[1] /= nl ;
         normal[2] /= nl ;
         glBegin(GL_TRIANGLES);
          glNormal3d(normal[0],normal[1],normal[2]);
              glTexCoord2f(0.0,0.0);
              glVertex3d(p3[0],p3[1],p3[2]) ;
              glTexCoord2f(1.0,0.0);
              glVertex3d(p4[0],p4[1],p4[2]) ;
              glTexCoord2f(0.5,1.0);
              glVertex3d(p2[0],p2[1],p2[2]) ;
          glEnd() ;
        }
    }
}

/*
 * Render a frame
 * Author: Alex Clarke
 */
void RenderScene(void) {

    GLfloat position[] = {0.0,0.0,12.0,1.0} ;     //set position of light source
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
    glColor3f(1.0,1.0,1.0);

    glLightfv(GL_LIGHT0,GL_POSITION,position) ;
    glutPostRedisplay() ;
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,texture[0]);
    glPushMatrix(); //Rug
    glTranslatef(-7.5f,-4.0f,-0.25f);
    glScalef(15.0f,7.5f,1.0f);
    drawQuadFace();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,texture[1]);
    glPushMatrix();      //Table leg 1
    glTranslatef(5.0f,-2.5f,2.5f);
    glScalef(0.175f,0.175f,2.5f);
    drawCube();
    glPopMatrix();

    glPushMatrix();     //Table leg 2
    glTranslatef(-5.0f,-2.5f,2.5f);
    glScalef(0.175f,0.175f,2.5f);
    drawCube();
    glPopMatrix();

    glPushMatrix();     //Table leg 3
    glTranslatef(5.0f,2.5f,2.5f);
    glScalef(0.175f,0.175f,2.5f);
    drawCube();
    glPopMatrix();

    glPushMatrix();     //Table leg 4
    glTranslatef(-5.0f,2.5f,2.5f);
    glScalef(0.175f,0.175f,2.5f);
    drawCube();
    glPopMatrix();

    glPushMatrix(); //Table top
    glTranslatef(0.0f,0.0f,5.0f);
    glScalef(5.175f,2.75f,0.05f);
    drawCube();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,texture[2]);
    glPushMatrix(); //Magic cone
    glTranslatef(2.5f,0.0f,5.0f);
    glScalef(1.0f,1.0f,2.0f);
    drawCone();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,texture[3]);
    glPushMatrix(); //Super Sphere
    glTranslatef(2.5f,0.0f,7.6f);
    glRotatef(23.0f,0.0f,1.0f,0.0f);
    glRotatef(spin,0.0,0.0,1.0);
    gluSphere(myQuadric,0.6,32,32);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glColor3f(0.0,0.0,0.75);
    glPushMatrix(); //Teapot orbiting the super sphere
    glTranslatef(2.5 + 2.5*cos(tip),2.5*sin(tip),7.6f + sin(tip));
    glRotatef(90.0f,1.0f,0.0,0.0f);
    glRotatef(spin,0.0f,1.0f,0.0f);
    glutSolidTeapot(0.25);
    glPopMatrix();

    glColor3f(0.5,0.0,0.5);
    glPushMatrix(); //Tippy Teapot of doom
    glTranslatef(-1.5f,0.0f,7.0f);
    glRotatef(90.0f,1.0f,0.0f,0.0f);
    glRotatef(180.0f,0.0f,1.0f,0.0f);
    glRotatef(-30.0f*sin(tip),0.0f,0.0f,1.0f);
    glutSolidTeapot(1.0);
    glPopMatrix();

    glColor3f(0.5,0.3,0.1);
    glPushMatrix(); //mug
    glTranslatef(-3.5f,0.0f,5.75f);
    glScalef(0.5f,0.5f,5.0f);
    glutSolidTorus(0.075,1.0,64,64);
    glPopMatrix();

    glPushMatrix(); //mug handle
    glTranslatef(-4.125f,0.0f,5.75f);
    glScalef(0.16f,0.25f,0.3f);
    glRotatef(90.0f,1.0f,0.0f,0.0f);
    glutSolidTorus(0.075,1.0,32,32);
    glPopMatrix();

    ++spin;
    if(spin > 360.0f)spin = 0.0f;
    tip += 0.05;
    if(tip > 360.0f)tip = 0.0f;



    glutSwapBuffers() ;
}
/*
 * Adjust camera
 * Author: Alex Clarke
 */
void TimerFunction(int value) {
    glMatrixMode(GL_PROJECTION) ;     /* Operation on the Projection matrix */
    glLoadIdentity() ;
    gluPerspective(VIEW_ANGLE,ASPECT_RATIO,N,F) ;     /* Define view volume */
    glMatrixMode(GL_MODELVIEW) ;       /* Operation on the modelview matrix */
    glLoadIdentity() ;
    gluLookAt(EYEx*cos(t),EYEy*sin(t),EYEz,GAZEx,GAZEy,GAZEz,UPx,UPy,UPz) ;
    glutTimerFunc(MSEC,TimerFunction,1) ;
    t += 0.01 ;
    theta += 0.01;
}
/*
 * Handle changing of screen size
 * Author: Alex Clarke
 */
void ChangeSize(int w, int h) {
    glViewport(0,0,(GLsizei) w,(GLsizei) h) ;
    glMatrixMode(GL_PROJECTION) ;
    glLoadIdentity() ;
    glOrtho((double)-WIN_Y/2,(double)WIN_X/2,(double)-WIN_Y/2,(double)WIN_Y/2,N,F);
    glMatrixMode(GL_MODELVIEW) ;
    glLoadIdentity() ;
}

/*
 * Handle keyboard input
 * Author: Alex Clarke
 */
void keyboard(unsigned char k, int x, int y) {
    switch(k) {
    case 'q': exit(0);  //exit program on 'q' pressed
            break;
    default: break;
    }
}
/*
 * Main method, generate points, setup opengl and start loop
 * Author: Alex Clarke
 */
int main(int argc, char** argv) {
    TexBits[0] = LoadDIBitmap(argv[1],&TexInfo[0]);
    TexBits[1] = LoadDIBitmap(argv[2],&TexInfo[1]);
    TexBits[2] = LoadDIBitmap(argv[3],&TexInfo[2]);
    TexBits[3] = LoadDIBitmap(argv[4],&TexInfo[3]);
    glutInit(&argc,argv) ;
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA) ;  /* Z-buffer */
    glutInitWindowSize((int)WIN_X,(int)WIN_Y) ;
    glutInitWindowPosition(0,0) ;
    glutCreateWindow(argv[0]) ;
    std::cout<< (myQuadric = gluNewQuadric())<<std::endl;
    gluQuadricCallback(myQuadric,GLU_ERROR,errorCallback);
    gluQuadricTexture(myQuadric,GL_TRUE) ;
    gluQuadricOrientation(myQuadric,GLU_OUTSIDE) ;
    gluQuadricNormals(myQuadric,GLU_SMOOTH) ;
    glutDisplayFunc(RenderScene) ;
    glutReshapeFunc(ChangeSize) ;
    glClearColor(0.0,0.0,0.0,1.0) ;
    glEnable(GL_DEPTH_TEST) ;                            /* Enable Z-buffer */
    glFrontFace(GL_CCW);
    glEnable(GL_NORMALIZE);
                                                     /* Force true normals */
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE) ;
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE) ;  /* Front @ back faces */
    glShadeModel(GL_SMOOTH) ;                             /* Gouraud shading */
    glEnable(GL_LIGHTING) ;
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientlight) ;
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuselight) ;
    glLightfv(GL_LIGHT0,GL_SPECULAR,specular) ;
    glEnable(GL_LIGHT0) ;
    glEnable(GL_COLOR_MATERIAL) ;
    glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,30) ;
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE) ;
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specref) ;
    InitTex(0);
    InitTex(1);
    InitTex(2);
    InitTex(3);
    glutTimerFunc(MSEC,TimerFunction,1) ;
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}
