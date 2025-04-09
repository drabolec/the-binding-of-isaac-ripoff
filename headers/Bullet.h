#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet: public Entity{
public:
    sf::Vector2f direction; //speed and direction
    float speed;
    float dmg;
    float range;
    float rangeControl;
    bool isVisible=true;
    sf::Vector2f initPos;
    virtual void setInitPos();

    
    

};
void Bullet::setInitPos(){};


#endif