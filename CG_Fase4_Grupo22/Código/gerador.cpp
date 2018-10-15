#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;




void drawPlano(float length , float width , char* filename){
	FILE* f ; 
	char* aux = (char*)malloc(sizeof(char)*64) ; 
	strcpy(aux , filename) ;

	strcat(aux , ".3d") ; 
	f = fopen(aux,"w") ; 

    int pontos = 2*2*3;
	if(f!=NULL)
	{
        fprintf(f,"%d\n" , pontos) ;
		fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, 0.0, -width/2, 0.0, 1.0, 0.0, 0.0, 0.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, 0.0, width/2, 0.0, 1.0, 0.0, 0.0, 1.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, 0.0, width/2, 0.0, 1.0, 0.0, 1.0, 1.0);
        
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, 0.0, width/2, 0.0, 1.0, 0.0, 1.0, 1.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, 0.0, -width/2, 0.0, 1.0, 0.0, 1.0, 0.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, 0.0, -width/2, 0.0, 1.0, 0.0, 0.0, 0.0);
        
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, 0.0, width/2, 0.0, -1.0, 0.0, 0.0, -1.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, 0.0, -width/2, 0.0, -1.0, 0.0, 0.0, 0.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, 0.0, width/2, 0.0, -1.0, 0.0, 1.0, -1.0);
        
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, 0.0, -width/2, 0.0, -1.0, 0.0, 1.0, 0.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, 0.0, width/2, 0.0, -1.0, 0.0, 1.0, -1.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, 0.0, -width/2, 0.0, -1.0, 0.0, 0.0, 0.0); 
	}

	fclose(f) ; 
}

void createXML(char* filename){
	FILE* f ;

	char* aux = (char*)malloc(sizeof(char)*64) ; 
	strcpy(aux , filename) ; 

	f = fopen(strcat(aux,".xml"),"w") ; 
	
	char* ss = (char*)malloc(sizeof(char)*100) ; 
	 ss = strcat(ss, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<cena>\n") ;
	 ss = strcat(ss,"<modelo ficheiro=\"3D/") ; 
	 ss = strcat(ss,filename) ; 
	 ss = strcat(ss , ".3d\" />\n" );
	 ss= strcat(ss,"</cena>\n" );

	 fprintf(f , "%s" , ss) ; 
	 fclose(f) ; 
} 




void drawCaixa(float length , float height , float width , char* filename){
	FILE* f ; 
	char* aux = (char*)malloc(sizeof(char)*64) ; 
	strcpy(aux , filename) ;

	strcat(aux , ".3d") ; 
    int pontos=2*6*3;
	f = fopen(aux,"w") ; 

	if(f!=NULL)
	{
        fprintf(f,"%d\n" , pontos) ;
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, -height/2, -width/2, 0.0, -1.0, 0.0, 1.0, 0.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, -height/2, width/2, 0.0, -1.0, 0.0, 0.0, -1.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, -height/2, -width/2, 0.0, -1.0, 0.0, 0.0, 0.0);
        
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, -height/2, width/2, 0.0, -1.0, 0.0, 0.0, -1.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, -height/2, -width/2, 0.0, -1.0, 0.0, 1.0, 0.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, -height/2, width/2, 0.0, -1.0, 0.0, 1.0, -1.0);
        
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, height/2, -width/2, 0.0, 1.0, 0.0, 1.0, 0.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, height/2, -width/2, 0.0, 1.0, 0.0, 0.0, 0.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, height/2, width/2, 0.0, 1.0, 0.0, 0.0, 1.0);
        
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, height/2, width/2, 0.0, 1.0, 0.0, 0.0, 1.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, height/2, width/2, 0.0, 1.0, 0.0, 1.0, 1.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, height/2, -width/2, 0.0, 1.0, 0.0, 1.0, 0.0);
        
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, -height/2, width/2, 0.0, 0.0, 1.0, 0.0, 0.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, -height/2, width/2, 0.0, 0.0, 1.0, 1.0, 0.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, height/2, width/2, 0.0, 0.0, 1.0, 0.0, -1.0);
        
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, -height/2, width/2, 0.0, 0.0, 1.0, 1.0, 0.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, height/2, width/2, 0.0, 0.0, 1.0, 1.0, -1.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, height/2, width/2, 0.0, 0.0, 1.0, 0.0, -1.0);
        
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, -height/2, width/2, 1.0, 0.0, 0.0, 0.0, 0.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, -height/2, -width/2, 1.0, 0.0, 0.0, 1.0, 0.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, height/2, width/2, 1.0, 0.0, 0.0, 0.0, -1.0);
        
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, -height/2, -width/2, 1.0, 0.0, 0.0, 1.0, 0.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, height/2, -width/2, 1.0, 0.0, 0.0, 1.0, -1.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, height/2, width/2, 1.0, 0.0, 0.0, 0.0, -1.0);
        
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, -height/2, -width/2, 0.0, 0.0, -1.0, 0.0, 0.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, -height/2, -width/2, 0.0, 0.0, -1.0, 1.0, 0.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, height/2, -width/2, 0.0, 0.0, -1.0, 0.0, -1.0);
        
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, -height/2, -width/2, 0.0, 0.0, -1.0, 1.0, 0.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, height/2, -width/2, 0.0, 0.0, -1.0, 1.0, -1.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",length/2, height/2, -width/2, 0.0, 0.0, -1.0, 0.0, -1.0);
        
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, -height/2, -width/2, -1.0, 0.0, 0.0, 0.0, 0.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, -height/2, width/2, -1.0, 0.0, 0.0, 1.0, 0.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, height/2, -width/2, -1.0, 0.0, 0.0, 0.0, -1.0);
        
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, -height/2, width/2, -1.0, 0.0, 0.0, 1.0, 0.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, height/2, width/2, -1.0, 0.0, 0.0, 1.0, -1.0);
        fprintf(f,"%f %f %f %f %f %f %f %f\n",-length/2, height/2, -width/2, -1.0, 0.0, 0.0, 0.0, -1.0);
	}

	fclose(f) ; 	
}

void drawEsfera(float radius , int slices , int stacks , char* filename){
	FILE* f ; 
	
	char* aux = (char*)malloc(sizeof(char)*64) ; 
	strcpy(aux , filename) ;
	strcat(aux , ".3d") ; 

	f = fopen(aux,"w") ; 
	float doisPi = 2*M_PI, slice = doisPi/slices;
    float pi = M_PI, stack = pi/stacks;
	float piMeios = M_PI/2 ;   
    int pontos = 2*slices*stacks*3;

	if(f!=NULL)
	{
        fprintf(f,"%d\n" , pontos) ;
        for(int j=-stacks/2; j < stacks/2; j++)
            for(int i=0; i < slices; i++)
            {
				fprintf(f,"%f %f %f %f %f %f %f %f\n",cos((j+1)*stack)*sin(i*slice)*radius, sin((j+1)*stack)*radius, cos((j+1)*stack)*cos(i*slice)*radius, cos((j+1)*stack)*sin(i*slice), sin((j+1)*stack), cos((j+1)*stack)*cos(i*slice), (i*slice)/doisPi, -((j+1+stacks/2)*stack)/pi);
                fprintf(f,"%f %f %f %f %f %f %f %f\n",cos(j*stack)*sin(i*slice)*radius, sin(j*stack)*radius, cos(j*stack)*cos(i*slice)*radius, cos(j*stack)*sin(i*slice), sin(j*stack), cos(j*stack)*cos(i*slice), (i*slice)/doisPi, -((j+stacks/2)*stack)/pi);
                fprintf(f,"%f %f %f %f %f %f %f %f\n",cos(j*stack)*sin((i+1)*slice)*radius, sin(j*stack)*radius, cos(j*stack)*cos((i+1)*slice)*radius, cos(j*stack)*sin((i+1)*slice), sin(j*stack), cos(j*stack)*cos((i+1)*slice), ((i+1)*slice)/doisPi, -((j+stacks/2)*stack)/pi);
                
                fprintf(f,"%f %f %f %f %f %f %f %f\n",cos((j+1)*stack)*sin(i*slice)*radius, sin((j+1)*stack)*radius, cos((j+1)*stack)*cos(i*slice)*radius, cos((j+1)*stack)*sin(i*slice), sin((j+1)*stack), cos((j+1)*stack)*cos(i*slice), (i*slice)/doisPi, -((j+1+stacks/2)*stack)/pi);
                fprintf(f,"%f %f %f %f %f %f %f %f\n",cos(j*stack)*sin((i+1)*slice)*radius, sin(j*stack)*radius, cos(j*stack)*cos((i+1)*slice)*radius, cos(j*stack)*sin((i+1)*slice), sin(j*stack), cos(j*stack)*cos((i+1)*slice), ((i+1)*slice)/doisPi, -((j+stacks/2)*stack)/pi);
                fprintf(f,"%f %f %f %f %f %f %f %f\n",cos((j+1)*stack)*sin((i+1)*slice)*radius, sin((j+1)*stack)*radius, cos((j+1)*stack)*cos((i+1)*slice)*radius, cos((j+1)*stack)*sin((i+1)*slice), sin((j+1)*stack), cos((j+1)*stack)*cos((i+1)*slice), ((i+1)*slice)/doisPi, -((j+1+stacks/2)*stack)/pi);
		}
	}
	fclose(f) ; 
}


double *normal(double ponto1[3], double ponto2[3], double ponto3[3])
{
    double *normal = NULL;
    normal = (double*) malloc(3*sizeof(double));
    
    double vetor1[3] = { ponto2[0]-ponto1[0], ponto2[1]-ponto1[1], ponto2[2]-ponto1[2] };
    double vetor2[3] = { ponto3[0]-ponto1[0], ponto3[1]-ponto1[1], ponto3[2]-ponto1[2] };
    
    double vetor[3];
    vetor[0] = vetor1[1]*vetor2[2] - vetor1[2]*vetor2[1];
    vetor[1] = vetor1[2]*vetor2[0] - vetor1[0]*vetor2[2];
    vetor[2] = vetor1[0]*vetor2[1] - vetor1[1]*vetor2[0];
    
    double vn = sqrt(vetor[0]*vetor[0] + vetor[1]*vetor[1] + vetor[2]*vetor[2]);
    
    normal[0] = vetor[0]/vn;
    normal[1] = vetor[1]/vn;
    normal[2] = vetor[2]/vn;
    
    return normal;
}


void drawCone(float radius , float height ,  int slices , int stacks , char* filename){
	FILE* f ; 
	
	char* aux = (char*)malloc(sizeof(char)*64) ; 
	strcpy(aux , filename) ;
	strcat(aux , ".3d") ; 
	
	f = fopen(aux,"w") ; 

	float slice = (360/slices)*(M_PI/180) ; 
	float stack = height/stacks;
	float raio = radius/stacks ; 
	float doisPI = M_PI*2 ;  
     int pontos = slices*3 + 2*slices*stacks*3;

	if(f!=NULL)
	    {
        fprintf(f,"%d\n",pontos);
        
        for(int i=0; i < slices; i++)
        {
            fprintf(f,"%f %f %f %f %f %f %f %f\n",0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.5, 0.5);
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin((i+1)*slice)*radius, 0.0, cos((i+1)*slice)*radius, 0.0, -1.0, 0.0, ((i+1)*slice)/doisPI, 0.0);
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin(i*slice)*radius, 0.0, cos(i*slice)*radius, 0.0, -1.0, 0.0, (i*slice)/doisPI, 0.0);
        }
        
        float r = 0;
        for(int j=0; j < stacks; j++)
        {
            for(int i=0; i < slices; i++)
            {
                double p1[3] = { sin(i*slice)*(radius-(r+raio)), (j+1)*stack, cos(i*slice)*(radius-(r+raio)) };
                double p2[3] = { sin(i*slice)*(radius-r), j*stack, cos(i*slice)*(radius-r) };
                double p3[3] = { sin((i+1)*slice)*(radius-r), j*stack, cos((i+1)*slice)*(radius-r) };
                double p4[3] = { sin((i+1)*slice)*(radius-(r+raio)), (j+1)*stack, cos((i+1)*slice)*(radius-(r+raio)) };
                
                double *n1 = normal(p1,p2,p3);
                double *n2 = normal(p2,p3,p1);
                double *n3 = normal(p3,p1,p2);
                
                double *n4 = normal(p1,p3,p4);
                double *n5 = normal(p3,p4,p1);
                double *n6 = normal(p4,p1,p3);

                fprintf(f,"%f %f %f %f %f %f %f %f\n",p1[0],p1[1],p1[2],n1[0],n1[1],n1[2], (i*slice)/doisPI, -((j+1)*stack)/height);
                fprintf(f,"%f %f %f %f %f %f %f %f\n",p2[0],p2[1],p2[2],n2[0],n2[1],n2[2], (i*slice)/doisPI, -(j*stack)/height); 
                fprintf(f,"%f %f %f %f %f %f %f %f\n",p3[0],p3[1],p3[2],n3[0],n3[1],n3[2], ((i+1)*slice)/doisPI, -(j*stack)/height); 
                
                fprintf(f,"%f %f %f %f %f %f %f %f\n",p1[0],p1[1],p1[2],n4[0],n4[1],n4[2], (i*slice)/doisPI, -((j+1)*stack)/height);
                fprintf(f,"%f %f %f %f %f %f %f %f\n",p3[0],p3[1],p3[2],n5[0],n5[1],n5[2], ((i+1)*slice)/doisPI, -(j*stack)/height);
                fprintf(f,"%f %f %f %f %f %f %f %f\n",p4[0],p4[1],p4[2],n6[0],n6[1],n6[2], ((i+1)*slice)/doisPI, -((j+1)*stack)/height);
            }
            r += raio;
        }
    }

	fclose(f) ; 
}


void drawCilindro(float radius , float height , int slices , char*filename){
	FILE* f ; 
	int pontos = 4*slices*3;
	char* aux = (char*)malloc(sizeof(char)*64) ; 
	strcpy(aux , filename) ;
	strcat(aux , ".3d") ; 
	
	f = fopen(aux,"w") ; 

	float doisPi = 2*M_PI ; 
	float slice = doisPi/slices; 
	
	if (f!=NULL){
        fprintf(f,"%d\n" , pontos) ;
		for(int i=0; i < slices; i++)
        {
            fprintf(f,"%f %f %f %f %f %f %f %f\n",0.0, -height/2, 0.0, 0.0, -1.0, 0.0, 0.5, 0.5);
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin((i+1)*slice)*radius, -height/2, cos((i+1)*slice)*radius, 0.0, -1.0, 0.0, ((i+1)*slice)/doisPi, 0.0);
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin(i*slice)*radius, -height/2, cos(i*slice)*radius, 0.0, -1.0, 0.0, (i*slice)/doisPi, 0.0);
            
            fprintf(f,"%f %f %f %f %f %f %f %f\n",0.0, height/2, 0.0, 0.0, 1.0, 0.0, 0.5, 0.5);
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin(i*slice)*radius, height/2, cos(i*slice)*radius, 0.0, 1.0, 0.0, (i*slice)/doisPi, 0.0);
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin((i+1)*slice)*radius, height/2, cos((i+1)*slice)*radius, 0.0, 1.0, 0.0, ((i+1)*slice)/doisPi, 0.0);
            
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin(i*slice)*radius, height/2, cos(i*slice)*radius, sin(i*slice), 0.0, cos(i*slice), (i*slice)/doisPi, -1.0);
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin(i*slice)*radius, -height/2, cos(i*slice)*radius, sin(i*slice), 0.0, cos(i*slice), (i*slice)/doisPi, 0.0);
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin((i+1)*slice)*radius, -height/2, cos((i+1)*slice)*radius, sin((i+1)*slice), 0.0, cos((i+1)*slice), ((i+1)*slice)/doisPi, 0.0);
            
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin((i+1)*slice)*radius, height/2, cos((i+1)*slice)*radius, sin((i+1)*slice), 0.0, cos((i+1)*slice), ((i+1)*slice)/doisPi, -1.0);
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin(i*slice)*radius, height/2, cos(i*slice)*radius, sin(i*slice), 0.0, cos(i*slice), (i*slice)/doisPi, -1.0);
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin((i+1)*slice)*radius, -height/2, cos((i+1)*slice)*radius, sin((i+1)*slice), 0.0, cos((i+1)*slice), ((i+1)*slice)/doisPi, 0.0);
        }
	}	
	fclose(f) ; 
}
void drawAnel(float in_r , float out_r ,int slices, char* filename){
	FILE* f ; 
	char* aux = (char*)malloc(sizeof(char)*64) ; 
	strcpy(aux , filename) ;
	strcat(aux , ".3d") ; 
	f = fopen(aux,"w") ;
    int pontos = 4*slices*3;
	float doisPi = 2*M_PI;
	float slice = doisPi/slices;

if (f!=NULL){
    fprintf(f,"%d\n" , pontos) ;
	 for(int i=0; i < slices; i++)
        {
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin(i*slice)*in_r, 0.0, cos(i*slice)*in_r, 0.0, 1.0, 0.0, 0.0, (i*slice)/doisPi);
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin(i*slice)*out_r, 0.0, cos(i*slice)*out_r, 0.0, 1.0, 0.0, -1.0, (i*slice)/doisPi);
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin((i+1)*slice)*in_r, 0.0, cos((i+1)*slice)*in_r, 0.0, 1.0, 0.0, 0.0, ((i+1)*slice)/doisPi);
            
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin(i*slice)*out_r, 0.0, cos(i*slice)*out_r, 0.0, 1.0, 0.0, -1.0, (i*slice)/doisPi);
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin((i+1)*slice)*out_r, 0.0, cos((i+1)*slice)*out_r, 0.0, 1.0, 0.0, -1.0, ((i+1)*slice)/doisPi);
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin((i+1)*slice)*in_r, 0.0, cos((i+1)*slice)*in_r, 0.0, 1.0, 0.0, 0.0, ((i+1)*slice)/doisPi);
            
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin(i*slice)*out_r, 0.0, cos(i*slice)*out_r, 0.0, -1.0, 0.0, -1.0, (i*slice)/doisPi);
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin(i*slice)*in_r, 0.0, cos(i*slice)*in_r, 0.0, -1.0, 0.0, 0.0, (i*slice)/doisPi);
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin((i+1)*slice)*in_r, 0.0, cos((i+1)*slice)*in_r, 0.0, -1.0, 0.0, 0.0, ((i+1)*slice)/doisPi);
            
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin((i+1)*slice)*out_r, 0.0, cos((i+1)*slice)*out_r, 0.0, -1.0, 0.0, -1.0, ((i+1)*slice)/doisPi);
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin(i*slice)*out_r, 0.0, cos(i*slice)*out_r, 0.0, -1.0, 0.0, -1.0, (i*slice)/doisPi);
            fprintf(f,"%f %f %f %f %f %f %f %f\n",sin((i+1)*slice)*in_r, 0.0, cos((i+1)*slice)*in_r, 0.0, -1.0, 0.0, 0.0, ((i+1)*slice)/doisPi);
        }
 }

}

//CLASSE PONTO
class Ponto{
public: float x,y,z;
};

void drawPatch(const char* patchfilename, int tesselation, const char* savefilename)
{
    //--- PARSING PATCH ---//
    fstream f;
    f.open(patchfilename,ios::in);
    
    int patches=0;
    int vertices=0;
    
    vector<vector<int> > indicesPatch;
    vector<Ponto> vertixs;
    
    if(f.is_open())
    {
        string line;
        
        if(getline(f,line)) sscanf(line.c_str(),"%d\n",&patches);
        
        for(int i=0; i<patches ;i++)
        {
            vector<int> aux;
            
            if(getline(f,line))
            {
                int n1=0,n2=0,n3=0,n4=0,n5=0,n6=0,n7=0,n8=0,n9=0,n10=0,n11=0,n12=0,n13=0,n14=0,n15=0,n16=0;
                
                sscanf(line.c_str(),"%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n",&n1,&n2,&n3,&n4,&n5,&n6,&n7,&n8,&n9,&n10,&n11,&n12,&n13,&n14,&n15,&n16);
                
                aux.push_back(n1);
                aux.push_back(n2);
                aux.push_back(n3);
                aux.push_back(n4);
                aux.push_back(n5);
                aux.push_back(n6);
                aux.push_back(n7);
                aux.push_back(n8);
                aux.push_back(n9);
                aux.push_back(n10);
                aux.push_back(n11);
                aux.push_back(n12);
                aux.push_back(n13);
                aux.push_back(n14);
                aux.push_back(n15);
                aux.push_back(n16);
            }
            
            indicesPatch.push_back(aux);
        }
        
        if(getline(f,line)) sscanf(line.c_str(),"%d\n",&vertices);
        
        for(int i=0; i<vertices ;i++)
        {
            float x=0,y=0,z=0;
            if(getline(f,line)) sscanf(line.c_str(),"%f, %f, %f\n",&x,&y,&z);
            
            Ponto p;
            p.x = x; p.y = y; p.z = z;
            
            vertixs.push_back(p);
        }
        
        f.close();
    }
    else { printf("Não foi possível abrir o ficheiro patch!\n"); exit(0); }
    
    //--- DESENHAR PATCHES ---//
    float res[3];
    float t;
    int index,indices[4];
    float q[4][tesselation][3],r[tesselation][tesselation][3],tess = 1/((float)tesselation-1);
    
    float pontos = patches*(tesselation)*2*(tesselation)*3;
    
    fstream g;
    g.open(savefilename,ios::out);
    
    if(g.is_open())
    {   //numero de pontos
        g << pontos; g << '\n';
        
        for(int n=0; n<patches; n++)
        {
            //recolher os vértices do array vertixs para o x y e z
            float p[16][3];
            for(int m=0; m<16; m++)
            {
                p[m][0] = vertixs[indicesPatch[n][m]].x;
                p[m][1] = vertixs[indicesPatch[n][m]].y;
                p[m][2] = vertixs[indicesPatch[n][m]].z;
            }
            
            int j=0,k=0;
            //desenhar as 4 curvas
            for(int i=0; i<15; i+=4)
            {
                indices[0] = i;
                indices[1] = i+1;
                indices[2] = i+2;
                indices[3] = i+3;
                //calcular a curva
                for(int a=0; a<tesselation-1; a++)
                {
                    t = a*tess;
                    index = floor(t);
                    t = t - index;
                    
                    res[0] = (-p[indices[0]][0] +3*p[indices[1]][0] -3*p[indices[2]][0] +p[indices[3]][0])*t*t*t + (3*p[indices[0]][0] -6*p[indices[1]][0] +3*p[indices[2]][0])*t*t + (-3*p[indices[0]][0] +3*p[indices[1]][0])*t + p[indices[0]][0];
                    
                    res[1] = (-p[indices[0]][1] +3*p[indices[1]][1] -3*p[indices[2]][1] +p[indices[3]][1])*t*t*t + (3*p[indices[0]][1] -6*p[indices[1]][1] +3*p[indices[2]][1])*t*t + (-3*p[indices[0]][1] +3*p[indices[1]][1])*t + p[indices[0]][1];
                    
                    res[2] = (-p[indices[0]][2] +3*p[indices[1]][2] -3*p[indices[2]][2] +p[indices[3]][2])*t*t*t + (3*p[indices[0]][2] -6*p[indices[1]][2] +3*p[indices[2]][2])*t*t + (-3*p[indices[0]][2] +3*p[indices[1]][2])*t + p[indices[0]][2];
                    
                    q[j][k][0] = res[0];
                    q[j][k][1] = res[1];
                    q[j][k][2] = res[2];
                    k++;
                }
                
                t = 1;
                
                res[0] = (-p[indices[0]][0] +3*p[indices[1]][0] -3*p[indices[2]][0] +p[indices[3]][0])*t*t*t + (3*p[indices[0]][0] -6*p[indices[1]][0] +3*p[indices[2]][0])*t*t + (-3*p[indices[0]][0] +3*p[indices[1]][0])*t + p[indices[0]][0];
                
                res[1] = (-p[indices[0]][1] +3*p[indices[1]][1] -3*p[indices[2]][1] +p[indices[3]][1])*t*t*t + (3*p[indices[0]][1] -6*p[indices[1]][1] +3*p[indices[2]][1])*t*t + (-3*p[indices[0]][1] +3*p[indices[1]][1])*t + p[indices[0]][1];
                
                res[2] = (-p[indices[0]][2] +3*p[indices[1]][2] -3*p[indices[2]][2] +p[indices[3]][2])*t*t*t + (3*p[indices[0]][2] -6*p[indices[1]][2] +3*p[indices[2]][2])*t*t + (-3*p[indices[0]][2] +3*p[indices[1]][2])*t + p[indices[0]][2];
                
                q[j][k][0] = res[0];
                q[j][k][1] = res[1];
                q[j][k][2] = res[2];
                j++;
                k=0;
            }
            
            for(int j=0; j<tesselation; j++)
            {
                for(int a=0; a<tesselation-1; a++)
                {
                    t = a*tess;;
                    index = floor(t);
                    t = t - index;
                    
                    res[0] = (-q[0][j][0] +3*q[1][j][0] -3*q[2][j][0] +q[3][j][0])*t*t*t + (3*q[0][j][0] -6*q[1][j][0] +3*q[2][j][0])*t*t + (-3*q[0][j][0] +3*q[1][j][0])*t + q[0][j][0];
                    
                    res[1] = (-q[0][j][1] +3*q[1][j][1] -3*q[2][j][1] +q[3][j][1])*t*t*t + (3*q[0][j][1] -6*q[1][j][1] +3*q[2][j][1])*t*t + (-3*q[0][j][1] +3*q[1][j][1])*t + q[0][j][1];
                    
                    res[2] = (-q[0][j][2] +3*q[1][j][2] -3*q[2][j][2] +q[3][j][2])*t*t*t + (3*q[0][j][2] -6*q[1][j][2] +3*q[2][j][2])*t*t + (-3*q[0][j][2] +3*q[1][j][2])*t + q[0][j][2];
                    
                    r[j][k][0] = res[0];
                    r[j][k][1] = res[1];
                    r[j][k][2] = res[2];
                    k++;
                }
                
                t = 1;
                
                res[0] = (-q[0][j][0] +3*q[1][j][0] -3*q[2][j][0] +q[3][j][0])*t*t*t + (3*q[0][j][0] -6*q[1][j][0] +3*q[2][j][0])*t*t + (-3*q[0][j][0] +3*q[1][j][0])*t + q[0][j][0];
                
                res[1] = (-q[0][j][1] +3*q[1][j][1] -3*q[2][j][1] +q[3][j][1])*t*t*t + (3*q[0][j][1] -6*q[1][j][1] +3*q[2][j][1])*t*t + (-3*q[0][j][1] +3*q[1][j][1])*t + q[0][j][1];
                
                res[2] = (-q[0][j][2] +3*q[1][j][2] -3*q[2][j][2] +q[3][j][2])*t*t*t + (3*q[0][j][2] -6*q[1][j][2] +3*q[2][j][2])*t*t + (-3*q[0][j][2] +3*q[1][j][2])*t + q[0][j][2];
                
                r[j][k][0] = res[0];
                r[j][k][1] = res[1];
                r[j][k][2] = res[2];
                k=0;
            }
            
            for(int i=0; i<tesselation-1; i++)
                for(int j=0; j<tesselation-1; j++)
                {
                    double p1[3] = { r[i][j][0], r[i][j][1], r[i][j][2] };
                    double p2[3] = { r[i+1][j][0], r[i+1][j][1], r[i+1][j][2] };
                    double p3[3] = { r[i][j+1][0], r[i][j+1][1], r[i][j+1][2] };
                    double p4[3] = { r[i+1][j+1][0], r[i+1][j+1][1], r[i+1][j+1][2] };
                    
                    double *n1 = normal(p1,p2,p3);
                    double *n2 = normal(p2,p3,p1);
                    double *n3 = normal(p3,p1,p2);
                    
                    double *n4 = normal(p2,p4,p3);
                    double *n5 = normal(p4,p3,p2);
                    double *n6 = normal(p3,p2,p4);
                    
                    g << p1[0]; g << ' '; g << p1[1]; g << ' '; g << p1[2];
                    g << n1[0]; g << ' '; g << n1[1]; g << ' '; g << n1[2];
                    g << r[i][j][0]/tesselation; g << r[i][j][1]/tesselation; g << '\n';
                    g << p2[0]; g << ' '; g << p2[1]; g << ' '; g << p2[2];
                    g << n2[0]; g << ' '; g << n2[1]; g << ' '; g << n2[2];
                    g << r[i+1][j][0]/tesselation; g << r[i+1][j][1]/tesselation; g << '\n';
                    g << p3[0]; g << ' '; g << p3[1]; g << ' '; g << p3[2];   
                    g << n3[0]; g << ' '; g << n3[1]; g << ' '; g << n3[2];
                    g << r[i][j+1][0]/tesselation; g << r[i][j+1][1]/tesselation; g << '\n';
                    
                    g << p2[0]; g << ' '; g << p2[1]; g << ' '; g << p2[2];  
                    g << n4[0]; g << ' '; g << n4[1]; g << ' '; g << n4[2];
                    g << r[i+1][j][0]/tesselation; g << r[i+1][j][1]/tesselation; g << '\n';
                    g << p4[0]; g << ' '; g << p4[1]; g << ' '; g << p4[2];   
                    g << n5[0]; g << ' '; g << n5[1]; g << ' '; g << n5[2];
                    g << r[i+1][j+1][0]/tesselation; g << r[i+1][j+1][1]/tesselation; g << '\n';
                    g << p3[0]; g << ' '; g << p3[1]; g << ' '; g << p3[2];  
                    g << n6[0]; g << ' '; g << n6[1]; g << ' '; g << n6[2];
                    g << r[i][j+1][0]/tesselation; g << r[i][j+1][1]/tesselation; g << '\n';
                }
        }
        g.close();
    }
    else { printf("Erro a abrir o ficheiro\n"); exit(0); }
    
}





int main(int argc , char* argv[]) {

  if(argc <=1) { printf("Faltam parametros! [Plano , Caixa , Esfera , Cone ] ") ; }

  else if (!strcmp(argv[1] , "Plano"))
  {
   	if (argc != 5) {printf("Faltam Parametros! \"Plano <comprimento> <largura> <nome_ficheiro> \n") ; }
  		else {
  			float length = atof(argv[2]) ; 
  			float width = atof(argv[2]) ; 
  			
  			char* filename = (char*)malloc(sizeof(char)*64) ; 
  			filename = argv[4] ; 
  			filename = strcat(filename , argv[2]) ; 
  			filename = strcat(filename , argv[3]) ; 
 
  			drawPlano(length,width,filename) ; 


  			
  		}
  }

  else if (!strcmp(argv[1] , "Caixa"))
  {
  	if(argc!=6) { printf("Faltam Parametros! \"Caixa <comprimento> <altura> <largura> <nome_ficheiro>\n");}
  		else 
  		{
  		float length = atof(argv[2]) ; 
  		float height = atof(argv[3]) ; 
  		float width = atof(argv[4]) ;  

  		char* filename = (char*)malloc(sizeof(char)*64) ; 
  			filename = argv[5] ; 
  			filename = strcat(filename , argv[2]) ; 
  			filename = strcat(filename , argv[3]) ; 
  			filename = strcat(filename , argv[4]) ; 

 
  		drawCaixa(length,height,width, filename) ;
  		
  		}
  }

  else if (!strcmp(argv[1] , "Esfera"))
  {
  	if(argc!=6) { printf("Faltam Parametros! \"Esfera <raio> <fatias> <camadas> <nome_ficheiro>\n" );}
  		else 
  		{
  		float radius = atof(argv[2]) ; 
  		int slices = atoi(argv[3]) ; 
  		float stacks = atoi(argv[4]) ;

  		char* filename = (char*)malloc(sizeof(char)*64) ; 
  			filename = argv[5] ; 
  			filename = strcat(filename , argv[2]) ; 
  			filename = strcat(filename , argv[3]) ; 
  			filename = strcat(filename , argv[4]) ; 
 
  		drawEsfera(radius , slices , stacks, filename) ;
  		}

  }

  else if (!strcmp(argv[1] , "Cone"))
  {
		if(argc!=7) { printf("Faltam Parametros! \"Cone <raio> <altura> <fatias> <camadas> <nome_ficheiro>\n" );}
  		else 
  		{
  		float radius = atof(argv[2]) ;
  		float height = atof(argv[3]) ;  
  		int slices = atoi(argv[4]) ; 
  		float stacks = atoi(argv[5]) ;  

  		char* filename = (char*)malloc(sizeof(char)*64) ; 
  			filename = argv[6] ; 
  			filename = strcat(filename , argv[2]) ; 
  			filename = strcat(filename , argv[3]) ; 
  			filename = strcat(filename , argv[4]) ;
  			filename = strcat(filename , argv[5]) ; 


  		drawCone(radius , height ,  slices , stacks, filename) ;
  		}
  	}
  	 else if (!strcmp(argv[1] , "Cilindro"))
  		{
		if(argc!=6) { printf("Faltam Parametros! \"Cilindro <raio> <altura> <fatias> <nome_ficheiro>\n" );}
  		else 
  		{
  		float radius = atof(argv[2]) ;
  		float height = atof(argv[3]) ;  
  		int slices = atoi(argv[4]) ;  

  		char* filename = (char*)malloc(sizeof(char)*64) ; 
  			filename = argv[5] ; 
  			filename = strcat(filename , argv[2]) ; 
  			filename = strcat(filename , argv[3]) ; 
  			filename = strcat(filename , argv[4]) ;
  			

 
  		drawCilindro(radius , height ,  slices ,  filename) ;
  		}
	  }

	  else if (!strcmp(argv[1] , "Anel"))
  		{
		if(argc!=6) { printf("Faltam Parametros! \"Anel <raio_interior> <raio_exterior> <fatias> <nome_ficheiro>\n" );}
  		else 
  		{
  		float in_r = atof(argv[2]) ;
  		float out_r = atof(argv[3]) ;  
  		int slices = atoi(argv[4]) ;  

  		char* filename = (char*)malloc(sizeof(char)*64) ; 
  			filename = argv[5] ; 
  			filename = strcat(filename , argv[2]) ; 
  			filename = strcat(filename , argv[3]) ; 
  			filename = strcat(filename , argv[4]) ;
  			 
  		drawCilindro(in_r , out_r ,  slices ,  filename) ;
            }
        }
        else if (!strcmp(argv[1],"patch"))
        {
            if(argc!=5) { printf("Parâmetros errados! Formato: 'patch' <.patch> <tesselation> <nome_ficheiro>\n"); exit(0); }
            else
            {
                int tesselation = atoi(argv[3]);
                drawPatch(argv[2],tesselation,argv[4]);
                }
            }
	  return 0 ;   
  }



