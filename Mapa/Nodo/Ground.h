/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ground.h
 * Author: dan
 *
 * Created on 11 de abril de 2018, 3:34
 */

#ifndef GROUND_H
#define GROUND_H


class Ground {
public:
    Ground();
    Ground(const Ground& orig);
    virtual ~Ground();
    
private:
    pBody* body;
};

#endif /* GROUND_H */
