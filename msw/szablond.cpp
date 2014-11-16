
#include <c:/Dev-Cpp/include/GL/gl.h>
#include <c:/Dev-Cpp/include/GL/glu.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <c:/Dev-Cpp/include/GL/glut.h>
#include <windows.h>
#include <iostream>
#include <cstdlib>

void Display ()
{
	// kolor tla - zawartosc bufora koloru
	glClearColor (0.8,0.8,0.8,0.0);

	// czyszczenie bufora koloru
	glClear (GL_COLOR_BUFFER_BIT);

	// skierowanie polecen do wykonania
	glFlush ();

	// zamiana buforow koloru
	glutSwapBuffers();
}

int main (int argc, char *argv[])
{
	// inicjalizacja biblioteki GLUT
	glutInit (&argc,argv);

	// inicjalizacja bufora ramki
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

	// rozmiary glownego okna programu
	glutInitWindowSize (500,500);

	// utworzenie glownego okna programu
	glutCreateWindow ("Szescian 4");

	// dolaczenie funkcji generujacej scene 3D
	glutDisplayFunc (Display);

	// wprowadzenie programu do obslugi petli komunikatow
	glutMainLoop ();
	return 0;
}

