
Texture menu_background,
 welcome_texture, start_texture,
 play_texture,score_texture,menu_score_tex;

SDL_Rect play_rect;

bool first_time= true;

bool show_menu_textures()
{
  SBDL::clearRenderScreen();

  SBDL::showTexture(menu_background , 0 , 0 );
  SBDL::showTexture(start_texture , (screen_width - start_texture.width ) / 2, screen_height * 6/ 7 );

  SBDL::showTexture(play_texture, screen_width-play_texture.width, screen_height-play_texture.height);

  if(!first_time) SBDL::showTexture( menu_score_tex , (screen_width - menu_score_tex.width ) / 2, screen_height/1.2 );

  SBDL::updateRenderScreen();
  return true;
}


bool load_menu_textures(std::string text_title)
{

  menu_background = SBDL::loadTexture( "./assets/pic/menu/EBack.png" );

  Font * start_font = SBDL::loadFont("assets/font/smart_font_ui_japanese.otf",25);
  start_texture = SBDL::createFontTexture(start_font , "press SPACE to start", 20, 140, 133);

  play_texture = SBDL::loadTexture( "./assets/pic/menu/play.png" );
  play_rect = {screen_width-play_texture.width, screen_height-play_texture.height, play_texture.width, play_texture.height};

  //Font * menu_score_font = SBDL::loadFont("assets/Font/gobold.ttf",35);
  //menu_score_tex = SBDL::createFontTexture(menu_score_font , "SCORE : " + std::to_string(score) + " HIGHSCORE : " + std::to_string(high_score) , 30, 220, 50);


  return true;
}


bool new_game(std::string text_title)
{
  if(text_title != Game_Over) return false;
  score = 0;

  return true;
}


bool menu(std::string text_title = main_windows_title)
{
  setting();
  first_time = (text_title == main_windows_title);
  load_menu_textures(text_title);

  while( SBDL::isRunning() )
  {
    SBDL::updateEvents();
    if (SBDL::keyHeld(SDL_SCANCODE_SPACE)) {new_game(text_title); return true;}
    if (SBDL::Mouse.clicked())
    {
      if ( SBDL::mouseInRect( play_rect ) ) {new_game(text_title); return true;}
  //    if ( SBDL::mouseInRect( sound_rect ) ) sound_state = !sound_state;;
  //    if ( SBDL::mouseInRect( music_rect ) ) change_music();
    }
    show_menu_textures();
    SBDL::delay(1000/FPS);
  }
  return true;
}
