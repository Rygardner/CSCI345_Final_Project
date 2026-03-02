#pragma once
#include <random>
//const int WIDTH=640;
//const int HEIGHT=480;


class MyGame:public Game
{
    vector<Enemy *> characters;
    Character * player;
    int rcount, bcount;

    void spawnEnemy(){//NOTE :: will implement a steal dead char, rather than make new
        /*
          0-99
        |------|
300-399 |      | 100-199
        |------|
         200-299           
        
        */
        random_device rd; // Seed
        mt19937 gen(rd()); // Engine
        uniform_int_distribution<> distrib(0,399);
        int randX = 0,randY = 0;
        int spawnPoint=distrib(gen); // generate rand spawn point
        if (spawnPoint<100 || (200<=spawnPoint && spawnPoint<300) ){ 
            randX = (WIDTH/100)*(spawnPoint%100);
            if (spawnPoint >100){randY = HEIGHT;}
        }else{
            randY = (HEIGHT/100)*(spawnPoint%100);
            if (spawnPoint <300){randX = WIDTH;}
        }
        characters.push_back(new Enemy(renderer,1,"image",".bmp",1,1,1,randX,randY));
    }

    void setup()
    {
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        // our initial state here
        player = new Player(renderer,1,"karl",".bmp",100,1,10,WIDTH/2,HEIGHT/2);
        for (int i = 0; i < 2; i++) { characters.push_back(new Enemy(renderer)); }
        
    }
    void update(float dt,int ticks) { 
        for (auto c:characters) c->update(dt); 
        for (auto c:characters) {//colitions
            if (player->collided(c)) {
                player->takeDamage(c->damage());
                cout<<"HIT"<<player->getHP()<<endl;
                c->die();
            }
        }
        //NOTE:: could add extra event on collided if player has thorns or somthing

        //NOTE:: just a constant spawing speed could be changed later
        if (ticks%100==0){spawnEnemy();}
    }
    //there are 2 player->getSpeed() because of the option for diagonal speeds or such 
    void keyHandler(SDL_Keycode symbol) { for (auto c:characters) c->keyEvent(symbol,player->getSpeed(),player->getSpeed()); }
    void draw()
    {
        SDL_SetRenderDrawColor(renderer, rcount, 0, bcount, 255);
        for (auto c:characters) {c->draw(renderer);}
        player->draw(renderer);
    }

    public:
    MyGame():Game(768, 640, "D&D meets Vampire Survivors")
    {
        rcount = 0;
        bcount = 0; 
    }
};
