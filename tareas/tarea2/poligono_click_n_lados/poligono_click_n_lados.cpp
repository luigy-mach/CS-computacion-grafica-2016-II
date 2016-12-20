#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stddef.h>
#include <iostream>

#include<queue>
#include<utility>


using namespace std;


struct point{
	GLint _x;
	GLint _y;
	GLint _z;
	point(){
		_x=_y=_z=0;
	}

	point(int x ,int y,int z=0){
		_x=x;
		_y=y;
		_z=z;
	}
	point& operator=(point& o){
		_x=o._x;
		_y=o._y;
		return *this;
	}

};

point p1,p2;
queue< point > queue_points;
queue< point > queue_points_temp;



// values controlled by fast keys
float g_angle = 0.0f;
float g_xoffset = 0.0f;
float g_yoffset = 0.0f;
int x;
int y;

// increments
const float g_angle_step = 32.0f; // degrees
const float g_offset_step = 32.0f; // world coord units

// last cursor click
int g_cursor_x = 0;
int g_cursor_y = 0;


void dibujar_poligono(){

	if(queue_points.empty()){
		cout<<"cola vacia"<<endl;
	}else{
		cout<<"imprimiendo<<<<<"<<endl;
		glBegin(GL_LINE_LOOP);
		while(!queue_points.empty()){
			point p = queue_points.front();
			queue_points.pop();
			glVertex2f(p._x,p._y);
		}
		glEnd();
	}
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(500.0f+g_xoffset, 500.0f+g_yoffset, 0.0f);
        glScalef(100.0f, 100.0f, 1.0f);
        glRotatef(g_angle, 0.0f, 0.0f, 1.0f);
        //dibujar_poligono();
    glPopMatrix(); // done with stack

}


void mouse_click(int button, int state, int x, int y)
{
    if (button==GLUT_LEFT_BUTTON)
    {
        if (state==GLUT_UP)
        {
          std::cerr << "\t poligono finalizado" <<queue_points.size()<<" <-tamaño"<<endl;
			    dibujar_poligono();
					glutSwapBuffers();
					glutPostRedisplay();
        }
    }
    else if (button==GLUT_RIGHT_BUTTON)
    {
				p1._x=x;
				p1._y=y;
				queue_points.push(p1);
				std::cerr << "\t agregando a cola" <<x<<"<->"<<y<< std::endl;
    }

}



void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 1000);

    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glutSwapBuffers();


    g_cursor_x = g_cursor_y = 500; // middle of window
		//glutSwapBuffers();
		cout<<"******************"<<endl;
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("poligono click  n lados");


    glutDisplayFunc(display);

    // handlers for keyboard input
    //glutKeyboardFunc(keyboard);
    //glutSpecialFunc(special);

    // mouse event handlers
    glutMouseFunc(mouse_click);
    //glutPassiveMotionFunc(mouse_motion);
		glutSwapBuffers();
    init();
    glutMainLoop();

    return 0;
}
