#ifndef PLAYER_H
#define PLAYER_H



#include "Item.h"
#include "FirstWeapon.h"
#include "Entity.h"

class Player: public Entity{

public:
    Player();
    virtual ~Player();

    void update();
    void move();
    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition();
    void render(sf::RenderTarget* target);
    
private:
    sf::RectangleShape shape;
    float movespeed;
};

Player::Player(){
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setSize(sf::Vector2f(30.f, 30.f));
    this->movespeed = 10.f;
    this->hitbox.setSize({30.f, 30.f});
}
Player::~Player(){

}
void Player::setPosition(sf::Vector2f pos){
    this->shape.setPosition(pos);
}
sf::Vector2f Player::getPosition(){
    return this->shape.getPosition();
}
void Player::move(){
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        this->shape.move({0.f, -this->movespeed});
    }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        this->shape.move({0.f, this->movespeed});
    }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        this->shape.move({-this->movespeed, 0.f});
    }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        this->shape.move({this->movespeed, 0.f});
    }
    
}

void Player::update(){
    this->move();
}
void Player::render(sf::RenderTarget* target){
    target->draw(this->shape);
    
}

#endif