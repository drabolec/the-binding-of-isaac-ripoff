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
    this->shape.setRadius(15.f);
    this->shape.setFillColor(sf::Color::Red);
    this->speed = 10.f;
}
void RoundBullet::update(){
    this->shape.move(this->direction*10.f);
}
void RoundBullet::render(sf::RenderTarget* target){
    target->draw(this->shape);
}
void RoundBullet::setInitPos(){
    this->shape.setPosition(this->initPos);
}


#endif