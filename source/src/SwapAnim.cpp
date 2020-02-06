#include "SwapAnim.h"

SwapAnim::SwapAnim(Gem* first_gem, Gem* second_gem, int x1_end, int y1_end, int x2_end, int y2_end)
{
    // Init the gems and the coordinates
    _gem1   = first_gem;
    _gem2   = second_gem;
    _x1_end = x1_end;
    _y1_end = y1_end;
    _x2_end = x2_end;
    _y2_end = y2_end;

    // now the animation is running
    _running = true;
}

SwapAnim::~SwapAnim()
{
    // DO NOTHING
}

bool SwapAnim::isRunning()
{
    // return if finished or not
    return _running;
}

void SwapAnim::set_next_frame()
{
    // If is not running return
    if (!_running) return;

    int x_dir1 = 0, y_dir1 = 0, x_dir2 = 0, y_dir2 = 0;

    // move horizontally
    if(_gem1->x == _x1_end) x_dir1 = 0;
	if(_gem1->x > _x1_end)  x_dir1 = -1;
	if(_gem1->x < _x1_end)  x_dir1 = 1;

    // move vertically
	if(_gem1->y == _y1_end) y_dir1 = 0;
	if(_gem1->y > _y1_end)  y_dir1 = -1;
	if(_gem1->y < _y1_end)  y_dir1 = 1;

    // Set the direction
	x_dir2 = x_dir1 * -1;
	y_dir2 = y_dir1 * -1;

    // Change the gems position
	_gem1->x = _gem1->x + 10 * x_dir1;
	_gem1->y = _gem1->y + 10 * y_dir1;

	_gem2->x = _gem2->x + 10 * x_dir2;
	_gem2->y = _gem2->y + 10 * y_dir2;

    // Fix the position if the gems went over the bounds
	if((x_dir1 > 0 && _gem1->x > _x1_end) || (x_dir1 < 0 && _gem1->x < _x1_end))
        _gem1->x = _x1_end;

	if((y_dir1 > 0 && _gem1->y > _y1_end) || (y_dir1 < 0 && _gem1->y < _y1_end))
        _gem1->y = _y1_end;

	if((x_dir2 > 0 && _gem2->x > _x2_end) || (x_dir2 < 0 && _gem2->x < _x2_end))
        _gem2->x = _x2_end;

	if((y_dir2 > 0 && _gem2->y > _y2_end) || (y_dir2 < 0 && _gem2->y < _y2_end))
        _gem2->y = _y2_end;

    // If the gems reach the final position the animation is finished
    if(_gem1->x == _x1_end && _gem1->y == _y1_end)
        _running = false;
}
