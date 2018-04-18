/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nodo.h
 * Author: dan
 *
 * Created on 11 de abril de 2018, 3:33
 */

#ifndef NODO_H
#define NODO_H

#include <array>
#include <vector>

#include "NPCs/NPC.h"
#include "Ground.h"
#include "../../Player.h"

class Nodo {
public:

    Nodo(std::string sheet);
    Nodo(const Nodo& orig);
    virtual ~Nodo();
    
    void addTile(int id, int x, int y);
    void addGround(std::vector<std::array<float, 2>> coords);
    void addxPlotato(int x_, int y_, int x_min, int x_max);
    void addSkull(int x_, int y_, int x_min, int x_max, int y_min, int y_max);
    void addPower(int id, int xMin, int xMax, int y_);
    
    void setRectVector(std::vector<renderEngine::rIntRect> rect_);
    void setPop(int i);
    int getPop();
    
    void update();
    void preState();
    void newState();
    
    void draw(float tick_, renderEngine::rIntRect limit, int min, int max);
    
    int getSize();
    
private:
    
    renderEngine::rSprite tile;
    
    physicsEngine::type* t;
    
    // Objetos que contiene el nodo
    std::vector<std::array<int, 2>> tilePosition;
    std::vector<renderEngine::rIntRect> tileRect;
    std::vector<int> tileId;
    
    std::vector<NPC*> npcs;
    std::vector<pBody> ground;
    std::vector<renderEngine::rRectangleShape> pinchos;
    std::vector<renderEngine::rSprite> v_esprait;
    
    typedef void (Player::*pFunc)(void);
    pFunc array_funciones[4];
    
    struct power{
        int id = 0;
        renderEngine::rSprite sprite;
    };
    std::vector<power> powers;
    
    int aux_pop;
    
};

#endif /* NODO_H */

