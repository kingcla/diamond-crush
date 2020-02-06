#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "GameState.h"
#include "Engine.h"
#include "Sprite.h"

/**
 *  Class that manage the initial splash screen
 */
class SplashScreen : public GameState
{
    public:
        /** Default constructor */
        SplashScreen(Engine* const eng_ref);
        /** Default destructor */
        ~SplashScreen();

        /// Render the graphics
        void render();
        /// Execute the logic
        void logic();

        /// Keyboard and mouse event handlers
        void handle_mouse_move(int posX, int posY);
        void handle_mouse_click(int posX, int posY, int button);
        void handle_key_press(int keyCode);
        void handle_key_released(int keyCode);
    private:
        // Reference to the background image
        Sprite* _back;
        // Reference to the game engine
        Engine* game_core;
        // Timer to cound the second to show the logo
        Timer* _time;
};

#endif // SPLASHSCREEN_H
