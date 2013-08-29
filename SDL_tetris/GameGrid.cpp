#include "SDL.h"
#include "GameGrid.h"

// GameGrid class constructor
GameGrid::GameGrid()
{
	// Initialize bounds of playing area
	this->bounds.w = SQUARE_WIDTH * X_SQUARES;
    this->bounds.h = SQUARE_HEIGHT * Y_SQUARES; 

    this->bounds.x = 100;
    this->bounds.y = 100;

    // Initialize grid to all false (empty)
    for ( int i = 0; i < X_SQUARES; i++ )
    {
        for ( int j = 0; j < Y_SQUARES; j++ )
        {
            this->gridSquares[i][j] = NULL;
            this->gridBools[i][j] = false;
			this->gridCoords[i][j].x = this->bounds.x + i * SQUARE_WIDTH;
			this->gridCoords[i][j].y = this->bounds.y + j * SQUARE_HEIGHT;
			this->gridCoords[i][j].w = SQUARE_WIDTH;
			this->gridCoords[i][j].h = SQUARE_HEIGHT;
        }
    }
}

// Delete the SDL_Surface for the square
void GameGrid::delete_surface()
{
    SDL_FreeSurface( this->surface );
}

// Returns boundaries
SDL_Rect GameGrid::get_bounds()
{
    return this->bounds;
}

// Point a cell in the grid to a square and mark the cell as filled
void GameGrid::set_cell( Square *square, int xCell, int yCell)
{
    this->gridSquares[xCell][yCell] = square;
    this->gridBools[xCell][yCell] = true;
}

// Returns boolean value for whether a cell is occupied or not
bool GameGrid::get_bool( int xCell, int yCell )
{
    return this->gridBools[xCell][yCell];
}

// Returns a pointer to the square that occupies the space in the grid
Square* GameGrid::get_square( int xCell, int yCell)
{
    return this->gridSquares[xCell][yCell];
}

// Returns coordinates of a cell
SDL_Rect GameGrid::get_coords( int xCell, int yCell )
{
	return this->gridCoords[xCell][yCell];
}

// Adds a shape to the grid
void GameGrid::add_block( Shape * shape )
{
	int xCell, yCell;

	for ( int i = 0; i < 4; i++ )
	{
		xCell = ( shape->squares[i].get_position().x - this->bounds.x ) / SQUARE_WIDTH;
		yCell = ( shape->squares[i].get_position().y - this->bounds.y ) / SQUARE_HEIGHT;
		this->gridSquares[xCell][yCell] = &(shape->squares[i]);
		this->gridBools[xCell][yCell] = true;
	}
}