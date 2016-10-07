 #include <GL/glut.h>

#include <iostream>
#include <math.h>

using namespace std;



void my_line(int x1, int y1,int x2, int y2){
  int x,y;
  float a;
  int valor;

  a=(y2-y1)/(x2-x1);
  for(x=x1;x<=x2;x++){
    y=(y1+a*(x-x1));
     glVertex3f(-x, -y, 0.0);
     cout<<":::"<<x<<"::-::"<<y<<endl;
  }

}


void display2()
{
  glBegin( GL_POINTS );
   my_line(0,0,26,26);
   my_line(0,0,20,50);
   my_line(0,0,-20,-50);
    
  glEnd();
}







void display()
{

  glClear( GL_COLOR_BUFFER_BIT );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  double ar = glutGet( GLUT_WINDOW_WIDTH ) / (double)glutGet( GLUT_WINDOW_HEIGHT );
  // glOrtho( -2 * ar, 2 * ar, -2, 2, -1, 1);
  glOrtho( -100, 100, -100, 100, -1, 1);

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity(); 

  glColor3ub( 255, 0, 0 );

  display2();

  glutSwapBuffers();

}




void init()
{
  glClearColor(0,0,0,0);
}

void reshape(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // glOrtho(-1, 1, -1, 1, -1,1);
  // glOrtho(-50, 50, -50, 50, -20,20);
  glOrtho(-100, 100, -100, 100, -1,1 );
  // glOrtho(glutGet( GLUT_WINDOW_WIDTH )/-3, glutGet( GLUT_WINDOW_WIDTH )/3, glutGet( GLUT_WINDOW_HEIGHT )/-3, glutGet( GLUT_WINDOW_HEIGHT )/3, -300, 300);
  glMatrixMode(GL_MODELVIEW);
}





int main(int argc, char **argv)
{


  int tam=600;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(tam, tam);
  glutCreateWindow("Hello2 OpenGL");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
