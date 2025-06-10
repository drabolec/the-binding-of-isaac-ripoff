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
        void setIsUp(bool a);
        void changeState(int a);
    private:  
        int Random=100;
        int counter=0;
        bool is_up=0;
        int state=0; // 0 - wylaczony 1 - zaraz sie wlaczy 2 - atak
};

Spike::Spike(){};

Spike::Spike(sf::Vector2f pos){
    this->change_can_be_hit(false);
    this->setHp(20);
    this->setDmg(0);
    this->setHitboxSize({64.f, 64.f});
    this->setShapeSize({64.f, 64.f});
    this->texture = new sf::Texture("./Textures/floorall.png");
    this->shape.setTexture(this->texture);
    this->shape.setTextureRect(*(new sf::IntRect({0, 48}, {16, 16})));
    this->setPosition(pos);
};

Spike::~Spike(){
};

void Spike::setIsUp(bool a){
    this->is_up=a;
};

void Spike::update(sf::Vector2f pos){
    float x,y,chance;

    x=abs(pos.x-(this->getPosition().x+20.f));
    y=abs(pos.y-(this->getPosition().y+20.f));
    if(x<400){
        chance+=(400-x)/4;
    }
    else{
        chance=0;
    }

    if(y<400){
        chance+=(400-x)/4;
    }
    else{
        chance=0;
    }


    if(this->counter%20==0){
        Random = getRandomInt(0, 100);
    }

    if(Random<=chance&&this->state==0&&this->counter>60){
        this->state=1;
        this->counter=0;
    }

    if(this->counter==30&&this->state==1){
        this->state=2;
        this->counter=0;
    }
    if(this->counter==120&&this->state==2){
        this->state=0;
        this->counter=0;
    }


    if(this->state==1){
        this->shape.setTextureRect(*(new sf::IntRect({16, 48}, {16, 16})));
    }
    else if(this->state==2){
        this->shape.setTextureRect(*(new sf::IntRect({48, 48}, {16, 16})));
        this->setDmg(50);   
    }
    else{
        this->is_up=false;
        this->shape.setTextureRect(*(new sf::IntRect({0, 48}, {16, 16})));

        this->setDmg(0);
    }
    counter++;
};

void Spike::changeState(int a){
    this->state=a;
};

void Spike::move(sf::Vector2f pos){
};


#endif
