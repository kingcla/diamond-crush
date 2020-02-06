#include "Engine.h"
#include "SplashScreen.h"
#include "Instruction.h"
#include "Game.h"
#include "EndState.h"

Engine::Engine()
{
    // Init the state to null
    stateID      = STATE_NULL;

    nextState    = STATE_NULL;

    currentState = 0;
}

Engine::~Engine()
{
    /// DO NOTHING - CALL CLOSE INSTEAD
}

Sound* Engine::loadSound(char* path)
{
    // Load a sound from the system memory, NULL if there was a problem
    return new Sound(path);
}

Music* Engine::loadMusic(char* path)
{
    // Load a music from the system memory, NULL if there was a problem
    return new Music(path);
}

void Engine::draw_on_surface(int x, int y, SDL_Surface *surface)
{
    SDL_Rect rect;

    // Set the destination coordinate
    rect.x = x;
    rect.y = y;

    // Screen must exist
    if (!screen)
        return;

    //Blit the surface
    SDL_BlitSurface(surface, NULL, screen, &rect);
}

Sprite* Engine::loadRes(char* path)
{
    // Load an image and pass a new sprite
    return new Sprite(path, screen);
}

Sprite* Engine::loadResAlpha(char* path)
{
    // Load and image with alpha and pass a new sprite
    return new Sprite(path, screen, true);
}

AnimSprite* Engine::loadAnim(char* path, int sprite_size, int frame_rate)
{
    AnimSprite* s = new AnimSprite(path, screen, sprite_size, sprite_size);

    s->MaxFrames = s->_surf->h / sprite_size;

    s->SetFrameRate(frame_rate);

    return s;
}

void Engine::close()
{
    // Close the engine and free all the references
    delete(currentState);

    // Free the screen surface
    SDL_FreeSurface(screen);

    //Quit the mixer
    Mix_CloseAudio();

    //Close the font that was used
    TTF_CloseFont( font );

    // Quit the text engine
    TTF_Quit();

    // Quit SDL
    SDL_Quit();
}

bool Engine::init(char* icon, char* window_caption)
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return false;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // Set the window text
    SDL_WM_SetCaption(window_caption, NULL);

    // Center the main window
    SDL_putenv("SDL_VIDEO_CENTERED=center");

    // Load the icon picture
    SDL_WM_SetIcon(IMG_Load(icon), NULL);

    // create a new window
    screen = SDL_SetVideoMode(SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SCREEN_BPP,
                              SDL_HWSURFACE | SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set video: %s\n", SDL_GetError());
        return false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        printf("Unable to set text: %s\n", TTF_GetError());
        return false;
    }

    //Open the font
    font = TTF_OpenFont(FONT_PATH, 10);

    //Initialize SDL_mixer
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1)
    {
        printf("Unable to set audio: %s\n", Mix_GetError());
        return false;
    }

    // Start the state manager
    stateID = STATE_LOGO;

    // Set the initial state
    currentState = new SplashScreen(this);

    // Init the frame counter
    frame = 0;

    // Return true if all the initialization have been successful
    return true;
}

void Engine::drawText(const char* text, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
    int w = 0;
    int h = 0;

    // Draw text without return the box size
    drawText(text, x, y, r, g, b, &w, &h);
}

void Engine::drawText(const char* text, int x, int y, Uint8 r, Uint8 g, Uint8 b, int *w, int *h)
{
    // Create the colour from RGB values
    SDL_Color color = {r, g, b};

    // Render the text
    SDL_Surface* txt = TTF_RenderText_Blended(font, text, color);

    // If there was an error in rendering the text
    if( txt == NULL )
        return;

    // Apply the images to the screen
    draw_on_surface(x, y, txt);

    // Return the size of the box where the text is rendered
    TTF_SizeText(font, text, w, h);

    // destroy the surface
    SDL_FreeSurface(txt);
}

void Engine::getTextBox(const char* text, int* w, int* h)
{
    // Return the size of the box where the text is rendered
    TTF_SizeText(font, text, w, h);
}

void Engine::setTextSize(int t_size)
{
    // close the previous font opened
    TTF_CloseFont(font);

    // open a new font with the specified size
    font = TTF_OpenFont(FONT_PATH, t_size);
}

void Engine::set_next_state( int newState )
{
    //If the user doesn't want to exit
    if( nextState != STATE_EXIT )
    {
        //Set the next stateEngine* eng
        nextState = newState;
    }
}

void Engine::change_state()
{
    //If the state needs to be changed
    if( nextState != STATE_NULL )
    {
        //Delete the current stateSTATE_GAME
        if( nextState != STATE_EXIT )
        {
            delete(currentState);
        }

        //Change the state
        switch( nextState )
        {
            case STATE_LOGO:
                currentState = new SplashScreen(this);
                break;
            case STATE_INSTRUCTION:
                currentState = new Instruction(this);
                break;
            case STATE_GAME:
                currentState = new Game(this);
                break;
            case STATE_END:
                currentState = new EndState(this);
                break;
        }

        //Change the current state ID
        stateID = nextState;

        //NULL the next state ID
        nextState = STATE_NULL;
    }
}

void Engine::drawRect(int x, int y, int w, int h, int color)
{
    // Draw a rectangle in the specified position with passed size and colour
    SDL_Rect rect = {x,y,w,h};
    SDL_FillRect(screen, &rect, color);
}

bool Engine::update()
{
    //Start the frame timer
    fps.start();

    // message processing loop
    SDL_Event event;

    // Get all the SDL event
    while (SDL_PollEvent(&event))
    {
        // check for messages
        switch (event.type)
        {
        // exit if the window is closed
        case SDL_QUIT:
            return false;
            break;

        // check for keypresses
        case SDL_KEYDOWN:
            {
                // exit if ESCAPE is pressed
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    return false;

                // Pass the key down code to the current state
                currentState->handle_key_press(event.key.keysym.sym);

                break;
            }
        case SDL_KEYUP:
            {
                // Pass the key up code to the current state
                currentState->handle_key_released(event.key.keysym.sym);
                break;
            }
        case SDL_MOUSEBUTTONDOWN:
            {
                // Pass the mouse button code and position to the current state
                currentState->handle_mouse_click(event.button.x, event.button.y, event.button.button);
            }
        case SDL_MOUSEMOTION:
            {
                // Pass the mouse position to the current state
                currentState->handle_mouse_move(event.motion.x, event.motion.y);
            }
        } // end switch
    } // end of message processing

    //Do state logic
    currentState->logic();

    //Change state if needed
    change_state();

    // Check if the current state is Exit, so quit
    if (stateID == STATE_EXIT)
        return false;

    // clear screen
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

    //Do state rendering
    currentState->render();

    // finally, update the screen :)
    if (SDL_Flip(screen) == -1)
        return false;

    // increase the frame
    frame++;

    // If we want to cap the frame rate
    if(fps.get_ticks() < 1000 / FPS)
    {
        // Sleep the remaining frame time
        SDL_Delay( ( 1000 / FPS ) - fps.get_ticks() );
    }

    return true;
}
