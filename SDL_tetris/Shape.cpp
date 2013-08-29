#include "SDL.h"
#include "Shape.h"

// Constructor
Shape::Shape()
{
    // Shape is random
    int r = rand() % 7;
    this->type = static_cast<shape_types>(r);
    this->color = static_cast<shape_colors>(r);

    // Inactive upon instantiation
    this->active = false;

	// Default orientation
	this->orientation = 0;

	// Organize 4 squares into correct shape
	switch ( this->type )
	{
	case I:
		this->squares[0].set_position( 0,					0 );
		this->squares[1].set_position( -SQUARE_WIDTH,		0 );
		this->squares[2].set_position( SQUARE_WIDTH,		0 );
		this->squares[3].set_position( SQUARE_WIDTH * 2,	0 );
		break;
	case J:
		this->squares[0].set_position( 0,					0 );
		this->squares[1].set_position( -SQUARE_WIDTH,		0 );
		this->squares[2].set_position( SQUARE_WIDTH,		0 );
		this->squares[3].set_position( SQUARE_WIDTH,		SQUARE_HEIGHT );
		break;
	case L:
		this->squares[0].set_position( 0,					0 );
		this->squares[1].set_position( -SQUARE_WIDTH,		0 );
		this->squares[2].set_position( SQUARE_WIDTH,		0 );
		this->squares[3].set_position( -SQUARE_WIDTH,		SQUARE_HEIGHT );
		break;
	case O:
		this->squares[0].set_position( 0,					0 );
		this->squares[1].set_position( SQUARE_WIDTH,		0 );
		this->squares[2].set_position( 0,					SQUARE_HEIGHT );
		this->squares[3].set_position( SQUARE_WIDTH,		SQUARE_HEIGHT );
		break;
	case S:
		this->squares[0].set_position( 0,					0 );
		this->squares[1].set_position( SQUARE_WIDTH,		0 );
		this->squares[2].set_position( -SQUARE_WIDTH,		SQUARE_HEIGHT );
		this->squares[3].set_position( 0,					SQUARE_HEIGHT );
		break;
	case T:
		this->squares[0].set_position( 0,					0 );
		this->squares[1].set_position( -SQUARE_WIDTH,		0 );
		this->squares[2].set_position( SQUARE_WIDTH,		0 );
		this->squares[3].set_position( 0,					SQUARE_HEIGHT );
		break;
	case Z:
		this->squares[0].set_position( 0,					0 );
		this->squares[1].set_position( -SQUARE_WIDTH,		0 );
		this->squares[2].set_position( 0,					SQUARE_HEIGHT );
		this->squares[3].set_position( SQUARE_WIDTH,		SQUARE_HEIGHT );
		break;
	default:
		this->squares[0].set_position( 0,					0 );
		this->squares[1].set_position( 0,					0 );
		this->squares[2].set_position( 0,					0 );
		this->squares[3].set_position( 0,					0 );
		break;
	}
}

// Set activity
void Shape::set_active( bool value )
{
    this->active = value;
}

// Get activity
bool Shape::get_active()
{
    return this->active;
}

// Moves the shape to a coordinate
void Shape::set_position( SDL_Rect coords )
{
	// The coordinate offsets are the difference between the origin square's current position and its destination
	int xOffset, yOffset;
	xOffset = coords.x - this->squares[0].get_position().x;
	yOffset = coords.y - this->squares[0].get_position().y;

	for ( int i = 0; i < 4; i++ )
	{
		// New position for each square is the old position plus the change in position of the origin square
		this->squares[i].set_position(
			this->squares[i].get_position().x + xOffset, 
			this->squares[i].get_position().y + yOffset);
	}
}