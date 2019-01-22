
bool init_music()
{
  game_music = SBDL::loadMusic("./assets/sound/music.mp3");
  if(music_state) SBDL::playMusic(game_music, -1);
  coin_sound = SBDL::loadSound("./assets/sound/coin.wav");
  change_barry_sound = SBDL::loadSound("./assets/sound/changebarry.wav");
  grav1_sound = SBDL::loadSound("./assets/sound/grav_change_1.wav");
  grav2_sound = SBDL::loadSound("./assets/sound/grav_change_2.wav");
  on_sound = SBDL::loadSound("./assets/sound/soundonEffect.wav");
  missle_warning_sound = SBDL::loadSound("./assets/sound/missile_warning.wav");
  laser_warning_sound = SBDL::loadSound("./assets/sound/laser_fire_lp.wav");


  return true;
}



bool play_sound(sound_type s)
{
    if (s==missle_warning_s) std::cout << "missle sound\n";
    if(!sound_state) return false;
    if(barry.speed_token) return false;
    if (s == coin_s) SBDL::playSound(coin_sound,1);
    if (s==change_barry_s) SBDL::playSound(change_barry_sound,1);
    if (s==grav1_s) SBDL::playSound(grav1_sound,1);
    if (s==grav2_s) SBDL::playSound(grav2_sound,1);
    if (s==on_s) SBDL::playSound(on_sound,1);
    if (s==missle_warning_s) SBDL::playSound(missle_warning_sound,1);
    if (s==laser_warning_s) SBDL::playSound(laser_warning_sound,1);
    return true;
}
