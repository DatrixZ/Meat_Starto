/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   boss.cpp
 * Author: pablomanez
 * 
 * Created on 5 de abril de 2018, 16:11
 */

#include <math.h>

#include "boss.h"
#include "Juego.h"

#define DES 2000
#define ADJUST 490
#define SPRITE_FACTOR 16

boss::boss() {
}

void boss::init(int x_,int y_) {
    //x_ ES LA POSICION MAXIMA DEL ANTERIOR NODO DIBUJADO

    //COORDENADAS
    float a = 70;
    x_min = x_+(a*12);
    x_max = x_+(a*53);
    y_min = y_;
    
    on = false;
    restart = false;
    
    //BOSS
    javi.r.setSize(70,70);
    javi.r.setPosition(x_min+(a*5),y_min+560);
    javi.r.setFillColor('r');
    javi.x_f = -1;
    javi.y_f = -1;
    javi.x_v = 0;
    javi.y_v = 0;
    javi.ir = NULL;
    javi.llegada = true;
    
    //CREO LA "PUERTA"
    puerta[0].r.setSize(a*12,a*5);
    puerta[0].r.setPosition(x_min-(a*8),(a*20)+DES+y_min+ADJUST);
    puerta[1].r.setPosition(x_min+(a*4),(a*20)+DES+y_min+ADJUST);
    puerta[2].r.setPosition(x_min+(a*4),(a*21)+DES+y_min+ADJUST);
    puerta[3].r.setPosition(x_min+(a*4),(a*22)+DES+y_min+ADJUST);
    puerta[4].r.setPosition(x_min+(a*4),(a*23)+DES+y_min+ADJUST);
    puerta[5].r.setPosition(x_min+(a*4),(a*24)+DES+y_min+ADJUST);
    puerta[6].r.setPosition(x_min+(a*5),(a*22)+DES+y_min+ADJUST);
    puerta[7].r.setPosition(x_min+(a*5),(a*23)+DES+y_min+ADJUST);
    puerta[8].r.setPosition(x_min+(a*5),(a*24)+DES+y_min+ADJUST);
    puerta[9].r.setPosition(x_min+(a*6),(a*23)+DES+y_min+ADJUST);
    puerta[10].r.setPosition(x_min+(a*6),(a*24)+DES+y_min+ADJUST);
    puerta[11].r.setPosition(x_min+(a*7),(a*24)+DES+y_min+ADJUST);
    
    for(int i=0 ; i<12 ; i++){
        if(i != 0){
            puerta[i].r.setSize(a,a);
        }
        puerta[i].r.setFillRGBAColor(28,58,104);
    }
    
    //---DEBUG
    
    //POSICION FINAL
    r_aux.setFillColor('g');
    r_aux.setPosition(-1,-1);
    r_aux.setSize(20,20);
    
    //INTRECT
    ir_aux.setFillColor('t');
    ir_aux.setOutlineColor('g');
    ir_aux.setOutlineThickness(5);
    
    //std::string path = "assets/boss/fire_boss_ad.png";        //COMIDA    128x128
    std::string path = "assets/boss/fire1.png";                 //FUEGO     72x48
    proy_boss.loadFromFIle(path);

    //TEXTOS
    time_font.loadFromFile("resources/fuente.ttf");
    time_text.setFont(time_font);
    time_text.setCharacterSize(50);
    time_text.setFillColor('k');
    
}

void boss::update() {
    renderEngine *sfml;
    
    float x_m = sfml->Instance().getViewCenter()[0];
    
    //x_ MARCA LA POSICION CENTRAL DE LA VISTA
    physicsEngine *world;
    if(x_m> (x_min+(70*20)) && x_m < x_max){
        //std::cout << y_min << std::endl;
        //COMIENZA LA BATALLA FINAL
        on = true;        
        if(!restart){
            //std::cout << " | ----------- Restart" << std::endl;
            //AQUI SOLO ENTRA UNA VEZ
            //CREO LAS COLISIONES DE LA PUERTA 
            for(int i=0 ; i<12 ; i++){
                float x = puerta[i].r.getPosition()[0];
                float y = puerta[i].r.getPosition()[1]-DES;
                puerta[i].r.setPosition(x,y);

                float w = puerta[i].r.getSize()[0];
                float h = puerta[i].r.getSize()[1];
                x = puerta[i].r.getPosition()[0]+(w/2);
                y = puerta[i].r.getPosition()[1]+(h/2);
                
                t = new physicsEngine::type;
                t->id = 1;
                t->data = this;
                
                puerta[i].b = world->Instance().createBody(w, h ,x , y, 'k', t);
            }

            clock_boss.restart();   //REINICIO LOS RELOJES
            dt_boss.restart();
            dt_fan.restart();
            restart = true;
            
            time_text.setPosition(renderEngine::Instance().getViewCenter()[0]-70*22,renderEngine::Instance().getViewCenter()[1]-70*5);

        }
        
        //HACER UNA ESPECIE DE ANIMACION
        
        //UPDATE DE JAVI
        //std::cout << " | ----------- Update de Javi" << std::endl;
        updateJavi();
        
        //std::cout << " | ----------- Fases del Boss" << std::endl;
        fasesBoss();
            
        //std::cout << " | ----------- Habilidades especiales" << std::endl;
        if(dt_fan.getElapsedTime().asSeconds()>0.2){
            //GENERO EL NUMERO ALEATORIO
            int rand = physicsEngine::Instance().genIntRandom(0, 100);
            if(rand>97)    crearAbanicoProyectiles();
            //if(distribution(gen)>40)    crearProyectilTele();
            
            dt_fan.restart();
        }

        //std::cout << " | ----------- Movimiento de proyectiles" << std::endl << std::endl;
        //MOVIMIENTO DE LOS PROYECTILES
        for(int i=0 ; i<javi.proy.size() ; i++){
            float vx = javi.proy[i]->v_x;
            float vy = javi.proy[i]->v_y;

            javi.proy[i]->r.move(vx,vy);
            
            //MILAGROSAMENTE FUNCIONA
            if( javi.proy[i]->r.getPosition()[1]>y_min+2600    || javi.proy[i]->r.getPosition()[1]<y_min || 
                javi.proy[i]->r.getPosition()[0]>x_max+(70*5)   || javi.proy[i]->r.getPosition()[0]<x_min-(70*5)){
                    //std::cout << "Soy un proyectil y me destruyo" << std::endl;
                
                delete javi.proy[i];
                javi.proy[i] = NULL;
                
                javi.proy.erase(javi.proy.begin()+i); 
                if(i+1==javi.proy.size())   javi.proy.shrink_to_fit();
            }
        }
        
        if(clock_boss.getElapsedTime().asSeconds()>40){
            //std::cout << "SE HA ACABADO EL BOSS" << std::endl;
            sfml->Instance().ChangeState(MPuntuaciones::Instance());
        }
    
        time_text.setString(std::to_string(40-static_cast<int>(clock_boss.getElapsedTime().asSeconds())));
    }
    else{
        on = false;
    }
}

void boss::fasesBoss() {
    int np = Juego::Instance().getPlayers()->size();
    int r = physicsEngine::Instance().genIntRandom(0,np-1);
    
    //std::cout << Juego::Instance().getPlayers()[0][r]->getName() << std::endl;
    float x_ = Juego::Instance().getPlayers()[0][r]->getXPosition();
    float y_ = Juego::Instance().getPlayers()[0][r]->getYPosition();
    
    if(clock_boss.getElapsedTime().asSeconds()<20 && clock_boss.getElapsedTime().asSeconds()>=0){
        if(dt_boss.getElapsedTime().asSeconds() > 0.35){
                //std::cout << "CREO BALA EN (" << x_ << "," << y_ << ")" << std::endl;
            crearProyectil(x_,y_);
            dt_boss.restart();
        }
    }
    else if(clock_boss.getElapsedTime().asSeconds()>25 && clock_boss.getElapsedTime().asSeconds()<=26){
        if(dt_boss.getElapsedTime().asSeconds() > 0.05){
                //std::cout << "CREO BALA" << std::endl;
            crearProyectil(x_,y_);
            dt_boss.restart();
        }
    }
    else if(clock_boss.getElapsedTime().asSeconds()>28 && clock_boss.getElapsedTime().asSeconds()<=30){
        if(dt_boss.getElapsedTime().asSeconds() > 1){
            crearAbanicoProyectiles();
            dt_boss.restart();
        }
    }
    else if(clock_boss.getElapsedTime().asSeconds()>30 && clock_boss.getElapsedTime().asSeconds()<31){
        if(dt_boss.getElapsedTime().asSeconds() > 0.002){
                //std::cout << "CREO BALA" << std::endl;
            crearProyectil(x_,y_);
            dt_boss.restart();
        }
    }
    else if(clock_boss.getElapsedTime().asSeconds()>=31){
        if(dt_boss.getElapsedTime().asSeconds() > 0.3){
                //std::cout << "CREO BALA" << std::endl;
            crearProyectil(x_,y_);
            dt_boss.restart();
        }
    }
}

void boss::updateJavi() {
    //SI LLEGADA ES TRUE, ENTONCES ENCUENTRA OTRA POSICION DENTRO DE UN RANGO
        //std::cout << javi.llegada << std::endl;
    float factor = 100;
    float factor_v = 1;
    
    
    if(javi.llegada){
        //std::uniform_real_distribution<float> dv(1,3);
        
        //factor_v = dv(gen);
        javi.x_f = physicsEngine::Instance().genIntRandom(x_min+(70*3),x_min+(70*34));
        javi.y_f = physicsEngine::Instance().genIntRandom(y_min+70*7, y_min+70*15);
        /*
        float x_d = javi.r.getPosition()[0] - javi.x_f;
        float y_d = javi.r.getPosition()[1] - javi.y_f;
        
        float angle = atan2(y_d,x_d);

        javi.x_v = cos(angle)*factor;
        javi.y_v = sin(angle)*factor;
         */
        javi.x_v = (float) (javi.x_f-javi.r.getPosition()[0])/factor;
        javi.y_v = (float) (javi.y_f-javi.r.getPosition()[1])/factor;
        
        if(javi.ir == NULL){
            javi.ir = new renderEngine::rIntRect(javi.r.getPosition()[0],javi.r.getPosition()[1],javi.x_v * factor,javi.y_v * factor);
        }
        else{
            delete javi.ir;
            javi.ir = NULL;
            javi.ir = new renderEngine::rIntRect(javi.r.getPosition()[0],javi.r.getPosition()[1],javi.x_v * factor,javi.y_v * factor);
        }
            
        javi.llegada = false;
        
        //DEBUG
        r_aux.setPosition(javi.x_f,javi.y_f);
        ir_aux.setPosition(javi.r.getPosition()[0],javi.r.getPosition()[1]);
        ir_aux.setSize(javi.ir->widht,javi.ir->height);
            //std::cout   << "LEFT: " << javi.ir->left << ", TOP: " << javi.ir->top << ", WIDHT: " << javi.ir->widht << ", HEIGHT: " << javi.ir->height << std::endl;
            //std::cout << "X_f: " << javi.x_f << ", Y_f: " << javi.y_f << std::endl;
            //std::cout << "V(" << javi.x_v << "," << javi.y_v << ")" << std::endl;
    }
    
    javi.r.move(javi.x_v*factor_v,javi.y_v*factor_v);
        //std::cout << "V(" << javi.x_v*factor_v << "," << javi.y_v*factor_v << ")" << std::endl;
    
    if(!javi.ir->contains(javi.r.getPosition()[0],javi.r.getPosition()[1])){
        javi.llegada = true;
    }

}

renderEngine::rIntRect boss::getIntRect() {
    int f = SPRITE_FACTOR;
    
    //PARA LA COMIDA
    /*
    int x = physicsEngine::Instance().genIntRandom(1,7);
    int y = physicsEngine::Instance().genIntRandom(1,7);
    //std::cout << "X: " << x << " | Y: " << y << " | W: " << f << " | H: " << f << std::endl;
    renderEngine::rIntRect ret(x*16,y*16,f,f);
    return ret;
     */
}

void boss::crearProyectilTele() {
    // ------------ EN PRUEBAS ------------ //
    
    // x=y²/4, SE DEBE APLICAR UN OFFSET A LOS LADOS
    proyectilT *aux = new proyectilT;
    
    aux->r.setFillColor('b');
    aux->r.setSize(20,20);
    aux->angle = 45;
    
    aux->x_ini = javi.r.getPosition()[0];
    aux->y_ini = javi.r.getPosition()[1];
    aux->r.setPosition(aux->x_ini,aux->y_ini);
    aux->r.rotate(aux->angle);
    
    /*
    aux->a = 50;
    aux->a_1 = 100;
    aux->a_2 = 100;
    
    aux->x_fin = aux->x_ini+aux->a_1;
    aux->y_fin = aux->y_ini+aux->a_2;
    */
    
    javi.proyT.push_back(aux);
}

void boss::crearAbanicoProyectiles(){
    //std::cout << "Javi used fan of bullets" << std::endl;
    float r = physicsEngine::Instance().genFloatRandom(2.1,3.3);
        
    float ang = 0.125;
    for(float i=0 ; i<4 ; i+=ang){
        if(i<=r || i>=r+0.6){
            float i_a = i+1;
            if(i_a > 4){
                i_a-4;
            }
            
            int factor = 5;    //FACTOR VELOCIDAD
            float s_factor = 1.5;
                
            float w = 18*s_factor;
            float h = 48*s_factor;
            float w_ir = 18;
            float h_ir = 48;

            float s_x = sin(M_PI/180*(90*i_a));
            float s_y = cos(M_PI/180*(90*i_a));

                //std::cout << "X-> sin(" << 90*i << ") : " << s_x << std::endl; //X
                //std::cout << "Y-> cos(" << 90*i << ") : " << s_y << std::endl; //Y
                //std::cout << std::endl;

            proyectil *p_aux = new proyectil;
            p_aux->v_x = s_x*factor;
            p_aux->v_y = s_y*factor;

            p_aux->r.setSize(w,h);
            p_aux->r.setPosition(javi.r.getPosition()[0],javi.r.getPosition()[1]);
            //p_aux->r.setFillRGBAColor(160,196,255);
            //p_aux->r.setFillColor('b');
            
            //TEXTURA DE FUEGO
            renderEngine::rIntRect ir(0,0,w_ir,h_ir);
            p_aux->t.loadFromImage(proy_boss,ir);
            p_aux->r.setTexture(p_aux->t);
            
            float angle = atan2(s_y,s_x);
            p_aux->r.rotate((angle/M_PI*180)+90);

            
            
            //ELIJO LA TEXTURA ALEATORIAMENTE
            /*
            renderEngine::rIntRect ir = getIntRect();
            p_aux->t.loadFromImage(proy_boss,ir);
            p_aux->r.setTexture(p_aux->t);
            */

            javi.proy.push_back(p_aux);
        }
    }
}

void boss::crearProyectil(float x_, float y_) {
    //ELIJO LA TEXTURA ALEATORIAMENTE
    //renderEngine::rIntRect ir = getIntRect();
    
    //CREO EL PROYECTIL
    //LO AÑADO AL VECTOR DEL JEFE
    int a = 70;
    float factor = 20;
    float s_factor = 1.5;
    
    float w = 18*s_factor;
    float h = 48*s_factor;
    float w_ir = 18;
    float h_ir = 48;
    
    float x = javi.r.getPosition()[0];
    float y = javi.r.getPosition()[1];

    //std::cout << "CREO BALA EN (" << x_ << "," << y_ << ")" << std::endl;
    
    proyectil *aux = new proyectil;
    aux->r.setSize(w,h);
    aux->r.setPosition(x+(a/2),y+(a/2));
    //aux->r.setFillColor('k');
    
    //TEXTURA DEL PROYECTIL
    renderEngine::rIntRect ir(0,0,w_ir,h_ir);
    aux->t.loadFromImage(proy_boss,ir);
    aux->r.setTexture(aux->t);
    
    //AQUI SE DEBERIAN DE CONSEGUIR LAS POSICIONES DE LOS PERSONAJES
    //HE TENIDO QUE PASARLAS A TRAVES DE 3 FUNCIONES
        //std::cout << "X: " << x_ << std::endl;
        //std::cout << "Y: " << y_ << std::endl;
    float x_dist = x_ - x;
    float y_dist = y_ - y;
    
    float angle = atan2(y_dist,x_dist);
    //std::cout << "angle: " << angle/M_PI*180 << std::endl;
    aux->r.rotate((angle/M_PI*180)+90);
    
    aux->v_x = cos(angle)*factor;
    aux->v_y = sin(angle)*factor;
        //std::cout << "V (" << aux.v_x << "," << aux.v_y << ")" << std::endl;
    
    javi.proy.push_back(aux);
}

void boss::render() {
    
    if(on){
        //<DEBUG>
        /*
        r_aux.draw();
        ir_aux.draw();
        //*/
        //</DEBUG>
        
        for(int i=0 ; i<12 ; i++){
            puerta[i].r.draw();
        }
        for(int i=0 ; i<javi.proy.size() ; i++){
            javi.proy[i]->r.draw();
        }
        javi.r.draw();
        time_text.draw();
    }
}

bool boss::isBossOn() { return on;}




boss::boss(const boss& orig) {
}
