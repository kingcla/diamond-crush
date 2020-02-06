#include "Instruction.h"

Instruction::Instruction(Engine* const eng_ref)
{
    // Store the reference to the engine
    game_core = eng_ref;

    // Load the instruction backGround
    _back = game_core->loadRes("resources/Instruction.jpg");
}

Instruction::~Instruction()
{
    // Destroy the background to free memory
   _back->destroy();
}

void Instruction::handle_mouse_move(int posX, int posY)
{
    // DO NOTHING
}

void Instruction::handle_mouse_click(int posX, int posY, int button)
{
    // At mouse click pass to the next state
    game_core->set_next_state(STATE_GAME);
}

void Instruction::handle_key_press(int keyCode)
{
    // DO NOTHING
}

void Instruction::handle_key_released(int keyCode)
{
    // DO NOTHING
}

void Instruction::logic()
{
    // DO NOTHING
}

void Instruction::render()
{
    // Draw the background
    _back->draw(0,0);
}
