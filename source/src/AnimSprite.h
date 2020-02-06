#ifndef ANIMSPRITE_H
#define ANIMSPRITE_H

#include "Sprite.h"

/**
 *  Class that represent an animated image drawn on the screen
 */
class AnimSprite : public Sprite
{
    // Add Engine class as friend so it will be the only one that can create an object of this type
    friend class Engine;

    private:
        // Keep the current frame value, the frame increment and the time stored each frame rendering values
        int  CurrentFrame;
        int  FrameInc;
        long OldTime;
        // Store the size of the single sprite
        Uint16 _Spr_W;
        Uint16 _Spr_H;
        // Store the frame rate in Milliseconds (the speed of the animation)
        Uint32 FrameRate;
    public:
        // The user can set and get the maximum speed rate for the animation
        int  MaxFrames;
        /// Set the speed for the animation (in millisecond)
        void SetFrameRate(int Rate);
        /// Set which frame to show from now on (interval between 0 and the number of sprites in the sheet)
        void SetCurrentFrame(int Frame);
        /// Get the current frame index
        int GetCurrentFrame();
        /// To call every tick for let the class pass to the next frame
        void OnAnimate();
        /// Draw the sprite indicated by the current frame
        void draw(int x, int y);
    protected:
        /// Protected constructor to make possible to create a animated sprite object only to friend class
        // The constructor needs the path of the image file and the screen surface,
        // moreover it needs the size of the single sprite in the sheet
        AnimSprite(const char* path, SDL_Surface* screen, int width, int height);
};

#endif // ANIMSPRITE_H
