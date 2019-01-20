

struct coin_type
{
  bool move = false;
  bool is_turning = false;
  unsigned short int v  = 0;
  int x = screen_width;
  int y = screen_height;
};

const unsigned short int coins_width = 20;
const unsigned short int coins_height = 10;
coin_type coins[coins_height][coins_width];
//int a[10][10];
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
      coins[i][j].x = screen_width / coins_width * j;
      coins[i][j].y = screen_height / coins_height * i;
      coins[i][j].v = j%6;
    }

  return true;
}

bool show_coin_texture()
{
  for(int i=0;i < coins_height; i++)
    for (int j = 0; j < coins_width; j++)
    {

      SBDL::showTexture( coin_tex[coins[i][j].v],coins[i][j].x ,coins[i][j].y );
    }


}
