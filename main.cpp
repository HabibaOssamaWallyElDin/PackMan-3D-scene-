#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <string>

#include <stdlib.h>
#include <windows.h>

void display();
void endDisplay();
void reshape(int w,int h);
void timer(int);
void line(float x1, float y1, float x2, float y2);
void triangle(float x1, float y1, float side);
void square(float x1, float y1, float side);
void circle(float radiusX, float radiusY, float translatX, float translatY, int startAngle, int endAngle, GLenum mode);
void pacman (float radiusX, float radiusY, float translatX, float translatY, int startAngle, int endAngle, GLenum mode);

char s1[] = "wakawaka.wav";
char s2[] = "pacman_death.wav";
char s3[] = "kolorai7.wav";

void init(){
    glClearColor(0.0,0.0,0.0,1.0);
    PlaySound(s1, NULL, SND_ASYNC);
}

int main(int argc,char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200,0);
    glutInitWindowSize(1200,800);

    glutCreateWindow("19100290-19101509-19102929");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,timer,0);
    init();

    glutMainLoop();
}
float angleRotaion = -90;

float mouth = 0;
bool flag = true;

float food = 0;

int dieCoount = 0;
float dieColor = 0;
float dieCenter = 0;
bool die = false;
float dieMouth = 0;

int soundCount = 0;

void endDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glLineWidth(40.0);

    glRotatef(angleRotaion,0,0,1);

    glColor3f(1,1-dieColor,0);

    pacman(300,300,-500+dieCenter,0,30-mouth+dieMouth,330+mouth-dieMouth,GL_POLYGON);

    glColor3f(0,0,0);

    circle(30,30,-400+dieCenter,230,0,360,GL_POLYGON);

    glFlush();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glLineWidth(40.0);

    glColor3f(0,0,1);

    line(-980, 900,980, 900);
    line(-980, 900-20,980, 900-20);

    line(-980, 900-100,980, 900-100);
    line(-980, 900-20-100,980, 900-20-100);


    line(-980, -850,980, -850);
    line(-980, -850-20,980, -850-20);

    line(-980, -850+100,980, -850+100);
    line(-980, -850-20+100,980, -850-20+100);

    glColor3f(1,0.69,0);

    square(0-food,0,100);
    square(280-food,0,100);
    square(560-food,0,100);

    glColor3f(1,0,0);

    triangle(840-food,0,100);

    glColor3f(0,0,0);

    glBegin(GL_POLYGON);
        glVertex2d(-1000, -500);
        glVertex2d(-1000, 500);
        glVertex2d(-500, 500);
        glVertex2d(-500, -500);
    glEnd();

    glColor3f(1,1-dieColor,0);

    pacman(300,400,-500+dieCenter,0,30-mouth,330+mouth,GL_POLYGON);

    glColor3f(0,0,0);

    circle(30,50,-400+dieCenter,230,0,360,GL_POLYGON);



    glFlush();
}
void pacman (float radiusX, float radiusY, float translatX, float translatY, int startAngle, int endAngle, GLenum mode) {

    glBegin(mode);
    glVertex2f(translatX, translatY);
    for(int i=startAngle;i<endAngle;i++)
    {
      float andgleRad = i*3.14/180;
      glVertex2f(cos(andgleRad)*radiusX + translatX,
                  sin(andgleRad)*radiusY + translatY);
    }
    glEnd();

}

void square(float x1, float y1, float side) {

    float halfside = side/2;

    glBegin(GL_POLYGON);
    glVertex2d(x1 + halfside, y1 + halfside);
    glVertex2d(x1 + halfside, y1 - halfside);
    glVertex2d(x1 - halfside+20, y1 - halfside);
    glVertex2d(x1 - halfside+20, y1 + halfside);
    glEnd();
}
void triangle(float x1, float y1, float side) {
    glBegin(GL_TRIANGLES);
    glVertex2f(x1+side/2, y1-side/2);
    glVertex2f(x1-side/2, y1-side/2);
    glVertex2f(x1, y1+side-side/2);
    glEnd();
}

void line(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
}
void circle(float radiusX, float radiusY, float translatX, float translatY, int startAngle, int endAngle, GLenum mode) {

   glBegin(mode);
   for(int i=startAngle;i<endAngle;i++)
   {
      float andgleRad = i*3.14/180;
      glVertex2f(cos(andgleRad)*radiusX + translatX,
                  sin(andgleRad)*radiusY + translatY);
   }
   glEnd();
}

void reshape(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1000,1000,-1000,1000);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(5,timer,0);

    if(dieCoount < 8) {
        if(flag){
            mouth += 1;
        }
        else {
            mouth -= 1;
        }

        if(mouth >= 30) {
            flag = false;
            dieCoount++;
        }
        if(mouth <= 0){
            flag = true;
            dieCoount++;
        }


        food += 6.5;
    } else {
        if(dieCenter == 0) {
            PlaySound(s3, NULL, SND_ASYNC);
        }
        if(dieColor < 1) {
            dieColor += 0.005;
        }
        if(dieCenter <= 500) {
            dieCenter += 5;
        } else {
            if(!die) {
                die = true;
                glutDisplayFunc(endDisplay);
            }
            else {
                if(soundCount == 110) {
                    PlaySound(s2, NULL, SND_ASYNC);
                }
                else if(soundCount >= 110) {
                    dieMouth +=3;
                }
            }
            soundCount++;
        }
        if(angleRotaion == 360) {
            angleRotaion =0;
        }
        angleRotaion++;
    }




}


