#ifndef DROPANIM_H
#define DROPANIM_H

#include "GameAnim.h"
#include "Game.h"

// Default speed of dropping
#define DROP_SPEED 10

struct Gem;

/**
 *  Class to represent a gems drop animation sequence
 */
class DropAnim : public GameAnim
{
    public:
        /// Create the animation sequence with the y coordinate of the column to drop,
        /// the size of a box in the grid, the vector of the gems to drop and the length of the vector
        DropAnim(int start_y, int box_size, Gem* drop_vect[], int length);
        /** Default destructor */
        ~DropAnim();

        /// Check if the animation finished or not
        bool isRunning();

        /// Set the next frame of the animation
        void set_next_frame();
    private:
        // Store the y coordinate and the size of the box
        int _start_y;
        int _size;
        // List of the gems to drop
        std::vector<Gem*> _vect;
};

#endif // DROPANIM_H
