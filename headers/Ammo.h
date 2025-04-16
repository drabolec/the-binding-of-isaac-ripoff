#ifndef AMMO_H
#define AMMO_H

#include "Entity.h"
#include "RoundBullet.h"
#include "Bullet.h"

class Ammo:public Entity{
public:
    virtual void setPosition(sf::Vector2f pos);
    virtual Bullet* getType();
private:


};

void Ammo::setPosition(sf::Vector2f pos){

}
Bullet* Ammo::getType(){
    return new Bullet;
}

#endif