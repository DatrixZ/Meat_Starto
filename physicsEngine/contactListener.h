/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   contactListener.h
 * Author: dan
 *
 * Created on 4 de abril de 2018, 19:13
 */

#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <list>


class contactListener : public b2ContactListener {
public:
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
    
    std::list<b2Contact*> contacts;
};

#endif /* CONTACTLISTENER_H */

