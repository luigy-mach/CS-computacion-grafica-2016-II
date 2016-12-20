#include <GL/glut.h>
GLsizei MOUSEx=0, MOUSEy=0;
GLfloat SIDE=50;
GLfloat BLUE[3] = {0,0,1};

void drawSquare1()
{
    glColor3fv(BLUE);
    glBegin(GL_POLYGON);
        glVertex3f(MOUSEx, MOUSEy,0);
        glVertex3f(MOUSEx+SIDE, MOUSEy,0);
        glVertex3f(MOUSEx+SIDE, MOUSEy+SIDE,0);
        glVertex3f(MOUSEx, MOUSEy+SIDE,0);
    glEnd();
    glFlush();
}   

void display(void)
{   
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity(); 
    drawSquare1();
    glFlush();
}
void reshape(int w, int h)
{   
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
     //gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glOrtho(0.0,1368,768,0,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void spindisplay(void)
{       
    glutPostRedisplay();
}

void setX(int x)
{
    MOUSEx=x;
}

void setY(int y)
{
    MOUSEy=y;
}
void mouse(int btn, int state, int x, int y)
{
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)   
    {
        setX(x);
        setY(y);
        //drawSquare(MOUSEx,HEIGHT-MOUSEy);
        glutPostRedisplay();
    }
    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)   
    {
        exit(1);   // To Exit the Program
    }
}
int main(int argc, char **argv)
{   glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1366,768);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Moving squares");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutIdleFunc(spindisplay);
    glutMainLoop();
}
