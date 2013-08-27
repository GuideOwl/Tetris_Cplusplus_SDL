#include "SDL.h"
#include "square.h"

// Square class constructor
Square::Square()
{
    // Set the square's dimentions
    this->box.w = SQUARE_WIDTH;
    this->box.h = SQUARE_HEIGHT;
}

// Delete the SDL_Surface for the square
void Square::delete_surface()
{
    SDL_FreeSurface( this->surface);
}

// Set bounded game area
void Square::set_bounds(SDL_Rect rect)
{
	// set bounds
	this->bounds.x = rect.x;
	this->bounds.y = rect.y;
	this->bounds.w = rect.w;
	this->bounds.h = rect.h;
}

// Set position on the game area's grid
bool Square::set_position(int gridX, int gridY)
{
	// check that given grid positions are valid
	if ((gridX > this->bounds.w / this->box.w) || (gridX < 0)) { return false; }
	if ((gridY > this->bounds.h / this->box.h) || (gridY < 0)) { return false; }

	// The square's position is gridX number of box widths from the bound's left edge
	this->box.x = this->bounds.x + gridX * this->box.w;

	// The square's position is gridX number of box widths from the bound's left edge
	this->box.y = this->bounds.y + gridY * this->box.h;

	return true;
}

SDL_Rect Square::get_box()
{
	return this->box;
}

// Takes key presses and adjusts square's direction of movement, then moves the square
void Square::handle_input(SDL_Event event)
{
	// clears direction indicators
	this->xDir = 0;
	this->yDir = 0;

    // If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        // Adjust direction and move square
        switch( event.key.keysym.sym )
        {
            //case SDLK_UP: this->yDir -= 1; break;
            case SDLK_DOWN: this->yDir += 1; break;
            case SDLK_LEFT: this->xDir -= 1; break;
            case SDLK_RIGHT: this->xDir += 1; break;
        }
    }
}

void Square::set_dir(int x, int y)
{
	this->xDir = x;
	this->yDir = y;
}

// Moves the square, returns true if collision with bounds
bool Square::move()
{
	if ( ( this->xDir == 0 ) && ( this->yDir == 0 ) ) { return false; }

    // Move the square left or right
    this->box.x += this->xDir * this->box.w;

    // If the square went too far to the left or right
    if( ( this->box.x < this->bounds.x ) || ( this->box.x + this->box.w > this->bounds.x + this->bounds.w ) )
    {
        // report a collision
		return true;
    }

    // Move the square up or down
    this->box.y += this->yDir * this->box.h;

    // If the square went too far up or down
    if( ( this->box.y < this->bounds.y ) || ( this->box.y + this->box.h > this->bounds.y + this->bounds.h ) )
    {
        // report a collision
		return true;
    }

	// no collisions
	return false;
}

// Returns the square to it's previous position
void Square::unmove()
{
	// Move the square left or right
    this->box.x += this->xDir * this->box.w * -1;

	// Move the square up or down
    this->box.y += this->yDir * this->box.h * -1;
}

bool Square::get_active()
{
	return this->active;
}

void Square::set_active(bool value)
{
	this->active = value;
}