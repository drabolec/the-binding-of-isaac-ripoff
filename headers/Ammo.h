#ifndef AMMO_H
#define AMMO_H

#include "Entity.h"
#include "RoundBullet.h"
#include "Bullet.h"

class Ammo:public Entity{
public:
    virtual void setPosition(sf::Vector2f pos);
    virtual Bullet* getType();
    virtual ~Ammo();
private:


};
Ammo::~Ammo(){
    delete this->texture;
}
void Ammo::setPosition(sf::Vector2f pos){

}
Bullet* Ammo::getType(){
    return new Bullet;
}

#endif