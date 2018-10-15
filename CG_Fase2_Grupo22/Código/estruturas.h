
#include <stdio.h>
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
//Define a cor do objeto
class Cor{
public:
    float r,g,b;
};
//Define os raios da orbita
class Orbita{
public:
    float raioX,raioZ;
};
//Define uma lista de pontos
class Modelo{
public:
    string ficheiro;
    list<Ponto> pontos;
};
//Transformações necessárias para o Sistema Solar: Translação, Rotação e Escala
class Specs{
public:
    float coordx, coordy, coordz;
    float angulo,eixox,eixoy,eixoz;
    float escala_x,escala_y,escala_z;
};
//Reunião de todas as estruturas anteriores
class Grupo{
public:
    string tipo; // planeta ou orbita
    Specs specs;
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
        //specs
        Specs t;
        TiXmlNode* tNode = gNode->FirstChild("specs");
        if(tNode){
            TiXmlElement* tElem = tNode->ToElement();
            const char *tX = tElem->Attribute("X"), *tY = tElem->Attribute("Y"), *tZ = tElem->Attribute("Z");
            const char *angulo = tElem->Attribute("angulo") , *eixoX = tElem->Attribute("eixoX"), *eixoY = tElem->Attribute("eixoY"), *eixoZ = tElem->Attribute("eixoZ");
            const char *eX = tElem->Attribute("escala_x"), *eY = tElem->Attribute("escala_y"), *eZ = tElem->Attribute("escala_z");
            if(tX) t.coordx = atof(tX); else t.coordx = 0;
            if(tY) t.coordy = atof(tY); else t.coordy = 0;
            if(tZ) t.coordz = atof(tZ); else t.coordz = 0;
            if(angulo) t.angulo = atof(angulo); else t.angulo = 0;
            if(eixoX) t.eixox = atof(eixoX); else t.eixox = 0;
            if(eixoY) t.eixoy = atof(eixoY); else t.eixoy = 0;
            if(eixoZ) t.eixoz = atof(eixoZ); else t.eixoz = 0;
            if(eX) t.escala_x = atof(eX); else t.escala_x = 1;
            if(eY) t.escala_y = atof(eY); else t.escala_y = 1;
            if(eZ) t.escala_z = atof(eZ); else t.escala_z = 1;
        }
        else { t.coordx = 0; t.coordy = 0; t.coordz = 0; t.angulo=0; t.eixox=0; t.eixoy=0; t.eixoz=0; t.escala_x=1; t.escala_y=1; t.escala_z=1; }
        g.specs = t;
        
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
            const char *raioX = oElem->Attribute("raioX"), *raioZ = oElem->Attribute("raioZ");
            if(raioX) o.raioX = atof(raioX); else o.raioX = 0;
            if(raioZ) o.raioZ = atof(raioZ); else o.raioZ = 0;
            
            g.tipo = "orbita";
        }
        else { o.raioX = 0; o.raioZ = 0; g.tipo = "planeta"; }
        g.orbita = o;
        
        //modelos
        TiXmlNode* mNode = gNode->FirstChild("modelos");
        if(mNode){
            TiXmlElement* mElem = mNode->ToElement();
            TiXmlNode* testNode = mElem->FirstChild("modelo");
            if(testNode){
                for(TiXmlElement* modElem = mElem->FirstChild("modelo")->ToElement() ; modElem; modElem = modElem->NextSiblingElement()){
                    Modelo m;
                    const char *ficheiro = modElem->Attribute("ficheiro");
                    if(ficheiro) m.ficheiro = ficheiro;
                    
                    fstream f;
                    f.open(m.ficheiro.c_str());            
                    if(f.is_open()){
                        string line;
                        while (getline(f,line)){
                            float coordx,coordy,coordz;
                            sscanf(line.c_str(),"%f %f %f\n",&coordx,&coordy,&coordz);
                            Ponto p;
                            p.coordx = coordx; p.coordy = coordy; p.coordz =coordz;
                            m.pontos.push_back(p);
                        } 
                        f.close();
                    }
                    g.modelos.push_back(m);
                }
            }
        }
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


