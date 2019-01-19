const unsigned int FPS = 35;
const int screen_width = 1500;
const int screen_height = 800;

const int game_x = 20;
const unsigned int run_speed =12;
const unsigned int score_rate = 50;

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


const int g =+1;
const int jet_a = -g;

enum suits { Smain, Sgreen, Sgravity };

struct player
{
  Texture tex[3][4];
  unsigned short this_tex = 3;
  const int x = screen_height * 0.39;
  int y = screen_height / 3;
  int vy = 0;
  int ay = g;
  bool on_earth= false;
  bool jet_on = false;
  bool g_revers = false;
  bool speed_token = false;
  suits suit = Smain;
};

player barry;

Texture coin[6];

Music *game_music = NULL;
Sound *score_sound = NULL;
enum sound_type { score_s, die1_s, die2_s };
