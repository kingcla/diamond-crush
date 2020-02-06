#ifndef SOUND_H
#define SOUND_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

/**
 *  Class to manage and encapsulate the sounds
 */
class Sound
{
    // Add Engine class as friend so it will be the only one that can create an object of this type
    friend class Engine;

    public:
        /// - DO NOTHING - USE DESTROY INSTEAD
        ~Sound();

        /// Play, pause and stop the sound
        void play();
        void pause();
        void stop();

        /// Change the sound volume
        void setVolume(int v);

        /// Destroy the sound and free memory
        void destroy();

        /// Check if the sound is playing
        bool isPlaying();
    private:
        /// Only friend class can create sound, passing the path of the sound file
        Sound(const char* name);

        /// Reference to the sound
        Mix_Chunk* _sound;

        /// Store the channel where the sound is played
        int _channel;
};

/**
 *  Class to manage and encapsulate the music
 */
class Music
{
    // Add Engine class as friend so it will be the only one that can create an object of this type
    friend class Engine;

    public:
        /// - DO NOTHING - USE DESTROY INSTEAD
        ~Music();

        /// Play the music (with or without looping)
        void play(bool loop);
        /// Pause the music
        void pause();
        /// Stop the music, fading it if necessary
        void stop(bool fade, int delay_ms);

        /// Change the music volume
        void setVolume(int v);

        /// Destroy the music and free memory
        void destroy();

        /// Check if the music is playing
        bool isPlaying();
    private:
        /// Only friend class can create music, passing the path of the music file
        Music(const char* name);

        /// Reference to the music
        Mix_Music* _music;
};

#endif // SOUND_H
