#ifndef GAMEANIM_H
#define GAMEANIM_H

class GameAnim
{
    public:
        /** Default destructor */
        virtual ~GameAnim(){};

        /// Set the next frame of the animation
        virtual void set_next_frame() = 0;

        /// Check if the animation finished or not
        virtual bool isRunning() = 0;
    protected:
        // Flag to set when the animation is finished
        bool _running;
};

#endif // GAMEANIM_H
