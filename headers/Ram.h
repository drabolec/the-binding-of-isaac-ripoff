#ifndef RAM_H
#define RAM_H

#include "Enemy.h"

class Ram:public Enemy{
    public:
        Ram();
        Ram(sf::Vector2f pos);
        virtual ~Ram();
        void move(sf::Vector2f pos);
        void update(sf::Vector2f pos);
        void changeState(int a);
        std::vector<sf::IntRect*> curFrames;
        std::vector<sf::IntRect*> frames;
        std::vector<sf::IntRect*> framesR;
        int frame;
        void animate();
        sf::Clock clock;
        float speed;
    private:  
        float gox,goy;
        float Random=100;
        int counter=0;
        bool block_move=0;
        bool attacked=0;
        int state=0; // 0 - passive 1 - atak
};

Ram::Ram(){};

Ram::Ram(sf::Vector2f pos){
    //frames
    


    this->change_can_be_hit(true);
    this->setHp(20);
    this->setDmg(20);
    this->setColor(sf::Color::Green);
    this->setHitboxSize({40.f, 40.f});
    this->setShapeSize({40.f, 40.f});
    this->setPosition(pos);
};

Ram::~Ram(){
    
};


void Ram::update(sf::Vector2f pos){
    float x,y,chance,dist;

    this->attacked=this->getCollided();
    if(this->attacked){
        this->state=2;
    }

    counter++;
    if(counter>30){
        if(this->state==2){
            this->state=0;
        }
        counter=0;
    }

    if(counter==0){
    x=abs(pos.x-(this->getPosition().x+20.f));
    y=abs(pos.y-(this->getPosition().y+20.f));

    dist=sqrt(pow(x,2)+pow(y,2));


    if(dist>1000){
        this->state=0;
    }
    if(dist<=1000){
        Random = getRandomInt(0, 100);
        if(Random<(dist/10)){
            this->state=0;
        }
        else{
            this->state=1;
        }
    }


    if(this->state==1){
        this->setColor(sf::Color::Red);
        this->gox=pos.x;
        this->goy=pos.y;

    }
    else if(this->state==0){
        this->setColor(sf::Color::Black);      
    }
    else{
        this->setColor(sf::Color::Green); 
    }
    }
};

void Ram::changeState(int a){
    this->state=a;
};

void Ram::move(sf::Vector2f pos){
    
    if(this->state==2){
    }
    if(this->state==1){
    if(pos.x>this->getPosition().x){
        this->setPosition(this->getPosition().x+5.f,this->getPosition().y);
    }
    if(pos.x<this->getPosition().x){
        this->setPosition(this->getPosition().x-5.f,this->getPosition().y);
    }
    if(pos.y>this->getPosition().y){
        this->setPosition(this->getPosition().x,this->getPosition().y+5.f);
    }
    if(pos.y<this->getPosition().y){
        this->setPosition(this->getPosition().x,this->getPosition().y-5.f);
    }
    }
    else{
    if(pos.x>this->getPosition().x){
        this->setPosition(this->getPosition().x+1.f,this->getPosition().y);
    }
    if(pos.x<this->getPosition().x){
        this->setPosition(this->getPosition().x-1.f,this->getPosition().y);
    }
    if(pos.y>this->getPosition().y){
        this->setPosition(this->getPosition().x,this->getPosition().y+1.f);
    }
    if(pos.y<this->getPosition().y){
        this->setPosition(this->getPosition().x,this->getPosition().y-1.f);
    }
    }
};


#endif
