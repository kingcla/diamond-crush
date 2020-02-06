#ifndef SWAPANIM_H
#define SWAPANIM_H

#include "GameAnim.h"
#include "Game.h"

// The speed of swap animation
#define SWAP_SPEED 13

struct Gem;

/**
 *  Class to represent a gems swap animation sequence
 */
class SwapAnim : public GameAnim
{
    public:
        /// Create a new swap animation passing the two gems references and its coordinates
        SwapAnim(Gem* first_gem, Gem* second_gem, int x1_end, int y1_end, int x2_end, int y2_end);
        /** Default destructor */
        ~SwapAnim();

        /// Check if the animation finished or not
        bool isRunning();

        /// Set the next frame of the animation
        void set_next_frame();
    private:
        // References to the two gems to swap
        Gem* _gem1;
        Gem* _gem2;
        // Store the coordinates of the two gems
        int _x1_end;
        int _y1_end;
        int _x2_end;
        int _y2_end;
};

#endif // SWAPANIM_H
