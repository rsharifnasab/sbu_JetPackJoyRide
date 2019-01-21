const unsigned int FPS = 40;
const int screen_width = 1000;
const int screen_height = 461;

const int game_vx = -16;
const unsigned int run_speed =12;
const unsigned int score_rate = 50;
const unsigned int min_delay = 40;
const unsigned short int harder = 5;

bool music_state = true;
bool sound_state = true;

int icon_size = 60;
std::string main_windows_title = "welcome to JetPack JoyRide :)";
std::string Game_Over = "Game Over";

Font * score_font = NULL;
int score = 0;
int high_score=0;
unsigned int coin_ate_number = 0;
const unsigned int score_x = screen_width * 0.77;
const unsigned int score_y = 0;

const int g =+1;

Music *game_music = NULL;
Sound *coin_sound = NULL;
enum sound_type { coin_s, die1_s, die2_s }; //todo
