#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>


#include "Item.h"
#include "FirstWeapon.h"
#include "DmgEntity.h"

class Player: public DmgEntity{

public:
    Player();
    virtual ~Player();
    
    
    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition();
    void setFont(sf::Font* font);
    void initHp();

    
    void update();
    void move();
    void render(sf::RenderTarget* target);

    bool pressedE;
    
    
private:
    //clicking speed for E button
    const int clickSpeed = 10;
    //frame counter for E button might later be used for animations
    int counter;

    //player texture
    sf::RectangleShape shape;
    //movespeed
    float movespeed;
    //font
    sf::Font* font;
    //hp bar
    sf::Text* hpText;
};

Player::Player(){
    //seting defaul parameters
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setSize(sf::Vector2f(30.f, 30.f));
    this->movespeed = 10.f;
    this->pressedE = false;
    this->counter = 10;
    this->setHp(100);
    //setting hitbox size
    this->hitbox.setSize({30.f, 30.f});
}
//text class does not have and empty construcotr and it has to be creater after the font is set so 
//this spageti code fixes that 
void Player::initHp(){
    this->hpText = new sf::Text(*font);
    this->hpText->setString(std::to_string(this->getHp())+ " hp");
    this->hpText->setFillColor(sf::Color::White); //change later
    this->hpText->setCharacterSize(10);
    this->hpText->setPosition({this->shape.getPosition().x, this->shape.getPosition().y  - 30.f});
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
    
    //update change weapon bool if E is pressed 
    //if change weapon bool is true then it allows player to swap weapons
    //press E to swap ewapons
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)&&counter >= this->clickSpeed)
    {
        this->pressedE = true;
        counter = 0;
    }else{
        this->pressedE = false;
    }
    
}

void Player::update(){
    //updates counter
    if(counter <60){
        this->counter ++;
    }
    
    //mvoes and check for other actions
    this->move();

    //setting hitbox position to match player position
    this->hitbox.setPosition(this->shape.getPosition());

    //updating hp text box
    this->hpText->setPosition({this->shape.getPosition().x, this->shape.getPosition().y- 30.f});
    this->hpText->setString(std::to_string(this->getHp())+ " hp");
}
void Player::render(sf::RenderTarget* target){
    target->draw(this->shape);
    target->draw(*hpText);
    
}
void Player::setFont(sf::Font* font){
    this->font = font;
}


#endif