#include "SDL.h"
#include <string>
#include <queue>

// Screen attributes
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int SCREEN_BPP = 32;

// Frame rate
const int FRAMES_PER_SECOND = 20;

// Period of gravity timer
const int GRAVITY_PERIOD = 500;

// Possible commands
enum input_commands { LEFT, RIGHT, SOFT_DROP, HARD_DROP, ROT_CW, ROT_CCW, PAUSE, QUIT, MUTE };

// Definitions for clockwise and counterclockwise
#define CW 1
#define CCW -1

// Surfaces
SDL_Surface *screenSurface = NULL;
SDL_Surface *backgroundSurface = NULL;

/// Loads an image and returns an optimized surface
SDL_Surface *load_image( std::string filename );

// Event structure
SDL_Event event;

// Queue for commands
std::queue<input_commands> cmdQueue;

// Score counter
int score;

// Blit source surface onto destination surface at an offset
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);

// Initialize the app
bool init();

// Check for collision between two SDL_Rect objects
bool check_collision( SDL_Rect A, SDL_Rect B );

// Clean up
void clean_up( );

// Event handler
void handle_input();

// Adds value of action to the score
void add_score( int linesCleared );

