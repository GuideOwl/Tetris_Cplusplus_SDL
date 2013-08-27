#include "SDL.h"
#include <list>

const int SQUARE_WIDTH = 20;
const int SQUARE_HEIGHT = 20;

// The Square
class Square
{
private:
	// Collision box
	SDL_Rect box;

	// Bounded game area
	SDL_Rect bounds;

	// Direction of movement
	int xDir, yDir;

	// Surface
	SDL_Surface *surface;

	// Active flag
	bool active;

public:
	// Constructor
	Square();

	// Create an SDL_Surface for the square
	bool create_surface();

	// Delete the SDL_Surface for the square
	void delete_surface();

	// Set bounded game area
	void set_bounds(SDL_Rect rect);

	// Set position on the game area's grid
	bool set_position(int gridX, int gridY);

	// Gets collision box
	SDL_Rect get_box();

	// Takes key presses and adjusts square's direction of movement
	void handle_input(SDL_Event event);

	// Sets direction indicators
	void set_dir(int x, int y);

	// Moves the square one grid space
	bool move();

	// Returns the square to it's previous position
	void unmove();

	// Shows the square
	void show();

	bool get_active();
	void set_active(bool active);

	bool move_valid( std::list<Square> myList );
};