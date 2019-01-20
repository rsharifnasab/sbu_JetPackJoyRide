struct coin_type
{
  bool moving = true;
  bool show = false;
  unsigned short int v  = 0;
  int x = screen_width;
  int y = screen_height;
};

const unsigned short int coins_width = 35;
const unsigned short int coins_height = 16;
coin_type coins[coins_height][coins_width];
const unsigned int coins_series_delay = 0;
const unsigned int coin_speed = 4;

Texture coin_tex[6];

bool load_coin_texture()
{
  coin_tex[0]= SBDL::loadTexture( "./assets/pic/coin/1.png" );
  coin_tex[1]= SBDL::loadTexture( "./assets/pic/coin/2.png" );
  coin_tex[2]= SBDL::loadTexture( "./assets/pic/coin/3.png" );
  coin_tex[3]= SBDL::loadTexture( "./assets/pic/coin/4.png" );
  coin_tex[4]= SBDL::loadTexture( "./assets/pic/coin/5.png" );
  coin_tex[5]= SBDL::loadTexture( "./assets/pic/coin/6.png" );
  return true;
}

bool set_coin_place()
{
  for(int i=0;i < coins_height; i++)
    for (int j = 0; j < coins_width; j++)
    {
      coins[i][j].x = screen_width / coins_width * (j+coins_series_delay) + screen_width;
      coins[i][j].y = screen_height / coins_height * i;
      coins[i][j].v = j%6;
      coins[i][j].moving = true;
    }

  return true;
}

bool coin_pattern[] =
{
  1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,
  0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,0,
  0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
  0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,
  0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,
  0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,
  0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
  0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,0,
  1,1,1,1,1,0,0,1,1,0,0,1,0,0,1,0,
  1,0,0,0,0,0,0,1,1,1,1,0,0,0,1,0,
  0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,0,
  1,1,1,1,1,0,0,1,1,0,0,1,0,0,1,0
};

int coin_pattern_length = (sizeof(coin_pattern)/sizeof(*coin_pattern));

bool set_coin_pattern()
{
  for(int i=0;i < coins_height; i++)
    for (int j = 0; j < coins_width; j++)
    {
      int line = i*coins_height+j;
      if (line < coin_pattern_length) coins[i][j].show = coin_pattern[line];
    }
  return true;
}

bool coin_turn_handle()
{
  static unsigned int counter = 0;
  static unsigned int j_r = 0;
  counter++;
  j_r = (j_r+1) % 6;
  if (counter > coin_speed)
  {
     counter %= coin_speed;
     for(int i=0;i < coins_height; i++)
       for (int j = 0; j < coins_width; j++)
           if( (i + j+2*counter) % 6 == j_r)coins[i][j].v = (coins[i][j].v+1) % 6 ;
  }
  return true;
}

bool show_coin_texture()
{
  coin_turn_handle();
  for(int i=0;i < coins_height; i++)
    for (int j = 0; j < coins_width; j++)
      if(coins[i][j].show)SBDL::showTexture(coin_tex[coins[i][j].v],coins[i][j].x ,coins[i][j].y );

  return true;
}

bool all_coin_out_check()
{
  bool is_coin = false;
  for(int i=0;i < coins_height; i++)
    for (int j = 0; j < coins_width; j++)
      is_coin |= coins[i][j].moving;
  return !is_coin;
}

bool restart_coins()
{
  set_coin_pattern();
  set_coin_place();
  return true;
}
bool move_coin()
{
  for(int i=0;i < coins_height; i++)
    for (int j = 0; j < coins_width; j++)
    {
      if(coins[i][j].moving) coins[i][j].x += game_vx;
      if(coin_tex[coins[i][j].v].width + coins[i][j].x < 0) coins[i][j].moving = false;
    }
  if(all_coin_out_check()) restart_coins();
  return true;
}
bool coin_hit(coin_type& c)
{
  c.show = false;
  coin_ate_number++;
  if(sound_state) SBDL::playSound(coin_sound,1);
  return true;
}

bool coin_hit_check()
{
  SDL_Rect barry_rect =
  {
    barry.x , barry.y ,
    barry.tex[barry.suit][barry.this_tex].width,
    barry.tex[barry.suit][barry.this_tex].height
  };

  for(int i=0;i < coins_height; i++)
    for (int j = 0; j < coins_width; j++)
    {
      SDL_Rect coin_rect = {coins[i][j].x,coins[i][j].y,coin_tex[coins[i][j].v].width,coin_tex[coins[i][j].v].height};
      if ( SBDL::hasIntersectionRect(barry_rect,coin_rect)&& coins[i][j].show)
        coin_hit(coins[i][j]);
    }
  return true;
}
