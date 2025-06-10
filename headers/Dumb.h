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
//frames
    
    

    
    
    
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
    if(pos.x>this->getPosition().x){
        this->curFrames = this->frames;
        this->setPosition(this->getPosition().x+this->speed,this->getPosition().y);
    }
    if(pos.x<this->getPosition().x){
        this->curFrames = this->framesR;
        this->setPosition(this->getPosition().x-this->speed,this->getPosition().y);
        

    }
    if(pos.y>this->getPosition().y){
        
        this->setPosition(this->getPosition().x,this->getPosition().y+this->speed);
    }
    if(pos.y<this->getPosition().y){
        
        this->setPosition(this->getPosition().x,this->getPosition().y-this->speed);
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