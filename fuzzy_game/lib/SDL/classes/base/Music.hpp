/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Music
*/

#pragma once

#include <string>

#include <SDL2/SDL_mixer.h>

namespace SDL {
    class Music {
        public:
            Music();
            Music(const std::string path, bool loop);
            ~Music();

            void load(const std::string path, bool loop);
            void unload();

            void setVolume(float volume);
            void setSpeed(float speed);
            
            bool play();
            bool pause();
            bool stop();


            float getVolume() const { return _volume; }
            bool isLooping() const { return _loop; }

        protected:
        private:
            Mix_Music *m_mixMusic;

            bool _loop;
            float _volume;
            bool _initialized;
            bool _playing;
    };
}
