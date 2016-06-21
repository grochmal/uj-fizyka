#include "stdafx.h"
#include <windows.h>
#include <C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/include/gl.h>
#include <C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/include/glut.h>
#include <stdlib.h>
#include <math.h>	 

enum {
	point0,
	point1, 
	point2,
	point3
};
int button_state=GLUT_UP;
int button_x, button_y;


// Iloœæ punktów kontrolnych krzywej
GLint np = 4;

GLfloat Points[4][3]= {{  -4.0, 0.0, 0.0f}, // Punkt koñcowy
                           { -1.0f, 4.0f, 0.0f}, // Punkt kontrolny
                           {  6.0f, -4.0f, 0.0f}, // Punkt kontrolny
                           {  4.0f, 0.0f, 0.0f }}; // Punkt koñcowy


void RenderScene(void);

// Ta funkcja s³u¿y do rozmieszczenia punktów kontrolnych krzywej
void DrawPoints(void)
{
    int i;

    glPointSize(7.0f);
	glColor3f(1.0,0.0,0.0);

    // Pêtla dla wszystkich punktów kontrolnych w tym przyk³adzie
    glBegin(GL_POINTS);
        for(i = 0; i < np; i++)
            glVertex2fv(Points[i]);
    glEnd();
}


void ChangeSize(GLsizei w, GLsizei h)
{
    if(h == 0)
        h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-10.0f, 10.0f, -10.0f, 10.0f);

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
    glClear(GL_COLOR_BUFFER_BIT);

    // Przygotowanie krzywej Beziera
    // Trzeba to zrobiæ tylko raz, wiêc powinniœmy to
    // uczyniæ w funkcji przygotowuj¹cej kontekst.
    glMap1f(GL_MAP1_VERTEX_3,   // Rodzaj generowanych danych
            0.0f,               // Pocz¹tek zakresu u
            100.0f,             // Koniec zakresu u
            3,                  // Odstêp pomiêdzy danymi wierzcho³ków
            np,         // iloœæ punktów kontrolnych
            &Points[0][0]); // tablica punktów kontrolnych

    // W³¹czenie funkcji obliczaj¹cej
    glEnable(GL_MAP1_VERTEX_3);

     glBegin(GL_LINE_STRIP);
          for(int i = 0; i <= 100; i++) {
                // Obliczenie krzywej dla danego punktu
              glEvalCoord1f((GLfloat) i); 
          }
     glEnd();


    // Wyrysowanie punktów kontrolnych
    DrawPoints();

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

    glutCreateWindow ("Krzywa Béziera");

    glutDisplayFunc (Display);

    glutReshapeFunc (ChangeSize);
    
	glutMouseFunc(MouseButton);
    
    glutMainLoop ();
    return 0;
}
