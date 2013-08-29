#include "SDL.h"
#include "SDL_image.h"

#include "GameGrid.h"
#include "Timer.h"
#include <string>
#include <time.h>

#ifndef __MAIN_H_INCLUDED__
#define __MAIN_H_INCLUDED__
#include "Main.h"
#endif

#ifndef __SQUARE_H_INCLUDED__
#define __SQUARE_H_INCLUDED__
#include "Square.h"
#endif

#ifndef __SHAPE_H_INCLUDED__
#define __SHAPE_H_INCLUDED__
#include "Shape.h"
#endif

int main( int argc, char* args[] )
{
    // ------------------------------------------------------------------------
    // DECLARATIONS
    // ------------------------------------------------------------------------
    // Quit flag
    bool quit = false;

	// Create the game area
	GameGrid gameGrid;
	
    // Shapes: current active shape and next shape in queue
    Shape *activeShape = NULL;
    Shape *queuedShape = NULL;

	// Positions: starting, queued
	SDL_Rect startingPosition, queuedPosition;

    // Timers: frame rate regulator, dropdown
    Timer fps, dropdown;

    // Event structure
    SDL_Event event;

    // ------------------------------------------------------------------------
    // INITIALIZATIONS
    // ------------------------------------------------------------------------

    // Initialize
	if( init() == false ) { return 1; }

	// Create background surface
	backgroundSurface = load_image( "background.bmp" );
	if ( backgroundSurface == NULL ) { return 1; }

	// Create gameGrid surface
	if ( gameGrid.create_surface() != true ) { return 1; }

    // Start the timers
    dropdown.start();
    fps.start();

    // Seed rand
    srand(time(NULL));

	// Set starting and queued positions
	startingPosition = gameGrid.get_coords( ( X_SQUARES / 2 ) - 1, 0 );
	queuedPosition = gameGrid.get_bounds();
	queuedPosition.x = gameGrid.get_bounds().x + gameGrid.get_bounds().w + 100;


    // ------------------------------------------------------------------------
    // GAME LOOP
    // ------------------------------------------------------------------------
    while( quit == false )
    {
        // If there is no active shape: 
        if ( activeShape == NULL )
        {
            // If there is no queued shape:
            if ( queuedShape == NULL )
            {
                // Create new queued shape
                queuedShape = new Shape();
				// Create a surface for it
				if ( queuedShape->create_surfaces() != true ) { return 1; }
            }
            // Set queued shape as new active shape
            activeShape = queuedShape;
            // Create queued shape
            queuedShape = new Shape();
			// Create a surface for it
			if ( queuedShape->create_surfaces() != true ) { return 1; }
            // Move queued shape into queue position
            queuedShape->set_position( queuedPosition );
            // Move active shape to starting position
            activeShape->set_position( startingPosition );
            // If active shape collides with another shape, game over
            // if ( gameGrid.check_collision( activeShape ) )
            // {
                // quit = true;
                // break;
            // }
			// Else there is no collision
				// Update grid with new activeShape position
			gameGrid.add_block( activeShape );
		}

        // --------------------------------------------------------------------
        // EVENTS
        // --------------------------------------------------------------------

        // While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            // Handle events for the shape

            // If the user has Xed out the window, quit the program
            if( event.type == SDL_QUIT ) { quit = true; }
        }

        // --------------------------------------------------------------------
        // LOGIC
        // --------------------------------------------------------------------

		// If enough time has passed
		if ( dropdown.get_ticks() >= 1000 ) {
            // Set shape to move down

			dropdown.start();
		}

        // Move shape

        // If shape has hit bottom: deactivate shape, update grid
        //     If a row is complete: pop row, drop down rows from above, update grid, add points

        // --------------------------------------------------------------------
        // RENDERING
        // --------------------------------------------------------------------

        // Fill the screen with white
        SDL_FillRect( screenSurface, &screenSurface->clip_rect, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

		// Show the background
		apply_surface( 0, 0, backgroundSurface, screenSurface, NULL );

		// Show the game area
		gameGrid.show();

		// Show the queued shape
		if ( queuedShape != NULL )
		{
			queuedShape->show();
		}

        // Show the squares in play
		for ( int i = 0; i < X_SQUARES; i++)
		{
			for ( int j = 0; j < Y_SQUARES; j++)
			{
				if ( gameGrid.get_square(i, j) != NULL )
				{
					gameGrid.get_square(i, j)->show();
				}
			}
		}

        // Update the screen
        if( SDL_Flip( screenSurface ) == -1 )
        {
            return 1;
        }

        // --------------------------------------------------------------------
        // OTHER
        // --------------------------------------------------------------------

        // Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
        // Restart frame timer
        fps.start();
    }

    // Clean up

    return 0;
}

// ----------------------------------------------------------------------------
// FUNCTION DEFINITIONS
// ----------------------------------------------------------------------------

/// Loads an image and returns an optimized surface
SDL_Surface *load_image( std::string filename )
{
	// The image that's loaded
	SDL_Surface* loadedImage = NULL;

	// The optimized surface that is returned
	SDL_Surface* optimizedImage = NULL;

	// Load the image
	loadedImage = IMG_Load( filename.c_str() );

	// If the image loaded
	if ( loadedImage != NULL )
	{
		// Create an optimized surface
		optimizedImage = SDL_DisplayFormat( loadedImage );

		// Free the old surface
		SDL_FreeSurface( loadedImage );

		// If the surface was optimized
		if ( optimizedImage != NULL )
		{
			// Color key surface
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
		}
	}
	
	// Return the optimized surface
	return optimizedImage;
}

// Blit source surface onto destination surface at an offset
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL)
{
	// Holds offsets
	SDL_Rect offset;

	// Get offsets
	offset.x = x;
	offset.y = y;

	// Blit
	SDL_BlitSurface( source, clip, destination, &offset );
}

// Initialize the app
bool init()
{
    // Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) { return false; }

    // Set up the screen
    screenSurface = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    // If there was an error in setting up the screen
    if( screenSurface == NULL ){ return false; }

    // Set the window caption
    SDL_WM_SetCaption( "My Little Tetris", NULL );

    // If everything initialized fine
    return true;
}

// Check for collision between two SDL_Rect objects
bool check_collision( SDL_Rect A, SDL_Rect B )
{
	// The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	// Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    // Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

	// if bottomA is above topB
	if( bottomA <= topB ){ return false; }

	// if topA is below bottomB
    if( topA >= bottomB ){ return false; }

	// if rightA is left of leftB
    if( rightA <= leftB ){ return false; }

	// if leftA is right of rightB
    if( leftA >= rightB ){ return false; }

	// if none of these are satisfied, A and B have collided
	return true;
}

// Clean up
void clean_up( )
{
	// Free all surfaces

    // Quit SDL
    SDL_Quit();
}

// ----------------------------------------------------------------------------
// CLASS METHOD DEFINITIONS
// ----------------------------------------------------------------------------

// Create an SDL_Surface for the square
bool GameGrid::create_surface()
{
    // Load the square image
    this->surface = load_image( "GameGridSurface.bmp" );

    // If there was a problem in loading the square
	if( this->surface == NULL ){ return false; }

    // If everything loaded fine
    return true;
}

// Shows the square
void GameGrid::show()
{
    // Show the square
    apply_surface( this->bounds.x, this->bounds.y, this->surface, screenSurface );
}

// Create an SDL_Surface
bool Square::create_surface( std::string filename )
{
    // Load the square image
    this->surface = load_image( filename );

    // If there was a problem in loading the square
	if( this->surface == NULL ){ return false; }

    // If everything loaded fine
    return true;
}

// Apply the SDL_Surface
void Square::show()
{
    // Show the square
    apply_surface( this->box.x, this->box.y, this->surface, screenSurface );
}

// Creates a surface for the 4 constituent squares
bool Shape::create_surfaces()
{
	// String for the image's filename
	std::string filename;

	// Choose appropriate colored image
	switch (this->color)
	{
	case red:
		filename = "redSquare.bmp";
		break;
	case yellow:
		filename = "yellowSquare.bmp";
		break;
	case magenta:
		filename = "magentaSquare.bmp";
		break;
	case blue:
		filename = "blueSquare.bmp";
		break;
	case cyan:
		filename = "cyanSquare.bmp";
		break;
	case green:
		filename = "greenSquare.bmp";
		break;
	case orange:
		filename = "orangeSquare.bmp";
		break;
	default:
		filename = "blackSquare.bmp";
		break;
	}

	for ( int i = 0; i < 4; i++ )
	{
		// Create surface for each square in the shape with appropriate colored image
		if ( this->squares[i].create_surface( filename ) == false ) { return false; };
	}
	return true;
}

// Apply the SDL_Surface
void Shape::show()
{
	for ( int i = 0; i < 4; i++ )
	{
		// Show the square
		this->squares[i].show();
	}
}