/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mapa.h
 * Author: pablomanez
 *
 * Created on 23 de febrero de 2018, 15:42
 */

#ifndef MAPA_H
#define MAPA_H

#include <tinyxml2.h>
#include <vector>
#include <list>
#include <Box2D/Box2D.h>

#include "../mj_t.h"
#include "../boss.h"
#include "Nodo/Nodo.h"
#include "Nodo/NPCs/NPC.h"
#include "Nodo/NPCs/xPlotato.h"

class Mapa {
public:
    //----------------SINGLETON
    static Mapa& Instance(){
        static Mapa instance;
        return instance;
    }
    
    void CreaMapa();
    void render(float tick_);
    void update(float x, float y);
    void updateNPCs();
    void preStateNPCs();
    void newStateNPCs();
    
    std::list<std::vector<renderEngine::rRectangleShape>>* getPinchos();
    
    virtual ~Mapa();
    
private:
    Mapa();
    Mapa(const Mapa& orig);
    void operator=(Mapa const& orig);
    
    //----------------METODOS PRIVADOS
    void LeeNodo(std::string const& node_path);
    void CreaCasilla(int id, int x, int y);
    void InitMatrix();
    
    //----------------ATRIBUTOS
    //DOCUMENTO XML/TMX QUE TIENE LOS ATRIBUTOS DE LAS MAPAS
    tinyxml2::XMLDocument doc;
    
    //ALTO Y ANCHO DE CADA MAPA
    int ancho;
    int alto;
    
    //ALMACENA EL PATH DE LA IMAGEN Y SU ID
    tinyxml2::XMLDocument ts_doc;   //XML DEL MAPASHEET
    renderEngine::rImage ts;        //PNG DEL MAPASHEET
    struct _tile{
        int id;
        renderEngine::rIntRect ir;  //CUADRADO DE RECORTE
        renderEngine::rTexture t;   //TEXTURA
        std::string path;           //PATH DEL MAPA (NO SE USA)
    };
    _tile *tiles[37];
    
    //OBJETOS (colisiones del mapa)
    std::vector<renderEngine::rConvexShape> objetos;
    std::vector<std::vector<std::array<float, 2>>> colision;
    std::vector<std::array<float, 2>> spawn;
    
    //PARA CONSTRUIR EL MAPA
    int x_max;
    struct _cas{
        int id;
        renderEngine::rRectangleShape rect;
        renderEngine::rTexture *text;
    };
    struct _miArray{
        _cas *casillas;     //PUNTERO A ARRAY DE _cas
        int size;           //TAMANYO
        int aux_pop;
    };
    //std::list<std::vector<_cas>> lista_casillas;
    
    std::list<Nodo> hex_list;
    std::list<Nodo> complete_list;
    
    std::vector<renderEngine::rIntRect> spriteSheetRects;
    
    std::list<_miArray> lista_casillas;
    std::list<_miArray> lista_casillas_aux;
    bool pop;       //TRUE: HAY QUE HACER POP DE lista_casillas
    
    std::list<std::vector<renderEngine::rRectangleShape>> l_pinchos;        //MAPA ID's: 33,34,35,36
    std::list<std::vector<renderEngine::rRectangleShape>> l_pinchos_aux;
    
    std::vector<renderEngine::rRectangleShape> vector_pinchos;  //VECTOR AUXILIAR
    std::vector<_cas> vector_casillas;                          //VECTOR AUXILIAR
    std::vector<NPC*> vector_enemigos;
    int v[15][15];
    
    //TETRIS
    bool m_tetris;
};

#endif /* MAPA_H */
