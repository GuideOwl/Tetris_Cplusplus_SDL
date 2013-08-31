#include "SDL.h"

#ifndef __SQUARE_H_INCLUDED__
#define __SQUARE_H_INCLUDED__
#include "Square.h"
#endif

// Properties of pieces
enum shape_types { I, J, L, O, S, T, Z };
enum shape_colors { red, yellow, magenta, blue, cyan, green, orange };

class Shape
{
private:
    // Type of shape
    shape_types type;

    // Color of the shape
    shape_colors color;

	// Orientation of the shape
	int orientation;

	// If shape is the active shape
    bool active;

	// Array holding positions of each square for each rotation of the piece
	// rotations[rotation #][square ID]
	SDL_Rect rotations[4][4];

public:
    // Array of pointers to four squares composing the shape
    Square* squares[4];

    // Constructor
    Shape();

    // Set activity
    void set_active( bool value );

    // Get activity
    bool get_active();

	// Moves the shape to a coordinate
	void set_position( SDL_Rect coords );

	// Creates a surface for the 4 constituent squares
	bool create_surfaces();

	// Apply the SDL_Surface
    void show();

	// Moves shape in increments of cells
	void move_cell( int x, int y );

	// Rotates shape clockwise or counterclockwise
	void rotate( int direc );

	// Free surface and delete squares
	void clean_up();
};