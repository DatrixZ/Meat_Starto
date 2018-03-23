/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   renderEngine.h
 * Author: pablomanez
 *
 * Created on 21 de marzo de 2018, 15:30
 */

#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include <SFML/Graphics.hpp>
class renderEngine {
public:
    //<SINGLETON>
    static renderEngine& Instance(){
        static renderEngine instance;
        return instance;
    }
    //</SINGLETON>
    
    class rTexture {
        friend class renderEngine;
        public:
            rTexture();                             //CONSTRUCTOR SIN ARGUMENTOS
            rTexture(std::string path);             //CONSTRUCTOR CON ARGUMENTOS
            
            void loadFromFile(std::string path);    //APLICAR UNA IMAGEN A LA TEXTURA
            
            
        private:
            sf::Texture* getTexture();              //DEVUELVE LA TEXTURA (USAR SOLO INTERNAMENTE)
            sf::Texture text;
    };
    
    class rSprite {
        public:
            rSprite();                                  //CONSTRUCTOR
            
            void draw();
            
            void setTexture(rTexture &t);               //APLICAR UNA TEXTURA
            void setOrigin(float x, float y);           //ESTABLECER EL PUNTO ORIGEN
            void setScale(float x, float y);            //ESTABLECER LA ESCALA
            void setPosition(float x, float y);         //ESTABLECER LA POSICION
            void setRotation(float a);                  //ESTABLECER UNA ROTACION
            
            std::array<float,2> getPosition();
        private:
            sf::Sprite sprite;
    };
    
    
    class rView {
        friend class renderEngine;
        public:
            rView(float pos_x, float pos_y, float size_x, float size_y);        //CONSTRUCTOR
            
            void zoom(float z);
            void setCenter(float x, float y);
            std::array<float,2> getCenter();
            
        private:
            sf::View getView();
            sf::View view;
    };
    
    class rTime {
        public:
            rTime();
            
            float asSeconds();
            float asMilliseconds();
            float asMicroseconds();
        private:
            sf::Time time;
    };
    
    class rClock {
        public:
            rClock();
            
            renderEngine::rTime restart();
            float asSeconds();
        private:
            sf::Clock clock;
    };
    
    class rEvent {
        friend class renderEngine;
        public:
            rEvent();
            enum EventType{
                KeyPressed      = sf::Event::EventType::KeyPressed,
                KeyReleased     = sf::Event::EventType::KeyReleased,
            };
            sf::Event::EventType sfType();
            
            
            int getKeyCode();
            
        private:
            sf::Event* getEvent();
            
            sf::Event event;
    };
    
    //METODOS PUBLICOS
    bool isOpen();                                  //TRUE SI LA VENTANA ESTA ABIERTA
    void close();
    void clear(char c);                             //CLEAR DE SFML
    void display();                                 //DIBUJA LA VENTANA
    std::array<float,2> getSize();                  //DEVUELVE LAS DIMENSIONES DE LA VENTANA
    
    void setView(rView v);
    bool pollEvent(rEvent &e);
    
    
private:
    
    //<SINGLETON>
    renderEngine();
    renderEngine(const renderEngine& orig);
    void operator=(renderEngine const& orig);
    //</SINGLETON>
    
    sf::RenderWindow* getWindow();                  //DEVUELVE LA VENTANA A LAS CLASES Nested DE renderEngine

    sf::RenderWindow window;
};

#endif /* RENDERENGINE_H */

