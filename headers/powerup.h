
enum power_ups {Pnone,Pgravity,Pspeed};
const unsigned int powerup_rate = 500;
const unsigned int speed_token_len = 1200;
const unsigned int speed_token_speed = 5;

struct power_up_type
{
  Texture tex;
  power_ups type = Pnone;
  int y = 0.3 * screen_height;
  int x = screen_width;

}power_up;

power_ups powerup_rand()
{
  int a = rand()%2;
  return (a==0) ? Pgravity : Pspeed;
}


bool add_power_up()
{
  static unsigned int timer = 0;
  if(power_up.type != Pnone) return false;
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
bool move_powerup()
{
  if(power_up.x + power_up.tex.width < 0) {power_up.type = Pnone;return false;}
  power_up.x += game_vx;
  return true;
}

bool power_up_hit_check()
{
  SDL_Rect barry_rect =
  {
    barry.x , barry.y ,
    barry.tex[barry.suit][barry.this_tex].width,
    barry.tex[barry.suit][barry.this_tex].height
  };

  SDL_Rect power_up_rect = { power_up.x, power_up.y,power_up.tex.width,power_up.tex.height};
  if (SBDL::hasIntersectionRect(barry_rect,power_up_rect))
  {
    if(power_up.type == Pgravity) barry.suit = Sgravity;
    if(power_up.type == Pspeed) barry.speed_token = true;
    power_up.x=-1000; // out of screen;
  }
  return true;
}
bool speed_token_counter()
{
  if(!barry.speed_token) return false;
  static unsigned int x = 0;
  x++;
  if (x > speed_token_len) {barry.speed_token = false; x= 0; power_up.type=Pnone;}
  return true;
}

bool show_power_up()
{
  SBDL::showTexture(power_up.tex ,power_up.x ,power_up.y);
  return true;
}

bool power_up_handle()
{
  add_power_up();
  move_powerup();
  speed_token_counter();
  power_up_hit_check();
  return true;
}
