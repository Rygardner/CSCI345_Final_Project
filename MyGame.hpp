#pragma once

class MyGame:public Game
{
    vector<Character *> characters;
    vector<Enemy *> enemies;
    int rcount, bcount;

    void setup()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        // our initial state here
        characters.push_back(new Character(renderer, 1, "assets/barbarian/icon")); /* renderer, 1, "assets/barbarian/icon", ".bmp", 0, 0 */
        enemies.push_back(new Enemy(renderer, 1, "assets/Goblin_Sprite_Sheet", ".bmp", 0, 0));
    }
    void update(float dt)
    {
        for (auto c:characters) c->update(dt);
        for (auto e:enemies) e->update(dt);
    }
    void keyHandler(SDL_Keycode symbol)
    {
        for (auto c:characters) c->keyEvent(symbol);
        for (auto e:enemies) e->keyEvent(symbol);
    }
    void draw()
    {
        SDL_SetRenderDrawColor(renderer, rcount, 0, bcount, 255);
        for (auto c:characters) c->draw(renderer);
        for (auto e:enemies) e->draw(renderer);
    }
    public:
    MyGame():Game(768, 640, "D&D meets Vampire Survivors")
    {
        rcount = 0;
        bcount = 0;
    }
};
