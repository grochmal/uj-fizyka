#include "stdafx.h"
#include <windows.h>
#include <C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/include/gl.h>
#include <C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/include/glut.h>
#include <stdlib.h>
#include <math.h>	
#define glRGB(x, y, z)	glColor3ub((GLubyte)x, (GLubyte)y, (GLubyte)z)


enum {
	point0, 
	point1,
	point2,
	point3,
	point4
};
int button_state=GLUT_UP;
int button_x, button_y;
int wybor = 10;


// NURBS object pointer
GLUnurbsObj* pNurb =  gluNewNurbsRenderer(); 
GLUnurbsObj* pNurb2 =  gluNewNurbsRenderer();
// The number of control points for this curve
GLint np = 5; // 4 X 4

// Mesh extends four units -6 to +6 along x and y axis
// Lies in Z plane
//                 u  v  (x,y,z)	
GLfloat Points[5][3]  = {{  -5.0f, -3.0f, 0.0f}, // Punkt koñcowy
                           { 0.0f, -2.0f, 0.0f}, // Punkt kontrolny
                           {  1.0f, 6.0f, 0.0f}, // Punkt kontrolny
                           {  7.0f, 4.0f, 0.0f }, // Punkt kontrolny
							{5.0f, 2.0f, 0.0f }}; // Punkt koñcowy



// Knot sequence for the NURB
GLfloat Knots[9] = {0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.0f, 1.0f,1.0};





void DrawPoints(void)
	{
	int i;

	glPointSize(7.0f);
	glRGB(255,0,0);

	glBegin(GL_POINTS);
		for(i = 0; i < np; i++)
			glVertex3fv(Points[i]);	
	glEnd();
	}

void ChangeSize(GLsizei w, GLsizei h)
	{
	if(h == 0)
		h = 1;

    glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-10.0f,10.0f, -10.0f,10.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	}

void SetupRC()
	{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );

	glColor3f(0.0f, 0.0f, 1.0f);
	}




void Display(void)
{
    
    SetupRC();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    
	glLineWidth(3);
    // Renderuj krzyw¹ NURBS
    // Pocz¹tek definicji krzywej
    gluBeginCurve(pNurb);

    // Obliczanie krzywej
    gluNurbsCurve(pNurb, 
        9, Knots,
        3,
        &Points[0][0], 
        4,
        GL_MAP1_VERTEX_3);

    // Koniec definiowania krzywej
    gluEndCurve(pNurb);

    // Wyrysowanie punktów kontrolnych
    DrawPoints();

    // Zrzucenie poleceñ graficznych
    glFlush();
     glutSwapBuffers();
}
void MouseButton(int button, int state, int x, int y)
{
     if (button == GLUT_LEFT_BUTTON)
     {			
				
                button_state=state;
                
                if (button_state=GLUT_DOWN)
                {button_x=x;
                button_y=y;
                }
				else{button_x=x;
                button_y=y;}
                }
                }
                

int main (int argc, char *argv[])
{
    glutInit (&argc,argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize (800,800);

    glutCreateWindow ("Krzywa NURBS");

    glutDisplayFunc (Display);
    glutReshapeFunc (ChangeSize);
    glutMouseFunc(MouseButton);
    glutMainLoop ();
    return 0;
}
