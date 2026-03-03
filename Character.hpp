#pragma once

#include <sstream>

using namespace std;

class Sprite
{
    protected:
    vector<SDL_Texture *> textures;
    SDL_Rect src, dst;
    int which, totalMillis;
    bool animated, dead;

    void moveTo(int newX, int newY)
    {
        dst.x = newX;
        dst.y = newY;
    }

    public:
    SDL_Rect getDestination() { return dst; }
    void stop() { animated = false; }
    void go() { animated = true; }
    void die() { dead = true; }
    bool inside(int x, int y) { return (dst.x <= x && x <= dst.x + dst.w && dst.y <= y && y <= dst.y + dst.h); }
    bool collided (Sprite *other) { return inside(other->dst.x,other->dst.y) ||
                                           inside(other->dst.x+other->dst.w,other->dst.y) ||
                                           inside(other->dst.x,other->dst.y+other->dst.h) ||
                                           inside(other->dst.x+other->dst.w,other->dst.y+other->dst.h); }
    void update(float dt)
    {
        if (!animated || dead) return;
        totalMillis += dt * 1000;
        int frameTime = 250;

        while (totalMillis > frameTime)
        {
            which++;
            if (which >= textures.size()) which = 0;
            totalMillis -= frameTime;
        }
    }
    void draw(SDL_Renderer *renderer, int offsetx = 0, int offsety = 0)
    {
        if (dead) return;
        if (textures[which] == NULL) throw "About to rendor a null texture...";
        SDL_Rect finalDst = dst;
        finalDst.x += offsetx;
        finalDst.y += offsety;
        SDL_RenderCopy(renderer, textures[which], &src, &finalDst);
    }
    Sprite(SDL_Renderer *renderer, int count = 1, string fname = "assets/image", string exten = ".bmp", int newX = 0, int newY = 0)
    {
        for (int i = 0; i < count; i++)
        {
            stringstream ss;
            ss << fname << i << exten;
            textures.push_back(mm.read(renderer, ss.str().c_str(), src.w, src.h));
        }

        src.x = 0;
        src.y = 0;
        dst.w = src.w;
        dst.h = src.h;
        moveTo(newX, newY);
        which = 0;
        totalMillis;
        animated = true;
        dead = false;
    }
};

class Character:public Sprite
{
    float px, py, vx, vy, ax, ay;

    public:
    Character(SDL_Renderer *renderer, int count = 1, string fname = "assets/image",
              string exten = ".bmp", int newX = 0, int newY = 0, float newVx = 0.0,
              float newVy = 0.0, float newAx = 0.0, float newAy = 0.0)
              :Sprite(renderer, count, fname, exten, newX, newY)
    {
        px = newX;
        py = newY;
        vx = newVx;
        vy = newVy;
        ax = newAx;
        ay = newAy;
    }
    void update(float dt)
    {
        if (dead) return;
        Sprite::update(dt);

        vx += ax * dt;
        px += vx * dt;
        vy += ay * dt;
        py += vy * dt;

        moveTo(px, py);
    }
    void keyEvent(SDL_Keycode symbol)
    {
        if (symbol == SDLK_SPACE)
        {
            vx += 10.0;
            vy -= 10.0;
        }
        if (symbol == SDLK_a) px -= 32.0;
        if (symbol == SDLK_d) px += 32.0;
        if (symbol == SDLK_w) py -= 32.0;
        if (symbol == SDLK_s) py += 32.0;
    }
};

class Enemy:public Sprite
{
    float px, py, vx, vy, ax, ay;

    public:
    Enemy(SDL_Renderer *renderer, int count = 1, string fname = "assets/image",
              string exten = ".bmp", int newX = 0, int newY = 0, float newVx = 0.0,
              float newVy = 0.0, float newAx = 0.0, float newAy = 0.0)
              :Sprite(renderer, count, fname, exten, newX, newY)
    {
        px = newX;
        py = newY;
        vx = newVx;
        vy = newVy;
        ax = newAx;
        ay = newAy;
    }
    void update(float dt)
    {
        if (dead) return;
        Sprite::update(dt);

        vx += ax * dt;
        px += vx * dt;
        vy += ay * dt;
        py += vy * dt;

        moveTo(px, py);
    }
    void keyEvent(SDL_Keycode symbol)
    { /* WIDTH: 768px   HEIGHT: 640px */
        std::cout << "Location: " << px << "x, " << py << "y." << std::endl;
        if (symbol == SDLK_SPACE || symbol == SDLK_a || symbol == SDLK_d || symbol == SDLK_w || symbol == SDLK_s)
        { /* When the player acts, enemies move towards the center of the screen (eventually, where the player always is) */
            if (px >= (768 / 2) - 192.0) px -= 32.0;
            if (px < (768 / 2) - 192.0) px += 32.0;
            if (py >= (640 / 2) - 12.0) py -= 32.0;
            if (py < (640 / 2) - 128.0) py += 32.0;
        }
    }
};