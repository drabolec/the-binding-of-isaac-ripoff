#ifndef SPIKE2_H
#define SPIKE2_H

#include "Enemy.h"

class Spike2:public Enemy{
    public:
        Spike2();
        Spike2(sf::Vector2f pos);
        virtual ~Spike2();
        void move(sf::Vector2f pos);
        void update(sf::Vector2f pos);
    private:    

};

Spike2::Spike2(){};

Spike2::Spike2(sf::Vector2f pos){
    this->change_can_be_hit(false);
    this->setDmg(4.f);
    this->setHp(20);
    this->setColor(sf::Color::Black);
    this->setHitboxSize({40.f, 40.f});
    this->setShapeSize({40.f, 40.f});
    this->setPosition(pos);
};

Spike2::~Spike2(){
};

void Spike2::move(sf::Vector2f pos){
};

void Spike2::update(sf::Vector2f pos){
};
#endif
