#ifndef FASTBULLET_H
#define FASTBULLET_H

#include "Bullet.h"

class FastBullet:public Bullet{
    public:
    FastBullet();
        
        void update();
        void render(sf::RenderTarget* targe);
        void setInitPos();
        
    private:
        
};
FastBullet::FastBullet(){
    //setting up textrue
    this->texture = new sf::Texture("./Textures/necrobolt1_strip.png");
    //setting up int rect
    this->intrect = new sf::IntRect({0, 0},{10, 10});
    //seting defaul parameters
    this->shape.setSize({30.f, 30.f});
    this->shape.setTexture(texture);
    this->shape.setTextureRect(*intrect);
    this->shape.setFillColor(sf::Color(200, 0, 0));

    this->speed = 20.f;
    this->range = 600.f;
    this->hitbox.setSize({30.f, 30.f});
    this->rangeControl = 0;
}
void FastBullet::update(){    
    //moving bullet in correct direction and speed
    this->shape.move(this->direction*this->speed);
    //updating hitbox position
    this->hitbox.setPosition(this->shape.getPosition());
    //incremencting speed to range control
    this->rangeControl += this->speed;
    //range control
    if(this->rangeControl >= this->range){
        //makes bullet disapear when out of range and deleted in Game class
        this->isVisible = false;
    }
}
void FastBullet::render(sf::RenderTarget* target){

    target->draw(this->shape);
    

}
void FastBullet::setInitPos(){
    this->shape.setPosition(this->initPos);
    
    
}


#endif