#include <GL/glut.h>

float angle = 0;
void timer( int extra )
{
    angle += 0.5;

    glutPostRedisplay();
    glutTimerFunc( 16, timer, 0 );
}

void display(void)
{
    const double w = glutGet( GLUT_WINDOW_WIDTH );
    const double h = glutGet( GLUT_WINDOW_HEIGHT );
    const double ar = w / h;

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 60.0, ar, 0.1, 100.0 );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef( 0, 0, -4 );
    glRotatef( angle, 0.1, 0.5, 0.3 );

    glColor3ub( 255, 255, 255 );
    glutWireCube( 2.0 );


    GLdouble modelview[16];
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    GLdouble projection[16];
    glGetDoublev( GL_PROJECTION_MATRIX, projection ); 
    GLint viewport[4];
    glGetIntegerv( GL_VIEWPORT, viewport ); 

    double x, y, z;
    gluProject( 1, 1, 1, modelview, projection, viewport, &x, &y, &z );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( 0, w, 0, h, -1, 1 );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef( x, y, 0 );
    glScalef( 10, 10, 1 );
    glBegin( GL_QUADS );
    glColor3ub( 255, 0, 0 );
    glVertex2i( -1, -1 );
    glVertex2i(  1, -1 );
    glVertex2i(  1,  1 );
    glVertex2i( -1,  1 );
    glEnd();

    glutSwapBuffers();
}

int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( 800, 600 );
    glutCreateWindow( "GLUT" );
    glutDisplayFunc( display );
    glutTimerFunc( 0, timer, 0 );
    glutMainLoop();
    return 0;
}
