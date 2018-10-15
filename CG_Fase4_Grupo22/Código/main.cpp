#include "/usr/local/Cellar/devil/1.8.0_1/include/IL/il.h"
#include "estruturas.h"
#include <GLUT/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "tinyXml/tinyxml.h"
#include "tinyXml/tinystr.h"
#include "tinyXml/tinyxmlparser.cpp"
#include "tinyXml/tinystr.cpp"
#include "tinyXml/tinyxml.cpp"
#include "tinyXml/tinyxmlerror.cpp"


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

int times , timebase , frame=0 , fps=0 ; 
char print[20] = "" ; 

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
void drawOrbit(float raioX, float raioZ, int nControl)
{
    float res[3];
    float p[nControl][3];
    float t;
    int index, indices[4];
    
    float doisPi = 2*M_PI, slice = doisPi/nControl;
    for(int i=0; i<nControl ; i++)
    {
        p[i][0] = cos(i*slice)*raioX;
        p[i][1] = 0;
        p[i][2] = sin(i*slice)*raioZ;
    }
    
    glBegin(GL_LINE_LOOP);
    
    for(float a=0; a<1; a+=0.01)
    {
        t = a*nControl;
        index = floor(t);
        t = t - index;
        
        indices[0] = (index + nControl-1)%nControl;
        indices[1] = (indices[0]+1)%nControl;
        indices[2] = (indices[1]+1)%nControl;
        indices[3] = (indices[2]+1)%nControl;
        
        res[0] = (-0.5*p[indices[0]][0] +1.5*p[indices[1]][0] -1.5*p[indices[2]][0] +0.5*p[indices[3]][0])*t*t*t + (p[indices[0]][0] -2.5*p[indices[1]][0] +2*p[indices[2]][0] -0.5*p[indices[3]][0])*t*t + (-0.5*p[indices[0]][0] +0.5*p[indices[2]][0])*t + p[indices[1]][0];
        
        res[1] = (-0.5*p[indices[0]][1] +1.5*p[indices[1]][1] -1.5*p[indices[2]][1] +0.5*p[indices[3]][1])*t*t*t + (p[indices[0]][1] -2.5*p[indices[1]][1] +2*p[indices[2]][1] -0.5*p[indices[3]][1])*t*t + (-0.5*p[indices[0]][1] +0.5*p[indices[2]][1])*t + p[indices[1]][1];
        
        res[2] = (-0.5*p[indices[0]][2] +1.5*p[indices[1]][2] -1.5*p[indices[2]][2] +0.5*p[indices[3]][2])*t*t*t + (p[indices[0]][2] -2.5*p[indices[1]][2] +2*p[indices[2]][2] -0.5*p[indices[3]][2])*t*t + (-0.5*p[indices[0]][2] +0.5*p[indices[2]][2])*t + p[indices[1]][2];
        
        glVertex3f(res[0],res[1],res[2]);
    }
    
    glEnd();
}

void getRotation(float time , float eixox , float eixoy , float eixoz){
	float angle = 360/(time*1000) ; 
	int t = glutGet(GLUT_ELAPSED_TIME) ; 
	glRotatef(t*angle , eixox , eixoy , eixoz) ; 
}

void getTranslation(float time , list<Ponto> pontos){
	int nControl = (int) pontos.size() ; 
	float res[3] ; 
	float p[nControl][3] ;
	float t,a ; 
	int index , indices[4] , i=0 ; 

	for(list<Ponto>::iterator itp = pontos.begin() ; itp!=pontos.end() ; itp++)
	{
		p[i][0] = itp->x ; 
		p[i][1] = itp->y ; 
		p[i][2] = itp->z ;
		i++ ;  
	}


	float tempo = glutGet(GLUT_ELAPSED_TIME)%(int)(time*1000) ; 
	a = tempo/(time*1000) ; 

	t=a*nControl ; 
	index = floor(t) ; 
	t=t-index ; 

	indices[0] = (index + nControl-1)%nControl ; 
	indices[1] = (indices[0]+1)%nControl ; 
	indices[2] = (indices[1]+1)%nControl ; 
	indices[3] = (indices[2]+1)%nControl ; 

	res[0] = (-0.5*p[indices[0]][0] +1.5*p[indices[1]][0] -1.5*p[indices[2]][0]
	 +0.5*p[indices[3]][0])*t*t*t + (p[indices[0]][0] -2.5*p[indices[1]][0]
	  +2*p[indices[2]][0] -0.5*p[indices[3]][0])*t*t + (-0.5*p[indices[0]][0] 
	  +0.5*p[indices[2]][0])*t + p[indices[1]][0];

	 res[1] = (-0.5*p[indices[0]][1] +1.5*p[indices[1]][1] -1.5*p[indices[2]][1] +0.5*p[indices[3]][1])*t*t*t 
	 + (p[indices[0]][1] -2.5*p[indices[1]][1] +2*p[indices[2]][1] -0.5*p[indices[3]][1])*t*t 
	 + (-0.5*p[indices[0]][1] +0.5*p[indices[2]][1])*t + p[indices[1]][1];
    
    res[2] = (-0.5*p[indices[0]][2] +1.5*p[indices[1]][2] -1.5*p[indices[2]][2]
     +0.5*p[indices[3]][2])*t*t*t + (p[indices[0]][2] -2.5*p[indices[1]][2] +2*p[indices[2]][2] -0.5*p[indices[3]][2])*t*t 
    + (-0.5*p[indices[0]][2] +0.5*p[indices[2]][2])*t + p[indices[1]][2];


    glTranslatef(res[0] , res[1] , res[2]) ; 
}




void renderGrupo(list<Grupo>::iterator g){
	glPushMatrix();

	    if(!strcmp(g->tipo.c_str(),"orbita"))
    {
        glRotatef(g->rotacao.angulo, g->rotacao.eixox, g->rotacao.eixoy, g->rotacao.eixoz);
        glTranslatef(g->translacao.x, g->translacao.y, g->translacao.z);
    }
    else
    {
       
        if(g->translacao.tempo == -1) glTranslatef(g->translacao.x, g->translacao.y, g->translacao.z);
        else getTranslation(g->translacao.tempo,g->translacao.pontos);
        
        if(g->rotacao.tempo == -1) glRotatef(g->rotacao.angulo, g->rotacao.eixox, g->rotacao.eixoy, g->rotacao.eixoz);
        else getRotation(g->rotacao.tempo,g->rotacao.eixox,g->rotacao.eixoy,g->rotacao.eixoz);
    }
    
    glScalef(g->escala.x, g->escala.y, g->escala.z);
    glColor3f(g->cor.r,g->cor.g,g->cor.b);
    
    glDisable(GL_LIGHTING);
    drawOrbit(g->orbita.raioX,g->orbita.raioZ,g->orbita.nControl);
    glEnable(GL_LIGHTING);
    
    
    for(list<Modelo>::iterator itm = g->modelos.begin(); itm != g->modelos.end(); itm++)
    {
        GLfloat amb[3] = {itm->ambR,itm->ambG,itm->ambB}; glLightfv(GL_LIGHT0,GL_AMBIENT,amb);
        GLfloat diff[3] = {itm->diffR,itm->diffG,itm->diffB}; glLightfv(GL_LIGHT0,GL_DIFFUSE,diff);
        GLfloat spec[3] = {itm->specR,itm->specG,itm->specB}; glMaterialfv(GL_FRONT,GL_SPECULAR,spec);
        glLightfv(GL_LIGHT0,GL_SPECULAR,spec); glMaterialf(GL_FRONT,GL_SHININESS,120);
        GLfloat emi[3] = {itm->emiR,itm->emiG,itm->emiB}; glMaterialfv(GL_FRONT,GL_EMISSION,emi); glLightfv(GL_LIGHT0,GL_EMISSION,emi);
        
        glBindTexture(GL_TEXTURE_2D,itm->texID);
        
        glBindBuffer(GL_ARRAY_BUFFER,itm->buffers[0]);
        glVertexPointer(3,GL_FLOAT,0,0);
        glBindBuffer(GL_ARRAY_BUFFER,itm->buffers[1]);
        glNormalPointer(GL_FLOAT,0,0);
        glBindBuffer(GL_ARRAY_BUFFER,itm->buffers[2]);
        glTexCoordPointer(2,GL_FLOAT,0,0);
        
        glDrawArrays(GL_TRIANGLES,0,itm->pontos);
        glBindTexture(GL_TEXTURE_2D,0);
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

	// put drawing instructions here
	    for(list<Light>::iterator itl = figura.luzes.begin(); itl != figura.luzes.end(); itl++)
    {
        GLfloat pos[4] = { itl->posX, itl->posY, itl->posZ, itl->tipo };
        glLightfv(GL_LIGHT0,GL_POSITION,pos);
        glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,0.4);
    }

	for(list<Grupo>::iterator itg = figura.grupos.begin(); itg != figura.grupos.end(); itg++)
        renderGrupo(itg);
    frame++ ; 
    times=glutGet(GLUT_ELAPSED_TIME) ; 
    if(times -timebase >1000)
    {
    	fps = frame*1000.0/(times-timebase) ; 
    	timebase = times ; 
    	frame = 0 ; 
    }

   sprintf(print,"%d - %d " , fps , times/1000) ;  	
   glutSetWindowTitle(print) ; 
	// End of frame
	glutPostRedisplay();
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key)
    {
        case 27: exit(0); break;
		case 119 : radius -= 10; break;
		case 115 : radius += 10; break;
		case ('j'): xr=xr+1; break;
		case ('l'): xr=xr-1; break;
		case('i'): zr=zr-1; break;
		case('k'): zr=zr+1; break;

    }
    glutPostRedisplay();
   
}

void processSpecialKeys(int key, int x1, int y1)
{
	switch (key)
    {
		case GLUT_KEY_LEFT : alpha -= 0.1; break;
		case GLUT_KEY_RIGHT : alpha += 0.1; break;
		case GLUT_KEY_UP : if(beta < M_PI/2) beta += 0.1; break;
		case GLUT_KEY_DOWN : if(beta > -M_PI/2) beta -= 0.1; break;
	}

}

void mouseButton(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_UP) { xOrigin = -1; yOrigin = -1; }
		else { xOrigin = x; yOrigin = y; }
	}
}

void mouseMove(int x, int y)
{
	
	if(xOrigin >= 0)
    {
        alpha = (x + xOrigin) * 0.01;
        if(beta < M_PI/2) beta = (y - yOrigin) * 0.01;
        if(beta > -M_PI/2) beta = (y - yOrigin) * 0.01;
    }
    glutPostRedisplay();
}

void processFillMenu(int option)
{
	switch (option)
    {
		case FILL: glPolygonMode(GL_FRONT, GL_FILL); break;
		case LINE: glPolygonMode(GL_FRONT, GL_LINE); break;
        case POINT: glPolygonMode(GL_FRONT, GL_POINT); break;
	}
}

void createGLUTMenus()
{
    int menu;
    menu = glutCreateMenu(processFillMenu);
    
    glutAddMenuEntry("Fill",FILL);
	glutAddMenuEntry("Line",LINE);
    glutAddMenuEntry("Point",POINT);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


int main(int argc, char **argv) {


	// put GLUT init here
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(400, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM - TRABALHO PRATICO");

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

	// put callback registration here

	glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);


	createGLUTMenus();

	glewInit() ; 
	//figura.load(argv[1]) ; 
	
	//figura.load("./XML/teapot1.xml");
    figura.load("SistemaSolar/sistemasolar.xml");

	// OpenGL settings 
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
	
	

	// enter GLUT's main loop
	glutMainLoop();

	return 0;
}