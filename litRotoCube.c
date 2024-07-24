// Program name: MyRotoCube.cpp
//
// Written By: Carlos Santiago Date: 09/20/00
//
// This program demonstrates a rotating cube. The cube is rendered using
// vertex arrays. It also demonstrates view transformations (glFrustum(),
// glRotatef(), glMatrixMode(), and gluLookAt()).
//
// To correct for QUADS drawn out of order, I enabled Z-Buffering using
// the following functions:
//
// glEnable(GL_DEPTH_TEST);
// glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// glutInitDisplayMode (GLUT_DEPTH | GLUT_SINGLE | GLUT_RGB);
//
// Double buffering is used for animationg the cube.
// glutSwapBuffers() is used for page flipping GLUT_DOUBLE enables double buffering
// in glutInitDisplayMode().
//
//
// Modified to add lighting on 10/19/00
//
// Vertex Lighting
//
// Added an array of vertex normal required for the lighting to work. 
// Added Color Tracking for proper lighting.
//


#include <GL/glut.h>

void setupPointers(void)
{
   static GLfloat vertices[] = {	-1.0,	-1.0,	-1.0, 
									-1.0,	-1.0,	1.0, 
									-1.0,	1.0,	1.0,
									-1.0,	1.0,	-1.0,	
									1.0,	-1.0,	-1.0, 
									1.0,	-1.0,	1.0,
									1.0,	1.0,	1.0, 
									1.0,	1.0,	-1.0, 		};
								

   static GLfloat colors[] = {	1.0, 0.2, 0.2, //Red
								0.2, 0.2, 1.0, //Blue
								1.0, 1.0, 1.0, //White
								0.0, 1.0, 0.0, //Green
								0.0, 0.0, 0.0, //Black
								0.0, 1.0, 1.0, //Cyan
								1.0, 0.2, 1.0, //Magenta
								0.8, 1.0, 0.2	}; //Yellow

   static GLfloat normals[] = {	-0.57735,	-0.57735,	-0.57735, 
									-0.57735,	-0.57735,	0.57735, 
									-0.57735,	0.57735,	0.57735,
									-0.57735,	0.57735,	-0.57735,	
									0.57735,	-0.57735,	-0.57735, 
									0.57735,	-0.57735,	0.57735,
									0.57735,	0.57735,	0.57735, 
									0.57735,	0.57735,	-0.57735, 		};
								

   glEnableClientState (GL_VERTEX_ARRAY);
   glEnableClientState (GL_COLOR_ARRAY);
   glEnableClientState (GL_NORMAL_ARRAY);

   glVertexPointer (3, GL_FLOAT, 0, vertices);
   glColorPointer (3, GL_FLOAT, 0, colors);
   glNormalPointer (GL_FLOAT, 0, normals);
}


static GLfloat theta = 0;    //Initial angle of X rotation.
static GLfloat alpha = 0;    //Initial angle of Y rotation.

void init(void) 
{

	//Lighting variables
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   GLfloat light_position[] = { 1.0, 2.0, 1.0, 0.0 };
   

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
    
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_specular);

	//Setup Color tracking this is required for lighting objects with color.
	//If color tracking is not enabled the scene will be rendered in gray scale.
	glColorMaterial  (GL_FRONT, GL_DIFFUSE); 

	glEnable  (GL_COLOR_MATERIAL); 
	
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST); //Enable Z-Buffering
	
	setupPointers ();
}

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //Point the camera


	
//Draw the room before the cube is rotated otherwise, it will also rotate.

	glBegin(GL_QUADS);

		// Draw a Ceiling
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(-5.0, 5.0, 5.0);
		glVertex3f(5.0, 5.0, 5.0);
		glVertex3f(5.0, 5.0, -5.0);
		glVertex3f(-5.0, 5.0, -5.0);
		
		
		// Draw a Back Wall
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(5.0, -5.0, -5.0);
		glVertex3f(-5.0, -5.0, -5.0);
		glVertex3f(-5.0, 5.0, -5.0);
		glVertex3f(5.0, 5.0, -5.0);

		// Draw a Floor
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-5.0, -5.0, -5.0);
		glVertex3f(5.0, -5.0, -5.0);
		glVertex3f(5.0, -5.0, 5.0);
		glVertex3f(-5.0, -5.0, 5.0);

		// Draw a Left wall
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(-5.0, -5.0, 5.0);
		glVertex3f(-5.0, -5.0, -5.0);
		glVertex3f(-5.0, 5.0, -5.0);
		glVertex3f(-5.0, 5.0, 5.0);

		// Draw a Right wall
		glColor3f(0.0, 1.0, 1.0);
		glVertex3f(5.0, -5.0, 5.0);
		glVertex3f(5.0, 5.0, 5.0);
		glVertex3f(5.0, 5.0, -5.0);
		glVertex3f(5.0, -5.0, -5.0);

		// Draw a Front Wall
		glColor3f(1.0, 0.0, 1.0);
		glVertex3f(5.0, -5.0, 5.0);
		glVertex3f(-5.0, -5.0, 5.0);
		glVertex3f(-5.0, 5.0, 5.0);
		glVertex3f(5.0, 5.0, 5.0);

	glEnd();
	
	glRotatef(theta, 1.0, 0.0, 0.0);
	glRotatef(alpha, 0.0, 1.0, 0.0);
   

      GLubyte indices[] = {	4, 5, 6, 7, 
							1, 2, 6, 5,
							0, 1, 5, 4,
							0, 3, 2, 1,
							0, 4, 7, 3,
							2, 3, 7, 6  };

    	  
	glDrawElements (GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
	

	glFlush ();
	glutSwapBuffers(); //Flip the page
}

void RotateCube(void)
{
	theta+=3; // Increment X rotation angle
	alpha+=3; // Increment Y rotation angle

	if( theta > 360.0) theta -= 360.0;
    if( alpha > 360.0) alpha -= 360.0;

	glutPostRedisplay();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum(-1.0, 1.0, -1.0, 1.0, 0.5, 20.0);
   glMatrixMode(GL_MODELVIEW);
}


void keyboard(unsigned char key, int x, int y)
{
	//Exit when the <ESC> key is pressed
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
   glutInitWindowSize (250, 250); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("MyRotoCube");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutIdleFunc(RotateCube);
   glutKeyboardFunc (keyboard);
   glutMainLoop();
   return 0;
}
