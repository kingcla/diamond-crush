#ifndef SPRITE_H
#define SPRITE_H

// The frequency of how often decrease (or increase) the alpha for fading
#define FADE_FREQUENCY 50
// How much decrease or increase the alpha for fading
#define ALPHA_UNIT     5

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

/**
 *  Class that represent a static image drawn on the screen
 */
class Sprite
{
   // Add Engine class as friend so it will be the only one that can create an object of this type
   friend class Engine;

   public:
        /// - DO NOTHING - USE DESTROY INSTEAD
        ~Sprite();
        /// Draw the image on the scree at the passed coordinate
        void draw(int x, int y);
        /// Destroy the image and free the memory
        void destroy();
        /// Fade in or out the image
        void fade(bool in);
        /// Set the alpha value, used to blend and manage image transparency (0% - complete transparent) (100% - complete opaque)
        void setAlpha(int alpha_x100);
        /// Set the speed for the fade effect
        void setFadeSpeed(unsigned int speed);
   protected:
        /// Protected constructor to make possible to create a Sprite object only to friend class
        // It will need the path of the image and the screen surface
        Sprite(const char* path, SDL_Surface* screen);
        Sprite(const char* path, SDL_Surface* screen, bool alpha);

        /// Load and optimize images, returning the SDL surface
        SDL_Surface* load_image(const char* filename, bool alpha);

        // Reference of the image surface and the screen surface
        SDL_Surface* _surf;
        SDL_Surface* _refScr;
   private:
        // Store the alpha value, the start time for the fade
        Uint8 _alpha;
        int _start;
        // Fade speed
        unsigned int _fadeSpeed;
};

#endif // SPRITE_H
