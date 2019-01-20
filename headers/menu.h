
Texture menu_back_tex,
  menu_start_tex,menu_setting_tex,
  menu_play_tex,menu_score_tex;

SDL_Rect menu_play_rect,menu_setting_rect;

bool first_time= true;

bool show_menu_textures()
{
  SBDL::clearRenderScreen();

  SBDL::showTexture(menu_back_tex , 0 , 0 );
  SBDL::showTexture(menu_start_tex, (screen_width - menu_start_tex.width ) / 2, screen_height * 6/ 7 );
  SBDL::showTexture(menu_play_tex, screen_width-menu_play_tex.width, screen_height-menu_play_tex.height);
  SBDL::showTexture(menu_setting_tex,0, screen_height-menu_setting_tex.height);

  if(!first_time)
    SBDL::showTexture( menu_score_tex , (screen_width - menu_score_tex.width ) / 2, screen_height*0.07 );

  SBDL::updateRenderScreen();
  return true;
}

bool load_menu_textures(std::string text_title)
{
  menu_back_tex = SBDL::loadTexture( "./assets/pic/menu/EBack.png" );

  Font * start_font = SBDL::loadFont("assets/font/smart_font_ui_japanese.otf",25);
  menu_start_tex = SBDL::createFontTexture(start_font , "press SPACE to start", 20, 140, 133);

  menu_play_tex = SBDL::loadTexture( "./assets/pic/menu/play.png" );
  menu_play_rect = {screen_width-menu_play_tex.width, screen_height-menu_play_tex.height, menu_play_tex.width, menu_play_tex.height};

  menu_setting_tex = SBDL::loadTexture( "./assets/pic/menu/setting.png" );
  menu_setting_rect = {0, screen_height-menu_setting_tex.height, menu_setting_tex.width, menu_setting_tex.height};

  Font * menu_score_font = SBDL::loadFont("assets/font/SourceHanSansSC-Normal.otf",30);
  menu_score_tex = SBDL::createFontTexture(menu_score_font ,"distance:"+std::to_string(score)+" HIGHEST:"+std::to_string(high_score)+" COINS:"+std::to_string(coin_ate_number), 30, 220, 50);

  return true;
}


bool new_game(std::string text_title)
{
  if(text_title != Game_Over) return false;
  score = 0;
  coin_ate_number = 0;
  return true;
}


bool menu(std::string text_title = main_windows_title)
{
  first_time = (text_title == main_windows_title);
  load_menu_textures(text_title);

  while( SBDL::isRunning() )
  {
    SBDL::updateEvents();
    if (SBDL::keyHeld(SDL_SCANCODE_SPACE)) {new_game(text_title); return true;}
    if (SBDL::Mouse.clicked())
    {
      if ( SBDL::mouseInRect( menu_play_rect ) ) {new_game(text_title); return true;}
      if ( SBDL::mouseInRect( menu_setting_rect ) ) setting();
    }
    show_menu_textures();
    SBDL::delay(1000/FPS);
  }
  return true;
}
