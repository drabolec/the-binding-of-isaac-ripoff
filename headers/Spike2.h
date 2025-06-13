#ifndef SPIKE2_H
#define SPIKE2_H

#include "Enemy.h"

class Spike2:public Enemy{
    public:
        Spike2();
        Spike2(sf::Vector2f pos);
        int getState();
        virtual ~Spike2();
        void move(sf::Vector2f pos);
        void update(sf::Vector2f pos);
    private:    

};

Spike2::Spike2(){};

Spike2::Spike2(sf::Vector2f pos){
    this->change_can_be_hit(false);
    this->setDmg(10.f);
    this->setHp(20);
    this->setHitboxSize({64.f, 64.f});
    this->setShapeSize({64.f, 64.f});
    this->setPosition(pos);
    this->texture = new sf::Texture("./Textures/floorall.png");
    this->getShape().setTexture(this->texture);
    this->getShape().setTextureRect(*(new sf::IntRect({48, 48}, {16, 16})));
};
int Spike2::getState(){
    return 2;
}
Spike2::~Spike2(){
    delete this->texture;
};

void Spike2::move(sf::Vector2f pos){
};

void Spike2::update(sf::Vector2f pos){
};
#endif
