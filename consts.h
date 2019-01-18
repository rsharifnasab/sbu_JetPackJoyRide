const unsigned int FPS = 45;

const int screen_width = 800;
const int screen_height = 600;
const int bary_x = 0.3 * screen_width;

const unsigned short int harder = 5;

bool music_state = true;
bool sound_state = true;

int icon_size = 60;
std::string main_windows_title = "welcome to JetPack JoyRide :)";
std::string Game_Over = "Game Over";

Font * score_font = NULL;
int score = 0;
int high_score=0;

Music *game_music = NULL;
Sound *score_sound = NULL;

int g =10;

enum suits { Smain, Sgreen, Sgravity };

struct player
{
  Texture tex ;
  const int x = screen_height * 0.35;
  int y = screen_height / 2;
  int vy = 0;
  int ay = g;
  bool on_earth= false;
  bool jet_on = false;
  bool gravity_suit = false;
  bool gravity_revers = false;
  bool fast_forward = false;
  suits suit = Smain;
};

player barry;

enum sound_type { score_s, die1_s, die2_s };
enum Kind {circle , square};
