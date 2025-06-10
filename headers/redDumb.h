#ifndef REDDUMB_H
#define REDDUMB_H

#include "Dumb.h"

class redDumb:public Dumb{
public:
    redDumb(sf::Vector2f pos);
    ~redDumb();
};
redDumb::~redDumb(){
    delete this->texture;
}
redDumb::redDumb(sf::Vector2f pos){
    this->frame = 0;
    for(int i = 432; i < 500; i = i + 16){
        this->frames.emplace_back(new sf::IntRect({i, 64}, {16, 16}));
    }
    for(int i = 448; i < 516; i = i + 16){
        this->framesR.emplace_back(new sf::IntRect({i, 64}, {-16, 16}));
    }
    this->curFrames = this->frames;
    this->texture = new sf::Texture("./Textures/all.png");
    this->shape.setTexture(texture);
    this->setPosition(pos);
    this->speed = 5.f;
    this->setHp(300);
    this->setDmg(40.f);
}

#endif
