/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AssetManager.h
 * Author: claudiac
 *
 * Created on 22 de marzo de 2018, 22:52
 */

#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <map>

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


class AssetManager {
public:
    static sf::Texture& GetTexture(std::string const& filemane);
    
    static AssetManager& Instance(){
            static AssetManager instance;        // Las variables estáticas se destruyen al terminar el programa
            return instance;                // Return molón
        }
    
private:
    std::map<std::string,sf::Texture>m_Textures;
    //AssetManager is a singleton, solo una instancia puede existir en el mismo tiempo
    static AssetManager* sInstance;
    
    //============ SINGLETON ============
        AssetManager();
        AssetManager(AssetManager const& orig);           // <--------------------- No implementar estos métodos
        void operator=(AssetManager const& orig);    // <----------------'
    //===================================

};

#endif /* ASSETMANAGER_H */

