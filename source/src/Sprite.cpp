#include "Sprite.h"

Sprite::Sprite(const char* path, SDL_Surface* screen)
{
    // Init the alpha and load the image from memory
    _alpha  = SDL_ALPHA_OPAQUE;
    _surf   = load_image(path, false);
    _refScr = screen;

    // get the ticks for the fade effect
    _start  = SDL_GetTicks();
}

Sprite::Sprite(const char* path, SDL_Surface* screen, bool alpha)
{
    // Init the alpha and load the image from memory, with alpha parameter
    _alpha  = SDL_ALPHA_OPAQUE;
    _surf   = load_image(path, alpha);
    _refScr = screen;

    // Init the speed to a default value
    _fadeSpeed = FADE_FREQUENCY;

    // get the ticks for the fade effect
    _start  = SDL_GetTicks();
}

Sprite::~Sprite()
{
    /// DO NOTHING - USE DESTROY INSTEAD
}

SDL_Surface* Sprite::load_image(const char* filename, bool alpha)
{
    // The image that's loaded
    SDL_Surface* loadedImage = NULL;

    // The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    // Load the image using SDL_image
    loadedImage = IMG_Load(filename);

    // If the image loaded
    if( loadedImage != NULL )
    {
        // Create an optimized image

        // Check if it needs to load the alpha info
        if (alpha)
            optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
        else
            optimizedImage = SDL_DisplayFormat( loadedImage );

        // Free the old image
        SDL_FreeSurface(loadedImage);
    }
    else // if something went wrong print a message
        printf("There was a problem to load %s image\n%s", filename, IMG_GetError());

    // Return the optimized image
    return optimizedImage;
}

void Sprite::setFadeSpeed(unsigned int speed)
{
    _fadeSpeed = speed;
}

void Sprite::fade(bool in)
{
    // Check if the alpha value reach the max (fade in effect)
    // or the min (fade out), than exit
    if(in) {if(_alpha == SDL_ALPHA_OPAQUE) return;
    }else   if(_alpha == 0) return;

    // Apply the fade every FREQUENCY value
    if( SDL_GetTicks() - _start > _fadeSpeed )
    {
        // Reassign the time elapsed
        _start = SDL_GetTicks();

        // Decrease the alpha value
        if (in)
        {
            if ((_alpha + ALPHA_UNIT) <= SDL_ALPHA_OPAQUE)
                _alpha += ALPHA_UNIT;
            else
                _alpha = SDL_ALPHA_OPAQUE;
        }
        else // or increase for fading out
        {
            if ((_alpha - ALPHA_UNIT) >= 0)
                _alpha -= ALPHA_UNIT;
            else
                _alpha = 0;
        }
    }
}

void Sprite::draw(int x, int y)
{
    // Screen and image surface must exist
    if (!_refScr || !_surf)
        return;

    // Define the rectangle for the position coordinates
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;

    // Set the alpha to the surface (IT WILL NOT WORK IF THE IMAGE LOADED CONTAIN ALPHA INFORMATION ALREADY)
    SDL_SetAlpha(_surf, SDL_SRCALPHA | SDL_RLEACCEL, _alpha);

    // Blit the surface
    SDL_BlitSurface(_surf, NULL, _refScr, &rect);
}

void Sprite::destroy()
{
    // Free the memory and unload the surface
    SDL_FreeSurface(_surf);
}

void Sprite::setAlpha(int alpha_x100)
{
    // Check out bound values
    if (alpha_x100 < 0 || alpha_x100 > 100)
        return;

    // Convert the alpha from percentage to SDL value
    _alpha = (alpha_x100 * SDL_ALPHA_OPAQUE) / 100;
}
