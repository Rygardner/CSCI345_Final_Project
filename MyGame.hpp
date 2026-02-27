#pragma once

class MyGame:public Game
{
    vector<Character *> characters;
    int rcount, bcount;

    void setup()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        // our initial state here
        for (int i = 0; i < 2000; i++) { characters.push_back(new Character(renderer)); }
    }
    void update(float dt) { for (auto c:characters) c->update(dt); }
    void keyHandler(SDL_Keycode symbol) { for (auto c:characters) c->keyEvent(symbol); }
    void draw()
    {
        SDL_SetRenderDrawColor(renderer, rcount, 0, bcount, 255);
        for (auto c:characters) c->draw(renderer);
    }

    public:
    MyGame():Game(768, 640, "D&D meets Vampire Survivors")
    {
        rcount = 0;
        bcount = 0;
    }
};
