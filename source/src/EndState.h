#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "GameState.h"
#include "Engine.h"
#include "Sprite.h"

// Struct for RGB colour representation
struct RGB {
    RGB(int r, int g, int b) : r(r), g(g), b(b) {};
    int r; int g; int b;
};

// Define the selected and unselected colour
const RGB UNSELECTED = RGB(255, 255, 255);
const RGB SELECTED   = RGB(255, 0, 0);

// Struct for the menu button
struct Button {
    Button(const char* content, int x, int y, int w, int h) :
        text(content), x(x), y(y), width(w), height(h), isPressed(false), isOver(false), color(UNSELECTED){};

    const char* text;
    int   x;
    int   y;
    int   width;
    int   height;
    bool  isPressed;
    bool  isOver;
    RGB   color;
};

/**
 *  Class that manage the end game menu
 */
class EndState : public GameState
{
    public:
        /** Default constructor */
        EndState(Engine* core);
        /** Default destructor */
        virtual ~EndState();

        /// Render the graphics
        void render();
        /// Execute the logic
        void logic();

        /// Keyboard and mouse event handlers
        void handle_key_released(int keyCode);
        void handle_key_press(int keyCode);
        void handle_mouse_click(int posX, int posY, int button);
        void handle_mouse_move(int posX, int posY);
    private:
        // Reference to the game engine
        Engine* _core;
        // Reference to the background image
        Sprite* _back;
        // References to the button of the menu
        Button* _start;
        Button* _exit;

        /// True if the mouse is on the start button
        bool mouseOnStart(int x, int y);
        /// True if the mouse is on the exit button
        bool mouseOnExit(int x, int y);
};

#endif // ENDSTATE_H
