#include <iostream>
#include "Game.h"

Game::Game(Engine* const eng_ref)
{
    // Store the references of the game engine
    game_core = eng_ref;

    // Reset all the global variables
    curr_sel_row = -1;
    curr_sel_col = -1;
    score        = 0;
    combo        = 0;
    cur_score    = 0;
    handle_swap  = false;
    handle_match = false;
    go_back      = false;
    _timeOut     = false;

    // Init the string
    str_score = new char[30];
    str_combo = new char[10];
    str_time  = new char[5];

    // No swap animation
    _swapAnimation = NULL;

    // Load all the resources
    _end_screen = game_core->loadRes("resources/Black.jpg");
    // Set the game over background trasparent
    _end_screen->setAlpha(0);
    _back       = game_core->loadRes("resources/BackGround.jpg");
    _drop_back  = game_core->loadRes("resources/drop_back.png");
    _boom       = game_core->loadResAlpha("resources/Boom.png");
    // Load the gem sprites
    _blue_gem   = game_core->loadResAlpha("resources/Blue.png");
    _red_gem    = game_core->loadResAlpha("resources/Red.png");
    _green_gem  = game_core->loadResAlpha("resources/Green.png");
    _yellow_gem = game_core->loadResAlpha("resources/Yellow.png");
    _purple_gem = game_core->loadResAlpha("resources/Purple.png");
    // Load the sounds
    _matchSound = game_core->loadSound("resources/Sounds/Reward.wav");
    _boomSound  = game_core->loadSound("resources/Sounds/Boom.wav");
    _backMusic  = game_core->loadMusic("resources/Sounds/BackMusic.wav");

    // Set the size of the text font
    game_core->setTextSize(FONT_SIZE);

    // Init the dynamite fuse animation
    _fuseAnim = new FuseAnim(game_core, START_TIME/1000);

    // Init the random engine
    srand((unsigned)time(NULL));

    // Init the gems matrix
	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
           Gem* g = new Gem();

           g->type   = assignType(j, i);
           g->sprite = assingSprite(g->type);
           g->x      = START_X + BOX_SIZE*i;
           g->y      = START_Y + BOX_SIZE*j;

		   matrix[j][i] = g;
		}
	}

    // Init the timer and start it
    _timer = new Timer();
    _timer->start();

    // start to play the background music
    _backMusic->play(true);
}

Game::~Game()
{
    // destroy all the sprites used
    _end_screen->destroy();
    _back->destroy();
    _drop_back->destroy();
    _blue_gem->destroy();
    _red_gem->destroy();
    _green_gem->destroy();
    _yellow_gem->destroy();
    _purple_gem->destroy();
    _boom->destroy();

    // destroy all the sounds
    _matchSound->destroy();
    _boomSound->destroy();
    _backMusic->destroy();

    // delete all the gems in the matrix
    for (int i = 0; i < ROW; i++)
        for(int j = 0; j < COL; j++)
            delete matrix[i][j];
    delete[] matrix;

    // Delete animations
    delete(_swapAnimation);
    for (unsigned int i = 0; i < _dropAnims.size(); i++)
        delete(_dropAnims[i]);
    delete(_fuseAnim);

    // delete other object references
    delete(_timer);
    delete[] str_score;
    delete[] str_combo;
    delete[] str_time;
}

int Game::assignType(int row, int col)
{
    int t;

    // Take the type randomly
    t = rand() % G_TYPE_COUNT;

    // but before check if it will not create a row or column match
    while (check_match_back(row, col, t))
    {
        // if the type is creating a match

        // select the next type randomly
        if (t > 0)
        {
            // avoiding to the same type as before
            if (t < G_TYPE_COUNT - 1)
            {
                // therefore randomly choose a side
                // greater or lower than the type chose before
                if ((rand() % 2))
                    t = rand() % t; // greater
                else
                    t = rand() % (G_TYPE_COUNT - (t + 1)) + t + 1; // lower
            }
            else
                t = rand() % (G_TYPE_COUNT - 1); // the type is the upper bound
        }
        else
            t = rand() % (G_TYPE_COUNT - 1) + 1; // the type is the lower bound
    }

    return t;
}

Sprite* Game::assingSprite(int type)
{
    // Assign a sprite to the gem based on its type
    switch(type)
    {
    case BLUE:
        return _blue_gem;
    case GREEN:
        return _green_gem;
    case YELLOW:
        return _yellow_gem;
    case RED:
        return _red_gem;
    case PURPLE:
        return _purple_gem;
    }

    return NULL;
}

void Game::drawSelBox(int row, int col)
{
    ////////////////////////////////// |
    game_core->drawRect((START_X + BOX_SIZE*row) - 6, (START_Y + BOX_SIZE*col) - 3,
                        3, (BOX_SIZE / 2) - 3,
                        SEL_BOX_COLOR);
    game_core->drawRect((START_X + BOX_SIZE*row) - 6, (START_Y + BOX_SIZE*col) + (BOX_SIZE / 2),
                        3, (BOX_SIZE / 2) - 3,
                        SEL_BOX_COLOR);

    //////////////////////////////////    |
    game_core->drawRect((START_X + BOX_SIZE*row) + BOX_SIZE - 6, (START_Y + BOX_SIZE*col) - 3,
                        3, (BOX_SIZE / 2) - 3,
                        SEL_BOX_COLOR);

    game_core->drawRect((START_X + BOX_SIZE*row) + BOX_SIZE - 6, (START_Y + BOX_SIZE*col) + (BOX_SIZE / 2),
                        3, (BOX_SIZE / 2) - 3,
                        SEL_BOX_COLOR);

    ////////////////////////////////// ^
    game_core->drawRect((START_X + BOX_SIZE*row) - 6, (START_Y + BOX_SIZE*col) - 3,
                        (BOX_SIZE / 2) - 2, 3,
                        SEL_BOX_COLOR);

    game_core->drawRect((START_X + BOX_SIZE*row) + (BOX_SIZE / 2), (START_Y + BOX_SIZE*col) - 3,
                        (BOX_SIZE / 2) - 2, 3,
                        SEL_BOX_COLOR);

    ////////////////////////////////// _
    game_core->drawRect((START_X + BOX_SIZE*row) - 6, (START_Y + BOX_SIZE*col) + BOX_SIZE - 6,
                        (BOX_SIZE / 2) - 2, 3,
                        SEL_BOX_COLOR);

    game_core->drawRect((START_X + BOX_SIZE*row) + (BOX_SIZE / 2), (START_Y + BOX_SIZE*col) + BOX_SIZE - 6,
                        (BOX_SIZE / 2) - 2, 3,
                        SEL_BOX_COLOR);
}

bool Game::check_match_back(int row, int col, int type)
{
    // Check if there is a match with the previous 2 gems on the same row
    if(row-2 > -1)
        if(type == matrix[row-1][col]->type && type == matrix[row-2][col]->type)
            return true;

    // Check if there is a match with the previous 2 gems on the same column
    if(col-2 > -1)
        if(type == matrix[row][col-1]->type && type == matrix[row][col-2]->type)
            return true;

    return false;
}

char* Game::getStringInt(int i)
{
	// init the string space
	char mesg[50];

    // return the string format of the integer passed
    return itoa(i, mesg, 10);
}

void Game::formatTime(int *m, int *s, int millis)
{
    int ns;

    ns = millis / 1000;

    *m = ns / 60;

    *s = (ns % 60);
}

bool Game::check_match(int row, int col, int type)
{
    /// ---------- HORIZONTAL -----------

    // Check the next 2 columns *||
    if(col+2 < COL)
        if(type == matrix[row][col+1]->type && type == matrix[row][col+2]->type)
            return true;

    // Check the next 1 column and the column back |*|
    if(col+1 < COL && col-1 > -1)
        if(type == matrix[row][col-1]->type && type == matrix[row][col+1]->type)
            return true;

    // Check the 2 columns back ||*
    if(col-2 > -1)
        if(type == matrix[row][col-1]->type && type == matrix[row][col-2]->type)
            return true;

    /// ---------- VERTICAL -----------

    // Check the next 2 rows *||
    if(row+2 < ROW)
        if(type == matrix[row+1][col]->type && type == matrix[row+2][col]->type)
            return true;

    // Check the next 1 row and the row back |*|
    if(row+1 < ROW && row-1 > -1)
        if(type == matrix[row-1][col]->type && type == matrix[row+1][col]->type)
            return true;

    // Check the 2 rows back ||*
    if(row-2 > -1)
        if(type == matrix[row-1][col]->type && type == matrix[row-2][col]->type)
            return true;

    return false;
}

int Game::has_vertical_match(int row, int col)
{
	int i;

    // Check for all the rows of the same column
	for(i=1;i+row < ROW; i++)
        // if the type of the gem in the original row is the same of the one of the next row
        // remaining on the same column
		if(matrix[row][col]->type != matrix[row+i][col]->type)
			break;

    // if there are 3 or more gem of the same type in the column there is a match
	if(i >= 3)
		return i;
	else
		return 0;
}

int Game::has_horizontal_match(int row, int col)
{
    int i;

    // Check for all the columns of the same row
	for(i=1; i+col < COL; i++)
        // if the type of the gem in the original column is the same of the one of the next column
        // remaining on the same row
		if(matrix[row][col]->type != matrix[row][col+i]->type)
			break;

    // if there are 3 or more gem of the same type in the row there is a match
	if(i >= 3)
		return i;
	else
		return 0;
}

void Game::drop_gems(int col, int end_row, int gem_num)
{
    // create a vector with the list of gems that will be dropped
    Gem* temp_vector[end_row + 1];

    // for all the gems in the column to drop
	for(int i = end_row; i >= 0; i--)
	{
	    // delete the gem from the matrix
	    delete(matrix[i][col]);
	    // and create a new gem object
        Gem* g = new Gem();

        // if the gem exists already in the column
		if(i - gem_num >= 0)
        {
            // just copy the values in the new gem created
            g->sprite = matrix[i - gem_num][col]->sprite;
            g->type   = matrix[i - gem_num][col]->type;
            g->y      = matrix[i - gem_num][col]->y;
        }
        // otherwise create a new one
		else
        {
            // take the type and the sprite
           g->type   = rand() % G_TYPE_COUNT;
           g->sprite = assingSprite(g->type);
           // y coordinate will be up the existing gems in the column
           g->y      = START_Y + BOX_SIZE*(i - gem_num);
        }

        // the x coordinate is the column dropped
        g->x = START_X + BOX_SIZE*col;

        // insert the new gem object in the matrix
        // with the same indexes of the gem deleted
        matrix[i][col] = g;

        // insert the gem also in the array of the column dropped
        temp_vector[i] = g;
	}

    // Insert a new dropping animation in the list
    _dropAnims.push_back(new DropAnim(START_Y, BOX_SIZE, temp_vector, end_row + 1));
}

/// ------------------------------------- LOGIC ------------------------------------------

void Game::logic()
{
    /// If there are no drops animation calculate the score
    if (_dropAnims.empty() && cur_score > 0)
    {
        // Multiply combo per current score
        if (combo > 0)
            cur_score *= combo;

        // Add the current score to the total score
        score += cur_score;
    }

    /// If there was a swapping between two gems
    if (handle_swap)
    {
        // If there is not any other swap animations
        if (_swapAnimation != NULL && !_swapAnimation->isRunning())
        {
            // reset the swap handle
            handle_swap = false;

            // If the swap animation is not going back
            if (!go_back)
            {
                // Swap the gems in the matrix
                std::swap(matrix[__row1][__col1], matrix[__row2][__col2]);

                // Check the match with the two gems swapped
                if (check_match(__row2, __col2, matrix[__row2][__col2]->type) ||
                    check_match(__row1, __col1, matrix[__row1][__col1]->type))
                {
                    // If there is a match activate the match handle
                    handle_match = true;
                }
                else
                {
                    // Otherwise swap back
                    handle_swap = true;
                    go_back     = true;

                    // Recreate the animation to swap back
                    delete(_swapAnimation);
                    _swapAnimation = new SwapAnim(matrix[__row1][__col1], matrix[__row2][__col2],
                                                  matrix[__row2][__col2]->x, matrix[__row2][__col2]->y,
                                                  matrix[__row1][__col1]->x, matrix[__row1][__col1]->y);

                    // Swap back the gems in the matrix too
                    std::swap(matrix[__row2][__col2], matrix[__row1][__col1]);
                }// check match
            }// go back
        }// swap animation
    }// handle swap

    /// If it was a match and there are no drop animations
    if (handle_match && _dropAnims.empty())
    {
        // Init the amount of gems per rows and columns
        int ammount;
        bool reset;

        // Reset combo and current score
        cur_score  = 0;
        ammount    = 0;
        reset      = true;

        // Cycle until there are no more matches
        while (reset)
        {
            reset = false;

            // Cycle on the row until a match is found
            for(int i=0; i < ROW && !reset; i++)
            {
                // Cycle on the columns until a match is found
                for(int k=0; k < COL && !reset; k++)
                {
                    // If a match is found on a column, assign the amount of gems
                    if(ammount = has_vertical_match(i,k))
                    {
                        // Play the sound of match
                        _matchSound->play();

                        // Increment combo
                        combo++;

                        // Increment the current score based on the amount of gems matched
                        cur_score += BASE_POINT * ammount;

                        // Delete the gems and create a new drop animation
                        drop_gems(k, i + (ammount-1), ammount);

                        // reset and break the cycle
                        reset = true;
                        break;
                    }// vertical match

                    if(ammount = has_horizontal_match(i,k))
                    {
                        // Play the sound of match
                        _matchSound->play();

                        // Increment combo
                        combo++;

                        // Increment the current score based on the amount of gems matched
                        cur_score += BASE_POINT * ammount;

                        // Fro each gem matched in the row
                        for(int z=0; z<ammount; z++)
                        {
                            // Delete the gems and create a new drop animation for each columns
                            drop_gems(k+z,i,1);
                        }

                        // reset and break the cycle
                        reset = true;
                        break;
                    }// horizontal match
                }// columns cycle
            }// rows cycle

            // If there are animation exit the main cycle and don't check for other matches
            if (!_dropAnims.empty())
                break;

            // reset combo
            combo  = 0;

            // No more matches at the end of the cycle
            handle_match = false;
        }// while reset
    }// if handle match and no animations
}

/// ------------------------------------- RENDER ------------------------------------------

void Game::render()
{
    /// Draw the background
    _back->draw(BACKGROUND_POS_X, BACKGROUND_POS_Y);

    /// For each rows and columns draw the gem sprite on the screen
    for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
		    // Draw the gem only if it is in the border of the matrix
		    // For the upper bound is shifted of half the dimension of the gem sprite
		    // because when it is dropping a new column it will appear just under the drop background
		    if (matrix[i][j]->x >= START_X && matrix[i][j]->y >= START_Y - BOX_SIZE/2)
                matrix[i][j]->sprite->draw(matrix[i][j]->x, matrix[i][j]->y);
		}
	}

    /// If the game is finished
    if (_timeOut)
    {
        // Fade the end black background
        _end_screen->fade(true);
        _end_screen->draw(BACKGROUND_POS_X, BACKGROUND_POS_Y);

        // Draw the game over and the score text
        game_core->drawText("GAME OVER", SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 50, COLOR_RED);
        game_core->drawText(str_score, SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 50, COLOR_RED);
    }
    /// Otherwise draw the rest on the screen
    else
    {
        /// If there are drop animations
        if (!_dropAnims.empty())
        {
            // For each drop animations in the list...
            for (unsigned int i = 0; i < _dropAnims.size(); i++)
            {
                // ... if the animation has not finished yet
                if (((DropAnim*)_dropAnims[i])->isRunning())
                    ((DropAnim*)_dropAnims[i])->set_next_frame(); // pass to the next frame
                else
                    _dropAnims.pop_back();                        // otherwise delete it
            }
        }

        /// If the user select a gem draw the box around the gem
        if (curr_sel_row > -1 && curr_sel_col > -1)
            drawSelBox(curr_sel_col, curr_sel_row);

        /// If there is a swapping draw the animation
        if (_swapAnimation != NULL && _swapAnimation->isRunning())
            _swapAnimation->set_next_frame();

        /// Draw the drop background
        // if there is a drop animation, this sprite will be drawn just up the new gems
        _drop_back->draw(DROP_BACK_POS_X, DROP_BACK_POS_Y);

        /// Draw the total score
        // Init the string for the score
        strcpy(str_score, "Score: ");
        strcat(str_score, getStringInt(score));
        // Draw the text at the specified position and with that colour
        game_core->drawText(str_score, SCORE_TEXT_BOX_X, SCORE_TEXT_BOX_Y, COLOR_BLACK);

        /// Draw the number if combos
        strcpy(str_combo, "Combo: ");
        if (combo > 0)
        {
            // If there are combos write the number
            strcat(str_combo, "x");
            strcat(str_combo, getStringInt(combo));
        }
        // Draw the combo string on the screen
        game_core->drawText(str_combo, COMBO_TEXT_BOX_X, COMBO_TEXT_BOX_Y, COLOR_BLACK);

        /// Draw the time left
        // Calc the current time sub the initial timer and the game ticks (in millisecond)
        int curr_time = START_TIME - _timer->get_ticks();
        // if the time is still running
        if ( curr_time > 0)
        {
            // Get the time formatted in minutes and seconds
            int m,s;
            formatTime(&m, &s, curr_time);

            // Init the string of the time
            strcpy(str_time, getStringInt(m));
            strcat(str_time, ":");
            // If the seconds are less than 10 write a 0 before the seconds
            if (s < 10) strcat(str_time, "0");
            strcat(str_time, getStringInt(s));
            // Draw the time on the screen
            game_core->drawText(str_time, TIME_TEXT_BOX_X, TIME_TEXT_BOX_Y, COLOR_BLACK);

            // If the animation of the dynamite fuse is still running
            if (_fuseAnim->isRunning())
            {
                // Draw the animation
                 _fuseAnim->setTime((curr_time)/1000);
                _fuseAnim->set_next_frame();
            }
            else
            {
                // else draw the explosion
                _boom->draw(BOOM_POS_X, BOOM_POS_Y);
                // fade and stop the background music
                _backMusic->stop(true, MUSIC_FADE);
                // play the boom sound
                _boomSound->play();
            }
        }// if current time is > 0
        else
            // otherwise is timeout and the game ends
            _timeOut = true;
    }
}

/// ------------------------------------- MOUSE & KEYBOARD --------------------------------

void Game::handle_mouse_click(int posX, int posY, int button)
{
    // Init the matrix dimension based on the number of rows and columns and the box size
    int widthX  = BOX_SIZE*COL;
    int heightY = BOX_SIZE*ROW;
    int col     = 0;
    int row     = 0;

    // If is clicked the left button
    if (button == LEFT_BUTTON)
    {
        // If the game is end
        if (_timeOut)
            // pass to the next state (the next state is the end game)
            game_core->set_next_state(STATE_END);
        // otherwise check if the user click on a gem
        else if ((posX > START_X && posX < START_X + widthX) && (posY > START_Y && posY < START_Y + heightY))
        {
            // Take the position of the gem clicked
            col = (posX - START_X)/BOX_SIZE;
            row = (posY - START_Y)/BOX_SIZE;

            // check if there was a gem already selected and the user clicked on a contiguous gem
            if (row == curr_sel_row && (col == curr_sel_col-1 || col == curr_sel_col+1) ||
               (col == curr_sel_col && (row == curr_sel_row-1 || row == curr_sel_row+1)))
            {
                // assign the matrix coordinate of the two gem that have to be swapped
                __row1 = curr_sel_row;
                __col1 = curr_sel_col;
                __row2 = row;
                __col2 = col;

                // activate the swap
                handle_swap  = true;
                go_back      = false;

                // create the animation of the swapping
                _swapAnimation = new SwapAnim(matrix[curr_sel_row][curr_sel_col], matrix[row][col],
                                              matrix[row][col]->x, matrix[row][col]->y,
                                              matrix[curr_sel_row][curr_sel_col]->x, matrix[curr_sel_row][curr_sel_col]->y);

                // reset the gem selection indexes
                curr_sel_col = -1;
                curr_sel_row = -1;
            }
            // If the gem is not contiguous, select the new gem
            else
            {
                // assign the new matrix coordinate
                curr_sel_row = row;
                curr_sel_col = col;
            }
        }
    }
}

void Game::handle_mouse_move(int posX, int posY)
{
    /// DO NOTHING
}

void Game::handle_key_press(int keyCode)
{
    /// DO NOTHING
}

void Game::handle_key_released(int keyCode)
{
    /// DO NOTHING
}
