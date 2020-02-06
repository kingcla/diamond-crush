#include "Sound.h"

/// //////////////////////////////////////////////////////////////////////// ///
///                             SOUND                                        ///
/// //////////////////////////////////////////////////////////////////////// ///

Sound::Sound(const char* name)
{
    // Load the sound from the system memory
    _sound = Mix_LoadWAV(name);

    // no channel for now
    _channel = -1;

    // If there is any problem print the error
    if (_sound == NULL)
        printf("There was a problem to load %s sound\n%s", name, Mix_GetError());
}

Sound::~Sound()
{
    /// - DO NOTHING - USE DESTROY INSTEAD
}

void Sound::setVolume(int v)
{
    // The sound chunk must exist and the volume should not go more than the max value
    if (_sound == NULL && v < 0 && v > MIX_MAX_VOLUME)
        return;

    // Set the volume
    Mix_VolumeChunk(_sound, v);
}

void Sound::play()
{
    // The sound chunk must exist
    if (_sound == NULL)
        return;

    // Play the sound
    Mix_PlayChannel(-1, _sound, 0);
}

void Sound::pause()
{
    // The sound chunk must exist and is playing on a valid channel
    if (_sound == NULL && _channel < 0)
        return;

    // If is paused resumed
    if (Mix_Paused(_channel) == 1)
        Mix_Resume(_channel);
    else // otherwise pause the sound
        Mix_Pause(_channel);
}

void Sound::stop()
{
    // The sound chunk must exist and is playing on a valid channel
    if (_sound == NULL && _channel < 0)
        return;

    // If the sound is playing stop it
    if (Mix_Playing(_channel) == 1)
        Mix_HaltChannel(_channel);
}

bool Sound::isPlaying()
{
    // The sound chunk must exist and is playing on a valid channel
    if (_sound == NULL && _channel < 0)
        return false;

    // Return if it is playing or not
    return (Mix_Playing(_channel) == 1);
}

void Sound::destroy()
{
    // If the sound chunk is playing stop it
    if (isPlaying())
        stop();

    // Free the memory and destroy the sound
    Mix_FreeChunk(_sound);
}

/// //////////////////////////////////////////////////////////////////////// ///
///                             MUSIC                                        ///
/// //////////////////////////////////////////////////////////////////////// ///

Music::Music(const char* name)
{
    // Load the music from the system memory
    _music = Mix_LoadMUS(name);

    // If there is any problem print the error
    if (_music == NULL)
        printf("There was a problem to load %s music\n%s", name, Mix_GetError());
}

Music::~Music()
{
    /// - DO NOTHING - USE DESTROY INSTEAD
}

void Music::play(bool loop)
{
    if (_music == NULL)
        return;

    if (loop)
        Mix_PlayMusic(_music, -1);
    else
        Mix_PlayMusic(_music, 1);
}

void Music::pause()
{
    // The music must exist
    if (_music == NULL)
        return;

    //If the music is paused
    if( Mix_PausedMusic() == 1 )
        //Resume the music
        Mix_ResumeMusic();
    //If the music is playing
    else
        //Pause the music
        Mix_PauseMusic();
}

void Music::stop(bool fade, int delay_ms)
{
    // The music must exist
    if (_music == NULL)
        return;

    //If the music is playing
    if (Mix_PlayingMusic() == 1)
    {
        // If was set a fade apply it and stop
        if (fade && delay_ms > 0)
            Mix_FadeOutMusic(delay_ms);
        else
            Mix_HaltMusic();
    }
}

void Music::setVolume(int v)
{
    // The music must exist and the volume should not go more than the max value
    if (_music == NULL && v < 0 && v > MIX_MAX_VOLUME)
        return;

    // Set the volume
    Mix_VolumeMusic(v);
}

void Music::destroy()
{
    //If the music is playing stop it
    if (isPlaying())
        stop(false, 0);

    // Free the memory and destroy the sound
    Mix_FreeMusic(_music);
}

bool Music::isPlaying()
{
    // The music must exist
    if (_music == NULL)
        return false;

    // Return if it is playing or not
    return (Mix_PlayingMusic() == 1);
}
