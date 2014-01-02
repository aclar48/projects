#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

#define WIN_X        1200.0
#define WIN_Y        900.0
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

using namespace std;

GLfloat t = 0.0 ;
GLfloat theta = 0.0;
GLfloat ambientlight[] = {0.0,0.0,0.3,1.0} ;
GLfloat diffuselight[] = {0.4,0.0,0.0,1.0} ;
GLfloat specular[] = {0.0,1.0,0.0,1.0} ;
GLfloat specref[] = {0.0,1.0,0.0,1.0} ;
vector<vector<vector<GLfloat> > > pts;  //list of points
vector<vector<GLfloat> > normals;   //list of normals
static int spin = 0;

/*
 * Calculate a series of points on a circle of given radius and store the point along with
 * its z value into a vector of points
 * Author: Alex Clarke
 */
void calcCircle(const double &r,const double &z) {
      vector<vector<GLfloat> > temppts;
    for(double u = 0.0; u < M_PI*2.0; u += 0.018 ) {
      vector<GLfloat> temp;
      temp.push_back(r*cos(u));
      temp.push_back(r*sin(u));
      temp.push_back(z);
      temppts.push_back(temp);
     }
    pts.push_back(temppts);
}
/*
 * Calculate the normals of each 4 pt section of the polygon mesh and store them
 * in a vector
 * Author: Alex Clarke
 */
void calcNormals() {
    GLfloat nl;
    GLfloat a[3] ;
    GLfloat b[3] ;
    GLfloat normal[3] ;
    for(int i = 0; i < pts.size()-1; ++i) {
        for(int j = 0; j < pts[0].size(); ++j) {
            b[0] = pts[i+1][j][0]; b[1] = pts[i+1][j][1]; b[2] = pts[i+1][j][2];
            a[0] = pts[i][j][0]; a[1] =pts[i][j][1]; a[2] = pts[i][j][2];
            normal[0] = a[1]*b[2] - a[2]*b[1] ;
            normal[1] = a[2]*b[0] - a[0]*b[2] ;
            normal[2] = a[0]*b[1] - a[1]*b[0] ;
            nl = sqrt(normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2]);
            normal[0] /= nl ;
            normal[1] /= nl ;
            normal[2] /= nl ;
            vector<GLfloat> temp;
            temp.push_back(normal[0]); temp.push_back(normal[1]); temp.push_back(normal[2]);
            normals.push_back(temp);
        }
    }
}
/*
 * Load in points from a file and get them ready to be rotated
 * Author: Alex Clarke
 */
void load() {
    ifstream file("file.txt");
    string line;
    int i = 0;
    if(file.is_open()) {
         while(getline(file,line)) {
             istringstream s1(line);
            double x,z;
            if( ! (s1 >> x >> z >> z)) return;
            calcCircle(x/4,z/4);
            i++;
        }
     }
    calcNormals();

}
/*
 * Render a frame
 * Author: Alex Clarke
 */
void RenderScene(void) {
    GLfloat position[] = {0.0,0.0,30,1.0} ;     //set position of light source
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
    glPushMatrix();
    glRotated((GLdouble)spin,0.0,1.0,1.0) ; //move the light source around the x and z axis
    glLightfv(GL_LIGHT0,GL_POSITION,position) ;
    spin = (spin +2) % 360; //rotate the light
    glPopMatrix();
    glutPostRedisplay() ;
    glColor3f(1.0,1.0,1.0) ;    //set the colour of the object
    for(int i = 0; i < pts.size()-1; ++i) {
        for(int j = 0; j < pts[0].size(); ++j) {        //loop through the set of points
            vector<GLfloat> tempNormal = normals[i+j];  //get the normal
            glBegin(GL_TRIANGLES) ;     //generate the first polygon
                glNormal3d(tempNormal[0],tempNormal[1],tempNormal[2]);

                glVertex3d(pts[i][j][0],pts[i][j][1],pts[i][j][2]);
                if(j < pts[0].size()-1) glVertex3d(pts[i][j+1][0],pts[i][j+1][1],pts[i][j+1][2]);   //1 to 2
                else glVertex3d(pts[i][0][0],pts[i][0][1],pts[i][0][2]);

                if(j < pts[0].size()-1)   glVertex3d(pts[i+1][j+1][0],pts[i+1][j+1][1],pts[i+1][j+1][2]); //4 to 1
                else glVertex3d(pts[i+1][0][0],pts[i+1][0][1],pts[i+1][0][2]);
                glVertex3d(pts[i][j][0],pts[i][j][1],pts[i][j][2]);

                if(j < pts[0].size()-1) {
                    glVertex3d(pts[i][j+1][0],pts[i][j+1][1],pts[i][j+1][2]);
                    glVertex3d(pts[i+1][j+1][0],pts[i+1][j+1][1],pts[i+1][j+1][2]); //2 to 4
                }
                else {
                    glVertex3d(pts[i][0][0],pts[i][0][1],pts[i][0][2]);
                    glVertex3d(pts[i+1][0][0],pts[i+1][0][1],pts[i+1][0][2]);
                }
            glEnd() ;

            glBegin(GL_TRIANGLES) ; //generate the second polygon
                glNormal3d(tempNormal[0],tempNormal[1],tempNormal[2]);

                glVertex3d(pts[i][j][0],pts[i][j][1],pts[i][j][2]);
                glVertex3d(pts[i+1][j][0],pts[i+1][j][1],pts[i+1][j][2]);  //1 to 3

                if(j < pts[0].size()-1)   glVertex3d(pts[i+1][j+1][0],pts[i+1][j+1][1],pts[i+1][j+1][2]); //4 to 1
                else glVertex3d(pts[i+1][0][0],pts[i+1][0][1],pts[i+1][0][2]);
                glVertex3d(pts[i][j][0],pts[i][j][1],pts[i][j][2]);

                if(j < pts[0].size()-1) {
                    glVertex3d(pts[i+1][j][0],pts[i+1][j][1],pts[i+1][j][2]);
                    glVertex3d(pts[i+1][j+1][0],pts[i+1][j+1][1],pts[i+1][j+1][2]); //3 to 4
                }
                else {
                    glVertex3d(pts[i+1][j][0],pts[i+1][j][1],pts[i+1][j][2]);
                    glVertex3d(pts[i+1][0][0],pts[i+1][0][1],pts[i+1][0][2]);
                }
            glEnd();
        }
    }
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
    gluLookAt(EYEx*cos(t),EYEy*sin(t),EYEz*sin(theta),GAZEx,GAZEy,GAZEz,UPx,UPy,UPz) ;
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
    load();
    glutInit(&argc,argv) ;
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA) ;  /* Z-buffer */
    glutInitWindowSize((int)WIN_X,(int)WIN_Y) ;
    glutInitWindowPosition(0,0) ;
    glutCreateWindow(argv[0]) ;
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
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE) ;
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specref) ;
    glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,30) ;
    glutTimerFunc(MSEC,TimerFunction,1) ;
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}
