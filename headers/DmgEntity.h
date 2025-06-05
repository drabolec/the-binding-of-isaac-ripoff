#ifndef DMGENTITY_H
#define DMGENTITY_H

#include "Entity.h"

class DmgEntity: public Entity{
public:
    void setHp(int hp);
    int getHp();
    void changeHp(int hp);
    void setDmg(int dmg);
    int getDmg();

private:
    int hp;
    int dmg;
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

void DmgEntity::setDmg(int dmg){
    this->dmg = dmg;
}
int DmgEntity::getDmg(){
    return this->dmg;
}






#endif