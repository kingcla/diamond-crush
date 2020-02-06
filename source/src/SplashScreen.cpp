#include "SplashScreen.h"

SplashScreen::SplashScreen(Engine* const eng_ref)
{
    // Store the reference to the engine
    game_core = eng_ref;

    // Load the instruction backGround
    _back = game_core->loadRes("resources/SplashScreen.png");

    // Set the background transparent for the fade effect
    _back->setAlpha(0);
    _back->setFadeSpeed(25);

    // Init and start the timer
    _time = new Timer();
    _time->start();
}

SplashScreen::~SplashScreen()
{
    // Destroy the background to free memory
    _back->destroy();

    // delete the timer
    delete(_time);
}

void SplashScreen::handle_mouse_move(int posX, int posY)
{
    // DO NOTHING
}

void SplashScreen::handle_mouse_click(int posX, int posY, int button)
{
    // DO NOTHING
}

void SplashScreen::handle_key_press(int keyCode)
{
    // DO NOTHING
}

void SplashScreen::handle_key_released(int keyCode)
{
    // DO NOTHING
}

void SplashScreen::logic()
{
    // Passed 3 seconds switch to the next state
    if (_time->get_ticks() >= 3000)
        game_core->set_next_state(STATE_INSTRUCTION);
}

void SplashScreen::render()
{
    // Fade the background
    _back->fade(true);
    // Draw the background
    _back->draw(0,0);
}
