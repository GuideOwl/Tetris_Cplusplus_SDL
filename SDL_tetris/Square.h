#include "SDL.h"
#include <string>

const int SQUARE_WIDTH = 30;
const int SQUARE_HEIGHT = 30;

// The Square
class Square
{
private:
	// Collision box
	SDL_Rect box;

	// Surface
	SDL_Surface *surface;

public:
	// Constructor
	Square();

	// Create an SDL_Surface
	bool create_surface( std::string filename );

	// Delete the SDL_Surface
	void delete_surface();

    // Apply the SDL_Surface
    void show();

	// Moves the square to given coordinates
	void set_position( int x, int y );

	// Returns the square's coordinates
	SDL_Rect get_position();
};