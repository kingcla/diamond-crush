#include "AnimSprite.h"

AnimSprite::AnimSprite(const char* path, SDL_Surface* screen, int width, int height) :
    Sprite(path, screen, true) // call the sprite constructor with alpha loading true
{
    // Init the frame related variables
    CurrentFrame    = 0;
    MaxFrames       = 0;
    // Frames will incremented by one
    FrameInc        = 1;
    FrameRate       = 100; // default frame rate
    OldTime         = 0;

    // Store the size of the sprite
    _Spr_W          = width;
    _Spr_H          = height;
}

void AnimSprite::OnAnimate()
{
    // Not update the frame if the time is under the frame rate
    if(OldTime + FrameRate > SDL_GetTicks()) {
        return;
    }

    // Set the new time
    OldTime = SDL_GetTicks();

    // and increment the frame
    CurrentFrame += FrameInc;

    // If the current frame is over the max, reset it
    if(CurrentFrame >= MaxFrames)
        CurrentFrame = 0;
}

void AnimSprite::SetFrameRate(int Rate)
{
    // Set the frame rate
    FrameRate = Rate;
}

void AnimSprite::SetCurrentFrame(int Frame)
{
    // If the frame is over the bound don't change it
    if(Frame < 0 || Frame >= MaxFrames) return;

    CurrentFrame = Frame;
}

int AnimSprite::GetCurrentFrame()
{
    // Return the frame drawn in the moment
    return CurrentFrame;
}

void AnimSprite::draw(int x, int y)
{
    // If the image surface or screen surface are null exit
    if(_refScr == NULL || _surf == NULL)
        return;

    // Define the rectangle for the position coordinates
    SDL_Rect DestR;
    DestR.x = x;
    DestR.y = y;

    // Tile the sprite from the image sheet passed in the constructor
    SDL_Rect SrcR;
    SrcR.x = 0;
    SrcR.y = GetCurrentFrame() * _Spr_H; // using the size of the sprite
    SrcR.w = _Spr_W;
    SrcR.h = _Spr_H;

    // Draw the current sprite frame on the screen
    SDL_BlitSurface(_surf, &SrcR, _refScr, &DestR);
}
