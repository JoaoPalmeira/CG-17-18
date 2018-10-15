#include "estruturas.h"

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"


#define FILL 1 
#define LINE 2 
#define POINT 3

using namespace std;


Figura figura;

//Angulos e raio
float alpha = 0.5 , beta = 0.5 , radius = 10 ;
//Variaveis para rotates
float xOrigin = -1 ; 
float yOrigin = -1 ;  
float xr = 0;
float zr = 0;

void changeSize(int w, int h) {
	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;
	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;
	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

//Função que gera floats aleatorios
float RandomFloat(float x1, float x2) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = x2 - x1;
    float r = random * diff;
    return x1 + r;
}

void renderScene(void) {
	srand(0)  ; 
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(cos(beta)*sin(alpha)*radius, sin(beta)*radius, cos(beta)*cos(alpha)*radius,
		0.0, 0.0, -1.0,
		0.0f, 1.0f, 0.0f);

	// put drawing instructions here

	glTranslatef(xr, 0, zr);

	glBegin(GL_TRIANGLES) ;
	for(list<Modelo>::iterator it = figura.modelos.begin(); it != figura.modelos.end() ; it++){
		for(list<Ponto>::iterator it2 = it->pontos.begin() ; it2!=it->pontos.end(); it2++){
            //floats aleatorios para a escolha da cor dos triangulos
			float r1 , r2 , r3 ;
			r1 = RandomFloat(0,1); 
			r2 = RandomFloat(0,1); 
			r3 = RandomFloat(0,1);  
			glColor3f(r1, r2, r3);
			glVertex3f(it2->coordx,it2->coordy , it2->coordz) ;
			
			}
		}

		glEnd() ; 

	// End of frame
	glutPostRedisplay() ; 
	glutSwapBuffers();
}

//Funcionalidades para os rotates
void processNormalKeys(unsigned char key, int x, int y){
	switch (key){
        case 27: exit(0); break;
		case 119 : radius -= 0.1; break;
		case 115 : radius += 0.1; break;
		case ('j'): xr=xr+0.1; break;
		case ('l'): xr=xr-0.1; break;
		case('i'): zr=zr-0.1; break;
		case('k'): zr=zr+0.1; break;
    }
    glutPostRedisplay();
}

//Função que permite mover o objeto para cima/baixo, esquerda/direita
void processSpecialKeys(int key, int x1, int y1){
	switch (key){
		case GLUT_KEY_LEFT : alpha -= 0.1; break;
		case GLUT_KEY_RIGHT : alpha += 0.1; break;
		case GLUT_KEY_UP : if(beta < M_PI/2) beta += 0.1; break;
		case GLUT_KEY_DOWN : if(beta > -M_PI/2) beta -= 0.1; break;
	}
}

//Função que permite selecionar o objeto através do touchpad
void mouseButton(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_UP) { xOrigin = -1; yOrigin = -1; }
		else { xOrigin = x; yOrigin = y; }
	}
}

//Função que permite mexer na camera através do touchpad
void mouseMove(int x, int y){
	
	if(xOrigin >= 0){
        alpha = (x + xOrigin) * 0.01;
        if(beta < M_PI/2) beta = (y - yOrigin) * 0.01;
        if(beta > -M_PI/2) beta = (y - yOrigin) * 0.01;
    }
    glutPostRedisplay();
}

void processFillMenu(int option){
	switch (option){
		case FILL: glPolygonMode(GL_FRONT, GL_FILL); break;
		case LINE: glPolygonMode(GL_FRONT, GL_LINE); break;
        case POINT: glPolygonMode(GL_FRONT, GL_POINT); break;
	}
}

void createGLUTMenus(){
    int menu;
    menu = glutCreateMenu(processFillMenu);
    
    glutAddMenuEntry("Fill",FILL);
	glutAddMenuEntry("Line",LINE);
    glutAddMenuEntry("Point",POINT);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


int main(int argc, char **argv) {

	figura.load(argv[1]) ; 
	
	// put GLUT init here
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(400, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM - TRABALHO PRATICO DE COMPUTAÇÃO GRÁFICA");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// put callback registration here

	glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);


	createGLUTMenus();

	// OpenGL settings 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// enter GLUT's main loop
	glutMainLoop();

	return 0;
}
