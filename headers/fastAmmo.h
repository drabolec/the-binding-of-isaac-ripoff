#ifndef FASTAMMO_H
#define FASTAMMO_H

#include "Entity.h"

#include "Bullet.h"
#include "FastBullet.h"
#include "Ammo.h"

class fastAmmo:public Ammo{
    public:
    fastAmmo(sf::Vector2f pos);
    fastAmmo();
        Bullet* type;
        void setPosition(sf::Vector2f pos);
        Bullet* getType();

        void update();
        void render(sf::RenderTarget* target);
        ~fastAmmo();
    private:
        

};
fastAmmo::~fastAmmo(){
    delete this->texture;
}
Bullet* fastAmmo::getType(){
    return this->type;
}
fastAmmo::fastAmmo(sf::Vector2f pos){
    //setting tezture
    this->texture = new sf::Texture("./Textures/default_ammo.png");
    //setting intrect
    this->intrect = new sf::IntRect({0,0},{32, 32});
    //setting shape
    this->shape.setSize({50.f, 50.f});
    this->shape.setTexture(texture);
    this->shape.setTextureRect(*intrect);
    //setting type
    this->type = new FastBullet;
    //setting hitbox
    this->hitbox.setSize({50.f, 50.f});
    this->hitbox.setPosition(this->shape.getPosition());
    pos.x +=6.f;
    pos.y +=6.f;
    this->setPosition(pos);
}
fastAmmo::fastAmmo(){
    //setting tezture
    this->texture = new sf::Texture("./Textures/default_ammo.png");
    //setting intrect
    this->intrect = new sf::IntRect({0,0},{32, 32});
    //setting shape
    this->shape.setSize({50.f, 50.f});
    this->shape.setTexture(texture);
    this->shape.setTextureRect(*intrect);
    //setting type
    this->type = new FastBullet;
    //setting hitbox
    this->hitbox.setSize({50.f, 50.f});
    this->hitbox.setPosition(this->shape.getPosition());
}
void fastAmmo::setPosition(sf::Vector2f pos){
    this->shape.setPosition(pos);
    this->hitbox.setPosition(pos);

}
void fastAmmo::update(){
    this->hitbox.setPosition(this->shape.getPosition());
}
void fastAmmo::render(sf::RenderTarget* target){
    target->draw(this->shape);
}

#endif