#ifndef MINIGUNWEAPON_H
#define MINIGUNWEAPON_H

#include "Item.h"
#include "Bullet.h"
#include "RoundBullet.h"
#include "Game.h"

#include "cmath"

class MiniGunWeapon: public Item{
    public:
        
        void update();
        void updatePos(sf::Vector2f pos);
        void render(sf::RenderTarget* target);
        MiniGunWeapon();
        const float time = 0.2f;
        
    private:
        
        

    
};
MiniGunWeapon::MiniGunWeapon(){
    //setting texture
    this->texture = new sf::Texture("./Textures/minigun_weapon.png");
    //setting intrect
    this->intrect = new sf::IntRect({0, 0},{64, 18});
    //setting shape
    this->shape.setTextureRect(*intrect);
    this->shape.setTexture(texture);
    this->shape.setSize({80.f, 20.f});
    
    this->hitbox.setSize({80.f,20.f});
    this->hitbox.setPosition(this->shape.getPosition());

    
}
void MiniGunWeapon::update(){

    

    if(clock.getElapsedTime().asSeconds() > this->time){
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        //shooting
        this->shoot({0.f, -1.f});
        this->clock.restart();
        
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        this->shoot({0.f, 1.f});
        this->clock.restart();
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        this->shoot({-1.f, 0.f});
        this->clock.restart();
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        this->shoot({1.f, 0.f});
        this->clock.restart();
    }
    
    }
    this->shape.setPosition(this->playerPos);
    this->hitbox.setPosition(this->playerPos);
    
}
void MiniGunWeapon::updatePos(sf::Vector2f pos){
    this->shape.setPosition(pos);
    this->hitbox.setPosition(pos);
}
void MiniGunWeapon::render(sf::RenderTarget* target){
    target->draw(this->shape);
}


#endif