#ifndef BOOST_H
#define BOOST_H

#include "Entity.h"

class Boost:public Entity{
public:
//sth will be here
    virtual void setPosition(sf::Vector2f pos);
    int value;
private:
};
void Boost::setPosition(sf::Vector2f){

}

#endif