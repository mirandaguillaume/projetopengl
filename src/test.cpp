#ifndef config_h
#define config_h

#include "os.h"

#ifdef MAC
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#endif

#ifdef LINUX
#include <GL/glut.h>
#endif

#endif

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include<ctime>

#include "Mnt.hpp"

#define PATH "/Users/emmanuelmelin/Documents/donnees/codes_exemples/TDA2/TD2"


using namespace std;

static GLboolean vboenable=0,lumenable=0;


void MyReDisplay(void)
{
	glutPostRedisplay();
	
}


void fleche(float t1,float t2,float t3,float taille,char dim){
	switch(dim)
	{
		case 'x': 
			glBegin(GL_LINE_STRIP);
			glVertex3f (t1-taille, t2+taille, t3); 
			glVertex3f (t1, t2, t3); 
			glVertex3f (t1-taille, t2-taille, t3); 	
			glEnd();
			break;
		case 'y': 
			glBegin(GL_LINE_STRIP);
			glVertex3f (t1, t2-taille, t3+taille); 
			glVertex3f (t1, t2, t3); 
			glVertex3f (t1, t2-taille, t3-taille); 	
			glEnd();
			break;
		case 'z': 
			glBegin(GL_LINE_STRIP);
			glVertex3f (t1, t2+taille, t3-taille); 
			glVertex3f (t1, t2, t3); 
			glVertex3f (t1, t2-taille, t3-taille); 	
			glEnd();
			break;
		default :;
	}
}


void repere(float t){
	float coef=1;
	GLboolean islumenable;
 	glGetBooleanv(GL_LIGHTING, &islumenable);
	
	if(islumenable)glDisable(GL_LIGHTING);
	
	
	glDisable(GL_LIGHTING);
	glLineWidth(1.0);
	glBegin(GL_LINES);
	glColor3f(1.0,0.0,0.0);
	glVertex3f (t, 0.0, 0.0); 
	glVertex3f (-t, 0.0, 0.0);
	glColor3f(0.0,1.0,0.0); 
	glVertex3f ( 0.0, 0.0, coef*t); 
	glVertex3f ( 0.0, 0.0, -t*coef); 
	glColor3f(0.0,1.0,1.0); 
	glVertex3f ( 0.0, t, 0.0); 
	glVertex3f ( 0.0, -t, 0.0); 
	glEnd();
	glColor3f(1.0,0.0,0.0);
	fleche(t, 0.0, 0.0,t*0.1 ,'x');	
	glColor3f(0.0,1.0,0.0); 
	fleche(0.0, 0.0, coef*t,t*0.1 ,'z');	
	glColor3f(0.0,1.0,1.0); 
	fleche(0.0, t, 0.0,t*0.1 ,'y');	
	glLineWidth(0.1);
	if(islumenable)glEnable(GL_LIGHTING);
}


void framerate(void){
	static int frame=0,time,timebase=0;
	static char titre[100];
	
	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(titre,"FPS:%4.2f",
				frame*1000.0/(time-timebase));
		glutSetWindowTitle(titre);	
		timebase = time;		
		frame = 0;
	}
	
}	



GLfloat R=0.0;

Mnt* test;

void display(void)
{
//	framerate();
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //vide r√àellement la fen√çtre
	glLoadIdentity();
	float* sommets = test->toSommetsTab();
	GLuint * indexes = test->toIndexTab();
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,sommets);
	glTranslated(0,0,-10);
	//	glColor3f(0,255,0);
	
	glDrawElements(GL_TRIANGLES,8*3,GL_UNSIGNED_INT,indexes);
	glutSwapBuffers();
	delete sommets;
	delete indexes;
}


void init (string fic) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0); //√àtabli vers quelle couleur la fen√çtre sera vid√àe
	glEnable(GL_DEPTH_TEST);
	test = new Mnt(fic);
}



void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(70.0, (GLfloat) w/(GLfloat) h, 0.01, 30.0);
	glMatrixMode(GL_MODELVIEW);

}


void key(unsigned char key,int x,int y) {
	switch ( key ) {
		case 'w'  : R-=0.1f;printf(" %f -Rayon ",R);						
			break;
		case 'x'  : R+=0.1f; printf(" %f +Rayon ",R);					
			break;			
	case 0x1B : exit(0); }
	MyReDisplay();
}

void GestionSpecial(int key, int x, int y)
{printf("vous avez appuy√à sur ");
	switch (key)
	{	
		case GLUT_KEY_F1 : printf("F1 ");glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			
			break;
		case GLUT_KEY_F2 : printf("F2 ");glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);break;

		case GLUT_KEY_LEFT : R-=0.1;printf("Gauche ");break; 
		case GLUT_KEY_RIGHT : R+=0.1; printf("Droite ");break; 

	}	
	printf("position de la souris : ");
	printf("%d,%d ",x,y);
	MyReDisplay();
	
}	

void Effets(int selection)
{ 
	
	switch (selection)
	{	
		case 0 : 	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);break; 
		case 1 :glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);break; 
		case 2 :exit(0);break; 
	}		
	
	MyReDisplay();	
}

void Menu2(int selection)
{ 
	printf("selection Menu2 %i",selection);
	switch (selection)
	{	
		case 0 : 	printf("action toto");break; 
		case 1:	printf("action titi");break; 	
	}	
		MyReDisplay();	
}

void spinDisplay(void)
{
	R+=2;
	glutPostRedisplay();
}


int main(int argc, char** argv)
{

  test = NULL;
	glutInit(&argc, argv); 
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 350);
	glutCreateWindow ("Second Window"); 
	init (argv[1]);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutSpecialFunc(GestionSpecial);
	glutDisplayFunc(display); 
	glutIdleFunc(spinDisplay);

	GLuint* indexes = test->toIndexTab();

	
	for (int i=0;i<8*3;i++)
	  cout<<indexes[i]<<endl;
	
	int sMenu;
	sMenu = glutCreateMenu(Menu2);
	glutAddMenuEntry("toto",0);
	glutAddMenuEntry("titi",1);

	int mainMenu;
	mainMenu = glutCreateMenu(Effets);
	glutAddMenuEntry("Mode plein",0);
	glutAddMenuEntry("Mode fil de fer",1);
	glutAddMenuEntry("Quitter",2);
	glutAddSubMenu("Maillages",
				   sMenu);

	glutAttachMenu(GLUT_LEFT_BUTTON);	
	
	

	glutMainLoop();
	delete test;
	delete indexes;
	return 0;   
}

