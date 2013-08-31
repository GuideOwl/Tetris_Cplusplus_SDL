#include "SDL.h"
#include "Square.h"

// Square class constructor
Square::Square()
{
	this->box.w = SQUARE_WIDTH;
    this->box.h = SQUARE_HEIGHT;
    this->box.x = 100;
    this->box.y = 100;
}

// Destructor
Square::~Square()
{
	this->delete_surface();
}

// Delete the SDL_Surface
void Square::delete_surface()
{
    SDL_FreeSurface( this->surface );
}

// Moves the square to given coordinates
void Square::set_position( int x, int y  )
{
	this->box.x = x;
	this->box.y = y;
}

// Returns the square's coordinates
SDL_Rect Square::get_position()
{
	return this->box;
}