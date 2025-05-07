#ifndef FIRSTWEAPON_H
#define FIRSTWEAPON_H

#include "Item.h"
#include "Bullet.h"
#include "RoundBullet.h"
#include "Game.h"

#include "cmath"

class FirstWeapon: public Item{
    public:
        void shoot(sf::Vector2f direction);
        void update();
        void updatePos(sf::Vector2f pos);
        void render(sf::RenderTarget* target);
        FirstWeapon();
        int counter;
        const int shootingSpeed = 20;
    private:
        sf::RectangleShape shape;
        
};
FirstWeapon::FirstWeapon(){
    shape.setFillColor(sf::Color::Red);
    shape.setSize({30.f, 10.f});
    
    this->hitbox.setSize({30.f,10.f});
    this->hitbox.setPosition(this->shape.getPosition());

    counter = this->shootingSpeed;
}
void FirstWeapon::update(){

    

    if(this->counter >=shootingSpeed){
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        //shooting
        this->shoot({0.f, -1.f});
        counter = 0;
        
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        this->shoot({0.f, 1.f});
        counter = 0;
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        this->shoot({-1.f, 0.f});
        counter = 0;
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        this->shoot({1.f, 0.f});
        counter = 0;
    }
    
    }else{
        this->counter ++;
    }
    
}
void FirstWeapon::updatePos(sf::Vector2f pos){
    this->shape.setPosition(pos);
    this->hitbox.setPosition(pos);
}
void FirstWeapon::render(sf::RenderTarget* target){
    target->draw(this->shape);
}
void FirstWeapon::shoot(sf::Vector2f direction){
    Bullet* bullet;
    if(dynamic_cast<RoundBullet*>(this->bullet)!=NULL){
        bullet = new RoundBullet;
    }
    bullet->direction = direction;
    bullet->initPos = this->playerPos;
    bullet->setInitPos();
    this->playerBullets.emplace_back(bullet);
}

#endif