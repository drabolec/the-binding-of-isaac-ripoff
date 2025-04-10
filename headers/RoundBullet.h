#ifndef ROUNDBULLET_H
#define ROUNDBULLET_H

#include "Bullet.h"

class RoundBullet:public Bullet{
    public:
        RoundBullet();
        
        void update();
        void render(sf::RenderTarget* targe);
        void setInitPos();
        
    private:
        sf::CircleShape shape;
};
RoundBullet::RoundBullet(){
    //seting defaul parameters
    this->shape.setRadius(15.f);
    this->shape.setFillColor(sf::Color::Red);
    this->speed = 10.f;
    this->range = 300.f;
    this->hitbox.setSize({20.f, 20.f});
}
void RoundBullet::update(){
    //updating hitbox position
    this->hitbox.setPosition(this->shape.getPosition());
    //range control
    if(rangeControl >= range){
        //makes bullet disapear when out of range and deleted in Game class
        this->isVisible = false;
    }
    //moving bullet in correct direction and speed
    this->shape.move(this->direction*this->speed);
    //incremencting speed to range control
    rangeControl += speed;
}
void RoundBullet::render(sf::RenderTarget* target){
    target->draw(this->shape);
}
void RoundBullet::setInitPos(){
    this->shape.setPosition(this->initPos);
}


#endif