#include <c:/Dev-Cpp/include/windows.h>
#include <c:/Dev-Cpp/include/GL/gl.h>
#include <c:/Dev-Cpp/include/GL/glu.h>
#include <c:/Dev-Cpp/include/GL/glut.h>
#include <stdlib.h>
#include <windows.h>

GLfloat rx=200.0;

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glScalef(0.5,0.5,0.5);
	
	glBegin(GL_QUAD_STRIP);
		// pierwszy czworok¹t
		glTexCoord2i(0,1);
		glVertex3i(-600,-300,-600);
		glTexCoord2i(1,1);
		glVertex3i(-600, 300,-600);
		glTexCoord2i(0,0);
		glVertex3i( 600,-300,-600);
		glTexCoord2i(1,0);
		glVertex3i( 600, 300,-600);
		// drugi czworok¹t
		glTexCoord2i(0,2);
		glVertex3i( 600,-300, 600);
		glTexCoord2i(2,2);
		glVertex3i( 600, 300, 600);
		// trzeci czworok¹t
		glTexCoord2i(0,0);
		glVertex3i(-600,-300, 600);
		glTexCoord2i(2,0);
		glVertex3i(-600, 300, 600);
		// czwarty czworok¹t
		glTexCoord2i(0,2);
		glVertex3i(-600,-300,-600);
		glTexCoord2i(2,2);
		glVertex3i(-600, 300,-600);
	glEnd();
	glPopMatrix();

	glFlush();
}

void Reshape(int s, int w)
{	
	glViewport(0,0,s,w);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (s<=w) glOrtho(-1000,1000,-1000*(w/s),1000*(w/s),-1000,1000);
	else glOrtho(-1000*(s/w),1000*(s/w),-1000,1000,-1000,1000);

	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 

	glRotated(40,1.0f,1.0f,0.0f);

}

void tekstura(void)
{
	
	GLubyte tekstura[8][8][3]=
	{
		{
		{250,  0,  0},{250,  0,  0},{250,  0,  0},{250,  0,  0},
		{230,230,230},{230,230,230},{230,230,230},{230,230,230}
		},
		{
		{250,  0,  0},{250,  0,  0},{250,  0,  0},{250,  0,  0},
		{230,230,230},{230,230,230},{230,230,230},{230,230,230}
		},
		{
		{250,  0,  0},{250,  0,  0},{250,  0,  0},{250,  0,  0},
		{230,230,230},{230,230,230},{230,230,230},{230,230,230}
		},
		{
		{250,  0,  0},{250,  0,  0},{250,  0,  0},{250,  0,  0},
		{230,230,230},{230,230,230},{230,230,230},{230,230,230}
		},
		{
		{  0,250,  0},{  0,250,  0},{  0,250,  0},{  0,250,  0},
		{  0,  0,250},{  0,  0,250},{  0,  0,250},{  0,  0,250}
		},
		{
		{  0,250,  0},{  0,250,  0},{  0,250,  0},{  0,250,  0},
		{  0,  0,250},{  0,  0,250},{  0,  0,250},{  0,  0,250}
		},
		{
		{  0,250,  0},{  0,250,  0},{  0,250,  0},{  0,250,  0},
		{  0,  0,250},{  0,  0,250},{  0,  0,250},{  0,  0,250}
		},
		{
		{  0,250,  0},{  0,250,  0},{  0,250,  0},{  0,250,  0},
		{  0,  0,250},{  0,  0,250},{  0,  0,250},{  0,  0,250}
		}
	};

	// definicja tekstury
	glTexImage2D(GL_TEXTURE_2D,0,3,8,8,0,GL_RGB,GL_UNSIGNED_BYTE,tekstura);
	// ustalenie parametrów tekstury
   	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
   	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
   	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	// ustalenie trybu teksturowania
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);	
	// w³¹czenie teksturowania
	glDisable(GL_TEXTURE_1D);
	glEnable(GL_TEXTURE_2D);
}

int main (int argc, char *argv[])
{
   
    glutInit (&argc,argv);

	glutInitDisplayMode(GLUT_RGBA);
	
	glutInitWindowSize(800,800);

	glutInitWindowPosition(50,50);

	glutCreateWindow("Nak³adanie tekstur");

	glClearColor(0,0,0,0);

	tekstura();

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);

	glutMainLoop();
}
