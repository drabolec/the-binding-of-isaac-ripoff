#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"
#include "DmgEntity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

class Enemy:public DmgEntity{
    public:
        Enemy();
        virtual ~Enemy();
        void move();
        void update(sf::RenderTarget* target);
        void render(sf::RenderTarget* target);
        bool getIsDead();
        void setPosition(sf::Vector2f pos);
        sf::Vector2f getPosition();
    private:    
        int hp;
        bool isDead;
        float movespeed;
        sf::RectangleShape shape;
        
};

Enemy::Enemy(){
    this->shape.setFillColor(sf::Color::Red);  //temporary
    this->shape.setSize(sf::Vector2f(10.f, 10.f));
    this->hitbox.setSize(sf::Vector2f(10.f, 10.f));
    this->movespeed = 1.f;
};
Enemy::~Enemy(){
};
void Enemy::setPosition(sf::Vector2f pos){
    this->shape.setPosition(pos);
}
sf::Vector2f Enemy::getPosition(){
    return this->shape.getPosition();
}


void Enemy::move(){ //temporary
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I))
    {
        this->shape.move({0.f, -this->movespeed});
        this->hitbox.move({0.f, -this->movespeed});
    }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
    {
        this->shape.move({0.f, this->movespeed});
        this->hitbox.move({0.f, this->movespeed});
    }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
    {
        this->shape.move({-this->movespeed, 0.f});
        this->hitbox.move({-this->movespeed, 0.f});
    }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
    {
        this->shape.move({this->movespeed, 0.f});
        this->hitbox.move({this->movespeed, 0.f});
    }
};

void Enemy::update(sf::RenderTarget* target){
    this->move();
    if(this->hp<=0){
        this->isDead=true;
    }
};
void Enemy::render(sf::RenderTarget* target){
    target->draw(this->shape);
};

bool Enemy::getIsDead(){
    return this->isDead;
}

#endif