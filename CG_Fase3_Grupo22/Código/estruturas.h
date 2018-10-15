#include <GL/glew.h>
//#include <OpenGL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "./tinyxml/tinyxml.h"
#include "./tinyxml/tinystr.h"

using namespace std;

//Define um ponto no espaço 3d
class Ponto{
public:
    float coordx;
    float coordy;
    float coordz;
};
class Translacao{
public:
    float coordx,coordy,coordz,tempo;
    list<Ponto> pontos;
};
//a -> angulo
class Rotacao{
public:
    float angulo,eixox,eixoy,eixoz,tempo;
};
class Escala{
public:
    float escala_x,escala_y,escala_z;
};
//Define a cor do objeto
class Cor{
public:
    float r,g,b;
};
//Define os raios da orbita
class Orbita{
public:
    float raioX,raioZ;
    int nControl;
};
//Define uma lista de pontos
class Modelo{
public:
    string ficheiro;
    int pontos;
    GLuint buffers[2];
    
  //  Modelo() { this->ficheiro = "untitled"; this->pontos = list<Ponto>(); }
   // Modelo(const string& ficheiro, list<Ponto> pontos) { this->ficheiro = ficheiro; this->pontos = pontos; }
};
//Reunião de todas as estruturas anteriores
class Grupo{
public:
    string tipo; // planeta ou orbita
    Translacao translacao;
    Rotacao rotacao;
    Escala escala;
    Cor cor;
    Orbita orbita;
    list<Modelo> modelos;
    list<Grupo> grupos;
};


//Função que vai carregar os grupos.
void GRload(TiXmlNode *currentNode, list<Grupo> *grupos){
    //percorre os grupos
    for(TiXmlNode* gNode = currentNode->FirstChild("grupo") ; gNode; gNode = gNode->NextSiblingElement()){
        Grupo g;
        //translacao
        Translacao t;
        TiXmlNode* tNode = gNode->FirstChild("translacao");
        if(tNode){
            TiXmlElement* tElem = tNode->ToElement();
            const char *tTempo = tElem->Attribute("tempo");
            if(tTempo) t.tempo = atof(tTempo); else t.tempo = -1;
            
            if(t.tempo == -1){
            const char *tX = tElem->Attribute("X"), *tY = tElem->Attribute("Y"), *tZ = tElem->Attribute("Z");
            if(tX) t.coordx = atof(tX); else t.coordx = 0;
            if(tY) t.coordy = atof(tY); else t.coordy = 0;
            if(tZ) t.coordz = atof(tZ); else t.coordz = 0;
            }
        else {
            TiXmlNode* testNode = tElem->FirstChild("ponto");
            if(testNode){
                for(TiXmlElement* ptElem = tElem->FirstChild("ponto")->ToElement() ; ptElem; ptElem = ptElem->NextSiblingElement()){
                    Ponto ponto;
                    const char *tX = ptElem->Attribute("X"), *tY = ptElem->Attribute("Y"), *tZ = ptElem->Attribute("Z");
                    if(tX) ponto.coordx = atof(tX); else ponto.coordx = 0;
                    if(tY) ponto.coordy = atof(tY); else ponto.coordy = 0;
                    if(tZ) ponto.coordz = atof(tZ); else ponto.coordz = 0;
                    t.pontos.push_back(ponto);
                }
            }
            else t.tempo = -1;
            }
        }
        else { t.tempo = -1; t.coordx = 0; t.coordy = 0; t.coordz = 0; }
        g.translacao = t;
        //rotacao
        Rotacao r;
        TiXmlNode* rNode = gNode->FirstChild("rotacao");
        if(rNode){
            TiXmlElement* rElem = rNode->ToElement();
            const char *angulo = rElem->Attribute("angulo") , *eixoX = rElem->Attribute("eixoX"), *eixoY = rElem->Attribute("eixoY"), *eixoZ = rElem->Attribute("eixoZ"), *rTempo = rElem->Attribute("tempo");
            if(angulo) r.angulo = atof(angulo); else r.angulo = 0;
            if(eixoX) r.eixox = atof(eixoX); else r.eixox = 0;
            if(eixoY) r.eixoy = atof(eixoY); else r.eixoy = 0;
            if(eixoZ) r.eixoz = atof(eixoZ); else r.eixoz = 0;
            if(rTempo) r.tempo = atof(rTempo); else r.tempo = -1;
        }
        else { r.angulo = 0; r.eixox = 0; r.eixoy = 0; r.eixoz = 0; r.tempo = -1; }
        g.rotacao = r;
        //escala
        Escala e;
        TiXmlNode* eNode = gNode->FirstChild("escala");
        if(eNode){
            TiXmlElement* eElem = eNode->ToElement();
            const char *eX = eElem->Attribute("X"), *eY = eElem->Attribute("Y"), *eZ = eElem->Attribute("Z");
            if(eX) e.escala_x = atof(eX); else e.escala_x = 1;
            if(eY) e.escala_y = atof(eY); else e.escala_y = 1;
            if(eZ) e.escala_z = atof(eZ); else e.escala_z = 1;
        }
        else { e.escala_x = 1; e.escala_y = 1; e.escala_z = 1; }
        g.escala = e;
        
        //cor
        Cor c;
        TiXmlNode* cNode = gNode->FirstChild("cor");
        if(cNode){
            TiXmlElement* cElem = cNode->ToElement();
            const char *R = cElem->Attribute("R"), *G = cElem->Attribute("G"), *B = cElem->Attribute("B");
            if(R) c.r = atof(R); else c.r = 1;
            if(G) c.g = atof(G); else c.g = 1;
            if(B) c.b = atof(B); else c.b = 1;
        }
        else { c.r = 1; c.g = 1; c.b = 1; }
        g.cor = c;
        
        //orbita
        Orbita o;
        TiXmlNode* oNode = gNode->FirstChild("orbita");
        if(oNode){
            TiXmlElement* oElem = oNode->ToElement();
            const char *raioX = oElem->Attribute("raioX"), *raioZ = oElem->Attribute("raioZ"), *nControl = oElem->Attribute("nControl");
            if(raioX) o.raioX = atof(raioX); else o.raioX = 0;
            if(raioZ) o.raioZ = atof(raioZ); else o.raioZ = 0;
            if(nControl) o.nControl = atoi(nControl); else o.nControl = 4;
            
            if(o.nControl<4) o.nControl = 4;
            g.tipo = "orbita";
        }
        else { o.raioX = 0; o.raioZ = 0; o.nControl = 4; g.tipo = "planeta"; }
        g.orbita = o;
        
        //modelos
        TiXmlNode* mNode = gNode->FirstChild("modelos");
        if(mNode){
            TiXmlElement* mElem = mNode->ToElement();
            TiXmlNode* testNode = mElem->FirstChild("modelo");
            if(testNode){
                
                for(TiXmlElement* modElem = mElem->FirstChild("modelo")->ToElement(); modElem; modElem = modElem->NextSiblingElement()){
                    Modelo m;
                    const char *ficheiro = modElem->Attribute("ficheiro");
                    if(ficheiro) m.ficheiro = ficheiro;
                    fstream f;
                    //f.open(m.ficheiro,ios::in);
                    f.open(m.ficheiro.c_str());
                    if(f.is_open()){
                        string line;
                        int nPontos=0, j=0;
                        float *verticeB = NULL;
                        
                        if(getline(f,line)){
                            sscanf(line.c_str(),"%d\n",&nPontos);
                            m.pontos = nPontos;
                        }
                        
                        verticeB = (float*) malloc(nPontos*sizeof(float));
                        glEnableClientState(GL_VERTEX_ARRAY);
                        
                        while(getline(f,line)){
                            float x,y,z;
                            sscanf(line.c_str(),"%f %f %f\n",&x,&y,&z);
                            verticeB[j++] = x; verticeB[j++] = y; verticeB[j++] = z;
                        }
                        
                        glGenBuffers(1,m.buffers);
                        glBindBuffer(GL_ARRAY_BUFFER,m.buffers[0]);
                        glBufferData(GL_ARRAY_BUFFER,m.pontos*sizeof(float),verticeB,GL_STATIC_DRAW);
                        free(verticeB);
                        
                        f.close();
                    }
                    
                    g.modelos.push_back(m);
                }
            }
        }
        //recursividade sobre grupos
        if(gNode) GRload(gNode,&g.grupos);
        grupos->push_back(g);
    }
}

//Reunião dos Grupos
class Figura{
public:
    list<Grupo> grupos;  
    void load(const char* pFilename);
};

void Figura::load(const char* pFilename){
    TiXmlDocument doc(pFilename);
    if (!doc.LoadFile()) return;
    TiXmlNode* nRoot = TiXmlHandle(doc.RootElement()).ToNode();
    
    GRload(nRoot,&this->grupos);

}


