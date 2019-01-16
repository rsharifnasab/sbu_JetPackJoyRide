#include <bits/stdc++.h>
#include <exception>
#include "SBDL.h"
#include "consts.h"
#include "menu.h"

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
  try{
    //game_music = SBDL::loadMusic("./assets/Sounds/music.wav");
  //  if(music_state) SBDL::playMusic(game_music, -1);
  //  score_sound = SBDL::loadSound("assets/Sounds/score.wav");
  //  die1_sound = SBDL::loadSound("assets/Sounds/die1.wav");
  //  die2_sound = SBDL::loadSound("assets/Sounds/die2.wav");
    return true;
  }
  catch (int e){
    std::cout << "An exception occurred. Exception Nr. " << e << '\n';
    return false;
  }
}

bool init()
{
  SBDL::InitEngine ("Jetpack Joyride", screen_width, screen_height);
  srand(time(0));

  init_high_score();
  init_music();

  return true;
}


bool handle_keyboard()
{
  if (SBDL::keyPressed(SDL_SCANCODE_RIGHT)) ;
  if (SBDL::keyPressed(SDL_SCANCODE_LEFT))  ;
  if (SBDL::keyPressed(SDL_SCANCODE_P)) menu("Game Paused");
  return true;
}

bool load_game_texture()
{
  //background = SBDL::loadTexture( "assets/Background.png" );
  barry.tex = SBDL::loadTexture( "./assets/pic/barry/barry.png" );
  //score_font = SBDL::loadFont("assets/Font/gobold.ttf",27);
  return true;
}

bool show_game_texture()
{
  SBDL::showTexture( background , 0 , 0 );
  SBDL::showTexture( barry.tex , 0 , 0 );

	//score_tex = SBDL::createFontTexture(score_font , "SCORE : " + std::to_string(score) + " HIGHSCORE : " + std::to_string(high_score) , 30, 220, 50);
  //SBDL::showTexture( score_tex , screen_width * 0.27 ,screen_height - score_tex.height );

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


/*
bool play_sound(sound_type s)
{
    if(!sound_state) return false;
    if (s == score_s) SBDL::playSound(score_sound,1);
    if (s == die1_s) SBDL::playSound(die1_sound,1);
    if (s == die2_s) SBDL::playSound(die2_sound,1);
    return true;
}
*/
bool handle_physics()
{
  barry.vx+=barry.ax;
  barry.vy+=barry.ay;
  barry.x+=barry.vx;
  barry.y+=barry.vy;
  if(barry.x < 0) barry.x = 0;
  if(barry.y < 0) barry.y = 0;
  if(barry.x + barry.tex.width >  screen_width) barry.x = screen_width - barry.tex.width;
  if(barry.y + barry.tex.height >  screen_height) barry.y = screen_height - barry.tex.height;
}


int main()
{
  init();
  menu();
  load_game_texture();

  while( SBDL::isRunning() )
  {
    unsigned int start_time = SBDL::getTime();

    SBDL::updateEvents();
    handle_keyboard();

    handle_physics();
    show_game_texture();
    SBDL::updateRenderScreen();
    delay_handle(start_time);
}
  return 0;
}
