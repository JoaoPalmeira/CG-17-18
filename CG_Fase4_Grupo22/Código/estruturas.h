
#include <GL/glew.h>
//#include <OpenGL/gl.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
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



class Ponto
{
public:
    float x,y,z;
};


class Translacao
{
public:
    float x,y,z,tempo;
    list<Ponto> pontos;
};


class Rotacao
{
public:
    float angulo,eixox,eixoy,eixoz,tempo;
};

class Escala
{
public:
    float x,y,z;
};

class Cor
{
public:
    float r,g,b;
};

//raios da elipse
class Orbita
{
public:
    float raioX,raioZ;
    int nControl;
};

class Modelo
{
public:
    string ficheiro;
    int pontos;
    float ambR,ambG,ambB;
    float diffR,diffG,diffB;
    float specR,specG,specB;
    float emiR,emiG,emiB;
    string textura;
    unsigned int t,width,height,texID;
    unsigned char *texData;
    GLuint buffers[3];
};

class Grupo
{
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

void loadGrupos(TiXmlNode *currentNode, list<Grupo> *grupos)
{
    //percorre os grupos
    for(TiXmlNode* gNode = currentNode->FirstChild("grupo") ; gNode; gNode = gNode->NextSiblingElement())
    {
        Grupo g;
        
        //translacao
        Translacao t;
        TiXmlNode* tNode = gNode->FirstChild("translacao");
        if(tNode)
        {
            TiXmlElement* tElem = tNode->ToElement();
            const char *tTempo = tElem->Attribute("tempo");
            if(tTempo) t.tempo = atof(tTempo); else t.tempo = -1;
            
            if(t.tempo == -1)
            {
            const char *tX = tElem->Attribute("X"), *tY = tElem->Attribute("Y"), *tZ = tElem->Attribute("Z");
            if(tX) t.x = atof(tX); else t.x = 0;
            if(tY) t.y = atof(tY); else t.y = 0;
            if(tZ) t.z = atof(tZ); else t.z = 0;
            }
        else {
            TiXmlNode* testNode = tElem->FirstChild("ponto");
            if(testNode)
            {
                for(TiXmlElement* ptElem = tElem->FirstChild("ponto")->ToElement() ; ptElem; ptElem = ptElem->NextSiblingElement())
                {
                    Ponto ponto;
                    const char *tX = ptElem->Attribute("X"), *tY = ptElem->Attribute("Y"), *tZ = ptElem->Attribute("Z");
                    if(tX) ponto.x = atof(tX); else ponto.x = 0;
                    if(tY) ponto.y = atof(tY); else ponto.y = 0;
                    if(tZ) ponto.z = atof(tZ); else ponto.z = 0;
                    
                    t.pontos.push_back(ponto);
                }
            }
            else t.tempo = -1;
            }
        }
        else { t.tempo = -1; t.x = 0; t.y = 0; t.z = 0; }
        g.translacao = t;
        
        //rotacao
        Rotacao r;
        TiXmlNode* rNode = gNode->FirstChild("rotacao");
        if(rNode)
        {
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
        if(eNode)
        {
            TiXmlElement* eElem = eNode->ToElement();
            const char *eX = eElem->Attribute("X"), *eY = eElem->Attribute("Y"), *eZ = eElem->Attribute("Z");
            if(eX) e.x = atof(eX); else e.x = 1;
            if(eY) e.y = atof(eY); else e.y = 1;
            if(eZ) e.z = atof(eZ); else e.z = 1;
        }
        else { e.x = 1; e.y = 1; e.z = 1; }
        g.escala = e;
        
        //cor
        Cor c;
        TiXmlNode* cNode = gNode->FirstChild("cor");
        if(cNode)
        {
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
        if(oNode)
        {
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
        if(mNode)
        {
            TiXmlElement* mElem = mNode->ToElement();
            TiXmlNode* testNode = mElem->FirstChild("modelo");
            if(testNode)
            {
                
                for(TiXmlElement* modElem = mElem->FirstChild("modelo")->ToElement() ; modElem; modElem = modElem->NextSiblingElement())
                {
                    Modelo m;
                    const char *ficheiro = modElem->Attribute("ficheiro");
                    if(ficheiro) m.ficheiro = ficheiro;
                    
                    const char *ambR = modElem->Attribute("ambR"), *ambG = modElem->Attribute("ambG"), *ambB = modElem->Attribute("ambB");
                    if(ambR) m.ambR = atof(ambR); else m.ambR = 0;
                    if(ambG) m.ambG = atof(ambG); else m.ambG = 0;
                    if(ambB) m.ambB = atof(ambB); else m.ambB = 0;
                    
                    const char *diffR = modElem->Attribute("diffR"), *diffG = modElem->Attribute("diffG"), *diffB = modElem->Attribute("diffB");
                    if(diffR) m.diffR = atof(diffR); else m.diffR = 0;
                    if(diffG) m.diffG = atof(diffG); else m.diffG = 0;
                    if(diffB) m.diffB = atof(diffB); else m.diffB = 0;
                    
                    const char *specR = modElem->Attribute("specR"), *specG = modElem->Attribute("specG"), *specB = modElem->Attribute("specB");
                    if(specR) m.specR = atof(specR); else m.specR = 0;
                    if(specG) m.specG = atof(specG); else m.specG = 0;
                    if(specB) m.specB = atof(specB); else m.specB = 0;
                    
                    const char *emiR = modElem->Attribute("emiR"), *emiG = modElem->Attribute("emiG"), *emiB = modElem->Attribute("emiB");
                    if(emiR) m.emiR = atof(emiR); else m.emiR = 0;
                    if(emiG) m.emiG = atof(emiG); else m.emiG = 0;
                    if(emiB) m.emiB = atof(emiB); else m.emiB = 0;
                    
                    
                    const char *textura = modElem->Attribute("textura");
                    if(textura) m.textura = textura;
                    
                    ilInit();
                    ilGenImages(1,&m.t);
                    ilBindImage(m.t);
                    ilLoadImage((ILstring)m.textura.c_str());
                    ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE);
                    
                    m.width = ilGetInteger(IL_IMAGE_WIDTH);
                    m.height = ilGetInteger(IL_IMAGE_HEIGHT);
                    m.texData = ilGetData();
                    
                    glGenTextures(1,&m.texID);
                    glBindTexture(GL_TEXTURE_2D,m.texID);
                    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
                    
                    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,m.width,m.height,0,GL_RGBA,GL_UNSIGNED_BYTE,m.texData);
                    

                    fstream f;
                    
                    //f.open(m.ficheiro,ios::in);
                    f.open(m.ficheiro.c_str());
                    
                    if(f.is_open())
                    {
                        string line;
                        int pontos=0,j=0,k=0,l=0;
                        float *vertexB = NULL, *normalB = NULL, *textureB=NULL;
                        
                        if(getline(f,line))
                        {
                            sscanf(line.c_str(),"%d\n",&pontos);
                            m.pontos = pontos;
                        }
                        
                        vertexB = (float*) malloc(3*pontos*sizeof(float));
                        normalB = (float*) malloc(3*pontos*sizeof(float));
                        textureB = (float*) malloc(2*pontos*sizeof(float));
                        
                        glEnableClientState(GL_VERTEX_ARRAY);
                        glEnableClientState(GL_NORMAL_ARRAY);
                        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                   
                        
                        while(getline(f,line))
                        {
                            float x,y,z,xIl,yIl,zIl,xText,yText;
                            sscanf(line.c_str(),"%f %f %f %f %f %f %f %f\n",&x,&y,&z,&xIl,&yIl,&zIl,&xText,&yText);
                            vertexB[j++] = x; vertexB[j++] = y; vertexB[j++] = z;
                            normalB[k++] = xIl; normalB[k++] = yIl; normalB[k++] = zIl;
                            textureB[l++] = xText; textureB[l++] = yText;
                        }
                        
                        glGenBuffers(3,m.buffers);
                        
                        glBindBuffer(GL_ARRAY_BUFFER,m.buffers[0]);
                        glBufferData(GL_ARRAY_BUFFER,3*m.pontos*sizeof(float),vertexB,GL_STATIC_DRAW);
                        
                        glBindBuffer(GL_ARRAY_BUFFER,m.buffers[1]);
                        glBufferData(GL_ARRAY_BUFFER,3*m.pontos*sizeof(float),normalB,GL_STATIC_DRAW);

                        glBindBuffer(GL_ARRAY_BUFFER,m.buffers[2]);
                        glBufferData(GL_ARRAY_BUFFER,2*m.pontos*sizeof(float),textureB,GL_STATIC_DRAW);
                        
                       
                        free(vertexB);
                        free(normalB);
                        free(textureB);
                        
                        
                        f.close();
                    }
                    
                    g.modelos.push_back(m);
                }
            }
        }
        
        
        
        
        //recursividade sobre grupos
        if(gNode) loadGrupos(gNode,&g.grupos);
        grupos->push_back(g);
    }
}

class Light
{ public:
    float posX,posY,posZ,tipo;
};


class Figura
{
public:
    list<Grupo> grupos;
    list<Light> luzes;  
    void load(const char* pFilename);
};

void Figura::load(const char* pFilename)
{
    TiXmlDocument doc(pFilename);
    if (!doc.LoadFile()) return;
    TiXmlNode* nRoot = TiXmlHandle(doc.RootElement()).ToNode();
    
    TiXmlNode* lNode = nRoot->FirstChild("luzes");
    if(lNode)
    {
        TiXmlElement* lElem = lNode->ToElement();
        TiXmlNode* testNode = lElem->FirstChild("luz");
        if(testNode)
            for(TiXmlElement* luzElem = lElem->FirstChild("luz")->ToElement() ; luzElem; luzElem = luzElem->NextSiblingElement())
            {
                Light l;
                const char *tipo = luzElem->Attribute("tipo"), *posX = luzElem->Attribute("posX"), *posY = luzElem->Attribute("posY"), *posZ = luzElem->Attribute("posZ");
                if(tipo) l.tipo = atof(tipo); else l.tipo = 0;
                if(posX) l.posX = atof(posX); else l.posX = 0;
                if(posY) l.posY = atof(posY); else l.posY = 0;
                if(posZ) l.posZ = atof(posZ); else l.posZ = 0;
                
                this->luzes.push_back(l);
            }
    }

    loadGrupos(nRoot,&this->grupos);

}


