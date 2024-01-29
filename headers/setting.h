
Texture setting_background,
        back_texture, suit_texture,
        sound_texture, no_sound_texture;

SDL_Rect sound_rect, music_rect, back_rect, suit_rect;

bool show_setting_textures()
{
    SBDL::clearRenderScreen();
    SBDL::showTexture (setting_background, 0.1 * screen_width, -10);
    SBDL::showTexture (back_texture, screen_width-back_texture.width, screen_height-back_texture.height);
    SBDL::showTexture (suit_texture, suit_texture.width, screen_height - suit_texture.height);

    if (sound_state) {
        SBDL::showTexture (sound_texture, 0, screen_height - sound_texture.height);
    } else {
        SBDL::showTexture (no_sound_texture, 0, screen_height - sound_texture.height);
    }

    SBDL::updateRenderScreen();
    return true;
}

bool load_setting_textures()
{
    setting_background = SBDL::loadTexture ("./assets/pic/menu/pauseb.png");
    sound_texture = SBDL::loadTexture ("assets/pic/menu/sound on.png");
    no_sound_texture = SBDL::loadTexture ("assets/pic/menu/sound off.png");
    sound_rect = { 0, screen_height - sound_texture.height, sound_texture.width, sound_texture.height};
    suit_texture = SBDL::loadTexture ("./assets/pic/menu/change keys.png");
    suit_rect = {suit_texture.width, screen_height - suit_texture.height, suit_texture.width, suit_texture.height};
    back_texture = SBDL::loadTexture ("./assets/pic/menu/back.png");
    back_rect = {screen_width-back_texture.width, screen_height-back_texture.height, back_texture.width, back_texture.height};
    return true;
}

bool change_music()
{
    if (music_state) {
        SBDL::stopMusic();
    } else {
        SBDL::playMusic (game_music, -1);
    }

    music_state = !music_state;
    sound_state = !sound_state;
    play_sound (on_s);
    return true;
}

bool change_suit()
{
    std::cout << "suit chenged\n";
    barry.last_suit = (barry.last_suit==Smain)? Sgreen:Smain;

    if (barry.suit != Sgravity) {
        barry.suit =  barry.last_suit;
    }

    play_sound (change_barry_s);
    return true;
}

bool setting()
{
    load_setting_textures();

    while (SBDL::isRunning()) {
        SBDL::updateEvents();

        if (SBDL::keyHeld (SDL_SCANCODE_BACKSPACE)) {
            return true;
        }

        if (SBDL::Mouse.clicked()) {
            if (SBDL::mouseInRect (back_rect)) {
                return true;
            }

            if (SBDL::mouseInRect (sound_rect)) {
                change_music();
            }

            if (SBDL::mouseInRect (suit_rect)) {
                change_suit();
            }
        }

        show_setting_textures();
        SBDL::delay (1000/FPS);
    }

    return true;
}
