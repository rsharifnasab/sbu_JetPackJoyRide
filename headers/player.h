const int jet_a = -g;

enum suits { Smain, Sgreen, Sgravity };

struct player
{
  Texture tex[3][4];
  unsigned short this_tex = 3;
  const int x = screen_height * 0.39;
  int y = screen_height / 3;
  int vy = 0;
  int ay = g;
  bool on_earth= false;
  bool jet_on = false;
  bool g_revers = false;
  bool speed_token = false;
  suits suit = Smain;
  suits last_suit = Smain;
};

player barry;


bool load_player_texture()
{
  barry.tex[Smain][0] = SBDL::loadTexture( "./assets/pic/barry/barry.png" );
  barry.tex[Smain][1] = SBDL::loadTexture( "./assets/pic/barry/barry2.png" );
  barry.tex[Smain][2] = SBDL::loadTexture( "./assets/pic/barry/barry3.png" );
  barry.tex[Smain][3] = SBDL::loadTexture( "./assets/pic/barry/barryst.png" );

  barry.tex[Sgreen][0] = SBDL::loadTexture( "./assets/pic/barry/alien.png" );
  barry.tex[Sgreen][1] = SBDL::loadTexture( "./assets/pic/barry/alien2.png" );
  barry.tex[Sgreen][2] = SBDL::loadTexture( "./assets/pic/barry/alienup.png" );
  barry.tex[Sgreen][3] = SBDL::loadTexture( "./assets/pic/barry/aliendown.png" );

  barry.tex[Sgravity][0] = SBDL::loadTexture( "./assets/pic/barry/gg1.png" );
  barry.tex[Sgravity][1] = SBDL::loadTexture( "./assets/pic/barry/gg2.png" );
  barry.tex[Sgravity][2] = SBDL::loadTexture( "./assets/pic/barry/gg3.png" );
  barry.tex[Sgravity][3] = SBDL::loadTexture( "./assets/pic/barry/gg4.png" );

  return true;
}


bool show_player()
{
  static unsigned int counter = 0;
  counter = (counter+1) % run_speed;
  barry.this_tex = counter >= run_speed/2 ;
  if(barry.suit != Sgravity)
  {
    if(!barry.on_earth && barry.jet_on) barry.this_tex = 2;
    if(!barry.on_earth && !barry.jet_on) barry.this_tex = 3;
  }
  else
    barry.this_tex += 2*barry.g_revers;
  SBDL::showTexture( barry.tex[barry.suit][barry.this_tex], barry.x ,  barry.y );
  return true;
}



bool handle_player_physics()
{
  if(barry.jet_on)
  {
    if(barry.vy >0 ) barry.vy = 0;
    barry.ay = jet_a;
    if( barry.y <=0 ) barry.vy = 0;
  }
  else barry.ay = g + (-2 * g * barry.g_revers);
  barry.vy+=barry.ay;
  barry.y+=barry.vy;
  if(barry.y < 0) { barry.y = 0; barry.vy=0; }
  if(barry.y + barry.tex[barry.suit][barry.this_tex].height > screen_height)
  {
    barry.y = screen_height - barry.tex[barry.suit][barry.this_tex].height;
    barry.vy=0;
    barry.on_earth = true;
  }
  else  barry.on_earth = false;

  return true;
}
