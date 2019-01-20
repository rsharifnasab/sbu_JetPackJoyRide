const unsigned int FPS = 35;
const int screen_width = 1500;
const int screen_height = 800;

const int game_vx = -20;
const unsigned int run_speed =12;
const unsigned int score_rate = 50;

const unsigned short int harder = 5;

bool music_state = false;
bool sound_state = true;

int icon_size = 60;
std::string main_windows_title = "welcome to JetPack JoyRide :)";
std::string Game_Over = "Game Over";

Font * score_font = NULL;
int score = 0;
int high_score=0;
const unsigned int score_x = screen_width * 0.77;
const unsigned int score_y = 0;

enum { Ezapper , Elaser , Ecoin } enemy;
const int g =+1;

Music *game_music = NULL;
Sound *coin_sound = NULL;
enum sound_type { coin_s, die1_s, die2_s };
