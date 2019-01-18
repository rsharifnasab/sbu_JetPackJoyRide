const unsigned int FPS = 35;

const int screen_width = 1500;
const int screen_height = 800;

const int game_x = 20;

const unsigned short int harder = 5;

bool music_state = true;
bool sound_state = true;

int icon_size = 60;
std::string main_windows_title = "welcome to JetPack JoyRide :)";
std::string Game_Over = "Game Over";

Font * score_font = NULL;
int score = 0;
int high_score=0;

enum { zapper , laser , } enemy;


int g =+1;

enum suits { Smain, Sgreen, Sgravity };

struct player
{
  Texture tex ;
  const int x = screen_height * 0.39;
  int y = screen_height / 5;
  int vy = 0;
  int ay = g;
  bool on_earth= false;
  bool jet_on = false;
  bool gravity_suit = false;
  bool gravity_revers = false;
  bool speed_token = false;
  suits suit = Smain;
};

player barry;


Music *game_music = NULL;
Sound *score_sound = NULL;
enum sound_type { score_s, die1_s, die2_s };
