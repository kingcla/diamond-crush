#ifndef ENGINE_H
#define ENGINE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

#include "GameState.h"
#include "Sprite.h"
#include "Timer.h"
#include "AnimSprite.h"
#include "Sound.h"

// Define the path of the font
#define FONT_PATH     "resources/ARBERKLEY.ttf"

// Define the left and right button code
#define LEFT_BUTTON   1
#define RIGHT_BUTTON  3

// Defines Screen data
#define SCREEN_WIDTH  755
#define SCREEN_HEIGHT 600
#define SCREEN_BPP    32

//The frames per second
#define FPS           30

/**
 *  Main Engine class that manage loading resources and changing game states
 */
class Engine
{
    public:
        /** Default constructor */
        Engine();
        /** Default destructor - DO NOTHING - CALL CLOSE INSTEAD */
        ~Engine();

        /// Init the engine and the window
        bool init(char* icon, char* window_caption);

        /// Close the engine
        void close();

        /// Main engine function, to call in the game loop
        bool update();

        /// Draw a rectangle
        void drawRect(int x, int y, int w, int h, int color);

        /// Draw text on the screen in the defined position with that colour (optionally return the size of the box)
        void drawText(const char* text, int x, int y, Uint8 r, Uint8 g, Uint8 b);
        void drawText(const char* text, int x, int y, Uint8 r, Uint8 g, Uint8 b, int *w, int *h);
        /// Get the size of the box of the text passed
        void getTextBox(const char* text, int *w, int *h);
        /// change the size of the font
        void setTextSize(int t_size);

        /// Load a image resource, giving back a Sprite ref. It is possible to load with or without the alpha information
        Sprite* loadRes(char* path);
        Sprite* loadResAlpha(char* path);
        /// Load an animated resources passing the size of the single sprite inside the file and the frame rate
        /// The image to pass must be: "sprite_size" large and "sprite_size*number_of frame" high
        AnimSprite* loadAnim(char* path, int sprite_size, int frame_rate);

        /// Load a sound or a music
        Sound* loadSound(char* path);
        Music* loadMusic(char* path);

        /// Set the next state
        void set_next_state(int newState);
    private:
        // Keep track of the current frame
        int frame;
        // The frame rate regulator
        Timer fps;

        // Main screen
        SDL_Surface* screen;

        // State variables
        int stateID;
        int nextState;

        // The font that's going to be used
        TTF_Font* font;

        // Game state object
        GameState* currentState;

        /// Draw a surface on the screen with defined coordinates
        void draw_on_surface(int x, int y, SDL_Surface *surface);

        /// State changer, execute the state changing if necessary
        void change_state();
};

#endif // ENGINE_H
