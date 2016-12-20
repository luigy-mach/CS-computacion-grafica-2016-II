/*********************************************************
**********************************************************
**** Universidad Nacional de San Agustín
**********************************************************
**** Algoritmo de brensenham para dibujar una linea
**********************************************************
**** autor: Luigy Machaca
**** curso: Computacion grafica
**********************************************************
*********************************************************/

#include <GL/glut.h>
#include <iostream>
#include <math.h>

using namespace std;

void bresenham_line(int x1,int y1,int x2,int y2)
{
 int x,y,dx,dy,dx1,dy1,px,py,xe,ye,i;
 dx=x2-x1;
 dy=y2-y1;
 dx1=fabs(dx);
 dy1=fabs(dy);
 px=2*dy1-dx1;
 py=2*dx1-dy1;
 if(dy1<=dx1)
 {
  if(dx>=0)
  {
   x=x1;
   y=y1;
   xe=x2;
  }
  else
  {
   x=x2;
   y=y2;
   xe=x1;
  }
  glVertex3f(x, y, 0.0);
  for(i=0;x<xe;i++)
  {
   x=x+1;
   if(px<0)
   {
    px=px+2*dy1;
   }
   else
   {
    if((dx<0 && dy<0) || (dx>0 && dy>0))
    {
     y=y+1;
    }
    else
    {
     y=y-1;
    }
    px=px+2*(dy1-dx1);
   }
   glVertex3f(x, y, 0.0);
  }
 }
 else
 {
  if(dy>=0)
  {
   x=x1;
   y=y1;
   ye=y2;
  }
  else
  {
   x=x2;
   y=y2;
   ye=y1;
  }
  glVertex3f(x, y, 0.0);
  for(i=0;y<ye;i++)
  {
   y=y+1;
   if(py<=0)
   {
    py=py+2*dx1;
   }
   else
   {
    if((dx<0 && dy<0) || (dx>0 && dy>0))
    {
     x=x+1;
    }
    else
    {
     x=x-1;
    }
    py=py+2*(dx1-dy1);
   }
   glVertex3f(x, y, 0.0);
  }
 }
}



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
      bresenham_line(0,0,-20,-50);
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
  glutCreateWindow("algoritmo bresenham");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
