#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "GameState.h"
#include "Engine.h"
#include "Sprite.h"

/**
 *  Class that manage the instruction for the game
 */
class Instruction : public GameState
{
    public:
        /** Default constructor */
        Instruction(Engine* const eng_ref);
        /** Default destructor */
        ~Instruction();

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
};

#endif // INSTRUCTION_H
