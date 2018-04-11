/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   xPlotato.h
 * Author: dan
 *
 * Created on 9 de abril de 2018, 8:27
 */

#ifndef XPLOTATO_H
#define XPLOTATO_H

#include "NPC.h"


class xPlotato : public NPC {
public:
    xPlotato(std::string const& name_, int x_, int y_, int x_b, int x_e);
    xPlotato(const xPlotato& orig);
    virtual ~xPlotato();
    
    void update();
    
private:
    int x_begin;
    int x_end;
    int target;
};

#endif /* XPLOTATO_H */
