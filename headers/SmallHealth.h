#ifndef SMALLHEALTH_H
#define SMALLHEALTH_H

#include "Boost.h"

class SmallHealth: public Boost{

public:
    SmallHealth(sf::Vector2f pos);
    void setPosition(sf::Vector2f pos);

    void render(sf::RenderTarget* target);
    void update();
    virtual ~SmallHealth();

private:
    

};
SmallHealth::~SmallHealth(){
    delete this->texture;
}
SmallHealth::SmallHealth(sf::Vector2f pos){
    
    //setting up hitbox
    this->hitbox.setSize({40.f, 40.f});
    
    this->value = 10;
    //seting up texture
    this->texture = new sf::Texture("./Textures/Heart.png");
    //setting up int rect
    this->intrect = new sf::IntRect({0, 0},{16, 16});

    //setting up shape
    this->shape.setSize({40.f, 40.f});
    this->shape.setTextureRect(*intrect);
    this->shape.setTexture(texture);
    pos.x +=8.f;
    pos.y+=8.f;
    this->setPosition(pos);


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