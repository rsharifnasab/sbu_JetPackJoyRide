bool die();
enum enemy_types{ EzapperV ,EzapperN , Elaser ,Emissle, Ecoin, EmissleW };

const unsigned int enemy_rate = 150;
const unsigned int enemy_len = 140;
unsigned long int frame_counter=0;
const int EMP = 20;
struct
{
  Texture tex[6][4];
  unsigned short int this_tex = 0;
  enemy_types type = Ecoin;
  int y = 0.3 * screen_height;
  int x = screen_width;
}enemy;


bool load_enemy_texture()
{
  //EzapperV ,EzapperN , Elaser ,Emissle
  enemy.tex[EzapperV][0] = SBDL::loadTexture("./assets/pic/zappers/v1.png");
  enemy.tex[EzapperV][1] = SBDL::loadTexture("./assets/pic/zappers/v2.png");
  enemy.tex[EzapperV][2] = SBDL::loadTexture("./assets/pic/zappers/v3.png");
  enemy.tex[EzapperV][3] = SBDL::loadTexture("./assets/pic/zappers/v4.png");

  enemy.tex[EzapperN][0] = SBDL::loadTexture("./assets/pic/zappers/h1.png");
  enemy.tex[EzapperN][1] = SBDL::loadTexture("./assets/pic/zappers/h2.png");
  enemy.tex[EzapperN][2] = SBDL::loadTexture("./assets/pic/zappers/h3.png");
  enemy.tex[EzapperN][3] = SBDL::loadTexture("./assets/pic/zappers/h4.png");

  enemy.tex[Elaser][0] = SBDL::loadTexture("./assets/pic/lazer/laser_noneactive.png");
  enemy.tex[Elaser][1] = SBDL::loadTexture("./assets/pic/lazer/laser_noneactive.png");
  enemy.tex[Elaser][2] = SBDL::loadTexture("./assets/pic/lazer/laser_active1.png");
  enemy.tex[Elaser][3] = SBDL::loadTexture("./assets/pic/lazer/laser_active2.png");

  enemy.tex[Emissle][0] = SBDL::loadTexture("./assets/pic/missle/missle (2).png");
  enemy.tex[Emissle][1] = SBDL::loadTexture("./assets/pic/missle/missle (3).png");
  enemy.tex[Emissle][2] = SBDL::loadTexture("./assets/pic/missle/missle (4).png");
  enemy.tex[Emissle][3] = SBDL::loadTexture("./assets/pic/missle/missle (6).png");

  enemy.tex[EmissleW][0] = SBDL::loadTexture("./assets/pic/missle/warn.png");

  return true;
}

int enemy_y_gen()
{
  if(enemy.type == Emissle) return (barry.y+100 - (rand()%250));
  else if(enemy.type == EzapperV) return (screen_height/10 * (rand()%8));
  else return (screen_height/10 * (rand()%10));

  return 0;
}

enemy_types enemy_type_rand()
{
  int a = rand()%4;
  std::cout << "enemy " << a << " is coming \n";
  if(a==0) return EzapperV;
  else if(a==1) return EzapperN;
  else if(a==2) return Elaser;
  else if(a==3) return Emissle;
  else return Ecoin;
}

bool add_enemy()
{
  static unsigned int timer = 0;
  timer++;
  if(timer > enemy_rate)
  {
    frame_counter=0;
    timer-=enemy_rate;
    enemy.type = enemy_type_rand();
    enemy.x = 1.5 * screen_width;
    enemy.y = enemy_y_gen();
    if(enemy.type == Emissle) play_sound(missle_warning_s);
    if(enemy.type == Elaser) play_sound(laser_warning_s);
  }
  return true;
}

bool move_enemy()
{
  if(enemy.type == Ecoin) return false;
  if(enemy.type==Elaser) {enemy.x=10; return true;}
  if(enemy.x + enemy.tex[enemy.type][enemy.this_tex].width < 0) {enemy.type = Ecoin;return false;}
  enemy.x += game_vx* (1 + 0.3*(enemy.type==Emissle));
  return true;
}

bool enemy_hit_check()
{
  SDL_Rect barry_rect =
  {
    barry.x , barry.y ,
    barry.tex[barry.suit][barry.this_tex].width,
    barry.tex[barry.suit][barry.this_tex].height
  };

  SDL_Rect enemy_rect = { enemy.x + EMP, enemy.y + EMP,
    enemy.tex[enemy.type][enemy.this_tex].width - EMP
    ,enemy.tex[enemy.type][enemy.this_tex].height - EMP};

  if (SBDL::hasIntersectionRect(barry_rect,enemy_rect))
    die();

  return true;
}

bool enemy_counter()
{
  static int s=0;
  frame_counter++;
  if(enemy.type == EzapperN || enemy.type ==  EzapperV || enemy.type == Emissle)
  {
    if(frame_counter>run_speed)
    {
      enemy.this_tex = (enemy.this_tex+1)%4;
      frame_counter-=run_speed;
    }
  }
  else if(enemy.type == Elaser)
  {
    if(frame_counter<enemy_len/4) enemy.this_tex = 0;
    else if(frame_counter>enemy_len)
    {
      enemy.x = -1000;
      enemy.type =Ecoin;
    }
    else if(frame_counter-(s*run_speed) >run_speed)
    {
       enemy.this_tex = enemy.this_tex+1; //3 or 2
       if(enemy.this_tex >3) enemy.this_tex = 2;
       s++;
    }
  }

  return true;
}

bool show_enemy()
{
  SBDL::showTexture(enemy.tex[enemy.type][enemy.this_tex] ,enemy.x ,enemy.y);
  if(enemy.type==Emissle && enemy.x > screen_width)
    SBDL::showTexture
    (enemy.tex[EmissleW][0],
      screen_width-enemy.tex[EmissleW][0].width,
      enemy.y);
  return true;
}

bool enemy_handle()
{
  add_enemy();
  move_enemy();
  enemy_counter();
  enemy_hit_check();
  return true;
}
