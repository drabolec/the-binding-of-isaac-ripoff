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
        std::vector<sf::IntRect*> curFrames;
        std::vector<sf::IntRect*> frames;
        std::vector<sf::IntRect*> framesR;
        int frame;
        void animate();
        sf::Clock clock;
        float speed;

    private:    

};

Dumb::Dumb(){
    //this->setColor(sf::Color::Green);
    this->setHitboxSize({64.f, 64.f});
    this->setShapeSize({64.f, 64.f});

};

Dumb::Dumb(sf::Vector2f pos){
    
    //this->setPosition(pos);
};

Dumb::~Dumb(){
    
};


void Dumb::update(sf::Vector2f pos){
    animate();
};

void Dumb::move(sf::Vector2f pos){
    pos = {pos.x-20.f, pos.y-20.f};
    sf::Vector2f dir = {pos.x-this->getPosition().x, pos.y-this->getPosition().y};
    dir = dir/(float)(sqrt(dir.x*dir.x+dir.y*dir.y));
    this->shape.move(dir*this->speed);
    this->hitbox.setPosition(this->shape.getPosition());
    if(this->getPosition().x<pos.x){
        this->curFrames = this->frames;
    }else{
        this->curFrames = this->framesR;
    }
    
};
void Dumb::animate(){
    if(this->clock.getElapsedTime().asSeconds() > 0.1f){
        this->clock.restart();
        this->shape.setTextureRect(*(this->curFrames.at(this->frame)));
        this->frame ++;
        if(this->frame >=4){
            this->frame = 0;
        }
    }
}









#endif