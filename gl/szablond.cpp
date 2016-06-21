
#include <c:/Dev-Cpp/include/GL/gl.h>
#include <c:/Dev-Cpp/include/GL/glu.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <c:/Dev-Cpp/include/GL/glut.h>
#include <windows.h>
#include <iostream>
#include <cstdlib>

void Display ()
{
  // kolor t�a - zawarto�� bufora koloru
  glClearColor (0.8,0.8,0.8,0.0);

  // czyszczenie bufora koloru
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glOrtho(-1, 1, -1, 1, 0, 2);
  glFrustum(-1, 1, -1, 1, 3, 8);

  //gluLookAt(0.1, 0.2, -3, 0, 0, -8, 0, 1, 0);

  glBegin(GL_POLYGON);
     glColor3f(0.1, 0.8, 0.1);
     glVertex3f(-0.4, 0.4, -4);
     glVertex3f(0.2, 0.4, -4);
     glVertex3f(0.2, -0.4, -4);
     glVertex3f(-0.4, -0.4, -4);
  glEnd();

  glBegin(GL_POLYGON);
     glColor3f(0.1, 0.1, 0.8);
     glVertex3f(0.2, 0.4, -4);
     glVertex3f(0.4, 0.4, -5.5);
     glVertex3f(0.4, -0.4, -5.5);
     glVertex3f(0.2, -0.4, -4);
  glEnd();

  glBegin(GL_POLYGON);
     glColor3f(0.8, 0.1, 0.1);
     glVertex3f(-0.8, 0.7, -5);
     glVertex3f(-0.3, 0.7, -6);
     glVertex3f(-0.3, -0.3, -6);
     glVertex3f(-0.8, -0.3, -5);
  glEnd();

glutWireCube(5);
glutWireTeapot(3.2);
glutWireSphere(4, 3, 3);

  // skierowanie polece� do wykonania
  glFlush ();

  // zamiana bufor�w koloru
  glutSwapBuffers();
}


int main (int argc, char *argv[])
{
  // inicjalizacja biblioteki GLUT
  glutInit (&argc,argv);

  // inicjalizacja bufora ramki
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

  // rozmiary g��wnego okna programu
  glutInitWindowSize (500,500);

  // utworzenie g��wnego okna programu
  glutCreateWindow ("Szescian 4");


  // do��czenie funkcji generuj�cej scen� 3D
  glutDisplayFunc (Display);

  // wprowadzenie programu do obs�ugi p�tli komunikat�w
  glutMainLoop ();
  return 0;
}
