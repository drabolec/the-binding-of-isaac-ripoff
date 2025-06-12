#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"
#include "Bullet.h"
#include "RoundBullet.h"
#include "Player.h"

class Boss:public Enemy{
    public:
        Boss();
        Boss(sf::Vector2f pos,Player* playerb);
        virtual ~Boss();
        void move(sf::Vector2f pos);
        void update(sf::Vector2f pos);
        void shoot(sf::Vector2f direction);
        void setCurrentEnemyBullets(std::vector<Bullet*> vec);
        std::vector<Bullet*> getCurrentEnemyBullet();
        void animate();
        void initBlinkFrames();
        void render(sf::RenderTarget* traget);
    private:    
        float Random;
        int newx,newy;
        int counter=0;
        int state=0;  // 0 - turret 1 - przesuwanie gracza 2 - atak soba
        std::vector<Bullet*> enemyBullets;
        Bullet* bullet;
        sf::Clock clock;
        std::vector<sf::IntRect*> frames;
        sf::RectangleShape blink;
        sf::Texture* blinkTex;
        std::vector<sf::IntRect*> blinkFrames;
        sf::Clock blinkClock;
        int blinkFrame;
        int frame;
        bool attacked2;
        Player* playerb;
};

Boss::Boss(){};

Boss::Boss(sf::Vector2f pos,Player* playerb){
    //blink frames
    this->blinkFrame = 0;
    this->blink.setSize({100.f, 100.f});
    this->blinkTex = new sf::Texture("./Textures/mageblink.png");
    this->blink.setTexture(this->blinkTex);
    this->initBlinkFrames();
    this->blink.setTextureRect(*(this->blinkFrames.at(this->blinkFrame)));
    //frames
    this->playerb=playerb;
    this->frame = 0;
    for(int i = 16; i < 144; i = i + 32){
        this->frames.emplace_back(new sf::IntRect({i, 436}, {32, 32}));
    }
    this->setHp(200.f);
    this->setDmg(20.f);
    this->setHitboxSize({80.f, 80.f});
    this->setShapeSize({80.f, 80.f});
    this->setPosition(pos);
    this->bullet = new RoundBullet();
    //texture
    this->texture = new sf::Texture("./Textures/all.png");
    this->shape.setTexture(this->texture);
    this->shape.setTextureRect(*(this->frames.at(this->frame)));
};

Boss::~Boss(){
    delete this->texture;
    delete this->blinkTex;
    for(auto el:this->blinkFrames){
        delete el;
    }
    for(auto el:this->frames){
        delete el;
    }
};


void Boss::update(sf::Vector2f pos){
    this->animate();
    this->blink.setPosition({this->shape.getPosition().x + this->shape.getSize().x/2-blink.getSize().x/2, this->shape.getPosition().y + this->shape.getSize().y/2-blink.getSize().y/2});
    counter++;
    if(counter>360){
        counter=0;
    }
    if(counter==0){
        this->state=0;
    }
    if(counter==120){
        this->state=1;
    }
    if(counter==240){
        this->state=2;
    }
};

void Boss::move(sf::Vector2f pos){

    Random = getRandomInt(200, 1400);
    newx=Random;
    Random = getRandomInt(200, 700);
    newy=Random;

    if(state==0)
    {
        this->shape.setSize({80, 80});
            this->hitbox.setSize({80, 80});
        //this->setColor(sf::Color::Red);
        this->setPosition(768.f,418.f);
        attacked2=false;

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

        //more bullets
    }
    if(state==1){
        //przesuwaj gracza


        if(playerb->getPosition().y<450.f){
            playerb->setPosition(sf::Vector2f(playerb->getPosition().x,playerb->getPosition().y+4.f));
        }
        else{
            playerb->setPosition(sf::Vector2f(playerb->getPosition().x,playerb->getPosition().y-4.f));
        }
        if(playerb->getPosition().x<800.f){
            playerb->setPosition(sf::Vector2f(playerb->getPosition().x+4.f,playerb->getPosition().y));
        }
        else{
            playerb->setPosition(sf::Vector2f(playerb->getPosition().x-4.f,playerb->getPosition().y));
        }
    }

    if(state==2){
        //atak
        if(attacked2==false){
            this->shape.setSize({160, 160});
            this->hitbox.setSize({160, 160});
            this->setPosition(0.f,newy);
            attacked2=true;
        }
        else{
            this->setPosition(this->getPosition().x+14.f,this->getPosition().y);
        }
    }


};

void Boss::shoot(sf::Vector2f direction){
    
        Bullet* bullet;
        if(dynamic_cast<RoundBullet*>(this->bullet)!=NULL){
            bullet = new RoundBullet;
        }
        bullet->shape.setFillColor(sf::Color::Blue);
        bullet->direction = direction;
        //masterpiece
        bullet->initPos = {this->getPosition().x + this->shape.getSize().x/2-bullet->shape.getSize().x/2, this->getPosition().y+ this->shape.getSize().y/2-bullet->shape.getSize().y/2};
        bullet->setInitPos();
        this->enemyBullets.emplace_back(bullet);
    
}
void Boss::setCurrentEnemyBullets(std::vector<Bullet*> vec){
    this->enemyBullets = vec;
}
std::vector<Bullet*> Boss::getCurrentEnemyBullet(){
    return this->enemyBullets;
}
void Boss::animate(){
    if(this->clock.getElapsedTime().asSeconds() > 0.2f){
        this->clock.restart();
        this->frame ++;
        if(this->frame >=4){
            this->frame = 0;
        }
        this->shape.setTextureRect(*(this->frames.at(this->frame)));
    }
    if(state){
        this->shape.setFillColor(sf::Color::White);
    }
    else{
        this->shape.setFillColor(sf::Color(92, 92, 255, 255));
    }
    if(counter<=50){
        this->blinkFrame = 0;
    }
    else if(counter > 50){
        if(this->blinkClock.getElapsedTime().asSeconds() > 0.04f){
            this->blinkClock.restart();
            this->blink.setTextureRect(*(this->blinkFrames.at(this->blinkFrame)));
            this->blinkFrame ++;
            if(this->blinkFrame >= this->blinkFrames.size()){
                this->blinkFrame = 0;
            }
        }
    }
}
void Boss::initBlinkFrames(){
    for(int i = 0; i < 1000; i = i + 100){
        for(int j = 0; j < 800; j = j + 100){
            this->blinkFrames.emplace_back(new sf::IntRect({i, j},{100, 100}));
        }
    }
}
void Boss::render(sf::RenderTarget* target){
    target->draw(this->shape);
    if(counter > 50){
        target->draw(this->blink);
    }
}

#endif