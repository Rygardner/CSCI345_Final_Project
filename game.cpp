#include <SDL.h>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int error(string s)
{
    cerr << s << SDL_GetError() << endl;
    return -1;
}

/* #include "my-additional-file-here.hpp" */
#include "MediaManager.hpp"
#include "Character.hpp"
#include "Game.hpp"
#include "MyGame.hpp"

MediaManager mm;

int main(int argc, char* args[])
{
    cout << "Our game is here." << endl;
}