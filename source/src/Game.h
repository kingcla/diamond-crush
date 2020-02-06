#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <vector>

#include "Engine.h"
#include "DropAnim.h"
#include "SwapAnim.h"
#include "FuseAnim.h"

// Numbers of rows and columns
#define ROW              8
#define COL              8

// Starting position of the gem grid
#define START_X          328
#define START_Y          100

// Size of the box of the gem grid
#define BOX_SIZE         43

// Time of a game turn
#define START_TIME       60500

// Size of the font for this game state
#define FONT_SIZE        30

// Points for each gem destroyed
#define BASE_POINT       5

// Coordinate of several image resources
#define BACKGROUND_POS_X 0
#define BACKGROUND_POS_Y 0
#define DROP_BACK_POS_X  313
#define DROP_BACK_POS_Y  64
#define BOOM_POS_X       0
#define BOOM_POS_Y       192

// Millisecond to fade the music at the end of the game
#define MUSIC_FADE       3000

// Coordinate of the on screen text
#define SCORE_TEXT_BOX_X 10
#define SCORE_TEXT_BOX_Y 50
#define COMBO_TEXT_BOX_X 10
#define COMBO_TEXT_BOX_Y 90
#define TIME_TEXT_BOX_X  90
#define TIME_TEXT_BOX_Y  435

// Some simple colour definition
#define COLOR_BLACK      0, 0, 0
#define COLOR_RED        255, 0, 0
#define COLOR_GREEN      0, 255, 0
#define COLOR_BLUE       0, 0, 255

// Colour of the selection box (in hex)
#define SEL_BOX_COLOR    0x9BFFF6

class DropAnim;
class SwapAnim;

// Enumerator of the different gem's type
enum GemType
{
    BLUE = 0,
    RED,
    GREEN,
    PURPLE,
    YELLOW,
    G_TYPE_COUNT
};

// Structure of a gem object
struct Gem
{
    int type;
    int x;
    int y;
    Sprite* sprite;
};

/**
 *  Class that manage the Game state
 */
class Game : public GameState
{
    public:
        /** Default constructor */
        Game(Engine* const eng_ref);
        /** Default destructor */
        virtual ~Game();

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
        // Timer for keep trace of the game turn time
        Timer* _timer;

        // Text on screen
        char* str_score;
        char* str_combo;
        char* str_time;

        // Pointer to image resources
        Sprite* _end_screen;
        Sprite* _back;
        Sprite* _drop_back;
        Sprite* _blue_gem;
        Sprite* _red_gem;
        Sprite* _green_gem;
        Sprite* _yellow_gem;
        Sprite* _purple_gem;
        Sprite* _boom;

        // Pointer to sound resources
        Sound* _matchSound;
        Sound* _boomSound;
        Music* _backMusic;

        // Reference of the game engine
        Engine* game_core;

        // Gems matrix
        Gem* matrix[ROW][COL];

        // Reference to the swap animation
        SwapAnim* _swapAnimation;

        // Reference to the dynamite fuse animation
        FuseAnim* _fuseAnim;

        // Keep trace of the selected gem indexes
        int curr_sel_row;
        int curr_sel_col;
        // Keep trace of swapping gem indexes
        int __row1;
        int __col1;
        int __row2;
        int __col2;

        // Flag to switch different behave if swap,
        // match, go back on swap and end game is triggered
        bool handle_swap;
        bool handle_match;
        bool go_back;
        bool _timeOut;

        // Score, number of combo and current score references
        int score;
        int combo;
        int cur_score;

        // List of the dropping animations
        std::vector<DropAnim*> _dropAnims;

        /// Drop gem_num new gems in the selected col, from the row where was the match until the end_row
        void drop_gems(int col, int end_row, int gem_num);

        /// Check if there are 3 or more gem of the same type in the column
        int has_vertical_match(int row, int col);

        /// Check if there are 3 or more gem of the same type in the row
        int has_horizontal_match(int row, int col);

        /// Check if there is a match with the previous 2 gems on the same row or column
        bool check_match_back(int row, int col, int type);

        /// Check 3 or more gem matches in the grid for the type of the gem in col and row
        bool check_match(int row, int col, int type);

        /// Draw the selection box
        void drawSelBox(int row, int col);

        /// Assign a sprite to the gem with the selected type
        Sprite* assingSprite(int type);

        /// Assign the type of the gem
        int assignType(int row, int col);

        /// Get the string format of the passed integer
        char* getStringInt(int i);

        /// Get the time formatted in minutes and seconds of the time passed (in milliseconds)
        void formatTime(int *m, int *s, int millis);
};

#endif // GAME_H
