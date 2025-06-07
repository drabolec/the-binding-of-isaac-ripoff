#ifndef DUMB_H
#define DUMB_H

#include "Enemy.h"

class Dumb:public Enemy{
    public:
        Dumb();
        Dumb(sf::Vector2f pos);
        virtual ~Dumb();
        void move(sf::Vector2f pos);
        void update(sf::Vector2f pos);

    private:    

};

Dumb::Dumb(){};

Dumb::Dumb(sf::Vector2f pos){
    this->setHp(20);
    this->setDmg(5.f);
    this->setColor(sf::Color::Green);
    this->setHitboxSize({40.f, 40.f});
    this->setShapeSize({40.f, 40.f});
    this->setPosition(pos);
};

Dumb::~Dumb(){
};


void Dumb::update(sf::Vector2f pos){};

void Dumb::move(sf::Vector2f pos){
    if(pos.x>this->getPosition().x){
        this->setPosition(this->getPosition().x+2.f,this->getPosition().y);
    }
    if(pos.x<this->getPosition().x){
        this->setPosition(this->getPosition().x-2.f,this->getPosition().y);
    }
    if(pos.y>this->getPosition().y){
        this->setPosition(this->getPosition().x,this->getPosition().y+2.f);
    }
    if(pos.y<this->getPosition().y){
        this->setPosition(this->getPosition().x,this->getPosition().y-2.f);
    }
};









#endif