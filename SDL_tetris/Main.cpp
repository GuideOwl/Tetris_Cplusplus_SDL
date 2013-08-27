#include "SDL.h"
#include "SDL_image.h"
#include "square.h"
#include "Timer.h"
#include <string>
#include <list>


// Screen attributes
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

// Frame rate
const int FRAMES_PER_SECOND = 20;

// Game area bounds
const int GAME_AREA_WIDTH = 10 * SQUARE_WIDTH;
const int GAME_AREA_HEIGHT = 20 * SQUARE_HEIGHT;

// Surfaces
SDL_Surface *screenSurface = NULL;
SDL_Surface *gameAreaSurface = NULL;

// Event structure
SDL_Event event;

// Game area
SDL_Rect gameArea;

// Loads an image and returns an optimized surface
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
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    // Set up the screen
    screenSurface = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    // If there was an error in setting up the screen
    if( screenSurface == NULL )
    {
        return false;
    }

    // Set the window caption
    SDL_WM_SetCaption( "My Little Tetris", NULL );

    // If everything initialized fine
    return true;
}

// Clean up
void clean_up( std::list<Square> myList, Square square )
{
	for ( std::list<Square>::iterator it = myList.begin(); it != myList.end(); ++it )
	{
		it->delete_surface();
	}
    // Free the surface
    square.delete_surface();

    // Quit SDL
    SDL_Quit();
}

// Create an SDL_Surface for the square
bool Square::create_surface()
{
    // Load the square image
    this->surface = load_image( "square.bmp" );

    // If there was a problem in loading the square
	if( this->surface == NULL ){ return false; }

    // If everything loaded fine
    return true;
}

// Shows the square
void Square::show()
{
    // Show the square
    apply_surface( this->box.x, this->box.y, this->surface, screenSurface );
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

bool Square::move_valid( std::list<Square> myList )
{
	// move square, unmove if out of bounds
	if ( this->move() )
	{
		this->unmove();
		return false;
	}
	// unmove if collision
	else 
	{
		for ( std::list<Square>::iterator it = myList.begin(); it != myList.end(); ++it )
		{
			if ( check_collision( this->get_box(), it->get_box() ) )
			{
				this->unmove();
				return false;
			}
		}
		return true;
	}
}

int main( int argc, char* args[] )
{
	std::list<Square> myList;
	std::list<Square>::iterator it;

    //Quit flag
    bool quit = false;

	// Set the game area
	gameArea.x = 100;
	gameArea.y = 100;
	gameArea.w = SQUARE_WIDTH * 10;
	gameArea.h = SQUARE_HEIGHT * 20;

    // The frame rate regulator
    Timer fps;

	// The dropdown timer
	Timer dropdown;

    // Initialize
	if( init() == false ) { return 1; }

	// Start the dropdown timer
	dropdown.start();

	// Initialize square
	Square square;
	square.set_active(true);
	square.set_bounds(gameArea);
	square.set_position(0,0);
	if ( square.create_surface() == false ){ return 1; }

    // While the user hasn't quit
    while( quit == false )
    {
        // Start the frame timer
        fps.start();

		// if no active square, create new square
		if ( square.get_active() != true  ) {
			myList.push_front( square );
			square.set_active(true);
			square.set_bounds(gameArea);
			square.set_position(0,0);
			if ( square.create_surface() == false ){ return 1; }
			dropdown.start();
		}

        // While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            // Handle events for the square
            square.handle_input(event);

            // If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                // Quit the program
                quit = true;
            }
        }
		
		// move square if able
		square.move_valid( myList );
		square.set_dir(0,0);

		// if enough time has passed, drop the square down one level
		if ( dropdown.get_ticks() >= 1000 ) {
			square.set_dir(0,1);

			// move square if able
			if ( square.move_valid( myList ) == false )
			{
				// deactivate square if at bottom
				square.set_active(false);
			}
			square.set_dir(0,0);
			dropdown.start();
		}

        // Fill the screen white
        SDL_FillRect( screenSurface, &screenSurface->clip_rect, SDL_MapRGB( screenSurface->format, 0x77, 0x00, 0x00 ) );

		// Show the game area
		SDL_FillRect( screenSurface, &gameArea, SDL_MapRGB( screenSurface->format, 0x00, 0x00, 0x77 ) );

        // Show the square on the screen
        square.show();

		// Show all older squares
		for (std::list<Square>::iterator it=myList.begin(); it!=myList.end(); ++it)
		{
			it->show();
		}

        // Update the screen
        if( SDL_Flip( screenSurface ) == -1 )
        {
            return 1;
        }

        // Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }

    // Clean up
    clean_up(myList, square);

    return 0;
}