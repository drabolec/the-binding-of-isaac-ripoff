#ifndef RBAMMO_H
#define RBAMMO_H

#include "Entity.h"

#include "Bullet.h"
#include "RoundBullet.h"
#include "Ammo.h"

class rbAmmo:public Ammo{
    public:
        rbAmmo();
        Bullet* type;
        void setPosition(sf::Vector2f pos);
        Bullet* getType();

        void update();
        void render(sf::RenderTarget* target);
    private:
        sf::RectangleShape shape;
        sf::Texture *texture;
        sf::IntRect *intrect;

};
Bullet* rbAmmo::getType(){
    return this->type;
}
rbAmmo::rbAmmo(){
    //setting tezture
    this->texture = new sf::Texture("./Textures/default_ammo.png");
    //setting intrect
    this->intrect = new sf::IntRect({0,0},{32, 32});
    //setting shape
    this->shape.setSize({50.f, 50.f});
    this->shape.setTexture(texture);
    this->shape.setTextureRect(*intrect);
    this->shape.setFillColor(sf::Color(209, 0, 150));
    //setting type
    this->type = new RoundBullet();
    //setting hitbox
    this->hitbox.setSize({50.f, 50.f});
    this->hitbox.setPosition(this->shape.getPosition());
}
void rbAmmo::setPosition(sf::Vector2f pos){
    this->shape.setPosition(pos);
    this->hitbox.setPosition(pos);

}
void rbAmmo::update(){
    this->hitbox.setPosition(this->shape.getPosition());
}
void rbAmmo::render(sf::RenderTarget* target){
    target->draw(this->shape);
}

#endif