#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

//Função que cria o ficheiro xml
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

//Função que cria o PLANO (guardando o mesmo num ficheiro .3d);
//Primeiro aloca-se espaço para um novo ficheiro e define-se-o como .3d. 
//Apos isso gera-se o objeto e guarda-se a informação do mesmo no ficheiro.
void drawPlano(float length, float width, char* filename){
	FILE* f; 
	char* aux = (char*)malloc(sizeof(char)*64); 
	strcpy(aux , filename);

	strcat(aux , ".3d"); 
	f = fopen(aux,"w"); 

	if(f!=NULL){
		fprintf(f, "%f %d %f \n", -length/2, 0, -width/2); 
		fprintf(f, "%f %d %f \n", -length/2, 0, width/2);
		fprintf(f, "%f %d %f \n", length/2, 0, width/2);  
	
		fprintf(f, "%f %d %f \n", length/2, 0, width/2);
		fprintf(f, "%f %d %f \n", length/2, 0, -width/2);
		fprintf(f, "%f %d %f \n", -length/2, 0, -width/2); 
	}

	fclose(f) ; 
}



//Função que cria a CAIXA (guardando o mesmo num ficheiro .3d)
//Primeiro aloca-se espaço para um novo ficheiro e define-se-o como .3d. 
//Apos isso gera-se o objeto e guarda-se a informação do mesmo no ficheiro.
void drawCaixa(float length, float height, float width, char* filename){
	FILE* f; 
	char* aux = (char*)malloc(sizeof(char)*64); 
	strcpy(aux ,filename);

	strcat(aux ,".3d"); 

	f = fopen(aux,"w"); 

	if(f!=NULL){
		fprintf(f, "%f %f %f \n", length/2, -height/2, -width/2); 
		fprintf(f, "%f %f %f \n", -length/2, -height/2,  width/2);
		fprintf(f, "%f %f %f \n", -length/2, -height/2, -width/2);  
	
		fprintf(f, "%f %f %f \n", -length/2, -height/2, width/2); 
		fprintf(f, "%f %f %f \n", length/2, -height/2, -width/2);
		fprintf(f, "%f %f %f \n", length/2, -height/2, width/2);

		fprintf(f, "%f %f %f \n", length/2, height/2, -width/2); 
		fprintf(f, "%f %f %f \n", -length/2, height/2, -width/2);
		fprintf(f, "%f %f %f \n", -length/2, height/2, width/2); 

		fprintf(f, "%f %f %f \n", -length/2, height/2, width/2); 
		fprintf(f, "%f %f %f \n", length/2, height/2, width/2);
		fprintf(f, "%f %f %f \n", length/2, height/2, -width/2);

		fprintf(f, "%f %f %f \n", -length/2, -height/2, width/2); 
		fprintf(f, "%f %f %f \n", length/2, -height/2, width/2);
		fprintf(f, "%f %f %f \n", -length/2, height/2, width/2);

		fprintf(f, "%f %f %f \n", length/2, -height/2, width/2); 
		fprintf(f, "%f %f %f \n", length/2, height/2, width/2);
		fprintf(f, "%f %f %f \n", -length/2, height/2, width/2);

		fprintf(f, "%f %f %f \n", length/2, -height/2, width/2); 
		fprintf(f, "%f %f %f \n", length/2, -height/2, -width/2);
		fprintf(f, "%f %f %f \n", length/2, height/2, width/2) ;

		fprintf(f, "%f %f %f \n", length/2, -height/2, -width/2) ; 
		fprintf(f, "%f %f %f \n", length/2, height/2, -width/2) ;
		fprintf(f, "%f %f %f \n", length/2, height/2, width/2) ;

		fprintf(f, "%f %f %f \n", length/2, -height/2, -width/2) ; 
		fprintf(f, "%f %f %f \n", -length/2, -height/2, -width/2) ;
		fprintf(f, "%f %f %f \n", length/2, height/2, -width/2) ;

		fprintf(f, "%f %f %f \n", -length/2, -height/2, -width/2) ; 
		fprintf(f, "%f %f %f \n", -length/2, height/2, -width/2) ;
		fprintf(f, "%f %f %f \n", length/2, height/2, -width/2) ;

		fprintf(f, "%f %f %f \n", -length/2, -height/2, -width/2) ; 
		fprintf(f, "%f %f %f \n", -length/2, -height/2, width/2) ;
		fprintf(f, "%f %f %f \n", -length/2, height/2, -width/2) ;

		fprintf(f, "%f %f %f \n", -length/2, -height/2, width/2) ; 
		fprintf(f, "%f %f %f \n", -length/2, height/2, width/2) ;
		fprintf(f, "%f %f %f \n", -length/2, height/2, -width/2) ;
	}

	fclose(f) ; 	
}

//Função que cria o ESFERA (guardando o mesmo num ficheiro .3d)
//Primeiro aloca-se espaço para um novo ficheiro e define-se-o como .3d. 
//Apos isso gera-se o objeto e guarda-se a informação do mesmo no ficheiro.
void drawEsfera(float radius, int slices, int stacks, char* filename){
	FILE* f; 
	
	char* aux = (char*)malloc(sizeof(char)*64); 
	strcpy(aux ,filename);
	strcat(aux ,".3d"); 

	f = fopen(aux,"w"); 

	float slice = (360/slices)*(M_PI/180); 
	float stack = (180/slices)*(M_PI/180);
	float piMeios = M_PI/2; 
	float doisPI = M_PI*2;  


	if(f!=NULL){
		for(float j = -piMeios; j < piMeios; j+=stack){
			for(float i = 0; i <= doisPI; i+=slice){
			fprintf(f, "%f %f %f \n", cos(j+stack)*sin(i)*radius, sin(j+stack)*radius, cos(j+stack)*cos(i)*radius) ; 
			fprintf(f, "%f %f %f \n", cos(j)*sin(i)*radius, sin(j)*radius, cos(j)*cos(i)*radius) ; 
			fprintf(f, "%f %f %f \n", cos(j)*sin(i+slice)*radius, sin(j)*radius, cos(j)*cos(i+slice)*radius) ; 
	
			fprintf(f, "%f %f %f \n", cos(j+stack)*sin(i)*radius, sin(j+stack)*radius, cos(j+stack)*cos(i)*radius) ; 
			fprintf(f, "%f %f %f \n", cos(j)*sin(i+slice)*radius, sin(j)*radius, cos(j)*cos(i+slice)*radius) ; 
			fprintf(f, "%f %f %f \n", cos(j+stack)*sin(i+slice)*radius, sin(j+stack)*radius, cos(j+stack)*cos(i+slice)*radius) ; 
			}
		}
	}
	fclose(f) ; 
}

//Função que cria o CONE (guardando o mesmo num ficheiro .3d)
//Primeiro aloca-se espaço para um novo ficheiro e define-se-o como .3d. 
//Apos isso gera-se o objeto e guarda-se a informação do mesmo no ficheiro.
void drawCone(float radius, float height,  int slices, int stacks, char* filename){
	FILE* f; 
	
	char* aux = (char*)malloc(sizeof(char)*64); 
	strcpy(aux , filename);
	strcat(aux , ".3d"); 
	
	f = fopen(aux,"w"); 

	float slice = (360/slices)*(M_PI/180); 
	float stack = height/stacks;
	float raio = radius/stacks; 
	float doisPI = M_PI*2;  


	if(f!=NULL){
		for(float i = 0 ; i < doisPI ; i+=slice){
			fprintf(f, "%d %f %d \n", 0, -height/3, 0); 
			fprintf(f, "%f %f %f \n", sin(i+slice)*radius, -height/3, cos(i+slice)*radius); 
			fprintf(f, "%f %f %f \n", sin(i)*radius, -height/3, cos(i)*radius); 
		}
		float r = 0; 
		for(float j = -height/3; j < (height-height/3); j+=stack){
			for(float i = 0; i < doisPI; i+=slice){
				fprintf(f, "%f %f %f \n", sin(i)*(radius-(r+raio)), j+stack, cos(i)*(radius-(r+raio))); 
				fprintf(f, "%f %f %f \n", sin(i)*(radius-r), j, cos(i)*(radius-r)); 
				fprintf(f, "%f %f %f \n", sin(i+slice)*(radius-r), j, cos(i+slice)*(radius-r)); 
			}
				r+=raio ; 	
			}
		r=0 ; 
		for(float j = -height/3; j < (height-height/3)-stack; j+=stack){
			for(float i = 0; i< doisPI; i+=slice){
				fprintf(f, "%f %f %f \n", sin(i)*(radius-(r+raio)), j+stack, cos(i)*(radius-(r+raio)) ) ; 
				fprintf(f, "%f %f %f \n", sin(i+slice)*(radius-r), j, cos(i+slice)*(radius-r)) ; 
				fprintf(f, "%f %f %f \n", sin(i+slice)*(radius-(r+raio)),j+stack, cos(i+slice)*(radius-(r+raio))) ; 
		}
		r+=raio ; 
		}
	}
	fclose(f) ; 
}

//Função que cria o ANEL (guardando o mesmo num ficheiro .3d)
//Primeiro aloca-se espaço para um novo ficheiro e define-se-o como .3d. 
//Apos isso gera-se o objeto e guarda-se a informação do mesmo no ficheiro.
void drawAnel(float in_r , float out_r ,int slices, char* filename){
	FILE* f; 
	char* aux = (char*)malloc(sizeof(char)*64); 
	strcpy(aux, filename);
	strcat(aux, ".3d"); 
	f = fopen(aux,"w"); 

	float slice = (360/slices)*(M_PI/180);
	float doisPi = 2*M_PI;
	if (f!=NULL){
		for (float i = 0; i < doisPi; i += slice){
			fprintf(f , "%f %f %f \n" ,sin(i)*in_r, 0.0, cos(i)*in_r);
			fprintf(f , "%f %f %f \n" ,sin(i)*out_r, 0.0, cos(i)*out_r);
			fprintf(f , "%f %f %f \n" ,sin(i+slice)*in_r, 0.0, cos(i+slice)*in_r);
			fprintf(f , "%f %f %f \n" ,sin(i)*out_r, 0.0, cos(i)*out_r);
			fprintf(f , "%f %f %f \n" ,sin(i+slice)*out_r, 0.0, cos(i+slice)*out_r);
			fprintf(f , "%f %f %f \n" ,sin(i+slice)*in_r, 0.0, cos(i+slice)*in_r);
			fprintf(f , "%f %f %f \n" ,sin(i)*out_r, 0.0, cos(i)*out_r);
			fprintf(f , "%f %f %f \n" ,sin(i)*in_r, 0.0, cos(i)*in_r);
			fprintf(f , "%f %f %f \n" ,sin(i+slice)*in_r, 0.0, cos(i+slice)*in_r);
			fprintf(f , "%f %f %f \n" ,sin(i+slice)*out_r, 0.0, cos(i+slice)*out_r);
			fprintf(f , "%f %f %f \n" ,sin(i)*out_r, 0.0, cos(i)*out_r);
			fprintf(f , "%f %f %f \n" ,sin(i+slice)*in_r, 0.0, cos(i+slice)*in_r);
		}
 	}
}

//Função principal do gerador que invoca as funções anteriores e que lhes forneces os parametros que o utilizador define
//Caso falte algum parametro, o sistema indica que existe falta de parametros e apresenta todos os parametros necessarios para a criaçao
//desse mesmo objeto.
int main(int argc , char* argv[]) {

  if(argc <=1) { printf("Faltam parametros! [Plano , Caixa , Esfera , Cone ] "); }
  //Caso do Plano
  else if (!strcmp(argv[1], "Plano")){
   	if (argc != 5) {printf("Faltam Parametros! \"Plano <comprimento> <largura> <nome_ficheiro> \n"); }
  		else{
  			float length = atof(argv[2]); 
  			float width = atof(argv[2]); 
  			
  			char* filename = (char*)malloc(sizeof(char)*64); 
  			filename = argv[4]; 
  			filename = strcat(filename, argv[2]); 
  			filename = strcat(filename, argv[3]); 
  			createXML(filename);  
  			drawPlano(length,width,filename); 


  			
  		}
  }
  //Caso da Caixa
  else if (!strcmp(argv[1], "Caixa")){
  	if(argc!=6) { printf("Faltam Parametros! \"Caixa <comprimento> <altura> <largura> <nome_ficheiro>\n");}
  		else {
  			float length = atof(argv[2]); 
  			float height = atof(argv[3]); 
  			float width = atof(argv[4]);  

  			char* filename = (char*)malloc(sizeof(char)*64); 
  			filename = argv[5] ; 
  			filename = strcat(filename, argv[2]); 
  			filename = strcat(filename, argv[3]); 
  			filename = strcat(filename, argv[4]); 

  			drawCaixa(length,height,width,filename);
  		
  		}
  }
  //Caso da Esfera
  else if (!strcmp(argv[1] ,"Esfera")){
  	if(argc!=6) { printf("Faltam Parametros! \"Esfera <raio> <fatias> <camadas> <nome_ficheiro>\n" );}
  		else{
  			float radius = atof(argv[2]); 
  			int slices = atoi(argv[3]); 
  			float stacks = atoi(argv[4]);

  			char* filename = (char*)malloc(sizeof(char)*64); 
  			filename = argv[5]; 
  			filename = strcat(filename, argv[2]); 
  			filename = strcat(filename, argv[3]); 
  			filename = strcat(filename, argv[4]); 

  			drawEsfera(radius, slices, stacks, filename);
  		}
  }
  //Caso do Cone
  else if (!strcmp(argv[1] ,"Cone")){
		if(argc!=7) { printf("Faltam Parametros! \"Cone <raio> <altura> <fatias> <camadas> <nome_ficheiro>\n" );}
  		else {
  			float radius = atof(argv[2]);
  			float height = atof(argv[3]);  
  			int slices = atoi(argv[4]); 
  			float stacks = atoi(argv[5]);  

  			char* filename = (char*)malloc(sizeof(char)*64); 
  			filename = argv[6]; 
  			filename = strcat(filename, argv[2]); 
  			filename = strcat(filename, argv[3]); 
  			filename = strcat(filename, argv[4]);
  			filename = strcat(filename, argv[5]); 
 
  			drawCone(radius, height,  slices, stacks, filename);
  		}
  	}
  	//Caso do Anel
  	else if (!strcmp(argv[1] , "Anel")){
		if(argc!=6) { printf("Faltam Parametros! \"Anel <raio_interior> <raio_exterior> <fatias> <nome_ficheiro>\n" );}
  		else {
  			float in_r = atof(argv[2]) ;
  			float out_r = atof(argv[3]) ;  
  			int slices = atoi(argv[4]) ;  

  			char* filename = (char*)malloc(sizeof(char)*64) ; 
  			filename = argv[5] ; 
  			filename = strcat(filename , argv[2]) ; 
  			filename = strcat(filename , argv[3]) ; 
  			filename = strcat(filename , argv[4]) ;
  			 
  			drawAnel(in_r , out_r ,  slices ,  filename) ;
  		}
	  }
	return 0 ;   
  }



