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
    
	// 2D array of the coordinates on the screen for each cell
	SDL_Rect gridCoords[X_SQUARES][Y_SQUARES];

	// Array of boolean values for each line. 
	// True means line is completed and should be cleared. False means not completed
	bool lineStatus[Y_SQUARES];

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

    // Returns a pointer to the square that occupies the space in the grid
    Square* get_square( int xCell, int yCell);

	// Returns coordinates of a cell
	SDL_Rect get_coords( int xCell, int yCell );

	// Updates the grid's information on the shape
	void update_piece( Shape * shape );

	// Check if given block collides with the gameGrid boundaries or with another block
	bool check_collision( Shape* shape );

	// Updates lineStatus array with completed lines, returns number of lines completed
	int check_lines();

	// Deletes all the squares in every completed line
	void clear_lines();

	// Move down the lines above each deleted line
	void drop_lines();

	// Free surface and delete squares
	void clean_up();
};