#include "SDL.h"

#ifndef __SQUARE_H_INCLUDED__
#define __SQUARE_H_INCLUDED__
#include "Square.h"
#endif

#ifndef __SHAPE_H_INCLUDED__
#define __SHAPE_H_INCLUDED__
#include "Shape.h"
#endif

// Game attributes
const int X_SQUARES = 10;
const int Y_SQUARES = 20;

class GameGrid
{
private:
	// Boundaries
	SDL_Rect bounds;

	// Surface
	SDL_Surface *surface;

    // 2D array of where squares are in the grid
    Square* gridSquares[X_SQUARES][Y_SQUARES];
    bool gridBools[X_SQUARES][Y_SQUARES];
	SDL_Rect gridCoords[X_SQUARES][Y_SQUARES];

public:
	// Constructor
	GameGrid();

	// Create an SDL_Surface
	bool create_surface();

	// Delete the SDL_Surface
	void delete_surface();

    // Apply the SDL_Surface
    void show();

    // Returns boundaries
    SDL_Rect get_bounds();

    // Point a cell in the grid to a square and mark the cell as filled
    void set_cell( Square *square, int xCell, int yCell );

    // Returns boolean value for whether a cell is occupied or not
    bool get_bool( int xCell, int yCell );

    // Returns a pointer to the square that occupies the space in the grid
    Square* get_square( int xCell, int yCell);

	// Returns coordinates of a cell
	SDL_Rect get_coords( int xCell, int yCell );

	// Adds a shape to the grid
	void add_block( Shape * shape );
};