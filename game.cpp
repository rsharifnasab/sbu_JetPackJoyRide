#include <bits/stdc++.h>
#include <exception>
#include "headers/SBDL.h"
#include "headers/consts.h"
#include "headers/player.h"
#include "headers/setting.h"
#include "headers/menu.h"
#include "headers/coin.h"
#include "headers/background.h"
#include "headers/powerup.h"
#include "headers/enemy.h"


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

bool show_score()
{
  Texture score_tex = SBDL::createFontTexture(score_font ,"distance:"+std::to_string(score)+" HIGHEST:"+std::to_string(high_score)+" COINS:"+std::to_string(coin_ate_number),30,220,50);
  SBDL::showTexture( score_tex , score_x - score_tex.width , score_y);
  SBDL::freeTexture(score_tex);
  return true;
}

bool show_game_texture()
{
  SBDL::clearRenderScreen();
  show_background();
  show_coin_texture();
  show_enemy();
  show_power_up();
  show_player();
  show_score();
  SBDL::updateRenderScreen();
  return true;
}

bool delay_handle(int start_time)
{
    unsigned int delay_time = 1000 / FPS;
    if(barry.speed_token) delay_time/=speed_token_speed; //decrease delay have sped token
    else if(delay_time>min_delay)delay_time -= (score/harder); // make game harder
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


int main()
{
  init();
  menu();
  while(SBDL::isRunning())
  {
    unsigned int start_time = SBDL::getTime();
    score_add();
    handle_keyboard();
    handle_player_physics();
    coin_handle();
    power_up_handle();
    enemy_handle();
    show_game_texture();
    SBDL::updateRenderScreen();
    delay_handle(start_time);
  }
  return 0;
}
