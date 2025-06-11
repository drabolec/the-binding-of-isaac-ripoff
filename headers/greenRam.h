#ifndef GREENRAM_H
#define GREENRAM_H

#include "Ram.h"

class greenRam:public Ram{
    public:
    greenRam(sf::Vector2f pos);
    ~greenRam();
};
greenRam::~greenRam(){
    delete this->texture;
}
greenRam::greenRam(sf::Vector2f pos){
    //frames
    this->frame = 0;
    for(int i = 144; i < 272; i = i + 32){
        this->frames.emplace_back(new sf::IntRect({i, 386}, {32, 32}));
    }
    for(int i = 176; i < 304; i = i + 32){
        this->framesR.emplace_back(new sf::IntRect({i, 386}, {-32, 32}));
    }
    for(int i = 16; i < 144; i = i + 32){
        this->idleframes.emplace_back(new sf::IntRect({i, 386}, {32, 32}));
    }
    for(int i = 48; i < 176; i = i + 32){
        this->idleframesR.emplace_back(new sf::IntRect({i, 386}, {-32, 32}));
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