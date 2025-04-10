#ifndef DMGENTITY_H
#define DMGENTITY_H

#include "Entity.h"

class DmgEntity: public Entity{
public:
    void setHp(int hp);
    int getHp();
    void changeHp(int hp);
private:
    int hp;
};

void DmgEntity::setHp(int hp){
    this->hp = hp;
}
int DmgEntity::getHp(){
    return this->hp;
}
void DmgEntity::changeHp(int hp){
    this->hp += hp;
}

#endif