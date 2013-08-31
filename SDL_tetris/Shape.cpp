#include "SDL.h"
#include "Shape.h"

SDL_Rect rect( int x, int y )
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	return rect;
}

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

	// Define rotations for each piece
	switch ( this->type )
	{
	case I:
		// rotation 0
		this->rotations[0][0] = rect(0,0);
		this->rotations[0][1] = rect(-1,0);
		this->rotations[0][2] = rect(1,0);
		this->rotations[0][3] = rect(2,0);
		
		// rotation 1
		this->rotations[1][0] = rect(0,0);
		this->rotations[1][1] = rect(0,-1);
		this->rotations[1][2] = rect(0,1);
		this->rotations[1][3] = rect(0,2);
		
		// rotation 2
		this->rotations[2][0] = rect(0,0);
		this->rotations[2][1] = rect(1,0);
		this->rotations[2][2] = rect(-1,0);
		this->rotations[2][3] = rect(-2,0);
		
		// rotation 3
		this->rotations[3][0] = rect(0,0);
		this->rotations[3][1] = rect(0,1);
		this->rotations[3][2] = rect(0,-1);
		this->rotations[3][3] = rect(0,-2);
		
		break;
	case J:
		// rotation 0
		this->rotations[0][0] = rect(0,0);
		this->rotations[0][1] = rect(-1,0);
		this->rotations[0][2] = rect(1,0);
		this->rotations[0][3] = rect(1,1);
		
		// rotation 1
		this->rotations[1][0] = rect(0,0);
		this->rotations[1][1] = rect(0,-1);
		this->rotations[1][2] = rect(0,1);
		this->rotations[1][3] = rect(-1,1);
		
		// rotation 2
		this->rotations[2][0] = rect(0,0);
		this->rotations[2][1] = rect(1,0);
		this->rotations[2][2] = rect(-1,0);
		this->rotations[2][3] = rect(-1,-1);
		
		// rotation 3
		this->rotations[3][0] = rect(0,0);
		this->rotations[3][1] = rect(0,1);
		this->rotations[3][2] = rect(0,-1);
		this->rotations[3][3] = rect(1,-1);
		
		break;
	case L:
		// rotation 0
		this->rotations[0][0] = rect(0,0);
		this->rotations[0][1] = rect(-1,0);
		this->rotations[0][2] = rect(1,0);
		this->rotations[0][3] = rect(-1,1);
		
		// rotation 1
		this->rotations[1][0] = rect(0,0);
		this->rotations[1][1] = rect(0,-1);
		this->rotations[1][2] = rect(0,1);
		this->rotations[1][3] = rect(-1,-1);
		
		// rotation 2
		this->rotations[2][0] = rect(0,0);
		this->rotations[2][1] = rect(1,0);
		this->rotations[2][2] = rect(-1,0);
		this->rotations[2][3] = rect(1,-1);
		
		// rotation 3
		this->rotations[3][0] = rect(0,0);
		this->rotations[3][1] = rect(0,1);
		this->rotations[3][2] = rect(0,-1);
		this->rotations[3][3] = rect(1,1);
		
		break;
	case O:
		// rotation 0
		this->rotations[0][0] = rect(0,0);
		this->rotations[0][1] = rect(1,0);
		this->rotations[0][2] = rect(0,1);
		this->rotations[0][3] = rect(1,1);
		
		// rotation 1
		this->rotations[1][0] = rect(0,0);
		this->rotations[1][1] = rect(1,0);
		this->rotations[1][2] = rect(0,1);
		this->rotations[1][3] = rect(1,1);
		
		// rotation 2
		this->rotations[2][0] = rect(0,0);
		this->rotations[2][1] = rect(1,0);
		this->rotations[2][2] = rect(0,1);
		this->rotations[2][3] = rect(1,1);
		
		// rotation 3
		this->rotations[3][0] = rect(0,0);
		this->rotations[3][1] = rect(1,0);
		this->rotations[3][2] = rect(0,1);
		this->rotations[3][3] = rect(1,1);
		
		break;
	case S:
		// rotation 0
		this->rotations[0][0] = rect(0,0);
		this->rotations[0][1] = rect(1,0);
		this->rotations[0][2] = rect(-1,1);
		this->rotations[0][3] = rect(0,1);
		
		// rotation 1
		this->rotations[1][0] = rect(0,0);
		this->rotations[1][1] = rect(0,1);
		this->rotations[1][2] = rect(-1,-1);
		this->rotations[1][3] = rect(-1,0);
		
		// rotation 2
		this->rotations[2][0] = rect(0,0);
		this->rotations[2][1] = rect(1,0);
		this->rotations[2][2] = rect(-1,1);
		this->rotations[2][3] = rect(0,1);
		
		// rotation 3
		this->rotations[3][0] = rect(0,0);
		this->rotations[3][1] = rect(0,1);
		this->rotations[3][2] = rect(-1,-1);
		this->rotations[3][3] = rect(-1,0);
		
		break;
	case T:
		// rotation 0
		this->rotations[0][0] = rect(0,0);
		this->rotations[0][1] = rect(-1,0);
		this->rotations[0][2] = rect(1,0);
		this->rotations[0][3] = rect(0,1);
		
		// rotation 1
		this->rotations[1][0] = rect(0,0);
		this->rotations[1][1] = rect(0,-1);
		this->rotations[1][2] = rect(0,1);
		this->rotations[1][3] = rect(-1,0);
		
		// rotation 2
		this->rotations[2][0] = rect(0,0);
		this->rotations[2][1] = rect(1,0);
		this->rotations[2][2] = rect(-1,0);
		this->rotations[2][3] = rect(0,-1);
		
		// rotation 3
		this->rotations[3][0] = rect(0,0);
		this->rotations[3][1] = rect(0,1);
		this->rotations[3][2] = rect(0,-1);
		this->rotations[3][3] = rect(1,0);
		
		break;
	case Z:
		// rotation 0
		this->rotations[0][0] = rect(0,0);
		this->rotations[0][1] = rect(-1,0);
		this->rotations[0][2] = rect(0,1);
		this->rotations[0][3] = rect(1,1);
		
		// rotation 1
		this->rotations[1][0] = rect(0,0);
		this->rotations[1][1] = rect(0,-1);
		this->rotations[1][2] = rect(-1,0);
		this->rotations[1][3] = rect(-1,1);
		
		// rotation 2
		this->rotations[2][0] = rect(0,0);
		this->rotations[2][1] = rect(-1,0);
		this->rotations[2][2] = rect(0,1);
		this->rotations[2][3] = rect(1,1);
		
		// rotation 3
		this->rotations[3][0] = rect(0,0);
		this->rotations[3][1] = rect(0,-1);
		this->rotations[3][2] = rect(-1,0);
		this->rotations[3][3] = rect(-1,1);
		break;
	default:
		// rotation 0
		this->rotations[0][0] = rect(0,0);
		this->rotations[0][1] = rect(0,2);
		this->rotations[0][2] = rect(0,4);
		this->rotations[0][3] = rect(0,6);
		
		// rotation 1
		this->rotations[1][0] = rect(0,0);
		this->rotations[1][1] = rect(0,2);
		this->rotations[1][2] = rect(0,4);
		this->rotations[1][3] = rect(0,6);
		
		// rotation 2
		this->rotations[2][0] = rect(0,0);
		this->rotations[2][1] = rect(0,2);
		this->rotations[2][2] = rect(0,4);
		this->rotations[2][3] = rect(0,6);
		
		// rotation 3
		this->rotations[3][0] = rect(0,0);
		this->rotations[3][1] = rect(0,2);
		this->rotations[3][2] = rect(0,4);
		this->rotations[3][3] = rect(0,6);
		
		break;
	}


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

// Moves shape in increments of cells
void Shape::move_cell( int x, int y )
{
	// Destination coordinates
	SDL_Rect dest;

	dest.x = this->squares[0].get_position().x + x * SQUARE_WIDTH;
	dest.y = this->squares[0].get_position().y + y * SQUARE_HEIGHT;

	this->set_position( dest );
}

// Rotates shape clockwise or counterclockwise
void Shape::rotate( int direc )
{
	SDL_Rect newOffset, oldOffset, newCoords, oldCoords;
	int newOrientation, oldOrientation;

	for ( int i = 0; i < 4; i++ )
	{
		// Piece's current orientation and it's orientation after a CW or CCW rotation
		oldOrientation = this->orientation;
		newOrientation = ( oldOrientation + direc ) % 4;

		// Offset from origin square of the piece
		oldOffset = this->rotations[oldOrientation][i];
		newOffset = this->rotations[newOrientation][i];
		
		// Coordinates of the square
		oldCoords = this->squares[i].get_position();
		newCoords.x = ( newOffset.x - oldOffset.x ) * SQUARE_WIDTH + oldCoords.x;
		newCoords.y = ( newOffset.y - oldOffset.y ) * SQUARE_HEIGHT + oldCoords.y;

		// Set the new, rotated position of the square
		this->squares[i].set_position( newCoords.x, newCoords.y );
	}
	// Sets the new orientation of the piece
	this->orientation = newOrientation;
}