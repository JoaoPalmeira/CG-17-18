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


Figura figura ; 

float alpha = 0.5 , beta = 0.5 , radius = 10 ; 
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
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

// --- DESENHAR ORBITA - ELIPSE --- //
void drawOrbita(float rX, float rZ){
    float slice = M_PI/180;
    float doisPi = 2*M_PI;
    
    glBegin(GL_LINE_STRIP);
    
    for(float i=0; i<=doisPi ; i+=slice)
        glVertex3f(cos(i)*rX,0,sin(i)*rZ);
    
    glEnd();
}


void renderGrupo(list<Grupo>::iterator g){
	glPushMatrix();

	    if(!strcmp(g->tipo.c_str(),"orbita")){
        glRotatef(g->specs.angulo, g->specs.eixox, g->specs.eixoy, g->specs.eixoz);
        glTranslatef(g->specs.coordx, g->specs.coordy, g->specs.coordz);
    }
    else{
        glTranslatef(g->specs.coordx, g->specs.coordy, g->specs.coordz);
        glRotatef(g->specs.angulo, g->specs.eixox, g->specs.eixoy, g->specs.eixoz);
    }
    
    glScalef(g->specs.escala_x, g->specs.escala_y, g->specs.escala_z);
    glColor3f(g->cor.r,g->cor.g,g->cor.b);
    //Função que desenha as elipses das orbitas
    drawOrbita(g->orbita.raioX,g->orbita.raioZ);
    
    for(list<Modelo>::iterator itm = g->modelos.begin(); itm != g->modelos.end(); itm++){
        glBegin(GL_TRIANGLES);
        
        for(list<Ponto>::iterator itp = itm->pontos.begin(); itp != itm->pontos.end(); itp++){
            glVertex3f(itp->coordx,itp->coordy,itp->coordz);
        }
        
        glEnd();
    }
    
    for(list<Grupo>::iterator itg = g->grupos.begin(); itg != g->grupos.end(); itg++)
        renderGrupo(itg);

	glPopMatrix();

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

	glTranslatef(xr, 0, zr);
	// put drawing instructions here
	for(list<Grupo>::iterator itg = figura.grupos.begin(); itg != figura.grupos.end(); itg++)
        renderGrupo(itg);

	// End of frame
	glutPostRedisplay() ; 
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y){
	switch (key){
        case 27: exit(0); break;
		case ('w') : radius -= 10; break;
		case ('s') : radius += 10; break;
		case ('g'): xr=xr+1; break;
		case ('j'): xr=xr-1; break;
		case('y'): zr=zr-1; break;
		case('h'): zr=zr+1; break;

    }
    glutPostRedisplay();
   
}

void processSpecialKeys(int key, int x1, int y1){
	switch (key){
		case GLUT_KEY_LEFT : alpha -= 0.1; break;
		case GLUT_KEY_RIGHT : alpha += 0.1; break;
		case GLUT_KEY_UP : if(beta < M_PI/2) beta += 0.1; break;
		case GLUT_KEY_DOWN : if(beta > -M_PI/2) beta -= 0.1; break;
	}

}

void mouseButton(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_UP) { xOrigin = -1; yOrigin = -1; }
		else { xOrigin = x; yOrigin = y; }
	}
}

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
	glutCreateWindow("CG@DI-UM - TRABALHO PRATICO");

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

	// enter GLUT's main loop
	glutMainLoop();

	return 0;
}
