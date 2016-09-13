#include <GL/glut.h>
#include <cmath>

void glPolygon( unsigned int sides )
{
    if( sides < 3 ) return;

    const float PI = 3.14159;
    const float step = ( 2 * PI ) / static_cast< float >( sides );

    glBegin( GL_LINE_LOOP );
    for( unsigned int i = 0; i < sides; ++i )
    {
        glVertex2f( cos( i * step ), sin( i * step ) );
    }
    glEnd();
}

void display()
{
    glClear( GL_COLOR_BUFFER_BIT );
    glMatrixMode( GL_PROJECTION );

    glLoadIdentity();
    double ar = glutGet( GLUT_WINDOW_WIDTH ) / (double)glutGet( GLUT_WINDOW_HEIGHT );
    glOrtho( -2 * ar, 2 * ar, -2, 2, -1, 1);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glColor3ub( 255, 0, 0 );
    glPolygon( 8 );

    glutSwapBuffers();
}

int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( 640, 480 );
    glutCreateWindow( "Polygons" );
    glutDisplayFunc( display );
    glutMainLoop();
    return 0;
}
