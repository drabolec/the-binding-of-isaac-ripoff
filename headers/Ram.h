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
        std::vector<sf::IntRect*> idleframes;
        std::vector<sf::IntRect*> idleframesR;
        int frame;
        void animate();
        sf::Clock clock;
        float speed;
        sf::Clock animClock; 
        float gox,goy;
        float Random=100;
        int counter=0;
        bool block_move=0;
        bool attacked=0;
        int state; // 0 - passive 1 - atak
        bool wait;
        int rcount=0;
};

Ram::Ram(){};

Ram::Ram(sf::Vector2f pos){
    
};

Ram::~Ram(){
    
};

void Ram::animate(){
    if(this->animClock.getElapsedTime().asSeconds() > 0.1f){
        this->animClock.restart();
        this->frame ++;
        if(this->frame >=4){
            this->frame = 0;
        }
        this->shape.setTextureRect(*(this->curFrames.at(this->frame)));
    }
}
void Ram::update(sf::Vector2f pos){
    
    animate();
    float x,y,chance,dist;

    this->attacked=this->getCollided();
    if(this->attacked){
        this->counter = 61;
        
        
    }

    rcount++;
    counter++;
    if(rcount > 20){
        Random = getRandomInt(0, 600);
        rcount = 0;
    }
    if(counter>60){
        
        if(this->attacked){
            
            this->state=2;
            this->attacked = false;
            this->setCollided(false);
            wait = true;
            
        }else if(wait){
            wait = false;
        }
        counter=0;
    }

    if(counter==0){
        x=abs(pos.x-(this->getPosition().x+20.f));
        y=abs(pos.y-(this->getPosition().y+20.f));

        dist=sqrt(pow(x,2)+pow(y,2));


    if(dist>700 && !wait){
        this->state=2;
    }
    if(dist<=500 && !wait){
        
        
        //Random = getRandomInt(0, 300);
        if(dist<Random){
            this->state=1;
        }
        else{
            this->state=0;
        }
        
    }


    if(this->state==1 || this->state==0){
        if(pos.x < this->shape.getPosition().x){
            this->curFrames = this->framesR;
        }
        else if(pos.x > this->shape.getPosition().x){
            this->curFrames = this->frames;
        }
        this->gox=pos.x;
        this->goy=pos.y;

    }
    else{
        if(pos.x < this->shape.getPosition().x){
            this->curFrames = this->idleframesR;
        }
        else if(pos.x > this->shape.getPosition().x){
            this->curFrames = this->idleframes;
        } 
    }
    }
};

void Ram::changeState(int a){
    this->state=a;
};

void Ram::move(sf::Vector2f pos){
    pos = {pos.x-40.f, pos.y-40.f};
    if(this->state==2){
    }
    else if(this->state==1){
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
