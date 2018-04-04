/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   renderEngine.cpp
 * Author: pablomanez
 * 
 * Created on 21 de marzo de 2018, 15:30
 */

#include <SFML/Graphics.hpp>

#include "renderEngine.h"

#define FRAMERATE 60

renderEngine::renderEngine():
window(sf::VideoMode(1920,1080),"Carga de mapa",sf::Style::Default)
//window(sf::VideoMode(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height),"Carga de mapa",sf::Style::Default)
{
    window.setFramerateLimit(FRAMERATE);
}

void                renderEngine::display   ()          {   window.display();}
void                renderEngine::setView   (rView v)   {   window.setView(v.getView());}
void                renderEngine::close     ()          {   window.close();}

bool                renderEngine::isOpen    ()          {   return window.isOpen();}   //TRUE SI LA VENTANA ESTA ABIERTA
sf::RenderWindow*   renderEngine::getWindow ()          {   return &window;}   
bool                renderEngine::pollEvent (rEvent &e) {   return window.pollEvent(*e.getEvent());}

void renderEngine::clear(char c) {              //COLOR DEL CLEAR
    switch(c){
        case 'w':   window.clear(sf::Color::White);       break;
        case 'r':   window.clear(sf::Color::Red);       break;
        case 'y':   window.clear(sf::Color::Yellow);    break;
        default:    window.clear(sf::Color::Black);     break;
    }
}
std::array<float, 2> renderEngine::getSize() {          //X: getSize()[0] , Y: getSize()[1]
    std::array<float,2> v;

    v[0] = window.getSize().x;
    v[1] = window.getSize().y;
    
    return v;
}

std::array<float, 2> renderEngine::getViewCenter() {
    std::array<float,2> v;
    
    v[0] = window.getView().getCenter().x;
    v[1] = window.getView().getCenter().y;
    
    return v;
}


renderEngine::renderEngine(const renderEngine& orig) {}

//============================= TEXTURA =============================//
renderEngine::rTexture::rTexture() {}
renderEngine::rTexture::rTexture(std::string path) {    text.loadFromFile(path);}

void            renderEngine::rTexture::loadFromFile(std::string path)  {   text.loadFromFile(path);    }
int             renderEngine::rTexture::getXSize()                      {   text.getSize().x;           }
int             renderEngine::rTexture::getYSize()                      {   text.getSize().y;           }
sf::Texture*    renderEngine::rTexture::getTexture()                    {   return &text;               }


//============================= SPRITE =============================//
renderEngine::rSprite::rSprite() {}

void renderEngine::rSprite::setTexture  (rTexture &t)       {   sprite.setTexture(*t.getTexture()); }
void renderEngine::rSprite::setRotation (float a)           {   sprite.setRotation(a);              }
void renderEngine::rSprite::rotate      (float r)           {   sprite.rotate(r);                   }
float renderEngine::rSprite::getRotation()                  {   return sprite.getRotation();        }
void renderEngine::rSprite::setTextureRect(sf::IntRect& rect){  sprite.setTextureRect(rect);        }
void renderEngine::rSprite::setOrigin   (float x, float y)  {   sprite.setOrigin(x,y);              }
void renderEngine::rSprite::setScale    (float x, float y)  {   sprite.setScale(x,y);               }
void renderEngine::rSprite::setPosition (float x, float y)  {   sprite.setPosition(x,y);            }
void renderEngine::rSprite::draw() {
    renderEngine* sfml;
    sfml->Instance().getWindow()->draw(sprite);
}

std::array<float, 2> renderEngine::rSprite::getPosition() {
    std::array<float,2> ret;
    ret[0] = sprite.getPosition().x;
    ret[1] = sprite.getPosition().y;
    
    return ret;
}

//============================= VISTA =============================//
renderEngine::rView::rView(float pos_x, float pos_y, float size_x, float size_y):
view(sf::FloatRect(pos_x,pos_y,size_x,size_y)){}

void renderEngine::rView::zoom      (float z)           {   view.zoom(z);           }
void renderEngine::rView::setCenter (float x, float y)  {   view.setCenter(x,y);    }
void renderEngine::rView::move(float x, float y)        {   view.move(x,y);         }


sf::View                renderEngine::rView::getView    () {    return view;}
std::array<float, 2>    renderEngine::rView::getCenter  () {
    std::array<float, 2> ret;
    ret[0] = view.getCenter().x;
    ret[1] = view.getCenter().y;
    
    return ret;
}


//============================= RELOJ =============================//
renderEngine::rClock::rClock() {}

renderEngine::rTime renderEngine::rClock::restart() {clock.restart();}
renderEngine::rTime renderEngine::rClock::getElapsedTime() {clock.getElapsedTime();}

//============================= EVENTOS =============================//
renderEngine::rEvent::rEvent() {}

int renderEngine::rEvent::getKeyCode() {return event.key.code;}

sf::Event*              renderEngine::rEvent::getEvent  () {    return &event;}
sf::Event::EventType    renderEngine::rEvent::sfType    () {    return event.type;}

//============================= TIEMPO =============================//
renderEngine::rTime::rTime() {}
renderEngine::rTime::rTime(float sec){
    time = sf::seconds(sec);
}

float renderEngine::rTime::asSeconds        ()  {   return time.asSeconds();}
float renderEngine::rTime::asMilliseconds   ()  {   return time.asMilliseconds();}
float renderEngine::rTime::asMicroseconds   ()  {   return time.asMicroseconds();}
void renderEngine::rTime::Zero              ()  {   time = sf::Time::Zero;}
void renderEngine::rTime::incrementTime(renderEngine::rTime t){ time += t.getTime();}
sf::Time renderEngine::rTime::getTime()         {   return time; }

//============================= CONVEXSHAPE =============================//
renderEngine::rConvexShape::rConvexShape() {
}

void renderEngine::rConvexShape::draw() {
    renderEngine* sfml;
    sfml->Instance().getWindow()->draw(cs);
}
void renderEngine::rConvexShape::setPointCount      (int s)                     {   cs.setPointCount(s);}
void renderEngine::rConvexShape::setOutlineThickness(float f)                   {   cs.setOutlineThickness(f);}
void renderEngine::rConvexShape::setPoint           (int p, float x, float y)   {   cs.setPoint(p,sf::Vector2f(x,y));}
void renderEngine::rConvexShape::move               (float x, float y)          {   cs.move(x,y);}
void renderEngine::rConvexShape::setPosition        (float x, float y)          {   cs.setPosition(x,y);}
void renderEngine::rConvexShape::setTexture         (rTexture &t)               {   cs.setTexture(t.getTexture());}
void renderEngine::rConvexShape::setFillColor(char c) {
    switch(c){
        case 't':   cs.setFillColor(sf::Color::Transparent);    break;
        case 'r':   cs.setFillColor(sf::Color::Red);            break;
        case 'y':   cs.setFillColor(sf::Color::Yellow);         break;
        case 'm':   cs.setFillColor(sf::Color::Magenta);        break;
        case 'w':   cs.setFillColor(sf::Color::White);          break;
        case 'g':   cs.setFillColor(sf::Color::Green);          break;
        case 'b':   cs.setFillColor(sf::Color::Blue);           break;
        case 'k':   cs.setFillColor(sf::Color::Black);          break;
        default:    cs.setFillColor(sf::Color::Black);          break;
    }
}
void renderEngine::rConvexShape::setOutlineColor(char c) {
    switch(c){
        case 'r':   cs.setOutlineColor(sf::Color::Red);    break;
        case 'g':   cs.setOutlineColor(sf::Color::Green);  break;
        default:    break;
    }
}
std::array<float, 2> renderEngine::rConvexShape::getPosition() {
    std::array<float,2> a;
    
    a[0] = cs.getPosition().x;
    a[1] = cs.getPosition().y;
    
    return a;
}


//============================= RECTANGLESHAPE =============================//
renderEngine::rRectangleShape::rRectangleShape() {}

renderEngine::rRectangleShape::rRectangleShape(float x, float y):
rs(sf::Vector2f(x,y)){}

void renderEngine::rRectangleShape::draw() {
    renderEngine* sfml;
    sfml->Instance().getWindow()->draw(rs);
}
void renderEngine::rRectangleShape::setTexture  (rTexture &t)       {   rs.setTexture(t.getTexture());}
void renderEngine::rRectangleShape::setPosition (float x, float y)  {   rs.setPosition(x,y);}
void renderEngine::rRectangleShape::setSize     (float x, float y)  {   rs.setSize(sf::Vector2f(x,y));}
void renderEngine::rRectangleShape::move        (float x, float y)  {   rs.move(x,y);}

void renderEngine::rRectangleShape::setFillColor(char c) {
    switch(c){
        case 't':   rs.setFillColor(sf::Color::Transparent);    break;
        case 'r':   rs.setFillColor(sf::Color::Red);            break;
        case 'g':   rs.setFillColor(sf::Color::Green);          break;
        case 'b':   rs.setFillColor(sf::Color::Blue);           break;
        case 'y':   rs.setFillColor(sf::Color::Yellow);           break;
        case 'k':   rs.setFillColor(sf::Color::Black);           break;
        default:    break;
    }
}

std::array<float, 2> renderEngine::rRectangleShape::getPosition() {
    std::array<float, 2> ret;
    ret[0] = rs.getPosition().x;
    ret[1] = rs.getPosition().y;
    
    return ret;
}









