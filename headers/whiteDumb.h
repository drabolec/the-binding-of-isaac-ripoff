#ifndef WHITEDUMB_H
#define WHITEDUMB_H

#include "Dumb.h"

class whiteDumb:public Dumb{
public:
    whiteDumb(sf::Vector2f pos);
};
whiteDumb::whiteDumb(sf::Vector2f pos){
    this->frame = 0;
    for(int i = 432; i < 500; i = i + 16){
        this->frames.emplace_back(new sf::IntRect({i, 16}, {16, 16}));
    }
    for(int i = 448; i < 516; i = i + 16){
        this->framesR.emplace_back(new sf::IntRect({i, 16}, {-16, 16}));
    }
    this->curFrames = this->frames;
    this->texture = new sf::Texture("./Textures/all.png");
    this->shape.setTexture(texture);
    this->setPosition(pos);
    this->speed = 3.f;
    this->setHp(100);
    this->setDmg(20.f);
}

#endif