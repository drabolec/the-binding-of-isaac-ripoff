#ifndef GREENDUMB_H
#define GREENDUMB_H

#include "Dumb.h"

class greenDumb:public Dumb{
public:
    greenDumb(sf::Vector2f pos);
};
greenDumb::greenDumb(sf::Vector2f pos){
    this->frame = 0;
    for(int i = 432; i < 500; i = i + 16){
        this->frames.emplace_back(new sf::IntRect({i, 40}, {16, 16}));
    }
    for(int i = 448; i < 516; i = i + 16){
        this->framesR.emplace_back(new sf::IntRect({i, 40}, {-16, 16}));
    }
    this->curFrames = this->frames;
    this->texture = new sf::Texture("./Textures/all.png");
    this->shape.setTexture(texture);
    this->setPosition(pos);
    this->speed = 4.f;
    this->setHp(200);
    this->setDmg(30.f);
}

#endif
