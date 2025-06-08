#ifndef TURRET_H
#define TURRET_H

#include "Enemy.h"
#include "Bullet.h"
#include "RoundBullet.h"

class Turret:public Enemy{
    public:
        Turret();
        Turret(sf::Vector2f pos);
        virtual ~Turret();
        void move(sf::Vector2f pos);
        void update(sf::Vector2f pos);
        void shoot(sf::Vector2f direction);
        void setCurrentEnemyBullets(std::vector<Bullet*> vec);
        std::vector<Bullet*> getCurrentEnemyBullet();
    private:    
        float Random;
        int newx,newy;
        int counter=0;
        bool state=0;
        std::vector<Bullet*> enemyBullets;
        Bullet* bullet;
};

Turret::Turret(){};

Turret::Turret(sf::Vector2f pos){
    this->setHp(20);
    this->setDmg(5.f);
    this->setColor(sf::Color::Green);
    this->setHitboxSize({60.f, 60.f});
    this->setShapeSize({60.f, 60.f});
    this->setPosition(pos);
    this->bullet = new RoundBullet();
};

Turret::~Turret(){
};


void Turret::update(sf::Vector2f pos){
    counter++;
    if(counter>90){
        counter=0;
    }
    if(counter==0){
        if(state){
            state=false;
        }
        else{
            state=true;
        }
    }
};

void Turret::move(sf::Vector2f pos){

    Random = getRandomInt(200, 1400);
    newx=Random;
    Random = getRandomInt(200, 700);
    newy=Random;

    if(state){
        this->change_can_be_hit(true);
        this->setColor(sf::Color::Green);
    }
    else{
        this->change_can_be_hit(false);
        this->setColor(sf::Color::Red);
        if(counter==0){
        this->setPosition(sf::Vector2f(newx,newy));
        }

        if(counter==30){
        this->shoot({1.f, 0.f});
        this->shoot({0.f, 1.f});
        this->shoot({-1.f, 0.f});
        this->shoot({0.f, -1.f});
        }
        if(counter==45){
        this->shoot({1.f, 0.f});
        this->shoot({0.f, 1.f});
        this->shoot({-1.f, 0.f});
        this->shoot({0.f, -1.f});
        }      
        if(counter==60){
        this->shoot({1.f, 0.f});
        this->shoot({0.f, 1.f});
        this->shoot({-1.f, 0.f});
        this->shoot({0.f, -1.f});
        }
        if(counter==75){
        this->shoot({1.f, 0.f});
        this->shoot({0.f, 1.f});
        this->shoot({-1.f, 0.f});
        this->shoot({0.f, -1.f});
        }
        if(counter==90){
        this->shoot({1.f, 0.f});
        this->shoot({0.f, 1.f});
        this->shoot({-1.f, 0.f});
        this->shoot({0.f, -1.f});
        }
    }

};

void Turret::shoot(sf::Vector2f direction){
    
        Bullet* bullet;
        if(dynamic_cast<RoundBullet*>(this->bullet)!=NULL){
            bullet = new RoundBullet;
        }
        bullet->direction = direction;
        bullet->initPos = this->getPosition();
        bullet->setInitPos();
        this->enemyBullets.emplace_back(bullet);
    
}
void Turret::setCurrentEnemyBullets(std::vector<Bullet*> vec){
    this->enemyBullets = vec;
}
std::vector<Bullet*> Turret::getCurrentEnemyBullet(){
    return this->enemyBullets;
}



#endif