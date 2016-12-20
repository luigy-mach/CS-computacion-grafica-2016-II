#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <string>

using namespace std;


#define ALTO 600
#define ANCHO 400


#define pi 3.1415


int alto=600;
int ancho=400;

int Cordx=1000;
int Cordy=1000;

bool band = false;
bool cerrado = false;

bool distance(int px1 ,int py1, int px2 ,int py2){
  int distancia = sqrt(pow(px1 - px2 ,2)+pow(py1 - py2,2)); 
  if (distancia < 100)
	 return true;
  else 
	return false;
}


struct Punto{
  GLdouble x;
  GLdouble y;
  Punto(){}
  Punto(float _x, float _y)
  {
	x=_x;
	y=_y;
  }
  Punto & operator=(Punto& _o){
	x=_o.x;
	y=_o.y;
	return *this;
  }

}punto ;


vector<Punto> puntos;
Punto* centro = NULL;



void mouse(int boton,int estado,int x,int y)
{
  if(boton == GLUT_LEFT_BUTTON)
  {
    if(estado == GLUT_UP)
    { 
      band = false;
      punto.x = x;
      punto.y = alto-y;
      puntos.push_back(punto);

      glBegin(GL_POINTS);
        glVertex2d(punto.x,punto.y);
      glEnd();
      cout<<punto.x<<" "<<punto.y<<endl;
    }
  }
  if(boton == GLUT_RIGHT_BUTTON)
  {
	//finalizar poligono
    if(estado == GLUT_UP)
    { 
      band = false;
      punto.x = x;
      punto.y = alto-y;
      puntos.push_back(punto);

      glBegin(GL_POINTS);
        glVertex2d(punto.x,punto.y);
      glEnd();
      cout<<punto.x<<" "<<punto.y<<endl;
    }
  }


  glutPostRedisplay();
}



Punto* PuntoCentral()
{
  int tam = puntos.size();
  int xMin = puntos[0].x;
  int xMax = puntos[0].x;
  int yMin = puntos[0].y;
  int yMax = puntos[0].y;

  for(int i=1;i<tam;i++){
    if(puntos[i].x <= xMin) 
	xMin = puntos[i].x;
    else if(puntos[i].x >= xMax) 
	xMax = puntos[i].x; 

    if(puntos[i].y <= yMin) 
	yMin = puntos[i].y;
    else if(puntos[i].y >= yMax) 
	yMax = puntos[i].y; 
  }

  cout<<"*****************************"<<endl;

  static Punto p1 ;
  p1.x = (xMax + xMin)/2;
  p1.y = (yMax + yMin)/2;


  return &p1 ;

}

void edgedetect(GLdouble x1,GLdouble y1,GLdouble x2,GLdouble y2,int *le,int *re)
{
            float mx,x,temp;
            int i;
            if((y2-y1)<0)    // if second point is below first point interchange them
            {
              temp=x1;x1=x2;x2=temp;
              temp=y1;y1=y2;y2=temp;
            }
              if((y2-y1)!=0)      // if denominator is zero we can't find slope
                        mx=(x2-x1)/(y2-y1);
            else
                        mx=x2-x1;    // y2-y1=0 implies line is horizontal
            x=x1;
            for(i=y1;i<y2;i++)        // starting from x1,y1 add slope mx to x
            {                                  // and round it to find the next point on the
                                                // line. For that particular scan line i
                        if(x<le[i])         // insert the x value into either le or re.
                                    le[i]=x; // Initially both le and re will contain same
                                                // value...
                        if(x>re[i])         // in the next time for the other edge
                                    re[i]=x; // either le or re will change
                        x+=mx;            // NOTE: le and re are integer arrays and x
            }                                  // is float so automatic type conversion.
}

void drawpixel(int x,int y,int color)
{

   switch(color){
	case '0':       glColor3f(1.0,0.0,0.0);
	case '1':       glColor3f(0.0,1.0,0.0);
	case '2':       glColor3f(0.0,1.0,1.0);
	case '3':       glColor3f(1.0,0.0,1.0);
	default : cout<<"color invalido"<<endl;
   }
    
   glBegin(GL_POINTS);
   glVertex2i(x,y);
   glEnd();
}



void scanfill(int color)//float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4,float x5,float y5)
{
            int le[500],re[500];
            int i,y;
            for(i=0;i<500;i++)   // initialize le and re array values
            {
                        le[i]=500;
                        re[i]=0;
            }
            int tam=(int)puntos.size();
            for(int i=0;i<tam-1;i++)
            {
              edgedetect(puntos[i].x,puntos[i].y,puntos[i+1].x,puntos[i+1].y,le,re);    // call edge detect four times  
            }
            edgedetect(puntos[tam].x,puntos[tam].y,puntos[0].x,puntos[0].y,le,re);
            /*edgedetect(x2,y2,x3,y3,le,re);    // once for each edge.
            edgedetect(x3,y3,x4,y4,le,re);
            edgedetect(x4,y4,x5,y5,le,re);
            edgedetect(x5,y5,x1,y1,le,re);*/

        for(y=0;y<500;y++)        // for every scan line with value y
        {
           if(le[y]<=re[y])            // refer to le and re arrays to see if a part
                        for(i=le[y]+1;i<re[y];i++) // of the scanline is inside polygon
                                    drawpixel(i,y,color);       // if so draw a horizontal line from
        }                                                              // left edge to right edge
}


void pintar()
{
    int color;
    cout<<"0 - rojo"<<endl;
    cout<<"1 - verde"<<endl;
    cout<<"2 - celeste"<<endl;
    cout<<"3 - rosado"<<endl;
    cout<<"escoge el color"<<endl;
    cin
    cout<<"------------------------"<<endl;>>color;

    glClear(GL_COLOR_BUFFER_BIT);
    int tam=(int)puntos.size();
    glBegin(GL_LINE_LOOP);  
       for(int i=0;i<tam;i++)
       {
          glVertex2f(puntos[i].x,puntos[i].y);
       }
    glEnd();
   scanfill(color);//x1,y1,x2,y2,x3,y3,x4,y4,x5,y5);      
   glFlush();   
}


void trasladar(void){
  int distX,distY;
  int cambioX, cambioY;
  int XP,YP;
  //cout<<"Escoge distancia"<<endl;
  cout<<"Traslaccion de X en : ";
  cin>>distX;
  cout<<"Traslaccion de Y en : ";
  cin>>distY;
  cout<<endl;

  (*centro).x += distX;
  (*centro).y += distY;

  //cout<<"nuevo centro: "<<(*centro).x<<" "<<(*centro).y<<endl;

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0,1.0,1.0);   
  glLineWidth(2.0);
  int tam = puntos.size();

  XP = puntos[0].x;
  YP = puntos[0].y;

  glBegin(GL_LINES);
    for(int i=1;i<tam;i++){

      cambioX = XP + distX;
      cambioY = YP + distY;

      puntos[i-1].x = cambioX;
      puntos[i-1].y = cambioY;
      
      glVertex2d( cambioX , cambioY );
      glVertex2d(puntos[i].x + distX ,puntos[i].y + distY);

      XP = puntos[i].x;
      YP = puntos[i].y;
    }
    puntos[tam-1].x += distX;
    puntos[tam-1].y += distY;

    glVertex2d(puntos[tam-1].x ,puntos[tam-1].y );
    glVertex2d(puntos[0].x ,puntos[0].y);
  glEnd();
  return;

}

void escalar(void){
  float escX,escY;
  int XP, YP,X2P,Y2P;
  int actX, actY;

  
  cout<<"escala en X: ";
  cin>>escX;
  cout<<"escala en Y: ";
  cin>>escY;
  cout<<endl;

  if(escX == 0 || escY == 0){
    escX = 1;
    escY = 1;
    cout<<"El valor 0 no es valido"<<endl;
  }

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0,1.0,1.0);   
  glLineWidth(2.0);
  int tam = puntos.size();

  actX = puntos[0].x;
  actY = puntos[0].y;

  glBegin(GL_LINES);
    for(int i=1;i<tam;i++){

      XP = actX * escX + (*centro).x * (1 - escX);
      YP = actY * escY + (*centro).y * (1 - escY);

      puntos[i-1].x = XP;
      puntos[i-1].y = YP;

      X2P = puntos[i].x * escX + (*centro).x * (1 - escX);
      Y2P = puntos[i].y * escY + (*centro).y * (1 - escY); 

      glVertex2d(XP ,YP);
      glVertex2d(X2P ,Y2P);

      actX = puntos[i].x;
      actY = puntos[i].y;
    }

    puntos[tam-1].x = actX * escX + (*centro).x * (1 - escX);
    puntos[tam-1].y = actY * escY + (*centro).y * (1 - escY);

    glVertex2d(puntos[0].x ,puntos[0].y);
    glVertex2d(puntos[tam-1].x ,puntos[tam-1].y );

    (*centro).x = (*centro).x * escX + (*centro).x * (1 - escX);
    (*centro).y = (*centro).y * escY + (*centro).y * (1 - escY);
  glEnd();

}


void rotar(void){
  int angulo;
  int XP, YP,X2P,Y2P;
  int actX, actY;

  cout<<"Angulo nuevo: "<<endl;
  cin>>angulo;
  cout<<endl;

  angulo = (angulo * pi) / 180;

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0,1.0,1.0);   
  glLineWidth(2.0);
  int tam = puntos.size();
  actX = puntos[0].x;
  actY = puntos[0].y;

  glBegin(GL_LINES);
    for(int i=1;i<tam;i++){
      XP = (actX * cos(angulo)) + (-sin(angulo) * actY) + (((*centro).x * (1-cos(angulo))) + ( (*centro).y * sin(angulo)));
      YP = (actX * sin(angulo)) + (cos(angulo) * actY) + (((*centro).y * (1-cos(angulo))) - ( (*centro).x * sin(angulo)));

      puntos[i-1].x = XP;
      puntos[i-1].y = YP;

      X2P = (puntos[i].x * cos(angulo)) + (-sin(angulo) * puntos[i].y) + (((*centro).x * (1-cos(angulo))) + ( (*centro).y * sin(angulo)));
      Y2P = (puntos[i].x * sin(angulo)) + (cos(angulo) * puntos[i].y) + (((*centro).y * (1-cos(angulo))) - ( (*centro).x * sin(angulo)));

      glVertex2d(XP ,YP);
      glVertex2d(X2P ,Y2P);

      actX = puntos[i].x;
      actY = puntos[i].y;

    }

    puntos[tam-1].x = (actX * cos(angulo)) + (-sin(angulo) * actY) + (((*centro).x * (1-cos(angulo))) + ( (*centro).y * sin(angulo)));
    puntos[tam-1].y = (actX * sin(angulo)) + (cos(angulo) * actY) + (((*centro).y * (1-cos(angulo))) - ( (*centro).x * sin(angulo)));

    glVertex2d(puntos[0].x ,puntos[0].y);
    glVertex2d(puntos[tam-1].x ,puntos[tam-1].y );

    (*centro).x = ((*centro).x * cos(angulo)) + (-sin(angulo) * (*centro).y) + (((*centro).x * (1-cos(angulo))) + ( (*centro).y * sin(angulo)));
    (*centro).y = ((*centro).x * sin(angulo)) + (cos(angulo) * (*centro).y) + (((*centro).y * (1-cos(angulo))) - ( (*centro).x * sin(angulo)));

  glEnd();
  return;

}



void menu(){
  int opcion=6;
  centro = PuntoCentral();
  
  //cout<<"puntero"<<endl;
  //cout<<(*centro).x<<" "<<(*centro).y<<endl;

  //glFlush();
        while(opcion != 5)
        {
          glFlush();
          cout<<"Menu:"<<endl;
          cout<<"1) Traslaccion"<<endl;
          cout<<"2) Escalamiento"<<endl;
          cout<<"3) Rotacion"<<endl;
          cout<<"4) Pintado"<<endl;
          cout<<"5) Salir"<<endl;
          cout<<endl;
          cout<<"Escoge una opcion: ";
          cout<<endl;
          cin>>opcion;

          if(opcion == 1)
          {
            trasladar();
          }
          else if(opcion == 2){
            escalar();
          }
          else if(opcion ==3){
            rotar();
          }
          else if(opcion ==4){
            pintar();
          }
        }

        return;
  glFlush();
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0,1.0,1.0);   
  glLineWidth(2.0);
  int tam = puntos.size();

  glBegin(GL_LINES);
    for(int i=1;i<tam;i++){
      glVertex2d(puntos[i-1].x,puntos[i-1].y);
      glVertex2d(puntos[i].x,puntos[i].y);
    }
  glEnd();

    if(tam > 2 ){
      if(distance(puntos[0].x ,puntos[0].y ,puntos[tam-1].x,puntos[tam-1].y)){
        glBegin(GL_LINES);
          glVertex2d(puntos[0].x,puntos[0].y);
          glVertex2d(puntos[tam-1].x,puntos[tam-1].y);
        glEnd();

        glutMouseFunc(NULL);
        cerrado = true;   

        glFlush();
        menu();
        exit(0);
      }
    }
  glFlush();
}


void init(){  
  glClearColor(0.0,0.0,0.0,0.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,ANCHO,0,ALTO);
}




int main(int argc, char **argv){  
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(ancho,alto);
  glutInitWindowPosition(100,50);
  glutCreateWindow(" Computacion grafica - Traslaciones "); 
  init();

  glutDisplayFunc(display);
  glutMouseFunc(mouse);

  glutMainLoop();

return 0;
}
