enum enemy_types{ EzapperV ,EzapperN , Elaser ,Emissle, Ecoin };

const unsigned int enemy_rate = 500;
const unsigned int enemy_len = 1200;

struct
{
  Texture tex[4][4]; //  missle 2,3,4,6
  enemy_types type = Ecoin;
  int y = 0.3 * screen_height;
  int x = screen_width;
}enemy;


bool add_enemy()
{
  if(power_up.type != Pnone) return false;
  if(barry.suit==Sgravity) return false;
  if (barry.speed_token) return false;

  static unsigned int timer = 0;
  timer++;
  if(timer > powerup_rate)
  {
    timer-=powerup_rate;
    power_up.x = screen_width;
    power_up.y = screen_height * (0.1 + (rand()%8)/10);
    power_up.type = powerup_rand();
    if(power_up.type == Pspeed)power_up.tex = SBDL::loadTexture("./assets/pic/speedToken/speed token.png");
    if(power_up.type == Pgravity)power_up.tex = SBDL::loadTexture("./assets/pic/menu/gravity_token.png");
  }
  return true;
}

bool move_enemy()
{
  if(power_up.x + power_up.tex.width < 0) {power_up.type = Pnone;return false;}
  power_up.x += game_vx;
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

  SDL_Rect enemy_rect = { enemy.x, enemy.y,enemy.tex.width,enemy.tex.height};
  if (SBDL::hasIntersectionRect(barry_rect,enemy_rect))
  {
    //if(power_up.type == Pgravity) barry.suit = Sgravity;
    //if(power_up.type == Pspeed) barry.speed_token = true;
    //power_up.x=-1000; // out of screen;
    die();
  }
  return true;
}

bool enemy_counter()
{
  if(!barry.speed_token) return false;_power_up
  static unsigned int x = 0;
  x++;
  if (x > speed_token_len) {barry.speed_token = false; x= 0; power_up.type=Pnone;}
  return true;
}

bool show_enemy()
{
  SBDL::showTexture(power_up.tex ,power_up.x ,power_up.y);
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
