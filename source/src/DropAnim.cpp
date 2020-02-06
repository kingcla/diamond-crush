#include "DropAnim.h"

DropAnim::DropAnim(int start_y, int box_size, Gem* drop_vect[], int length)
{
    // Now the animation is running
    _running = true;

    // Set the coordinate and the size
    _start_y = start_y;
    _size    = box_size;

    // Init the list with the gems in the passed vector
    _vect.reserve(length);
    for(int i = 0; i < length; i++)
    {
        _vect.push_back(drop_vect[i]);
    }
}

DropAnim::~DropAnim()
{
    // Clear the gems list
    _vect.clear();
}

bool DropAnim::isRunning()
{
    // return if finished or not
    return _running;
}

void DropAnim::set_next_frame()
{
    // If is not running exit
    if (!_running) return;

    // cont the number of gems reach the final position
    unsigned int end_count = 0;

    // Cycle on the list
    for (unsigned int i = 0; i < _vect.size(); i++)
    {
        // Take the next gem
        Gem* g = (Gem*)_vect[i];
        // The final y coordinate is the start coordinate per the box size and gem index
        int end_y = _start_y + _size*i;

        // If the actual coordinate is less then the final position
        if (g->y <= end_y)
        {
            // Increment the position
            g->y += DROP_SPEED;

            // If went over bounds fix it
            if (g->y >= end_y)
            {
                g->y = end_y;
                end_count++;
            }
        }
    }

    // If all the gem in the list reach the final position, the animation finished
    if (end_count == _vect.size())
        _running = false;
}

