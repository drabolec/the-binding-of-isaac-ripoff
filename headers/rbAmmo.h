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

};
Bullet* rbAmmo::getType(){
    return this->type;
}
rbAmmo::rbAmmo(){
    shape.setSize({20.f, 20.f});
    shape.setFillColor(sf::Color::Yellow);
    type = new RoundBullet();
    this->hitbox.setSize({20.f, 20.f});
    this->hitbox.setPosition(this->shape.getPosition());
}
void rbAmmo::setPosition(sf::Vector2f pos){
    this->shape.setPosition(pos);

}
void rbAmmo::update(){
    this->hitbox.setPosition(this->shape.getPosition());
}
void rbAmmo::render(sf::RenderTarget* target){
    target->draw(this->shape);
}

#endif