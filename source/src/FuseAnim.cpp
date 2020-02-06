#include "FuseAnim.h"

FuseAnim::FuseAnim(Engine* core, int start_time)
{
    // Init the path of the fuse light
    createPath();

    // Now the animation is running
    _running = true;

    // Set the total time and the current time by the time passed
    _time     = start_time;
    _cur_time = start_time;

    // Load the fuse light sprite
    _dyn_fuse = core->loadAnim("resources/FuseAnim/Fuse.png", SPRITE_SIZE, FRAME_RATE);
}

FuseAnim::~FuseAnim()
{
    // Clear the list of coordinates
    _path.clear();

    // Destroy the fuse light sprite
    _dyn_fuse->destroy();
}

void FuseAnim::set_next_frame()
{
    // Get the next coordinate based on the current time
    Coordinate c = getPathXY();

    // animate the fuse light
    _dyn_fuse->OnAnimate();

    // Draw the light in the next coordinate on the path, and center the sprite
    _dyn_fuse->draw(c._x - (SPRITE_SIZE / 2), c._y - (SPRITE_SIZE / 2));
}

void FuseAnim::setTime(int current)
{
    // Set the current time
    _cur_time = current;
}

bool FuseAnim::isRunning()
{
    // return if finished or not
    return _running;
}

Coordinate FuseAnim::getPathXY()
{
    unsigned int index = 0;
    // If the current time is still running
    if (_cur_time > 0 && _cur_time <= _time)
        // the index is calculated based on the current time and the number of coordinates in the path
         index = abs((_cur_time * _path.size())/_time - _path.size());
    else // the animation is finished
        _running = false;

    // return the coordinate in the path
    return _path[index];
}

void FuseAnim::createPath()
{
    // Init the path with raw coordinates
    _path.push_back(Coordinate(260, 553));
    _path.push_back(Coordinate(259, 550));
    _path.push_back(Coordinate(254, 548));
    _path.push_back(Coordinate(252, 541));
    _path.push_back(Coordinate(251, 537));
    _path.push_back(Coordinate(251, 531));
    _path.push_back(Coordinate(253, 525));
    _path.push_back(Coordinate(254, 519));
    _path.push_back(Coordinate(251, 514));
    _path.push_back(Coordinate(247, 511));
    _path.push_back(Coordinate(242, 510));
    _path.push_back(Coordinate(235, 509));
    _path.push_back(Coordinate(227, 508));
    _path.push_back(Coordinate(220, 508));
    _path.push_back(Coordinate(213, 503));
    _path.push_back(Coordinate(212, 493));
    _path.push_back(Coordinate(212, 483));
    _path.push_back(Coordinate(212, 473));
    _path.push_back(Coordinate(212, 463));
    _path.push_back(Coordinate(212, 453));
    _path.push_back(Coordinate(210, 443));
    _path.push_back(Coordinate(210, 433));
    _path.push_back(Coordinate(210, 423));
    _path.push_back(Coordinate(210, 413));
    _path.push_back(Coordinate(208, 403));
    _path.push_back(Coordinate(208, 393));
    _path.push_back(Coordinate(208, 383));
    _path.push_back(Coordinate(206, 370));
    _path.push_back(Coordinate(199, 372));
    _path.push_back(Coordinate(189, 372));
    _path.push_back(Coordinate(182, 372));
}
