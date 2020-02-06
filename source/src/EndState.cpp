#include "EndState.h"

// Define the string of the little menu
const char* START_TETX = "Play again";
const char* EXIT_TEXT  = "Exit";

EndState::EndState(Engine* core)
{
    // Store the reference to the engine
    _core = core;

    // Load the instruction backGround
    _back = _core->loadRes("resources/Black.jpg");

    // Get the text box for the menu items and create the buttons
    int w,h;
    _core->getTextBox(START_TETX, &w, &h);
    _start = new Button(START_TETX, (SCREEN_WIDTH/2) - (w/2), (SCREEN_HEIGHT/2) - (h/2) - 50, w, h);

    _core->getTextBox(EXIT_TEXT, &w, &h);
    _exit = new Button(EXIT_TEXT, (SCREEN_WIDTH/2) - (w/2), (SCREEN_HEIGHT/2) - (h/2) + 50, w, h);
}

EndState::~EndState()
{
     // Destroy the background to free memory
    _back->destroy();
}

void EndState::render()
{
    // Draw the background
    _back->draw(0, 0);

    // Draw the text of the menu items, with the setted colour
    _core->drawText(_start->text, _start->x , _start->y, _start->color.r, _start->color.g, _start->color.b);

    _core->drawText(_exit->text, _exit->x, _exit->y, _exit->color.r, _exit->color.g, _exit->color.b);
}

void EndState::logic()
{
    // Change the colour of the buttons if the mouse is over them
    _start->color = _start->isOver ? SELECTED : UNSELECTED;

    _exit->color  = _exit->isOver ? SELECTED : UNSELECTED;
}

void EndState::handle_key_released(int keyCode)
{
    // DO NOTHING
}

void EndState::handle_key_press(int keyCode)
{
    // DO NOTHING
}

void EndState::handle_mouse_click(int posX, int posY, int button)
{
    // If there was a left click
    if (button == 1)
    {
        // Check on which menu button the user clicked
        if (mouseOnStart(posX, posY))
        {
            _core->set_next_state(STATE_GAME); // If start, replay the game
        }

        if (mouseOnExit(posX, posY))
        {
            _core->set_next_state(STATE_EXIT);  // If exit quit the game
        }
    }
}

void EndState::handle_mouse_move(int posX, int posY)
{
    // Set the state of the button if the mouse is over
    _start->isOver = mouseOnStart(posX, posY);

    _exit->isOver  = mouseOnExit(posX, posY);
}


bool EndState::mouseOnStart(int x, int y)
{
    // Return true if the mouse is over the box of the start button text
    if((x >= _start->x && x <= _start->x + _start->width) && (y >= _start->y && y <= _start->y + _start->height))
        return true;

    return false;
}

bool EndState::mouseOnExit(int x, int y)
{
    // Return true if the mouse is over the box of the exit button text
    if((x >= _exit->x && x <= _exit->x + _exit->width) && (y >= _exit->y && y <= _exit->y + _exit->height))
        return true;

    return false;
}
