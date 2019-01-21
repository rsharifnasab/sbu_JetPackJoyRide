enum enemy_types{ EzapperV ,EzapperN , Elaser ,Emissle, Ecoin };

const unsigned int enemy_rate = 150;
const unsigned int enemy_len = 1200;

struct
{
  Texture tex[5][4];
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
  return true;
}

int enemy_y_gen()
{
  if(enemy.type == Emissle) return (barry.y - (rand()%50));
  if(enemy.type == Elaser) return (screen_height/10 * rand()%10);
  if(enemy.type == EzapperN) return (screen_height/10 * rand()%10);
  if(enemy.type == EzapperV) return (screen_height/10 * rand()%6);

}

enemy_types enemy_type_rand()
{
  //enum enemy_types{ EzapperV ,EzapperN , Elaser ,Emissle, Ecoin };
  int a = rand()%5;
  return static_cast<enemy_types>(a);
}

bool add_enemy()
{

  static unsigned int timer = 0;
  timer++;
  if(timer > enemy_rate)
  {
    timer-=enemy_rate;
    enemy.type = enemy_type_rand();
    enemy.x = screen_width;
    enemy.y = enemy_y_gen();
    if(power_up.type == Pspeed)power_up.tex = SBDL::loadTexture("./assets/pic/speedToken/speed token.png");
    if(power_up.type == Pgravity)power_up.tex = SBDL::loadTexture("./assets/pic/menu/gravity_token.png");
  }
  return true;
}

bool move_enemy()
{
  if(enemy.type==Elaser || enemy.type == Ecoin) return false;
  if(enemy.x + enemy.tex[enemy.type][0].width < 0) {enemy.type = Ecoin;return false;}
  enemy.x += game_vx* (1 + (enemy.type==Emissle));
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

  SDL_Rect enemy_rect = { enemy.x, enemy.y,enemy.tex[enemy.type][0].width,enemy.tex[enemy.type][0].height};
  if (SBDL::hasIntersectionRect(barry_rect,enemy_rect))
  {
    enemy.x = -1000;
    enemy.type =Ecoin;
    die();
  }
  return true;
}
//um enemy_types{ EzapperV ,EzapperN , Elaser ,Emissle, Ecoin };
bool enemy_counter()
{
  if(enemy.type == EzapperN);
  if(enemy.type == EzapperN);
  if(enemy.type == Elaser);
  if(enemy.type == Emissle);
  if(enemy.type == Ecoin);

  static unsigned int x = 0;
  x++;
  return true;
}

bool show_enemy()
{
  SBDL::showTexture(enemy.tex[enemy.type][0] ,enemy.x ,enemy.y);
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
