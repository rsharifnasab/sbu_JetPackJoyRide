#include <bits/stdc++.h>
#include <exception>
#include "SBDL.h"
#include "consts.h"
#include "menu.h"
#include "coin.h"
Texture background;

bool init_high_score()
{
  std::string HS="";
  std::ifstream HS_S ("high_score.txt");
  if (HS_S.is_open())
  {
      getline (HS_S,HS);
      high_score = std::stoi(HS);
      HS_S.close();
  }
  else std::cout << "error in opening high score file\n";
  return true;
}


bool init_music()
{
  game_music = SBDL::loadMusic("./assets/sound/music.mp3");
  if(music_state) SBDL::playMusic(game_music, -1);
  coin_sound = SBDL::loadSound("./assets/sound/coin.wav");
  //  die1_sound = SBDL::loadSound("assets/Sounds/die1.wav");
  //  die2_sound = SBDL::loadSound("assets/Sounds/die2.wav");
  return true;
}

bool handle_keyboard()
{
  SBDL::updateEvents();

  if (SBDL::keyHeld(SDL_SCANCODE_SPACE) && barry.suit!= Sgravity)
    barry.jet_on = true;
  else barry.jet_on = false;

  if (SBDL::keyPressed(SDL_SCANCODE_SPACE) && barry.suit==Sgravity)
  {
    barry.g_revers=!barry.g_revers;
    barry.vy = 0.3 * barry.vy;
  }
  if (SBDL::keyPressed(SDL_SCANCODE_P)) menu("Game Paused");
  return true;
}


bool load_background_texture() // TODO
{
  //background = SBDL::loadTexture( "assets/Background.png" );
  return true;
}

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
bool load_game_texture()
{
  load_background_texture();
  load_player_texture();
  load_coin_texture();
  score_font = SBDL::loadFont("assets/font/Jetpackia.ttf",27);
  return true;
}

bool init()
{
  SBDL::InitEngine ("Jetpack Joyride", screen_width, screen_height);
  srand(time(0));
  init_high_score();
  init_music();
  load_game_texture();
  set_coin_place();
  set_coin_pattern();

  return true;
}


bool show_background()
{

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


bool show_game_texture()
{
  SBDL::clearRenderScreen();
  show_background();
  show_coin_texture();
  show_player();

	Texture score_tex = SBDL::createFontTexture(score_font ,"distance:"+std::to_string(score)+" HIGHEST:"+std::to_string(high_score),30,220,50);
  SBDL::showTexture( score_tex , score_x , score_y);

  SBDL::updateRenderScreen();
  return true;
}

bool delay_handle(int start_time)
{
    unsigned int delay_time = 1000 / FPS;
    unsigned int loop_time = SBDL::getTime() - start_time;

  	if ( loop_time < delay_time )
		  SBDL::delay( delay_time - loop_time );
    return true;
}

bool score_add()
{
    static unsigned int x = 0;
    x++;
    if(x < score_rate) return false;
    x%= score_rate;
    score++;
    if (score > high_score)
    {
      high_score = score;
      std::ofstream myfile;
      myfile.open ("high_score.txt");
      myfile << high_score << "\n";
      myfile.close();
    }
  return true;
}


bool play_sound(sound_type s)
{
    if(!sound_state) return false;
    if (s == coin_s) SBDL::playSound(coin_sound,1);

    return true;
}

bool handle_physics()
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


int main()
{
  init();
//  menu();
  while(SBDL::isRunning())
  {
    unsigned int start_time = SBDL::getTime();
    score_add();
    handle_keyboard();
    handle_physics();
    move_coin();
    coin_hit_check();
    show_game_texture();
    SBDL::updateRenderScreen();
    delay_handle(start_time);
}
  return 0;
}
