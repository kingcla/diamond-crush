#ifndef FUSEANIM_H
#define FUSEANIM_H

#include <vector>

#include "Engine.h"
#include "GameAnim.h"

// Define the size of the fuse sprite
#define SPRITE_SIZE 64
// Define the speed of the fuse animation
#define FRAME_RATE 50

// Struct to represent the coordinate
struct Coordinate {
    int _x;
    int _y;
    Coordinate(int x, int y) : _x(x), _y(y) {};
};

/**
 *  Class to represent a dynamite fuse light animation sequence
 */
class FuseAnim : public GameAnim
{
    public:
        /** Default constructor */
        FuseAnim(Engine* core, int start_time);
        /** Default destructor */
        ~FuseAnim();

        /// Set the next frame of the animation
        void set_next_frame();
        /// Check if the animation finished or not
        bool isRunning();
        /// Set the current time, to update the light position
        void setTime(int current);
    private:
        // Store the total and current time
        int _time;
        int _cur_time;

        // Reference to the fuse light animated sprite
        AnimSprite* _dyn_fuse;

        // List of raw coordinate of the path
        std::vector<Coordinate> _path;

        /// Creation of the fuse light path
        void createPath();

        /// Get the coordinate in the path based on the current time
        Coordinate getPathXY();
};

#endif // FUSEANIM_H
