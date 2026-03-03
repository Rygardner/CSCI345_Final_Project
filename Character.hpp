#pragma once

#include <sstream>

using namespace std;

const int WIDTH=640;
const int HEIGHT=480; 

class Sprite{
  protected:
    vector<SDL_Texture*> textures;
//  vector<SDL_Rect> srcs;
    SDL_Rect src,dst;
    int which;
    bool animated,dead;
    int totalMillis;
  void moveTo(int newX,int newY){
    dst.x=newX; dst.y=newY;
  }
  public:
  SDL_Rect getDestination() { return dst; }
  void stop(){ animated=false;}
  void go() {  animated=true;}
  void die(){ dead=true; moveTo(0,0); }
  bool inside(int x,int y){
    return (dst.x<=x && x<=dst.x+dst.w && dst.y<=y && y<=dst.y+dst.h); 
  }
  bool collided(Sprite *other){
    return inside(other->dst.x,other->dst.y) ||
           inside(other->dst.x+other->dst.w,other->dst.y) ||
           inside(other->dst.x,other->dst.y+other->dst.h) ||
           inside(other->dst.x+other->dst.w,other->dst.y+other->dst.h);
  }
  void update(float dt){
    if (!animated || dead) return;
    totalMillis+=dt*1000; // add the dt amount of milliseconds
    int frameTime=250;
    while (totalMillis>frameTime) {
      which++;
      if (which>=textures.size()) which=0;
      totalMillis-=frameTime;
    }
  }
  void draw(SDL_Renderer *renderer,int offsetx=0,int offsety=0){
    if (dead) return;
//    if (which<0 || which>=textures.size()) throw "Invalid which";
    if (textures[which]==NULL) throw "About to render a null texture";
    SDL_Rect finalDst=dst;
    finalDst.x+=offsetx;
    finalDst.y+=offsety;
   // cout << "Destination:" <<finalDst.x << ',' << finalDst.y << endl; 
    SDL_RenderCopy(renderer, textures[which], &src, &finalDst);
  }
  Sprite(SDL_Renderer *renderer,int count=1,string fname="image",string exten=".bmp",
      int newX=0,int newY=0,int r = 173, int g = 54, int b = 58){
    for (int i=0;i<count;i++){
      stringstream ss;
      ss << fname << i << exten;
      //cout << ss.str() << endl;
      textures.push_back(mm.read(renderer,ss.str().c_str(),src.w,src.h,r,g,b));
    }
    src.x=0; src.y=0;
    dst.w=src.w; dst.h=src.h;
    moveTo(newX,newY);
    which=0;
    totalMillis;
    animated=true;
    dead=false;
  }
};

class Character:public Sprite{
    //Stats
    protected:
    float speed;
    int health, dmg;
    //pos
    float px,py,vx,vy,ax,ay;
    
  public:
  Character(SDL_Renderer *renderer,int count=1,string fname="image",string exten=".bmp",
      int newHealth = 1, int newDmg = 0,
      float newSpeed = 1,
      int newX=0,int newY=0,
      float newVx=0.0,float newVy=0.0,
      float newAx=0.0,float newAy=0.0,
      int r=173, int g=54, int b=58)
    :Sprite(renderer,count,fname,exten,newX,newY,r,g,b){
    //px=rand()%640-32.0;
    //py=rand()%240-16.0;
    //if (newX==0 && newY==0) {
      //stat setters
      health=newHealth;
      dmg=newDmg;
      speed=newSpeed;

      //pos setters
      px=newX;
      py=newY;
      vx=newVx;
      vy=newVy;
      ax=newAx;
      ay=newAy;
    //}
  }
 
//stats updates
  void takeDamage(int damage = 0){
    health -= damage; // dmgReduction(damage_taken); could work for % off damage
    if (health<=0) die();
  }
  int damage(){
    return dmg;
  } 
  float getPX(){ return px;}
  float getPY(){ return py;}
  float getSpeed(){return speed;}
  int getHP(){return health;}

  void update(float dt){
    if (dead) return;
    Sprite::update(dt);
   
  }
  
  void keyEvent(SDL_Keycode symbol, float playerSpeedX, float playerSpeedY){
  
  }
};

class Player:public Character{

  public:
  Player(SDL_Renderer *renderer,int count=1,string fname="image",string exten=".bmp",
      int newHealth = 1, int newDmg = 0,
      float newSpeed = 1,
      int newX=0,int newY=0,
      float newVx=0.0,float newVy=0.0,
      float newAx=0.0,float newAy=0.0,
      int r=173, int g=54, int b=58)
      :Character(renderer,count,fname,exten,newHealth,newDmg,newSpeed,newX,newY,newVx,newVy,newAx,newAy){

      }
};

class Enemy:public Character{//NOTE:: this is where we can add the suff for skills/items interaction with the player


  public:
  Enemy(SDL_Renderer *renderer,int count=1,string fname="image",string exten=".bmp",
      int newHealth = 1, int newDmg = 1,
      float newSpeed = 1,
      int newX=0,int newY=0,
      float newVx=0.0,float newVy=0.0,
      float newAx=0.0,float newAy=0.0,
      int r=0, int g=0, int b=0)
      :Character(renderer,count,fname,exten,newHealth,newDmg,newSpeed,newX,newY,newVx,newVy,newAx,newAy){

      }

  float movementX(){
    int midPoint = WIDTH/2;
    int move = 1;
    if (px > midPoint) {move = -1;}
    return speed*move;
    }
  float movementY(){
    int midPoint = HEIGHT/2;
    int move=1;
    if (py > midPoint) {move = -1;}
    return speed*move;
  }
  void update(float dt){
    if (dead) return;
    Sprite::update(dt);
    //moves towards center
    px += movementX();
    py += movementY();

    moveTo(px,py);     
  }
  void keyEvent(SDL_Keycode symbol, float playerSpeedX, float playerSpeedY){
    
    if (symbol==SDLK_a) {px+=playerSpeedX;}
    if (symbol==SDLK_d) {px-=playerSpeedX;}
    if (symbol==SDLK_w) {py+=playerSpeedY;}
    if (symbol==SDLK_s) {py-=playerSpeedY;}
  } 

};

