#ifndef WHITERAM_H
#define WHITERAM_H

#include "Ram.h"

class whiteRam:public Ram{
    public:
    whiteRam(sf::Vector2f pos);
    ~whiteRam();
};
whiteRam::~whiteRam(){
    delete this->texture;
}
whiteRam::whiteRam(sf::Vector2f pos){
    //frames
    this->frame = 0;
    for(int i = 144; i < 272; i = i + 32){
        this->frames.emplace_back(new sf::IntRect({i, 340}, {32, 32}));
    }
    for(int i = 176; i < 304; i = i + 32){
        this->framesR.emplace_back(new sf::IntRect({i, 340}, {-32, 32}));
    }
    for(int i = 16; i < 144; i = i + 32){
        this->idleframes.emplace_back(new sf::IntRect({i, 340}, {32, 32}));
    }
    for(int i = 48; i < 176; i = i + 32){
        this->idleframesR.emplace_back(new sf::IntRect({i, 340}, {-32, 32}));
    }

    this->curFrames = this->idleframes;
    this->texture = new sf::Texture("./Textures/all.png");
    this->shape.setTexture(texture);
    this->shape.setTextureRect(*(this->curFrames.at(this->frame)));

    this->change_can_be_hit(true);
    this->setHp(20);
    this->setDmg(20);
    this->setHitboxSize({80.f, 80.f});
    this->setShapeSize({80.f, 80.f});
    this->setPosition(pos);
    this->state = 2;
}

#endif