#ifndef SMALLHEALTH_H
#define SMALLHEALTH_H

#include "Boost.h"

class SmallHealth: public Boost{

public:
    SmallHealth();
    void setPosition(sf::Vector2f pos);

    void render(sf::RenderTarget* target);
    void update();

private:
    sf::CircleShape shape;
    

};

SmallHealth::SmallHealth(){
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setRadius(5.f);
    this->hitbox.setSize({3.f, 3.f});
    
    this->value = 10;
}
void SmallHealth::setPosition(sf::Vector2f pos){
    this->shape.setPosition(pos);
    this->hitbox.setPosition(this->shape.getPosition());
}

void SmallHealth::update(){
    this->hitbox.setPosition(this->shape.getPosition());
}
void SmallHealth::render(sf::RenderTarget* target){
    target->draw(this->shape);
}

#endif