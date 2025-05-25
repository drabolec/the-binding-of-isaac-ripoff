#ifndef WALL_H
#define WALL_H

#include "Entity.h"

class Wall:public Entity{
    public:
        Wall();
        virtual ~Wall();
        Wall(int b);
        void render(sf::RenderTarget* target);
    private:
    int wallSide; // NE - 1 wzgledem zegara
};

void Wall::render(sf::RenderTarget* target){

    target->draw(this->hitbox);

};

Wall::Wall(){
    this->hitbox.setFillColor(sf::Color::Black);
    this->hitbox.setSize(sf::Vector2f(200.f, 200.f));
    this->hitbox.setPosition(sf::Vector2f(0.f, 0.f));

};
inline Wall::Wall(int b){
    this->hitbox.setFillColor(sf::Color::Blue);
    this->wallSide=b;
    if(this->wallSide==1){
        this->hitbox.setPosition(sf::Vector2f(850.f, 0.f));
        this->hitbox.setSize(sf::Vector2f(750.f, 100.f));
    }
    else if(this->wallSide==2){
        this->hitbox.setPosition(sf::Vector2f(1500.f, 100.f));
        this->hitbox.setSize(sf::Vector2f(100.f, 300.f));
    }
    else if(this->wallSide==3){
        this->hitbox.setPosition(sf::Vector2f(1500.f, 500.f));
        this->hitbox.setSize(sf::Vector2f(100.f, 300.f));
    }
    else if(this->wallSide==4){
        this->hitbox.setPosition(sf::Vector2f(850.f, 800.f));
        this->hitbox.setSize(sf::Vector2f(750.f, 100.f));
    }
    else if(this->wallSide==5){
        this->hitbox.setPosition(sf::Vector2f(0.f, 800.f));
        this->hitbox.setSize(sf::Vector2f(750.f, 100.f));
    }
    else if(this->wallSide==6){
        this->hitbox.setPosition(sf::Vector2f(0.f, 100.f));
        this->hitbox.setSize(sf::Vector2f(100.f, 300.f));
    }
    else if(this->wallSide==7){
        this->hitbox.setPosition(sf::Vector2f(0.f, 500.f));
        this->hitbox.setSize(sf::Vector2f(100.f, 300.f));
    }
    else if(this->wallSide==8){
        this->hitbox.setPosition(sf::Vector2f(0.f, 0.f));
        this->hitbox.setSize(sf::Vector2f(750.f, 100.f));
    }

};

Wall::~Wall(){
};


#endif