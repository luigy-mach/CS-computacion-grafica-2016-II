#include <GL/glut.h>

void reshape(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-10, 10, -10, 10, -10, 10);
  //glOrtho(-300, 300, -300, 300, -300, 300);
  glMatrixMode(GL_MODELVIEW);
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1,1,1);
  glLoadIdentity();
  glBegin(GL_LINES);
  glVertex3f(-1,-2,0);
  glVertex3f(1,-1,0);

  glEnd();
  glFlush();
}



void init()
{
  glClearColor(0,0,0,0);
}





int main(int argc, char **argv)
{
  int n=3;
  int theta=0;
  int alpha=0;
  int *p=NULL;
  p=new int[3];
  int i;
  for(i=0;i<3;i++)
    p[i]=-1;
  




  int tam=600;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(20, 0);
  glutInitWindowSize(tam, tam);
  glutCreateWindow("Hello OpenGL");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}
