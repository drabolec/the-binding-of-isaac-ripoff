#ifndef SPIKE_H
#define SPIKE_H

#include "Enemy.h"

class Spike:public Enemy{
    public:
        Spike();
        Spike(sf::Vector2f pos);
        virtual ~Spike();
        void move(sf::Vector2f pos);
        void update(sf::Vector2f pos);
        bool setIsUp(bool a);
        int changeState(int a);
    private:    
        bool is_up=0;
        int state=0; // 0 - wylaczony 1 - zaraz sie wlaczy 2 - atak
};

Spike::Spike(){};

Spike::Spike(sf::Vector2f pos){
    this->change_can_be_hit(false);
    this->setHp(20);
    this->setColor(sf::Color::Yellow);
    this->setHitboxSize({40.f, 40.f});
    this->setShapeSize({40.f, 40.f});
    this->setPosition(pos);
};

Spike::~Spike(){
};

bool Spike::setIsUp(bool a){
    this->is_up=a;
};

void Spike::update(sf::Vector2f pos){
    if(this->state==1){

    };
    else if(this->state==1){
        this->is_up=true;
    };
    else{
        this->is_up=false;
    };

};

int Spike::changeState(int a){
    this->state=a;
};
#endif
