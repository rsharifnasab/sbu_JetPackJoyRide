
Texture setting_background,
  back_texture,suit_texture,
  sound_texture,no_sound_texture;

SDL_Rect sound_rect,music_rect,back_rect,suit_rect;

bool show_setting_textures()
{
  SBDL::clearRenderScreen();

  SBDL::showTexture(setting_background , 0 , 0 );

  SBDL::showTexture(back_texture, screen_width-back_texture.width, screen_height-back_texture.height);
  SBDL::showTexture(suit_texture,suit_texture.width, screen_height - suit_texture.height);

  if (sound_state) SBDL::showTexture( sound_texture , 0 , screen_height - sound_texture.height  );
  else SBDL::showTexture( no_sound_texture , 0 , screen_height - sound_texture.height  );

  SBDL::updateRenderScreen();
  return true;
}


bool load_setting_textures()
{
  setting_background = SBDL::loadTexture( "./assets/pic/menu/EBack.png" );

  sound_texture = SBDL::loadTexture( "assets/pic/menu/sound on.png" );
  no_sound_texture = SBDL::loadTexture( "assets/pic/menu/sound off.png" );
  sound_rect = { 0 , screen_height - sound_texture.height , sound_texture.width, sound_texture.height};

  back_texture = SBDL::loadTexture( "./assets/pic/menu/back.png" );
  back_rect = {screen_width-back_texture.width, screen_height-back_texture.height,back_texture.width,back_texture.height};

  suit_texture = SBDL::loadTexture( "./assets/pic/menu/change keys.png" );
  suit_rect = {screen_width-suit_texture.width,suit_texture.height ,suit_texture.width,suit_texture.height};

  //Font * menu_score_font = SBDL::loadFont("assets/Font/gobold.ttf",35);
  //menu_score_tex = SBDL::createFontTexture(menu_score_font , "SCORE : " + std::to_string(score) + " HIGHSCORE : " + std::to_string(high_score) , 30, 220, 50);
  return true;
}

bool change_music()
{
    if (music_state) SBDL::stopMusic();
    else SBDL::playMusic(game_music, -1);
    music_state = !music_state;
    return true;
}


bool setting()
{
  load_setting_textures();

  while( SBDL::isRunning() )
  {
    SBDL::updateEvents();
    if (SBDL::keyHeld(SDL_SCANCODE_BACKSPACE)) return true;
    if (SBDL::Mouse.clicked())
    {
      if ( SBDL::mouseInRect( back_rect ) ) return true;
      if ( SBDL::mouseInRect( sound_rect ) ) sound_state = !sound_state;
  //    if ( SBDL::mouseInRect( music_rect ) ) change_music();
    }
    show_setting_textures();
    SBDL::delay(1000/FPS);
  }
  return true;
}
