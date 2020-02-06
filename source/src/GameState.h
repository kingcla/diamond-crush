#ifndef GAMESTATE_H
#define GAMESTATE_H


//Game states
enum GameStates
{
    STATE_NULL,
    STATE_LOGO,
    STATE_INSTRUCTION,
    STATE_GAME,
    STATE_END,
    STATE_EXIT
};

//Game state base class
class GameState
{
    public:
        virtual void handle_mouse_move(int posX, int posY) = 0;
        virtual void handle_mouse_click(int posX, int posY, int button) = 0;
        virtual void handle_key_press(int keyCode) = 0;
        virtual void handle_key_released(int keyCode) = 0;
        virtual void logic() = 0;
        virtual void render() = 0;
        virtual ~GameState(){};
};

#endif // GAMESTATE_H
