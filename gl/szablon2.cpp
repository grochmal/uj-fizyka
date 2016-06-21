#include <c:/Dev-Cpp/include/GL/gl.h>
#include <c:/Dev-Cpp/include/GL/glu.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <c:/Dev-Cpp/include/GL/glut.h>
#include <windows.h>
#include <iostream>
#include <cstdlib>

float par=0;
void kostka(void)
{
   glBegin(GL_POLYGON);
      glColor3f(0.8, 0.3, 0.3);
      glVertex3f(-0.4, 0.4, -6);
      glVertex3f(0.4, 0.4, -6);
      glVertex3f(-0.4, -0.4, -6);
      glVertex3f(0.4, -0.4, -6);
   glEnd();
   glBegin(GL_POLYGON);
      glColor3f(0.3, 0.3, 0.8);
      glVertex3f(0.4, 0.4, -4);
      glVertex3f(0.4, 0.4, -6);
      glVertex3f(0.4, -0.4, -6);
      glVertex3f(0.4, -0.4, -4);
   glEnd();
   glBegin(GL_POLYGON);
      glColor3f(0.3, 0.3, 0.8);
      glVertex3f(-0.4, -0.4, -4);
      glVertex3f(-0.4, -0.4, -6);
      glVertex3f(0.4, -0.4, -6);
      glVertex3f(0.4, -0.4, -4);
   glEnd();
   glBegin(GL_POLYGON);
      glColor3f(0.3, 0.3, 0.8);
      glVertex3f(-0.4, 0.4, -4);
      glVertex3f(-0.4, 0.4, -6);
      glVertex3f(-0.4, -0.4, -6);
      glVertex3f(-0.4, -0.4, -4);
   glEnd();
   glBegin(GL_POLYGON);
      glColor3f(0.3, 0.3, 0.8);
      glVertex3f(-0.4, 0.4, -4);
      glVertex3f(-0.4, 0.4, -6);
      glVertex3f(0.4, 0.4, -6);
      glVertex3f(0.4, 0.4, -4);
   glEnd();
   glBegin(GL_POLYGON);
      glColor3f(0.3, 0.8, 0.3);
      glVertex3f(-0.4, 0.4, -4);
      glVertex3f(0.4, 0.4, -4);
      glVertex3f(0.4, -0.4, -4);
      glVertex3f(-0.4, -0.4, -4);
   glEnd();
}

void MouseButton(int button, int state, int x, int y)
{
   int button_x, button_y, button_state;
   if(button == GLUT_LEFT_BUTTON)
   {
      if(button_state = GLUT_DOWN)
      {
         button_x = x;
         button_y =y;
      }
      else
      {
         button_x = x;
         button_y = y;
      }
   }
}
/*
void MouseMotion(int x, int y)
{
   if(button_state = GLUT_DOWN)
   {
      komendy; w main glutMotionFunc(MouseMotion);
   }
}
*/
void Display(void)
{
   // kolor t³a - zawartoœæ bufora koloru
   glClearColor (0.8,0.8,0.8,0.0);

   // czyszczenie bufora koloru
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glEnable(GL_DEPTH_TEST);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   //glOrtho(-1, 1, -1, 1, 0, 2);
   glFrustum(-1, 1, -1, 1, 3, 8);

   gluLookAt(par, 0.5, 0, 0, 0, -3, 0, 1, 0);

   kostka();

   // skierowanie poleceñ do wykonania
   glFlush ();

   // zamiana buforów koloru
   glutSwapBuffers();
}

void abc(int val)
{
   par += 1;
   Display();
   glutTimerFunc(25, abc, 0);
}
/*
void nazwa(unsigned char key, int x, int y)
{
   if(key = '-')
   {
      glBegin(GL_POLYGON);
         glColor3f(0.8, 0.1, 0.1);
         glVertex3f(-0.8, 0.7, -5);
         glVertex3f(-0.3, 0.7, -6);
         glVertex3f(-0.3, -0.3, -6);
         glVertex3f(-0.8, -0.3, -5);
      glEnd();
      Display();
   }
}

void nazwa(int key, int x, int y)
{
   switch(key)
   {
      case GLUT_KEY_UP:
         glBegin(GL_POLYGON);
            glColor3f(0.1, 0.1, 0.8);
            glVertex3f(0.2, 0.4, -4);
            glVertex3f(0.4, 0.4, -5.5);
            glVertex3f(0.4, -0.4, -5.5);
            glVertex3f(0.2, -0.4, -4);
         glEnd();
         break;
   }
}
*/
int main (int argc, char *argv[])
{
   // inicjalizacja biblioteki GLUT
   glutInit (&argc,argv);

   // inicjalizacja bufora ramki
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

   // rozmiary g³ównego okna programu
   glutInitWindowSize (500,500);

   // utworzenie g³ównego okna programu
   glutCreateWindow("Szescian 4");

  glutMouseFunc(MouseButton);
  
   glutTimerFunc(25, abc, 0);

   //glutKeyboardFunc(nazwa);

   // do³¹czenie funkcji generuj¹cej scenê 3D
   glutDisplayFunc(Display);

   // wprowadzenie programu do obs³ugi pêtli komunikatów
   glutMainLoop();
   return 0;
}
