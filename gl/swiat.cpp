#include <math.h>	
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <c:/Dev-Cpp/include/GL/gl.h>
#include <c:/Dev-Cpp/include/GL/glu.h>
#include <c:/Dev-Cpp/include/GL/glut.h>


#define glRGB(x, y, z)	glColor3ub((GLubyte)x, (GLubyte)y, (GLubyte)z)

GLuint texture; 
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

static GLsizei lastHeight; 
static GLsizei lastWidth;
GLfloat shadowMat[4][4];



void ReduceToUnit(float vector[3])
	{
	float length;
	
	length = (float)sqrt((vector[0]*vector[0]) + 
						(vector[1]*vector[1]) +
						(vector[2]*vector[2]));


	if(length == 0.0f)
		length = 1.0f;

	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
	}


void calcNormal(float v[3][3], float out[3])
	{
	float v1[3],v2[3];
	static const int x = 0;
	static const int y = 1;
	static const int z = 2;

	v1[x] = v[0][x] - v[1][x];
	v1[y] = v[0][y] - v[1][y];
	v1[z] = v[0][z] - v[1][z];

	v2[x] = v[1][x] - v[2][x];
	v2[y] = v[1][y] - v[2][y];
	v2[z] = v[1][z] - v[2][z];

	out[x] = v1[y]*v2[z] - v1[z]*v2[y];
	out[y] = v1[z]*v2[x] - v1[x]*v2[z];
	out[z] = v1[x]*v2[y] - v1[y]*v2[x];

	ReduceToUnit(out);
	}


void MakeShadowMatrix(float points[3][3], float lightPos[4], float destMat[4][4])
{
    float Coeff[3];
    float dot;
	float d;


	calcNormal(points,Coeff);
	d = - Coeff[0]*points[0][0]-Coeff[1]*points[0][1]-Coeff[2]*points[0][2];
	dot = Coeff[0]*lightPos[0]+Coeff[1]*lightPos[1]+Coeff[2]*lightPos[2]+d;

    // Pierwsza wiersz
    destMat[0][0] = dot-Coeff[0]*lightPos[0];
    destMat[1][0] =-Coeff[1]*lightPos[0] ;
    destMat[2][0] = -Coeff[2]*lightPos[0] ;
    destMat[3][0] = -d*lightPos[0] ;

    // Druga kolumna
    destMat[0][1] = -Coeff[0]*lightPos[1];
    destMat[1][1] =dot-Coeff[1]*lightPos[1];
    destMat[2][1] =-Coeff[2]*lightPos[1] ;
    destMat[3][1] =-d*lightPos[1] ;

    // Trzecia kolumna
    destMat[0][2] = -Coeff[0]*lightPos[2]; ;
    destMat[1][2] = -Coeff[1]*lightPos[2] ;
    destMat[2][2] = dot-Coeff[2]*lightPos[2];
    destMat[3][2] = -d*lightPos[2] ;

    // Czwarta kolumna
    destMat[0][3] = -Coeff[0]*lightPos[3]; 
    destMat[1][3] = -Coeff[1]*lightPos[3] ;
    destMat[2][3] =  -Coeff[2]*lightPos[3] ;
    destMat[3][3] = dot-d*lightPos[3];
 
} 
void ChangeSize(GLsizei w, GLsizei h)
	{
	GLfloat nRange = 80.0f;
	if(h == 0)
		h = 1;

	lastWidth = w;
	lastHeight = h;
		
    glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	}



void SetupRC()
{
  GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat  specular[] = { 0.8f, 0.8f, 0.8f, 1.0f};
   float  lightPos[] = { 0.0, 150.0, 50.0, 1.0 };
    GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };


    glEnable(GL_DEPTH_TEST);   
    glFrontFace(GL_CCW);         
                                
    glEnable(GL_CULL_FACE);     

    
    glEnable(GL_LIGHTING);
   
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
    glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL); 

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
    glMateriali(GL_FRONT,GL_SHININESS,128);


    glClearColor(0.0f, 0.0f, 1.0f, 1.0f );
}

	void kostka (){
float normal[3];
float v[3][3]={{-10.0,-10.0,-20},{10.0,-10.0,-20},{10.0,10.0,-20}};

glColor3f(1.0,0.0,0.0);
calcNormal(v,normal);
glBegin(GL_POLYGON);

glNormal3f(normal[0],normal[1],normal[2]);

glVertex3f(-10.0,-10.0,-20);

glVertex3f(10.0,-10.0,-20);

glVertex3f(10.0,10.0,-20);

glVertex3f(-10.0,10.0,-20);

glEnd();


	
{
glBegin(GL_POLYGON);

float v[3][3]={{10.0,-10.0,-20},{10.0,-10.0,-40},{10.0,10.0,-40}};
calcNormal(v,normal);

glNormal3f(normal[0],normal[1],normal[2]);

glVertex3f(10.0,-10.0,-20);

glVertex3f(10.0,-10.0,-40);

glVertex3f(10.0,10.0,-40);

glVertex3f(10.0,10.0,-20);
glEnd();
} 

glDisable( GL_TEXTURE_2D );

{
glBegin(GL_POLYGON);


float v[3][3]={{10.0,-10.0,-40},{-10.0,-10.0,-40},{-10.0,10.0,-40}};
calcNormal(v,normal);

glNormal3f(normal[0],normal[1],normal[2]);
glVertex3f(10.0,-10.0,-40);
glVertex3f(-10.0,-10.0,-40);
glVertex3f(-10.0,10.0,-40);
glVertex3f(10.0,10.0,-40);
glEnd();
} 
{
glBegin(GL_POLYGON);

float v[3][3]={{-10.0,-10.0,-40},{-10.0,-10.0,-20},{-10.0,10.0,-20}};
calcNormal(v,normal);

glNormal3f(normal[0],normal[1],normal[2]);
glVertex3f(-10.0,-10.0,-40);
glVertex3f(-10.0,-10.0,-20);
glVertex3f(-10.0,10.0,-20);
glVertex3f(-10.0,10.0,-40);
glEnd();
}
{
glBegin(GL_POLYGON);

float v[3][3]={{-10.0,10.0,-2.0},{10.0,10.0,-20},{10.0,10.0,-40}};
calcNormal(v,normal);

glNormal3f(normal[0],normal[1],normal[2]);
glVertex3f(-10.0,10.0,-20);
glVertex3f(10.0,10.0,-20);
glVertex3f(10.0,10.0,-40);
glVertex3f(-10.0,10.0,-40);
glEnd();
}
{
glBegin(GL_POLYGON);

float v[3][3]={{-10.0,-10.0,-40},{10.0,-10.0,-40},{10.0,-10.0,-20}};
calcNormal(v,normal);

glNormal3f(normal[0],normal[1],normal[2]);
glVertex3f(-10.0,-10.0,-40);
glVertex3f(10.0,-10.0,-40);
glVertex3f(10.0,-10.0,-20.0);
glVertex3f(-10.0,-10.0,-20.0);
glEnd();
}
	}
	void kostka2 (){
float normal[3];
float v[3][3]={{-10.0,-10.0,-20},{10.0,-10.0,-20},{10.0,10.0,-20}};


calcNormal(v,normal);
glBegin(GL_POLYGON);

glNormal3f(normal[0],normal[1],normal[2]);

glVertex3f(-10.0,-10.0,-20);

glVertex3f(10.0,-10.0,-20);

glVertex3f(10.0,10.0,-20);

glVertex3f(-10.0,10.0,-20);

glEnd();
	
{
glBegin(GL_POLYGON);

float v[3][3]={{10.0,-10.0,-20},{10.0,-10.0,-40},{10.0,10.0,-40}};
calcNormal(v,normal);

glNormal3f(normal[0],normal[1],normal[2]);
glVertex3f(10.0,-10.0,-20);
glVertex3f(10.0,-10.0,-40);
glVertex3f(10.0,10.0,-40);
glVertex3f(10.0,10.0,-20);
glEnd();
} 
{
glBegin(GL_POLYGON);


float v[3][3]={{10.0,-10.0,-40},{-10.0,-10.0,-40},{-10.0,10.0,-40}};
calcNormal(v,normal);

glNormal3f(normal[0],normal[1],normal[2]);
glVertex3f(10.0,-10.0,-40);
glVertex3f(-10.0,-10.0,-40);
glVertex3f(-10.0,10.0,-40);
glVertex3f(10.0,10.0,-40);
glEnd();
} 
{
glBegin(GL_POLYGON);

float v[3][3]={{-10.0,-10.0,-40},{-10.0,-10.0,-20},{-10.0,10.0,-20}};
calcNormal(v,normal);

glNormal3f(normal[0],normal[1],normal[2]);
glVertex3f(-10.0,-10.0,-40);
glVertex3f(-10.0,-10.0,-20);
glVertex3f(-10.0,10.0,-20);
glVertex3f(-10.0,10.0,-40);
glEnd();
}
{
glBegin(GL_POLYGON);

float v[3][3]={{-10.0,10.0,-2.0},{10.0,10.0,-20},{10.0,10.0,-40}};
calcNormal(v,normal);

glNormal3f(normal[0],normal[1],normal[2]);
glVertex3f(-10.0,10.0,-20);
glVertex3f(10.0,10.0,-20);
glVertex3f(10.0,10.0,-40);
glVertex3f(-10.0,10.0,-40);
glEnd();
}
{
glBegin(GL_POLYGON);

float v[3][3]={{-10.0,-10.0,-40},{10.0,-10.0,-40},{10.0,-10.0,-20}};
calcNormal(v,normal);

glNormal3f(normal[0],normal[1],normal[2]);
glVertex3f(-10.0,-10.0,-40);
glVertex3f(10.0,-10.0,-40);
glVertex3f(10.0,-10.0,-20.0);
glVertex3f(-10.0,-10.0,-20.0);
glEnd();
}
	}

void RenderScene(void)
	{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0,0.0,0.0);
    kostka();
	glPopMatrix();

float points[3][3] ={{-400.0f, -64.0, 200.0f},{400.0f, -64.0, 200.0f},{400.0f, -15.0, -200.0f}};
float  lightPos[] = { 0.0, 150.0, 50.0, 1.0 };
 MakeShadowMatrix(points, lightPos, shadowMat);

glPushAttrib(GL_LIGHTING_BIT);
glDisable(GL_LIGHTING);
glPushMatrix();
glMultMatrixf((float *)shadowMat);
glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
glColor3f(0.0,0.0,0.0);
	kostka2();
glPopMatrix();
glBegin(GL_POLYGON);
        glRGB(0,128,0);
        glVertex3f(-400.0f, -65.0, 200.0f);
        glVertex3f(400.0f, -65.0, 200.0f);
        glRGB(0,255,0);
        glVertex3f(400.0f, -15.0, -200.0f);
        glVertex3f(-400.0f, -15.0, -200.0f);
glEnd();
glPopAttrib();

glFlush ();
 glutSwapBuffers();

	}


void SpecialKeys (int key, int x, int y)
{
  switch (key)
  {
    case GLUT_KEY_LEFT:
    yRot -= 1;
    break;

    case GLUT_KEY_UP:
    xRot += 1;
    break;

    case GLUT_KEY_RIGHT:
    yRot+= 1;
    break;

    
    case GLUT_KEY_DOWN:
    xRot-= 1;
    break;
  }

  SetupRC();
	  RenderScene();
}
int main (int argc, char *argv[])
{
  glutInit (&argc,argv);
 
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

  glutInitWindowSize (700,700);


  glutCreateWindow ("Szeœcian 4");
 

  glutSpecialFunc (SpecialKeys);

  glutDisplayFunc (RenderScene);

  glutReshapeFunc (ChangeSize);
  

  glutMainLoop ();
  return 0;
}
