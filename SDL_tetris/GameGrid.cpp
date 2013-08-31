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
			this->gridCoords[i][j].x = this->bounds.x + i * SQUARE_WIDTH;
			this->gridCoords[i][j].y = this->bounds.y + j * SQUARE_HEIGHT;
			this->gridCoords[i][j].w = SQUARE_WIDTH;
			this->gridCoords[i][j].h = SQUARE_HEIGHT;
        }
    }

	// Initialize lineWaiting array to all false
	for ( int i = 0; i < Y_SQUARES; i++ )
	{
		this->lineStatus[i] = false;
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
    //this->gridBools[xCell][yCell] = true;
}

//// Returns boolean value for whether a cell is occupied or not
//bool GameGrid::get_bool( int xCell, int yCell )
//{
//    return this->gridBools[xCell][yCell];
//}

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
void GameGrid::update_piece( Shape * shape )
{
	int xCell, yCell;

	// If piece is already in the grid, remove it from the grid
	for ( int i = 0; i < X_SQUARES; i++ )
	{
		for ( int j = 0; j < Y_SQUARES; j++)
		{
			for ( int k = 0; k < 4; k++ )
			{
				if ( this->gridSquares[i][j] == shape->squares[k] )
				{
					this->gridSquares[i][j] = NULL;
				}
			}
		}
	}

	// Add piece to the grid
	for ( int i = 0; i < 4; i++ )
	{
		xCell = ( shape->squares[i]->get_position().x - this->bounds.x ) / SQUARE_WIDTH;
		yCell = ( shape->squares[i]->get_position().y - this->bounds.y ) / SQUARE_HEIGHT;
		this->gridSquares[xCell][yCell] = shape->squares[i];
		//this->gridBools[xCell][yCell] = true;
	}
}

// Check if given piece collides with the gameGrid boundaries or with another block
bool GameGrid::check_collision( Shape* shape )
{
	// No collision if shape is null
	if ( shape == NULL ) { return false; }

	// The sides of two squares
	int topA, bottomA, leftA, rightA;
	int topB, bottomB, leftB, rightB;

	// For each square in the given shape
	for ( int i = 0; i < 4; i++ )
	{
		// Calculate the sides of the square
		topA = shape->squares[i]->get_position().y;
		bottomA = topA + SQUARE_HEIGHT;
		leftA = shape->squares[i]->get_position().x;
		rightA = leftA + SQUARE_WIDTH;

		// Check for collision with boundaries
		//     Return true (collision) if any equality is satisfied

		// if topA is above top boundary
		if ( topA < this->bounds.y ) { 
			return true; }
		// if bottomA is below bottom boundary
		if ( bottomA > this->bounds.y + this->bounds.h ) { 
			return true; }
		// if leftA is left of left boundary
		if ( leftA < this->bounds.x ) { 
			return true; }
		// if rightA is right of right boundary
		if ( rightA > this->bounds.x + this->bounds.w ) { 
			return true; }

		// For each position in the grid
		for ( int m = 0; m < X_SQUARES; m++ )
		{
			for ( int n = 0; n < Y_SQUARES; n++ )
			{
				// If a square occupies the space
				if ( this->gridSquares[m][n] != NULL )
				{
					// If the square in the grid is not one of the active squares
					if (	( this->gridSquares[m][n] != shape->squares[0] ) &&
							( this->gridSquares[m][n] != shape->squares[1] ) &&
							( this->gridSquares[m][n] != shape->squares[2] ) &&
							( this->gridSquares[m][n] != shape->squares[3] ) )
					{
						// Calculate the sides of the square
						topB = this->gridSquares[m][n]->get_position().y;
						bottomB = topB + SQUARE_HEIGHT;
						leftB = this->gridSquares[m][n]->get_position().x;
						rightB = leftB + SQUARE_WIDTH;

						// Check for collision between the two squares
						//     Return true (collision) if no equality is satisfied

						// if bottomA is NOT above topB
						if ( ! ( bottomA <= topB ) )
						{
							// if topA is NOT below bottomB
							if ( ! ( topA >= bottomB ) )
							{
								// if rightA is NOT left of leftB
								if( ! ( rightA <= leftB ) )
								{
									// if leftA is NOT right of rightB
									if( ! ( leftA >= rightB ) )
									{
										// Collision occurred
										return true;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	// Return false (no collision) 
	return false;	
}

// Deletes all the squares in every completed line
void GameGrid::clear_lines()
{
	// For each line
	for ( int y = 0; y < Y_SQUARES; y++ )
	{
		// If the line is complete
		if ( this->lineStatus[y] == true )
		{
			// Delete all the squares in the line
			for ( int x = 0; x < X_SQUARES; x++ )
			{
				delete this->gridSquares[x][y];
				this->gridSquares[x][y] = NULL;
			}
		}
	}
}

// Updates lineStatus array with completed lines, returns true if any lines are complete
int GameGrid::check_lines()
{
	int lineOccupants;
	int numLinesDone = 0;

	// At each row
	for ( int y = 0; y < Y_SQUARES; y++ )
	{
		lineOccupants = 0;
		// Examine each cell in the line
		for ( int x = 0; x < X_SQUARES; x++)
		{
			// If the cell is not empty
			if ( this->gridSquares[x][y] != NULL )
			{
				// Increment the occupant counter
				lineOccupants += 1;
			}
		}
		// If the whole row is occupied
		if ( lineOccupants == X_SQUARES )
		{
			// Update lineStatus array
			this->lineStatus[y] = true;
			numLinesDone += 1;
		}
	}

	// Return whether or not any lines are completed
	return numLinesDone;
}

// Move down the lines above each deleted line
void GameGrid::drop_lines()
{
	SDL_Rect oldCoords;
	Square* square;

	// At each row
	for ( int y = 0; y < Y_SQUARES; y++ )
	{
		// If line is completed
		if ( this->lineStatus[y] == true )
		{
			// For each line above the completed line
			for ( int i = (y - 1); i >= 0; i-- )
			{
				// Move all the squares in the line down by 1
				for ( int x = 0; x < X_SQUARES; x++ )
				{
					// If the cell has a square in it
					if ( this->gridSquares[x][i] != NULL )
					{
						// Point to square and get its old info
						square = this->gridSquares[x][i];
						oldCoords = square->get_position();
					
						// Move square
						square->set_position( oldCoords.x, oldCoords.y + SQUARE_HEIGHT );

						// Update grid's information on the square
						this->gridSquares[x][i] = NULL;
						this->gridSquares[x][i+1] = square;

						// Uncheck the line in lineStatus
						lineStatus[y] = false;
					}
				}
			}
		}
	}
}

// Free surface and delete squares
void GameGrid::clean_up()
{
	// For each cell
	for ( int y = 0; y < Y_SQUARES; y++ )
	{
		for ( int x = 0; x < X_SQUARES; x++)
		{
			// If there is a square
			if ( this->gridSquares[x][y] != NULL )
			{
				// Delete the square
				delete this->gridSquares[x][y];
			}
		}
	}

	// Free the GameGrid surface
	this->delete_surface();
}